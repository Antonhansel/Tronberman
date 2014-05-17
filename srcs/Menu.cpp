/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Wed May 14 01:50:17 2014 Mehdi Chouag
*/

#include "Menu.hpp"
#include "CubeAnim.hpp"

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
  _timer = 0;
  _back = -1;
  _stepM = HOME;
  _func[HOME] = &Menu::home;
  _func[STEP1] = &Menu::step1;
  _func[STEP11] = &Menu::step11;
  _min = 0;
  _max = 2;
  _sizeMap.assign("50");
  _nbPlayer.assign("1");
  _nbBots.assign("1");
  _step1[std::make_pair(0, std::make_pair(15, 300))] = _text->putstr("LOCAL", 64);
  _step1[std::make_pair(1, std::make_pair(15, 380))] = _text->putstr("ONLINE", 64);
  _step1[std::make_pair(2, std::make_pair(15, 460))] = _text->putstr("SCORE", 64);
  _step1[std::make_pair(3, std::make_pair(15, 540))] = _text->putstr("", 64);
  _step1[std::make_pair(4, std::make_pair(15, 620))] = _text->putstr("", 64);
  _step1[std::make_pair(5, std::make_pair(700, 300))] = _text->putstr("", 64);
  _step1[std::make_pair(6, std::make_pair(700, 380))] = _text->putstr("", 64);
  _step1[std::make_pair(7, std::make_pair(700, 460))] = _text->putstr("", 64);
}

Menu::~Menu()
{
  delete _text;
  delete _background;
}

bool  Menu::drawBackground()
{
  _background = new Background(130, 130, 10.0f);
  if (_background->initialize() == false)
    return (false);
  _background->translate(glm::vec3(0, 0, 20));
  _background->rotate(glm::vec3(30, 0, 100));
  return (true);
}

bool	Menu::initialize()
{ 
  if (_cubeanim->initIntro() == false)
    return (false);
  if (drawBackground() == false)
    return (false);
  if (!initLogo())
    return (false);
  std::cout << "Menu init ended" << std::endl;
  return (true);
}

void    Menu::manageEventInput()
{
  if (_stepM == STEP11)
  {
    switch (_isSelect)
    {
      case 0:
        getInputNb(_sizeMap, 4, 4);
        break;
      case 1:
        getInputNb(_nbPlayer, 6, 1);
        break;
      case 2:
        getInputNb(_nbBots, 7, 2);
        break;
      case 3:
      {
        _isLaunch = true;
        _cubeanim->changeVolum(0.4f);
        break;
      }
      //lancer le jeu
      case 4:
        _stepM = STEP1;
        break;
  }

  }
}

void    Menu::getInputNb(std::string &s, int n, size_t size)
{
  key   k;

  if ((k = _event->getInput()) != NONE && 
      k != MBACKSPACE && k != MUP && k != MDOWN &&
        k != MLEFT && k != MRIGHT && s.size() < size)
  {
    _timer = 0;
    s += (((int)(k)) - 23) + 48;
    _text->addNb(&_step1, n, s);
    step11();
  }
  else if (k == MBACKSPACE)
  {
    _timer = 0;
    s.assign(s.substr(0, s.length() - 1));
    _text->addNb(&_step1, n, s);
    step11();
  }
}

void    Menu::chooseStep()
{
  if (_isSelect == 2 && _stepM == STEP1)
    _stepM = HOME;
  if (_isSelect == 0 && _stepM == HOME)
    _stepM = STEP1;
  else if (_isSelect == 0 && _stepM == STEP1)
  {
    _isSelect = 0;
    _stepM = STEP11;
  }
  (this->*_func[_stepM])();
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
        if (_isSelect >= _min)
          _isSelect--;
        if (_isSelect == _min - 1)
          _isSelect = _max;
        _timer = 0;
        break;
      case MDOWN:
        if (_isSelect <= _max)
          _isSelect++;
        if (_isSelect == _max + 1)
            _isSelect = 0;
        _timer = 0;
        break;
      case MRETURN:
      {
        _timer = 0;
        chooseStep();
        break;
      }
      default:
        manageEventInput();
        break;
    }
  }
}

bool    Menu::update()
{
  _camera->setPlayer(1);
  _clock = _camera->getClock();
  _input = _camera->getInput();
  _timer += _clock.getElapsed();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  if (_isLaunch == true)
    return (false);
  if (_event == NULL && _stopIntro == true)
    _event = new AInput(_input, MENU);
  if (_stopIntro == true)
  {
    _event->setInput(_input);
    event(_step1);
  }
  _cubeanim->update();
  return (true);
}

void    Menu::draw()
{
  type LastType = BLOCKD;

  if (_input.getKey(SDLK_p))
    {
      _isLaunch = true;
      _cubeanim->changeVolum(0.4f);
    }
  if (_input.getKey(SDLK_SPACE))
    {
      _cubeanim->stopIntro(true);
      _stopIntro = true;
    }
  _cubeanim->rotate();
  _loader->bindTexture(LastType);
  _cubeanim->draw(_shader, LastType);
  if (_cubeanim->getStatus())
    _background->draw(_shader, _clock);
  if (_stopIntro)
    _text->draw(_step1, _isSelect);
  drawLogo();
  _camera->flushContext();
}

void    Menu::reset()
{
  _isLaunch = false;
}

bool    Menu::launch() const
{
  return (_isLaunch);
}

void    Menu::home()
{
  std::vector<std::string> v;
  std::string u("LOCAL");
  std::string u1("ONLINE");
  std::string u2("SCORE");
  v.push_back(u);
  v.push_back(u1);
  v.push_back(u2);
  _isSelect = 0;
  _text->modifyWord(&_step1, v);
}

void    Menu::step1()
{
  std::vector<std::string> v;
  std::string u("New Game");
  std::string u1("Load Game");
  std::string u2("Back");
  v.push_back(u);
  v.push_back(u1);
  v.push_back(u2);
  _isSelect = 0;
  _text->modifyWord(&_step1, v);
}

void    Menu::step11()
{
  std::vector<std::string> v;
  std::string u("MAP SIZE");
  std::string u1("NB PLAYER");
  std::string u2("BOTS");
  std::string u3("GO");
  std::string u4("BACK");
  v.push_back(u);
  v.push_back(u1);
  v.push_back(u2);
  v.push_back(u3);
  v.push_back(u4);
  v.push_back(_sizeMap);
  v.push_back(_nbPlayer);
  v.push_back(_nbBots);
  _text->modifyWord(&_step1, v);
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