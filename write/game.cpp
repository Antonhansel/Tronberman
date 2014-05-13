#include "../game.hh"

Game::Game(gdl::SdlContext &context) : context(context)
{
}

int     Game::getColumn(char c)
{
  if (c == '.')
    {
      _firstChar = ' ';
      return (16);
    }
  if (c >= '0' && c <= '9')
    {
      _firstChar = '0';
      return (15);
    }
  if (c >= '@' && c <= 'O')
    {
      _firstChar = '@';
      return (14);
    }
  if (c >= 'P' && c <= '\\')
    {
      _firstChar = 'P';
      return (13);
    }
  return (0);
}

void	Game::putchar(char c, std::vector<gdl::Geometry *> &_text)
{
  gdl::Geometry	*_geometry = new gdl::Geometry();

  int	div;


  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  div = getColumn(c);
  _geometry->setColor(glm::vec4(0, 1, 1, 1));
  _geometry->pushVertex(glm::vec3(0, 0, 0));
  _geometry->pushVertex(glm::vec3(64, 0, 0));
  _geometry->pushVertex(glm::vec3(64, 64, 0));
  _geometry->pushVertex(glm::vec3(0, 64, 0));
  _geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, div / 16.0f));
  _geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, div / 16.0f));  
  _geometry->pushUv(glm::vec2((c - _firstChar + 1) / 16.0f, (div - 1) / 16.0f));
  _geometry->pushUv(glm::vec2((c - _firstChar) / 16.0f, (div - 1) / 16.0f));
  _geometry->build();
  _text.push_back(_geometry);
}

void	Game::putstr(char *str, int x, int y)
{
  int	i(-1);
  std::vector<gdl::Geometry *> _text;

  
  while (str[++i])
    putchar(str[i], _text);
  _menu[std::make_pair(x, y)] = _text;
}

bool Game::initialize()
{
  if ((!this->shader.load("./ressources/shaders/basic.fp", GL_FRAGMENT_SHADER)) ||
      (!this->shader.load("./ressources/shaders/basic.vp", GL_VERTEX_SHADER)) ||
      (!this->shader.build()))
    {
      std::cerr << "Impossible de creer/charger le shader" << std::endl;
      return (false);
    }

  glm::mat4 projection;
  projection = glm::ortho(0.0f, 1300.0f, 1000.0f, 0.0f, -1.0f, 1.0f);

  this->shader.bind();
  this->shader.setUniform("view", glm::mat4(1));
  this->shader.setUniform("projection", projection);

  if (!this->texture.load("./ressources/fonts/24BitTron.tga"))
    {
      std::cerr << "Impossible de charger la texture bomber.tga" << std::endl;
      return false;
    }
  return (true);
}

bool Game::update()
{
  this->context.updateInputs(this->input);
  return (!this->input.getInput(SDL_QUIT));
}

void		Game::draw()
{
  size_t        i(0);
  std::map<std::pair<int, int>, std::vector<gdl::Geometry *> >::iterator it;
  glm::mat4	transformation;
  int		add;
  int		line(15);

  add = 1300 / 2 - 50 * 5;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->shader.bind();
  this->texture.bind();
  for (it = _menu.begin(); it != _menu.end(); ++it)
    {
      for (i = 0; i != (*it).second.size(); i++)
	{
	  transformation = glm::translate(glm::mat4(1), glm::vec3(add, line, 0));
	  (*it).second[i]->draw(this->shader, transformation, GL_QUADS);
	  add += 50;
	}
      line += 128;
      add = 0;
    }
  this->context.flush();
}

Game::~Game()
{
  std::map<std::pair<int, int>, std::vector<gdl::Geometry *> >::iterator it;
  size_t	i = 0;

  for (it = _menu.begin(); it != _menu.end(); ++it)
    for (i = 0; i != (*it).second.size(); i++)
      delete (*it).second[i];
}
