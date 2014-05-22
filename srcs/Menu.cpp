/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Mon May 19 18:23:32 2014 ribeaud antonin
*/

# include "Generator.hpp"
# include "Menu.hpp"
# include "CubeAnim.hpp"
# include "Preview.hpp"

Menu::Menu(Camera *camera, Loader *loader) : _camera(camera)
{
  _camera->setPlayer(1);
  _loader = loader;
  _shader = _camera->getShader();
  _clock = _camera->getClock();
  _text = new Text(_camera, _loader);
  _players = 1;
  _isSelect = 0;
  _isLaunch = false;
  _stopIntro = false;
  _event = NULL;
  _cubeanim = new CubeAnim(camera, loader);
  _preview = new Preview(camera, loader);
  _timer = 0;
  _back = -1;
  _stepM = HOME;
  _pos = 0;
  _scoreToAdd.assign("");
  _func[HOME] = &Menu::home;
  _func[STEP1] = &Menu::step1;
  _func[STEP11] = &Menu::step11;
  _func[STEP12] = &Menu::step12;
  _func[SCORE] = &Menu::score;
  _func[LOADM] = &Menu::load;
  _func[LOADG] = &Menu::loadGame;
  _step[0] = &Menu::select0;
  _step[1] = &Menu::select1;
  _step[2] = &Menu::select2;
  _step[3] = &Menu::select3;
  _step[4] = &Menu::select4;
  _addScore = false;
  _previewMode = false;
  _exit = false;
  home();
}

Menu::~Menu()
{
  delete _text;
  delete _background;
  delete _cubeanim;
  delete _preview;
}

bool  Menu::drawBackground()
{
  _background = new Background(40, 40, 10.0f);
  if (_background->initialize() == false)
    return (false);
  _background->translate(glm::vec3(30, 0, 40));
  return (true);
}

bool	Menu::initialize()
{
  return ((!_cubeanim->initIntro()) || (!drawBackground()) || (!initLogo()) ? false : true);
}

bool    Menu::update()
{
  _camera->setPlayer(1);
  _clock = _camera->getClock();
  _input = _camera->getInput();
  _timer += _clock.getElapsed();
  if (_exit || _input.getInput(SDL_QUIT) || _isLaunch)
    return (false);
  if (_event == NULL && _stopIntro == true)
    _event = new AInput(_input, MENU);
  if (_stopIntro == true)
  {
    _event->setInput(_input);
    _background->update(_clock, _input);
    event(_step1);
  }
  if (_previewMode && !(_preview->update(_clock, _input)))
    _previewMode = false;
  else if (_previewMode == false)
    _cubeanim->update();
  return (true);
}

void    Menu::draw()
{
  type LastType = BLOCKD;

  if (_input.getKey(SDLK_SPACE))
    {
      _cubeanim->stopIntro(true);
      _stopIntro = true;
    }
  _cubeanim->rotate();
  if (_previewMode == false)
  {
    _loader->bindTexture(LastType);
    _cubeanim->draw(_shader, LastType);
  }
  if (_cubeanim->getStatus())
    _background->draw(_shader, _clock);
  if (_stopIntro)
    _text->draw(_step1, _isSelect);
  if (_previewMode == true)
    _preview->draw(_shader, _clock);
  drawLogo();
  _camera->flushContext();
}

void    Menu::manageEventInput()
{
  if (_stepM == STEP11)
  {
    switch (_isSelect)
    {
      case 0:
        getInputNb(_sizeMap, 5, 4, 5000, 0);
        break;
      case 1:
        if (_stepM == STEP11)
          getInputNb(_nbPlayer, 6, 1, 2, 1);
        break;
      case 2:
        if (_stepM == STEP11)
          getInputNb(_nbBots, 7, 2, convToInt(_sizeMap) / 10, 0);
        break;
    }
  }
  if (_stepM == STEP12 && _isSelect == 0)
    getInputNb(_sizeMap, 5, 4, 30, 0);
  if (_stepM == LOADG)
    switch (_isSelect)
    {
      case 0:
          getInputNb(_nbPlayer, 6, 1, 2, 1);
        break;
      case 1:
          getInputNb(_nbBots, 7, 2, 10/*convToInt(_sizeMap) / 10*/, 0);
        break;
    }

}

