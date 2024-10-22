/*
** CubeAnim.cpp for CubeAnim in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Wed May  14 14:50:25 2014 Antonin Ribeaud
** Last update Wed May  14 14:50:25 2014 Antonin Ribeaud
*/

#include "CubeAnim.hpp"

CubeAnim::CubeAnim(Camera *camera, Loader *loader)
{
  _isLaunch = false;
  _stopintro = false;
  _xend = 0;
  _inIntro = true;
  _camera = camera;
  _loader = loader;
  _width = MAX;
  _height = MAX;
  _angle = 0;
  _posy = 0;
  _posx = 0;
  _posz = -30;
}

CubeAnim::~CubeAnim()
{
  FMOD_Sound_Release(musique);
  FMOD_System_Close(system);
  FMOD_System_Release(system);
}

void 		CubeAnim::changeVolum(const float vol) const
{
  FMOD_Channel_SetVolume(canal, vol);
}

void 		CubeAnim::stopIntro(const bool status)
{
  _stopintro = status;
}

void  CubeAnim::changeMusic(const int i)
{
  if (i == 1)
  {
    _itp++;
    if (_itp == _paths.end())
      _itp = _paths.begin();
  }
  else if (i == -1)
  {
    if (_itp == _paths.begin())
    {
      _itp = _paths.end();
      _itp--;
    }
    else
      _itp--;
  }
  if (_paths.size() == 0)
    std::cout << "Error on loading" << std::endl;
  else
  {
    if (loadSound(*_itp) == false)
      return;
  }
}

bool 		CubeAnim::getStatus() const
{
  return (_stopintro);
}

void 		CubeAnim::draw(gdl::AShader &shader, type &LastType)
{
  for (size_t i = 0; i < _objects.size(); ++i)
  {
    if (_objects[i]->getType() != LastType)
    {
      LastType = _objects[i]->getType();
      _loader->bindTexture(LastType);
    }
    _loader->drawGeometry(shader, _objects[i]->getTransformation());
    _objects[i]->translate(vec3(0, -getEquation(i), 0));
  }
}

bool		CubeAnim::makeCube(const int x, const int y, const int z)
{
  AObject	*cube = create<Cube>();
  std::pair<float, float> pos;

  cube->setType(BLOCKD);
  if (cube->initialize() == false)
    return (false);
  pos = std::make_pair(x, z);
  cube->setPos(pos);
  _objects.push_back(cube);
  return (true);
}

void 	CubeAnim::update()
{
  FMOD_System_GetChannel(system, 0, &canal);
  FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0, FMOD_DSP_FFT_WINDOW_RECT);
  for (size_t i = 0; i < _objects.size(); ++i)
    _objects[i]->translate(vec3(0, getEquation(i), 0));
}

bool    CubeAnim::checkName(const char *str1) const
{
  std::string pp = "..";
  std::string p = ".";
  std::string tocheck = str1;

  if (pp == str1 || p == str1)
    return (false);
  return (true);
}

std::string   CubeAnim::makePath(const char *str1, const char *p) const
{
  std::string path = p;

  path += str1;
  return (path);
}

void    CubeAnim::getPaths(const char * path)
{
  DIR             *mydir;
  struct dirent   *currentdir;

  mydir = opendir(path);
  _paths.clear();
  if (mydir != NULL) 
    while ((currentdir = readdir(mydir)) != NULL)
    {
      if (checkName(currentdir->d_name) && 
        checkName(currentdir->d_name))
        _paths.push_back(makePath(currentdir->d_name, path));
    }
  }

  bool  CubeAnim::loadSound(const std::string &path)
  {
    resultat = FMOD_System_CreateSound(system, path.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &musique);
    if (resultat != FMOD_OK)
    {
      std::cout << "Impossible to open the audio file" << std::endl;
      return (false);
    }
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL); 
    FMOD_System_GetChannel(system, 0, &canal);
    return (true);
  }

  bool	CubeAnim::initFmod()
  {
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    getPaths(MUSIC_PATH);
    if (_paths.size() == 0)
      std::cout << "Error on loading" << std::endl;
    else
    {
      _itp = _paths.begin();
      if (loadSound(*_itp) == false)
        return (false);
    }
    return (true);
  }

  bool 		CubeAnim::initIntro()
  {
    if (!genSpiral())
      return (false);
    if (!initFmod())
      return (false);
    return (true);
  }

  float		CubeAnim::getEquation(const int i) const
  {
    float		y;
    int		coef;

    coef = 510;
    y = spectre[MAX*MAX - i]*(-((i-coef)*(i-coef)/2800)+100);
    return (y);
  }

  void    CubeAnim::rotate()
  {
    int   endintro;
    int   anglemax;
    int   ymax;

    ymax = 20;
    anglemax = 315;
    endintro = 1;
    if (_stopintro)
    {
      endintro = 100;
      if (_xend < 12)
      {
        _posy += 0.2;
        _xend += 0.2;
      }
      else
        _inIntro = false;
    }
    if (_angle < anglemax)
      _angle = _angle + 0.2 * endintro;
    if (_angle > 180 && _posy < ymax)
      _posy = _posy + 0.01 * endintro;
    if (_angle > anglemax)
      _angle = anglemax;
    if (_posy > ymax)
      _posy = ymax;
    _posx = cos((_angle/180) * PI) * 30;
    _posz = sin((_angle/180) * PI) * 30;
    _camera->moveCamera(vec3(_posx + _xend, _posy, _posz - _xend/2), vec3(_xend,0,_xend), vec3(0,1,0), 1);
  }

  bool CubeAnim::genSpiral()
  {
    int initial_direction = UP , n = MAX , p = 1 ;
    int r ,c;
    int row_right  = 0 , column_down = n-1 , row_left = n-1 , column_up = 0;
    for(r = 0 ; r < MAX ; r++)
    {
      for(c = 0 ; c < MAX ; c++)
        a[r][c] = 0 ;
    }
    while(p != n*n+1)
    { 
      if(initial_direction == UP)
      {
        r = row_right++ ;
        for(c = 0 ; c < n ; c++)
        {
          if(a[r][c] == 0)
          {
            a[r][c] = p++;
            if (makeCube(r-(MAX/2), 0, c-(MAX/2)) == false)
              return (false);
          }
        }
        initial_direction = RIGHT;
      }
      else if(initial_direction == RIGHT)
      {
        c = column_down-- ; 
        for(r = 0 ; r < n ; r++)
        {
          if(a[r][c] == 0)
          {
            a[r][c] = p++;
            if (makeCube(r-(MAX/2), 0, c-(MAX/2)) == false)
              return (false);
          }
        }
        initial_direction = DOWN ;
      }
      else if(initial_direction == DOWN)
      {
        r = row_left-- ;
        for(c = n-1 ; c >= 0 ; c--)
        {
          if(a[r][c] == 0)
          {
            a[r][c] = p++;
            if (makeCube(r-(MAX/2), 0, c-(MAX/2)) == false)
              return (false);
          }
        }
        initial_direction = LEFT ;
      }
      else if(initial_direction == LEFT)
      {
        c = column_up++;
        for(r = n-1 ; r >= 0 ; r--)
        {
          if(a[r][c] == 0)
          {
            a[r][c] = p++;
            if (makeCube(r-(MAX/2), 0, c-(MAX/2)) == false)
              return (false);
          }
        }
        initial_direction = UP ;
      }
    }
    return (true);
  }
