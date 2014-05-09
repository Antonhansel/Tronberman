/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Mon May  5 17:46:18 2014 ribeaud antonin
*/

#include "Menu.hpp"

Menu::Menu(Camera *camera, Loader *loader) : _camera(camera)
{
  _camera->setPlayer(1);
  _loader = loader;
  _width = MAX;
  _height = MAX;
  _shader = _camera->getShader();
  _clock = _camera->getClock();
  _angle = 0;
  _posy = 0;
  _posx = 0;
  _posz = -30;
  _isLaunch = false;
  _stopintro = false;
  _xend = 0;
  _inIntro = true;
}

Menu::~Menu()
{
  for (size_t i = 0; i < _objects.size(); ++i)
    delete _objects[i];
  FMOD_Sound_Release(musique);
  FMOD_System_Close(system);
  FMOD_System_Release(system);
}

bool	Menu::initFmod()
{
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
  resultat = FMOD_System_CreateSound(system, "./ressources/sounds/intro.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
  if (resultat != FMOD_OK)
    {
      std::cout << "Impossible to open the audio .mp3" << std::endl;
      return (false);
    }
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL); 
  FMOD_System_GetChannel(system, 0, &canal);
  return (true);
}

bool	Menu::initialize()
{ 
  if (!genSpiral())
    return (false);
  if (initFmod() == false)
    return (false);
  std::cout << "Menu init ended" << std::endl;
  return (true);
}

bool		Menu::makeCube(int x, int y, int z)
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

bool    Menu::update()
{
  _camera->setPlayer(1);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  if (_isLaunch == true)
    return (false);
  _clock = _camera->getClock();
  _input = _camera->getInput();
  FMOD_System_GetChannel(system, 0, &canal);
  FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0, FMOD_DSP_FFT_WINDOW_RECT);
  for (size_t i = 0; i < _objects.size(); ++i)
      _objects[i]->translate(vec3(0, getEquation(i), 0));
  return (true);
}

void    Menu::draw()
{
  type LastType = BLOCKD;

  if (_input.getKey(SDLK_p))
    _isLaunch = true;
  if (_input.getKey(SDLK_SPACE))
   _stopintro = true;
  rotate();
  _loader->bindTexture(LastType);
  for (size_t i = 0; i < _objects.size(); ++i)
    {
      if (_objects[i]->getType() != LastType)
      {
        LastType = _objects[i]->getType();
        _loader->bindTexture(LastType);
      }
      _loader->drawGeometry(_shader, _objects[i]->getTransformation());
      _objects[i]->translate(vec3(0, -getEquation(i), 0));
    }
  _camera->flushContext();
}

void    Menu::rotate()
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

bool Menu::genSpiral()
{
  int initial_direction = UP , n = MAX , p = 1 ;
  int r ,c;
  int row_right  = 0 , column_down = n-1 , row_left = n-1 , column_up = 0 ;
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

void		Menu::reset()
{
  _isLaunch = false;
}

float		Menu::getEquation(int i)
{
  float		y;
  int		coef;

  coef = 510;
  y = spectre[MAX*MAX - i]*(-((i-coef)*(i-coef)/2800)+100);
  return (y);
}

bool		Menu::launch() const
{
  return (_isLaunch);
}