void    Menu::manageEventInputScore(key &k)
{
  if (_stepM == SCORE)
  {
    const char *str = NULL;
    char c;

    if (_scoreToAdd.compare(""))
    {
      str = _scoreToAdd.c_str();
      c = (str[_pos] != '\0') ? (str[_pos]) : 65;
    }
    else
      c = 65;
    switch (k)
    {
      case MUP:
      {
        _timer = 0;
        c--;
        (c == 64) ? (c = 90) : 0;
        getInputPseudo(c);
        break;
      }
      case MDOWN:
      {
        _timer = 0;
        c++;
        (c == 91) ? (c = 65) : 0;
        getInputPseudo(c);
        break; 
      }
      case MRIGHT:
      {
        _timer = 0;
        _pos++;
        if (_pos >= 6)
        {
          _addScore = false;
          saveInFile();
        }
        break;
      }
      case MRETURN:
        if (_pos > 2)
        {
          _pos = 7;
          _addScore = false;
          saveInFile();          
        }
        break;
      default:
        break;
    }
  }
}

void    Menu::saveInFile()
{
  std::ofstream file("score", std::ios::app);
  std::string   s("");

  if (file.is_open())
  {
    convToString(s, _newScore);
    file << _scoreToAdd << "\t" << s << "\n";
    file.close();
  }
}

void    Menu::getInputPseudo(char c)
{
  _scoreToAdd = _scoreToAdd.substr(0, _pos);
  _scoreToAdd += c;
  (this->*_func[_stepM])();
}

void    Menu::getInputNb(std::string &s, int n, size_t size, int max, int min)
{
  key   k;

  if ((k = _event->getInput()) != NONE && 
      k != MBACKSPACE && k != MUP && k != MDOWN &&
        k != MLEFT && k != MRIGHT && s.size() < size)
  {
    _timer = 0;
    s += (((int)(k)) - 23) + 48;
    if (convToInt(s) > max || convToInt(s) < min)
      s.assign(s.substr(0, s.length() - 1));
    (this->*_func[_stepM])();
  }
  else if (k == MBACKSPACE)
  {
    _timer = 0;
    s.assign(s.substr(0, s.length() - 1));
    (this->*_func[_stepM])();
  }
}

void    Menu::startGenerator()
{
    Generator *gen = new Generator(_camera, _loader, convToInt(_sizeMap));

    _isSelect = 0;
    if (gen->initialize() == false)
      std::cout << "Error on initializing the map Generator" << std::endl;
    else
    {
      while (gen->update() == true)
        gen->draw();
      delete gen;
    }
}

void    Menu::startPreview()
{
  (_preview->initialize()) ? (_previewMode = true) : std::cout << "Failed to initialize preview mode" << std::endl;
}

void    Menu::chooseStep()
{
  bool  play = true;

  if (_isSelect >= 0 && _isSelect <= 4)
    (this->*_step[_isSelect])();
  else
    play = false;
  if (play == true)
  {
    (this->*_func[_stepM])();
    _oldStep = _stepM;    
  }
}

void    Menu::event(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &s)
{
  key   k;

  k = _event->getInput();
  if (_timer > DELAY)
  {
    switch (k)
    {
      case MUP:
        if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
        {
          _isSelect--;
          (_isSelect == - 1) ? (_isSelect = _max) : 0;
          _timer = 0;
        }
        else
          manageEventInputScore(k);
        break;
      case MDOWN:
        if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
        {
          _isSelect++;
          (_isSelect == _max + 1) ? (_isSelect = 0) : 0;
          _timer = 0;
        }
        else
          manageEventInputScore(k);
        break;
      case MRETURN:
      {
        if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
        {
          _timer = 0;
          chooseStep();          
        }
        else
          manageEventInputScore(k);
        break;
      }
      default:
        if (_pos < 6 && _stepM == SCORE)
          manageEventInputScore(k);
        else
          manageEventInput();
        break;
    }
  }
}

void    Menu::reset(const std::map<int, Player*> &p)
{
  int   max;
  int   i;

  _isLaunch = false;
  _isSelect = 0;
  max = 0;
  _pos = 0;
  _scoreToAdd.assign("");
  (p.find(1)->second->getScore() > max) ? (max = p.find(1)->second->getScore()) : 0;
  (p.find(2) != p.end() && p.find(2)->second->getScore() > max) ? (max = p.find(2)->second->getScore()) : 0; 
  _addScore = true;
  for (std::map<int, Player*>::const_iterator it = p.begin(); it != p.end(); ++it)
    if (((*it).second->getScore() > max && (*it).second->getId() != 1 && (*it).second->getId() != 2))
      i++;
  (i > 4) ? (_addScore = false) : 0; 
  if (_addScore == true)
  {
    getScore();
    _stepM = SCORE;
    _newScore = max;
  }
  (this->*_func[_stepM])();
}

