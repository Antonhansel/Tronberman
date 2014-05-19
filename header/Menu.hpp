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
# include <Game.hh> 
# include <Clock.hh> 
# include <Input.hh> 
# include <SdlContext.hh> 
# include <Geometry.hh> 
# include <Texture.hh> 
# include <Model.hh> 
# include <glm/glm.hpp>
# include <BasicShader.hh>
# include <glm/gtc/matrix_transform.hpp>
# include <OpenGL.hh>
# include <vector>
# include <iostream>
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
    BUILDER
  };

class Menu : public Game
{
public:
  Menu(Camera *, Loader *);
  ~Menu();
  bool			initialize();
  bool			update();
  void			reset(const std::map<int, Player *> &);
  void			draw();
  bool			launch() const;
  bool      drawBackground();
  void      event(std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > &);
  void      chooseStep();
  void      manageEventInput();
  void      getInputNb(std::string &, int, size_t, int, int);
  void      home();
  bool      initLogo();
  void      drawLogo();
  void      step1();
  void      step11();
  void      step12();
  void      score();
  int       getMapSize() const;
  int       getNbPlayer() const;
  int       getNbBots() const;
  Map       *getMap() const;
  void      setIsSelect();
  void      startGenerator();
  //int  operator=(const std::string &);

private:
  int         _isSelect;
  CubeAnim *_cubeanim;
  Background *_background;
  Camera		*_camera;
  bool      _stopIntro;
  Loader    *_loader;
  Clock			_clock;
  Input			_input;
  BasicShader		_shader;
  Text			*_text;
  int       _players;
  bool      _isLaunch;
  AInput    *_event;
  std::map<std::pair<int, std::pair<int, int> >, std::vector<gdl::Geometry *> > _step1;
  std::map<stepM, void (Menu::*)()>    _func;
  float     _timer;
  int       _back;
  int       _min;
  int       _max;
  stepM     _stepM;
  bool      _addScore;
  int       _newScore;
  int       _pos;
  std::string       _sizeMap;
  std::string       _nbPlayer;
  std::string       _nbBots;
  std::string       _scoreToAdd;
  gdl::Texture      _texture;
  gdl::Geometry     _geometry;
  Map               *_map;
  std::map<int, std::string> _score;

  private:
    int   convToInt(const std::string &) const;
    void  convToString(std::string &, int) const;
    void  getScore();
    void  manageEventInputScore(key &);
    void  getInputPseudo(char);
    void  saveInFile();
};

#endif /* !MENU_HPP_ */
