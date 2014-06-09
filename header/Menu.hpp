//
// Menu.hpp for Menu in /home/chouag_m/rendu/old
//
// Made by Mehdi Chouag
// Login   <chouag_m@epitech.net>
//
// Started on  Sat May  3 17:42:13 2014 Mehdi Chouag
// Last update Tue May 13 19:24:11 2014 Mehdi Chouag
//

#ifndef MENU_HPP_
# define MENU_HPP_

# include "Camera.hpp"
# include "CubeAnim.hpp"
# include "Loader.hpp"
# include "Background.hpp"
# include "AObject.hpp"
# include "Cube.hpp"
# include "Factory.hpp"
# include "Text.hpp"
# include "AInput.hpp"
# include "Map.hpp"
# include "Player.hpp"
# include "Preview.hpp"
# include "Networking.hh"
# include "BomberException.hpp"
# include "Core.hpp"
# include "Thread.hpp"
# include "Function.hpp"

# define DELAY  0.15

using namespace gdl;
using namespace glm;


enum stepM
  {
    HOME,
    STEP1,
    STEP11,
    STEP12,
    SCORE,
    STEP2,
    STEP3,
    BUILDER,
    LOADM,
    LOADG,
    LOADPREVIOUS,
    ONLINE,
    SERVER,
    CLIENT,
    OPTION, 
    WAITSERVER,
    WAITCLIENT
  };

class Menu : public Game
{
public:
  Menu(Camera *, Loader *, ParticleEngine *);
  ~Menu();
  bool			initialize();
  bool			update();
  void			reset(const std::vector<Player *> &);
  void			draw();
  bool			launch() const;
  bool      drawBackground();
  void      event();
  void      chooseStep();
  void      manageEventInput();
  void      getInputNb(std::string &, size_t const, int const, int const);
  void      getInputAddr(std::string &, size_t);
  void      home();
  bool      initLogo();
  void      drawLogo();
  void      step1();
  void      step11();
  void      step12();
  void      score();
  void      load();
  void      loadGame();
  void      loadPrevious();
  int       getMapSize() const;
  int       getNbPlayer() const;
  int       getNbBots() const;
  Map       *getMap() const;
  void      setIsSelect();
  void      startGenerator();
  void      startPreview();
  bool      isSave() const;
  bool      getFx() const;
  Saving    *getSaving() const;
  void      setCore(Core *);
  Networking *getNetwork() const;
  void      createMap();
  void      generateMap();

  private:
    void  getScore();
    void  manageEventInputScore(key const &);
    void  getInputPseudo(char);
    void  saveInFile();
    bool  atLeastPlayer() const;
    void  select0();
    void  select1();
    void  select2();
    void  select3();
    void  select4();
    void  online();
    void  server();
    void  client();
    void  option();
    void  changeOption();
    void  getFxState();
    void  changeMusic();
    void  waitClient();
    void  waitServer();

private:
  bool          _isSave;
  bool          _previewMode;
  int           _isSelect;
  bool          _stopIntro;
  Clock			    _clock;
  Input			    _input;
  BasicShader		_shader;
  int           _players;
  bool          _isLaunch;
  float         _timer;
  int           _back;
  int           _max;
  stepM         _stepM;
  stepM         _oldStep;
  bool          _addScore;
  int           _newScore;
  int           _pos;
  bool          _exit;
  int           _vol;
  bool          _isFx;
  Thread        *_th;
private:
  Map               *_map;
  Text              *_text;
  AInput            *_event;
  Loader            *_loader;
  CubeAnim          *_cubeanim;
  Background        *_background;
  Camera            *_camera;
  Preview           *_preview;
  ParticleEngine    *_engine;
  Networking        *_network;
  Core              *_core;

private:
  std::string       _err;
  std::string       _fx;
  std::string       _volume;
  std::string       _sizeMap;
  std::string       _nbPlayer;
  std::string       _nbPort;
  std::string       _nbBots;
  std::string       _ipAddr;
  std::string       _scoreToAdd;
  gdl::Texture      _texture;
  gdl::Geometry     _geometry;
private:
  std::map<int, std::string> _score;
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > _step1;
  std::map<stepM, void (Menu::*)()>    _func;
  std::map<int, void (Menu::*)()>      _step;
};

void  *getGame(void *);
void  *getMapp(void *);
void  *crM(void *);

#endif /* !MENU_HPP_ */