bool    Menu::launch() const
{
  return (_isLaunch);
}

bool    Menu::atLeastPlayer() const
{
  return (((convToInt(_nbPlayer) + convToInt(_nbBots)) >= 2 && convToInt(_nbBots) <= convToInt(_sizeMap) / 10) ? true : false);
}

void    Menu::home()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "LOCAL", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "ONLINE", true);
  _text->addText(_step1, 2, std::make_pair(15, 460), "SCORE", true);
  _text->addText(_step1, 3, std::make_pair(15, 540), "OPTION", true);
  _text->addText(_step1, 4, std::make_pair(15, 620), "EXIT", true);
  _isSelect = 0;
  _max = 4;
}

void    Menu::step1()
{
  _sizeMap.assign("30");
  _nbPlayer.assign("1");
  _nbBots.assign("1");
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "NEW GAME", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "LOAD GAME", true);
  _text->addText(_step1, 2, std::make_pair(15, 460), "MAP BUILDER", true);
  _text->addText(_step1, 3, std::make_pair(15, 540), "BACK", true);
  _max = 3;
}

void    Menu::step11()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "MAP SIZE", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "NB PLAYER", true);
  _text->addText(_step1, 2, std::make_pair(15, 460), "BOTS", true);
  _text->addText(_step1, 3, std::make_pair(15, 540), "GO", true);
  _text->addText(_step1, 4, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 5, std::make_pair(700, 300), _sizeMap.c_str(), false);
  _text->addText(_step1, 6, std::make_pair(700, 380), _nbPlayer.c_str(), false);
  _text->addText(_step1, 7, std::make_pair(700, 460), _nbBots.c_str(), false);
  _max = 4;
}

void    Menu::step12()
{
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "MAP SIZE", true);
  _text->addText(_step1, 1, std::make_pair(15, 540), "GO", true);
  _text->addText(_step1, 2, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 5, std::make_pair(700, 300), _sizeMap.c_str(), false);
  _max = 2;
}

void    Menu::loadGame()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 380), "NB PLAYER", true);
  _text->addText(_step1, 1, std::make_pair(15, 460), "BOTS", true);
  _text->addText(_step1, 2, std::make_pair(15, 540), "GO", true);
  _text->addText(_step1, 3, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 4, std::make_pair(700, 380), _nbPlayer.c_str(), false);
  _text->addText(_step1, 5, std::make_pair(700, 460), _nbBots.c_str(), false);
  _max = 3;
}

void    Menu::score()
{
  int   y;
  int   id;
  int   myints[_score.size()];
  int   i;
  std::string s;
  typedef std::vector<int>::iterator iter_type;
  int     max;
  int     add;

  max = 5;
  y = 380;
  id = 1;
  add = 0;
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "BACK", true);
  _max = 0;
  (_addScore) ? (i = 1, myints[0] = _newScore) : (i = 0);
  if (_score.size() == 0 && _addScore == false)
  {
    _text->addText(_step1, 1, std::make_pair(600, 380), "NOT YET SCORE", true);
    return;    
  }
  for (std::map<int, std::string>::iterator it = _score.begin(); it != _score.end(); ++it)
  {
    myints[i] = (*it).first;
    i++;
  }
  (_addScore) ? (add = 1) : 0;
  std::vector<int> myvector (myints, myints + _score.size() + add);
  std::sort (myvector.begin(), myvector.end());
  iter_type from (myvector.begin());
  iter_type until (myvector.end());
  std::reverse_iterator<iter_type> rev_until (from);
  std::reverse_iterator<iter_type> rev_from (until);
  while (rev_from != rev_until && max > 0)
  {
    if (_score.find((*rev_from)) != _score.end() || (*rev_from) == _newScore)
    {
      convToString(s, (*rev_from));
      _text->addText(_step1, id, std::make_pair(700, y), s, false);
      id++;
      if (_score.find((*rev_from)) != _score.end())
        _text->addText(_step1, id, std::make_pair(15, y), _score.find((*rev_from))->second, true);
      else
        _text->addText(_step1, id, std::make_pair(15, y), _scoreToAdd, true);
      y += 80;
      id++;
      rev_from++;
      max--;
    }
  }
}

