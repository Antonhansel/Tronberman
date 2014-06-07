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

Menu::Menu(Camera *camera, Loader *loader, ParticleEngine *engine) : _camera(camera)
{
  _th = NULL;
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
  _func[LOADPREVIOUS] = &Menu::loadPrevious;
  _func[ONLINE] = &Menu::online;
  _func[SERVER] = &Menu::server;
  _func[CLIENT] = &Menu::client;
  _func[OPTION] = &Menu::option;
  _func[WAITSERVER] = &Menu::waitServer;
  _func[WAITCLIENT] = &Menu::waitClient;
  _step[0] = &Menu::select0;
  _step[1] = &Menu::select1;
  _step[2] = &Menu::select2;
  _step[3] = &Menu::select3;
  _step[4] = &Menu::select4;
  _addScore = false;
  _previewMode = false;
  _exit = false;
  _isSave = false;
  _isFx = true;
  _ipAddr.assign("127.0.0.1");
  _engine = engine;
  _vol = 100;
  _nbPort.assign("6666");
  _volume.assign("100");
  _fx.assign("ON");
  _network = NULL;
  _err = "";
  home();
}

Menu::~Menu()
{
  _text->deleteAllText(_step1);
  if (_network != NULL)
    delete _network;
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
  (_event == NULL && _stopIntro == true) ? (_event = new AInput(_input, MENU)) : 0;
  if (_stopIntro == true)
  {
    _event->setInput(_input);
    _background->update(_clock, _input);
    event(_step1);
  }
  if (_previewMode && !(_preview->update(_clock, _input, _isSave)))
    _previewMode = false;
  else if (_previewMode == false)
    _cubeanim->update();
  _cubeanim->changeVolum((float)_vol / 100.0);
  if (_network != NULL)
    _network->newPlayers();

  if (_stepM == WAITCLIENT && _network != NULL)
  {
    if ((_isLaunch = _network->isGameStarted()))
    {
      _map = new Map(30, false, _engine);
      _isSave = false;
    }
  }
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
        getInputNb(_sizeMap, 4, 5000, 0);
        break;
      case 1:
        if (_stepM == STEP11)
          getInputNb(_nbPlayer, 1, 2, 1);
        break;
      case 2:
        if (_stepM == STEP11)
          getInputNb(_nbBots, 2, convToInt(_sizeMap) / 10, 0);
        break;
    }
  }
  if (_stepM == STEP12 && _isSelect == 0)
    getInputNb(_sizeMap, 4, 30, 0);
  if (_stepM == LOADG)
  {
    switch (_isSelect)
    {
      case 0:
          getInputNb(_nbPlayer, 1, 2, 1);
        break;
      case 1:
          getInputNb(_nbBots, 2, _map->getSize() / 10, 0);
        break;
    }
  }
  if ((_stepM == SERVER && _isSelect == 0) || (_stepM == CLIENT && _isSelect == 1))
    getInputNb(_nbPort, 5, 65000, 1);
  if (_stepM == CLIENT && _isSelect == 0)
    getInputAddr(_ipAddr, 15);
  changeOption();
  getFxState();
  changeMusic();
}

void    Menu::changeMusic()
{
  std::vector<key>  ret;

  ret = _event->getInput();
  if (_stepM == OPTION && _isSelect == 2)
  {
    std::cout << "IN---->"  << std::endl;
    if (AInput::getKey(ret, MRIGHT))
    {
      _cubeanim->changeMusic(1);
      _timer = 0;
    }
    else if (AInput::getKey(ret, MLEFT))
    {
      _cubeanim->changeMusic(-1);
      _timer = 0;
    }
  }
}

void    Menu::changeOption()
{
  std::stringstream ss;
  std::vector<key>  ret;

  ret = _event->getInput();
  if (_stepM == OPTION && _isSelect == 0)
  {
    if (AInput::getKey(ret, MRIGHT) && _vol < 100)
    {
      _timer = 0;
      _vol += 10;
      ss << _vol;
      _volume = ss.str();
      (this->*_func[_stepM])();
    }
    else if (AInput::getKey(ret, MLEFT) && _vol > 0)
    {
      _timer = 0;
      _vol -= 10;
      ss << _vol;
      _volume = (_vol != 0) ? ss.str() : "MUTE";
      (this->*_func[_stepM])();
    }
  }
}

