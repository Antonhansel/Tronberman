/*
** Intro.cpp for Intro in /home/apollo/rendu/cpp_bomberman/srcs
**
** Made by Antonin Ribeaud
** Login   <ribeau_a@epitech.net>
**
** Started on  Thu May  01 12:48:21 2014 Antonin Ribeaud
// Last update Fri May  2 20:05:38 2014 charly roche
*/

# include "Intro.hpp"
# include "AObject.hpp"
# include <math.h>

Intro::Intro()
{
		_width = MAX;
		_height = MAX;
}

Intro::~Intro()
{
	for (size_t i = 0; i < _objects.size(); ++i)
		delete _objects[i];
	FMOD_Sound_Release(musique);
	FMOD_System_Close(system);
	FMOD_System_Release(system);
	_context.stop();
}

bool	Intro::initFmod()
{
  	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
	resultat = FMOD_System_CreateSound(system, "./ressources/sounds/intro.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
	if (resultat != FMOD_OK)
	  {
	    fprintf(stderr, "Impossible de lire le fichier mp3\n");
	  	return (false);
	  }
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL); 
	FMOD_System_GetChannel(system, 0, &canal);
	return (true);
}

bool	Intro::initialize()
{
	if (!_context.start(1800, 1000, "Best Bomberman!"))
		return (false);
	glEnable(GL_DEPTH_TEST);
	if (!_shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER) || 
	!_shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER) || 
	!_shader.build())
		return (false);
	_projection = glm::perspective(60.0f, 1800.0f / 1000.0f, 0.1f, 100.0f);
	_transformation = glm::lookAt(glm::vec3(0, 10, -20), glm::vec3(0, 0, -100), glm::vec3(0, 1, 0));
	_shader.bind();
	_shader.setUniform("view", _transformation);
	_shader.setUniform("projection", _projection);
	if (drawLimits() == false)
		return (false);
	if (drawBackground() == false)
		return (false);
	std::cout << "Load done!" << std::endl;
	return (initFmod());
}

bool	Intro::drawLimits()
{
	genSpiral();
	return (true);
}

bool	Intro::makeCube(int x, int y, int z)
{
	AObject	*cube = new	Cube;
	if (cube->initialize() == false)
		return (false);
	cube->translate(glm::vec3(x, y, z));
	cube->setPos(x, z);
	_objects.push_back(cube);
	return (true);
}

bool 	Intro::drawBackground()
{
	AObject	*background = new	Background(_width * 4, _height * 4, 10.0f);

	_objects.push_back(background);
	return (background->initialize());
}

bool    Intro::update()
{
  float y;
  float y2;
  int   A;
  float mult;

  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  _context.updateClock(_clock);
  _context.updateInputs(_input);
  FMOD_System_GetChannel(system, 0, &canal);
  FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0, FMOD_DSP_FFT_WINDOW_RECT);
  A = 500;
  for (size_t i = 0; i < _objects.size(); ++i)
    {

      // mult = (MAX*MAX-i)*(MAX*MAX-i);
      // mult = -((mult - 2*A*(MAX*MAX-i)) + A*A) / 4000 + 100;
      // y = spectre[MAX*MAX - i]*(MAX*MAX/(i/2 + 1))* mult / 1;
      // if (i < _objects.size() - 1)
      // 	{
      // 	  y2 = spectre[MAX*MAX - i + 1]*(MAX*MAX/(i/2 + 1))* (mult) / 1;
      // 	  y = (y + y2) / 2;
      // 	}

      y = spectre[MAX*MAX - i]*(-((i-A)*(i-A)/2800)+100);
      if (i < _objects.size() - 1)
	{
	  y2 = spectre[MAX*MAX - i]*(-((i-A)*(i-A)/2800)+100);
	  y = (y + y2) / 2;
	}
 
      _objects[i]->translate(glm::vec3(0, y * 2, 0));
    }
  return true;
}

void    Intro::draw()
{
  float y;
  float y2;
  int A;
  float        mult;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.setUniform("view", glm::lookAt(glm::vec3(0, 13, -10),
					 glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
  _shader.setUniform("projection", _projection);
  _shader.bind();
  A = 500;
  for (size_t i = 0; i < _objects.size(); ++i)
    {
      _objects[i]->draw(_shader, _clock);

             
      y = spectre[MAX*MAX - i]*(-((i-A)*(i-A)/2800)+100);
      if (i < _objects.size() - 1)
	{
	  // y2 = spectre[MAX*MAX - i + 1]*(MAX*MAX/(i/2 + 1))* (mult) / 1;                       
	  y2 = spectre[MAX*MAX - i]*(-((i-A)*(i-A)/2800)+100);
	  y = (y + y2) / 2;
	}

      _objects[i]->translate(glm::vec3(0, -y * 2, 0));
    }
  _context.flush();
}

bool Intro::genSpiral()
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
            initial_direction = RIGHT ;
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
    for(r = 0 ; r < MAX ; r++)
    {
          for(c = 0 ; c < MAX ; c++)
          printf("%4d ",a[r][c]);
    }
}