void    Menu::load()
{
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 840), "GO", true);
  _text->addText(_step1, 1, std::make_pair(15, 920), "BACK", true);
  startPreview();
  _max = 1;
}

bool    Menu::initLogo()
{
  if (!_texture.load("./ressources/assets/logo.tga"))
    return (false);
  _camera->setMode();
  glDisable(GL_DEPTH_TEST);
  _geometry.pushVertex(glm::vec3(0, 0, 0));
  _geometry.pushVertex(glm::vec3((float)_texture.getWidth(), 0, 0));
  _geometry.pushVertex(glm::vec3((float)_texture.getWidth(), (float)_texture.getHeight(), 0));
  _geometry.pushVertex(glm::vec3(0, (float)_texture.getHeight(), 0));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.build();
  glEnable(GL_DEPTH_TEST);
  _camera->setMode();
  return (true);
}

void  Menu::drawLogo()
{
  glm::mat4 transformation;

  _camera->setMode();
  _texture.bind();
  transformation = glm::translate(glm::mat4(1), glm::vec3(1300 / 2, 15, 0));
  _geometry.draw(_shader, transformation, GL_QUADS);
  _camera->setMode();
}

int   Menu::getMapSize() const
{
  return (convToInt(_sizeMap));
}

int   Menu::getNbPlayer() const
{
  return (convToInt(_nbPlayer));
}

int   Menu::getNbBots() const
{
  return (convToInt(_nbBots));
}

int  Menu::convToInt(const std::string &s) const
{
  std::istringstream iss(s);
  int        val = 0;

  iss >> val;
  return (val);
}

void  Menu::convToString(std::string &s, int i) const
{
  std::stringstream ss;

  ss << i;
  s = ss.str();
}

Map   *Menu::getMap() const
{
  return (_map);
}

void  Menu::setIsSelect()
{
  _isSelect = 0;
}

void  Menu::getScore()
{
  std::ifstream file("score", std::ios::in);
  std::string   res;
  std::size_t   found;

  if (file.is_open())
  { 
    while (!file.eof())
    {
      std::getline(file, res, '\n');
      found = res.find('\t');
      if (found != std::string::npos)
        _score[convToInt(res.substr(found, res.length()))] = res.substr(0, found);
      res.clear();
    }
    file.close();
  }
}

void  Menu::select0()
{
  (_stepM == HOME) ? (_stepM = STEP1) : (_stepM == STEP1) ? (_isSelect = 0, _stepM = STEP11) 
  : (_stepM == SCORE) ? (_stepM = HOME) : (_stepM == LOADM) ? (_previewMode = false ,_stepM = LOADG) : 0;
}

void  Menu::select1()
{
  stepM k;

  k = STEP1;
  (_stepM == STEP1) ? (_stepM = LOADM) : (_stepM == STEP12) ? (_stepM = STEP1) : (_stepM == LOADM) ? (_previewMode = false, k = LOADM,_stepM = STEP1) : 0;
  if (k != LOADM && _stepM == STEP1)
   startGenerator();
 std::cout << "-------> " << _stepM << std::endl;
}

void  Menu::select2()
{
  (_stepM == STEP1) ? (_stepM = STEP12) : (_stepM == STEP12) ? (_stepM = STEP1, _isSelect = 0) 
  : (_stepM == HOME) ?  (_isSelect = 0, _stepM = SCORE) : 0;
  if (_stepM == SCORE)
     getScore();
}

void  Menu::select3()
{
  bool isAnime(false);

  (_stepM == STEP1) ? (_stepM = HOME) : (_stepM == STEP11 && (convToInt(_sizeMap) >= 10 && atLeastPlayer())) 
  ? (_map = new Map(getMapSize()), _isLaunch = true, isAnime = true) : (_stepM == LOADG) ? (_stepM = LOADM) : 0;
  if (isAnime)
    _cubeanim->changeVolum(0.4f);
}

void  Menu::select4()
{
  (_stepM == STEP11) ? (_stepM = STEP1) : (_stepM == HOME) ? (_exit = true) : 0;
}