void    Menu::getInputAddr(std::string &s, size_t size)
{
  std::vector<key>  ret;

  ret = _event->getInput();
  if (!AInput::getKey(ret, NONE) &&
    !AInput::getKey(ret, MBACKSPACE) && !AInput::getKey(ret, MUP) &&
    !AInput::getKey(ret, MDOWN) && !AInput::getKey(ret, MLEFT) &&
    !AInput::getKey(ret, MRIGHT) && s.size() < size)
  {
    _timer = 0;
    if (ret[0] != MDOT)
      s += (((int)(ret[0])) - 23) + 48;
    else
      s += '.';
    (this->*_func[_stepM])();
  }
  else if (AInput::getKey(ret, MBACKSPACE))
  {
    _timer = 0;
    s.assign(s.substr(0, s.length() - 1));
    (this->*_func[_stepM])();
  }
}

void    Menu::getFxState()
{
  std::vector<key>  ret;

  ret = _event->getInput();
  if (_stepM == OPTION && _isSelect == 1
    && (AInput::getKey(ret, MRIGHT) || AInput::getKey(ret, MLEFT)))
  {
    _timer = 0;
    _isFx = !_isFx;
    _fx = (_isFx) ? "ON" : "OFF";
    (this->*_func[_stepM])();
  }
}


void    Menu::manageEventInputScore(key &k)
{
  if (_stepM == SCORE && _addScore)
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
        else
          getInputPseudo(65);
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
  std::ofstream file(".score", std::ios::app);
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

void    Menu::getInputNb(std::string &s, size_t size, int max, int min)
{
  std::vector<key>  ret;

  ret = _event->getInput();
  if (!AInput::getKey(ret, NONE) &&
    !AInput::getKey(ret, MBACKSPACE) && !AInput::getKey(ret, MUP) &&
    !AInput::getKey(ret, MDOWN) && !AInput::getKey(ret, MLEFT) &&
    !AInput::getKey(ret, MRIGHT) && s.size() < size)
  {
    _timer = 0;
    s += (((int)(ret[0])) - 23) + 48;
    if (convToInt(s) > max || convToInt(s) < min)
      s.assign(s.substr(0, s.length() - 1));
    (this->*_func[_stepM])();
  }
  else if (AInput::getKey(ret, MBACKSPACE))
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

void    Menu::chooseStep()
{
  bool  play = true;

  if (_isSelect >= 0 && _isSelect <= 4)
    (this->*_step[_isSelect])();
  else
    play = false;
  if (play == true && _isLaunch != true)
  {
    (this->*_func[_stepM])();
    _oldStep = _stepM;
  }
}

void    Menu::event(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &s)
{
  std::vector<key>   k;

  k = _event->getInput();
  if (_timer > DELAY)
  {
    for (std::vector<key>::iterator it = k.begin(); it != k.end(); ++it)
    {
      switch ((*it))
      {
        case MUP:
         if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
         {
           _isSelect--;
           (_isSelect == - 1) ? (_isSelect = _max) : 0;
           _timer = 0;
         }
         else
           manageEventInputScore((*it));
         break;
        case MDOWN:
          if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
          {
           _isSelect++;
            (_isSelect == _max + 1) ? (_isSelect = 0) : 0;
            _timer = 0;
          }
          else
            manageEventInputScore((*it));
          break;
        case MRETURN:
        {
          if ((_pos >= 6 && _stepM == SCORE && _addScore == true) || _addScore == false)
          {
           _timer = 0;
            chooseStep();
          }
          else
            manageEventInputScore((*it));
          break;
        }
        default:
          if (_pos < 6 && _stepM == SCORE)
           manageEventInputScore((*it));
          else
            manageEventInput();
          break;
      }
    }
  }
}

void    Menu::reset(const std::vector<Player*> &p)
{
  int   max;
  int   i = 0;

  if (_network != NULL)
  {
    delete _network;
    _network = NULL;
  }
  _isLaunch = false;
  _isSelect = 0;
  max = 0;
  _pos = 0;
  _scoreToAdd.assign("");
  (p[0]->getScore() > max) ? (max = p[0]->getScore()) : 0;
  (2 < p.size() && p[1] != NULL && p[1]->getScore() > max) ? (max = p[1]->getScore()) : 0;
  _addScore = true;
  for (std::vector<Player*>::const_iterator it = p.begin(); it != p.end(); ++it)
    if ((*it) && ((*it)->getScore() > max && (*it)->getId() != 1 && (*it)->getId() != 2))
      i++;
  if (i > 4)
    _addScore = false;
  getScore();
  _stepM = SCORE;
  _newScore = max;
  _previewMode = false;
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
  _text->addText(_step1, 2, std::make_pair(15, 460), "LOAD CUSTOM MAP", true);
  _text->addText(_step1, 3, std::make_pair(15, 540), "MAP BUILDER", true);
  _text->addText(_step1, 4, std::make_pair(15, 620), "BACK", true);
  _max = 4;
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

void    Menu::online()
{
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "CREATE", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "JOIN", true);
  _text->addText(_step1, 2, std::make_pair(15, 620), "BACK", true);
  _max = 2;
}

void    Menu::server()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "PORT", true);
  _text->addText(_step1, 1, std::make_pair(15, 540), "GO", true);
  _text->addText(_step1, 2, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 3, std::make_pair(700, 300), _nbPort.c_str(), false);
  _text->addText(_step1, 4, std::make_pair(15, 700), _err.c_str(), false);
  _max = 2;
}

void    Menu::client()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "ADDRESS", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "PORT", true);
  _text->addText(_step1, 2, std::make_pair(15, 540), "GO", true);
  _text->addText(_step1, 3, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 4, std::make_pair(700, 300), _ipAddr.c_str(), false);
  _text->addText(_step1, 5, std::make_pair(700, 380), _nbPort.c_str(), false);
  _text->addText(_step1, 4, std::make_pair(15, 700), _err.c_str(), false);
  _max = 3;
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

void    Menu::option()
{
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 300), "MUSIC", true);
  _text->addText(_step1, 1, std::make_pair(15, 380), "FX", true);
  _text->addText(_step1, 2, std::make_pair(15, 460), "CHANGE MUSIC", true);
  _text->addText(_step1, 3, std::make_pair(15, 620), "BACK", true);
  _text->addText(_step1, 4, std::make_pair(700, 300), _volume.c_str(), true);
  _text->addText(_step1, 5, std::make_pair(700, 380), _fx.c_str(), true);
  _max = 3;
}

void  Menu::waitClient()
{
    _isSelect = 1;
    _text->deleteAllText(_step1);
    _text->addText(_step1, 0, std::make_pair(15, 300), "WAITING THE SERVER...", true);
    _max = 0;
}

void   Menu::waitServer()
{
    _isSelect = 0;
    _text->deleteAllText(_step1);
    _text->addText(_step1, 0, std::make_pair(15, 300), "WAITING THE CLIENT...", true);
    _text->addText(_step1, 1, std::make_pair(15, 540), "GO", true);
    _max = 1;
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
  bool    d = true;

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
      {
         d = false;
        _text->addText(_step1, id, std::make_pair(15, y), _scoreToAdd, true);
       }
      y += 80;
      id++;
      rev_from++;
      max--;
    }
  }
  if (d == true)
    _addScore = false;
}

void    Menu::load()
{
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(600, 300), "LOADING....", true);
  if (_th == NULL)
  {
    PtrFonct pf = &getMapp;
    _th = new Thread();
    if (_th->createThread(pf, ((void*)(_preview))))
    {
      while (_preview->getState())
      {
        update();
        draw();
      }
      if (_th->joinThread())
      {
        delete _th;
        _th = NULL;
      }
      else
        std::cout << "ERROR ON JOIN THREAD\n";
    }
    else
        std::cout << "ERROR ON CREATE THREAD\n";
  }
  _preview->setState(true);
  _previewMode = _preview->getResult();
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 840), "GO", true);
  _text->addText(_step1, 1, std::make_pair(15, 920), "BACK", true);
  _max = 1;
}

void    Menu::loadPrevious()
{
  _isSelect = 0;
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(600, 300), "LOADING....", true);
  if (_th == NULL)
  {
    PtrFonct pf = &getGame;
    _th = new Thread();
    if (_th->createThread(pf, ((void*)(_preview))))
    {
      while (_preview->getState())
      {
        update();
        draw();
      }
      if (_th->joinThread())
      {
        delete _th;
        _th = NULL;
      }
      else
        std::cout << "ERROR ON JOIN THREAD\n";
    }
    else
        std::cout << "ERROR ON CREATE THREAD\n";
  }
  _preview->setState(true);
  _previewMode = _preview->getResult();
  _text->deleteAllText(_step1);
  _text->addText(_step1, 0, std::make_pair(15, 840), "GO", true);
  _text->addText(_step1, 1, std::make_pair(15, 920), "BACK", true);
  _max = 1;
}

void  *getGame(void *arg)
{
  reinterpret_cast<Preview *>(arg)->initializeSave();
  return (NULL);
}

void  *getMapp(void *arg)
{
  reinterpret_cast<Preview *>(arg)->initialize();
  return (NULL);
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
  std::ifstream file(".score", std::ios::in);
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
  : (_stepM == SCORE) ? (_stepM = HOME) : (_stepM == LOADM && (_map = _preview->getMap()) != NULL) ? (_previewMode = false ,_stepM = LOADG)
  : (_stepM == LOADPREVIOUS && (_map = _preview->getMap()) != NULL && _map->getSize() >= 10) ? (_previewMode = false, _isLaunch = true, _isSave = true)
  : (_stepM == ONLINE) ? (_stepM = SERVER, _isSelect = 0) : 0;
}

void  Menu::select1()
{
  stepM k;

  k = STEP1;
  (_stepM == STEP1) ? (_stepM = LOADPREVIOUS, _isSave = true) : (_stepM == STEP12 && convToInt(_sizeMap) >= 10) ? (_stepM = STEP1) : (_stepM == LOADM) ? (_previewMode = false, k = LOADM,_stepM = STEP1)
  : (_stepM == LOADPREVIOUS) ? (_stepM = STEP1, k = LOADM, _previewMode = false)
  : (_stepM == HOME) ? (_stepM = ONLINE) : (_stepM == ONLINE) ? (_stepM = CLIENT, _isSelect = 0) : 0;
  if (k != LOADM && _stepM == STEP1)
   startGenerator();
 if (_stepM == SERVER)
  {
    try
    {
      if (_network != NULL)
        delete _network;
      _network = new Networking(_nbPort);
      _stepM = WAITSERVER;
    }
    catch (BomberException *tmp)
    {
      _err = tmp->what();
    }
  }
  else if (_stepM == WAITSERVER && _network != NULL)
  {
    _map = new Map(30, _engine);
    _isLaunch = true;
    _isSave = false;
  }
}

void  Menu::select2()
{
  (_stepM == STEP1) ? (_stepM = LOADM, _isSave = false) : (_stepM == STEP12) ? (_stepM = STEP1, _isSelect = 0)
  : (_stepM == HOME) ?  (_isSelect = 0, _stepM = SCORE) : (_stepM == LOADG && _preview->getMap() != NULL && (convToInt(_nbPlayer) + convToInt(_nbBots)) >= 2 && convToInt(_nbBots) <= _map->getSize() / 10) ? (_isLaunch = true)
  : (_stepM == ONLINE) ? (_stepM = HOME) : (_stepM == SERVER) ? (_stepM = ONLINE) : 0;
  if (_stepM == SCORE)
     getScore();
  if (_stepM == CLIENT)
  {
    if (_network != NULL)
      delete _network;
    try
    {
      _network = new Networking(_nbPort, _ipAddr);
      _stepM = WAITCLIENT;
    }
    catch (BomberException *tmp)
    {
      _err = tmp->what();
    }
  }
  if (_stepM == ONLINE)
    _err = "";
}

void  Menu::select3()
{
  (_stepM == HOME) ? (_stepM = OPTION, _isSelect = 0) : (_stepM == STEP1) ? (_stepM = STEP12) : (_stepM == STEP11 && (convToInt(_sizeMap) >= 10 && atLeastPlayer()))
  ? (createMap(), _isSave = false) : (_stepM == LOADG) ? (_stepM = LOADM)
  : (_stepM == CLIENT) ? (_stepM = ONLINE)
  : (_stepM == OPTION) ? (_stepM = HOME) : 0;
  if (_stepM == ONLINE)
    _err = "";
}

void  Menu::createMap()
{
  bool  resume = true;

  _map = NULL;
  if (_th == NULL)
  {
    PtrFonct pf = &crM;
    _text->deleteAllText(_step1);
    _text->addText(_step1, 0, std::make_pair(600, 300), "LOADING....", true);
    _th = new Thread();
    if (_th->createThread(pf, ((void*)(this))))
    {
      while (resume)
      {
        update();
        draw();
        if (_map != NULL)
          resume = false;
      }
      if (_th->joinThread())
      {
        delete _th;
        _th = NULL;
      }
      else
        std::cout << "ERROR ON JOIN THREAD\n";
    }
    else
      std::cout << "ERROR ON CREATE THREAD\n";
  }
  _isLaunch = true;
}

void  *crM(void *arg)
{
  reinterpret_cast<Menu *>(arg)->generateMap();
  return (NULL);
}

void  Menu::generateMap()
{
  _map = new Map(getMapSize(), _engine);
}

void  Menu::select4()
{
  (_stepM == STEP11) ? (_stepM = STEP1) : (_stepM == HOME) ? (_exit = true) : (_stepM == STEP1) ? (_stepM = HOME) : 0;
}

bool  Menu::isSave() const
{
  return (_isSave);
}

bool  Menu::getFx() const
{
  return (_isFx);
}

Saving  *Menu::getSaving() const
{
  return (_preview->getInstance());
}

void    Menu::setCore(Core *core)
{
  _core = core;
}

Networking *Menu::getNetwork() const
{
  return (_network);
}
