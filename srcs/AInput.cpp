# include "AInput.hpp"

AInput::AInput(gdl::Input &input, inputType t) :
	_input(input)
{
	_ptrFunct[KEY1] = &AInput::createPlayer1Key;
	_ptrFunct[KEY2] = &AInput::createPlayer2Key;
	_ptrFunct[MENU] = &AInput::createMenuKey;
	(this->*_ptrFunct[t])();
}

AInput::~AInput()
{

}

key	AInput::getInput()
{
	for (std::map<int, key>::const_iterator it = _key.begin(); it != _key.end(); ++it)
	{
		if (_input.getKey((*it).first))
		{
			return ((*it).second);
		}
	}
	return (NONE);
}

void	AInput::setInput(gdl::Input &input)
{
	_input = input;
}

void	AInput::createPlayer1Key()
{
	_key[SDLK_UP] = PUP;
	_key[SDLK_DOWN] = PDOWN;
	_key[SDLK_LEFT] = PLEFT;
	_key[SDLK_RIGHT] = PRIGHT;
}

void	AInput::createPlayer2Key()
{
	_key[SDLK_z] = PUP;
	_key[SDLK_s] = PDOWN;
	_key[SDLK_q] = PLEFT;
	_key[SDLK_d] = PRIGHT;
}

void	AInput::createMenuKey()
{
	_key[SDLK_UP] = MUP;
	_key[SDLK_LEFT] = MLEFT;
	_key[SDLK_RIGHT] = MRIGHT;
	_key[SDLK_DOWN] = MDOWN;
	_key[SDLK_RETURN] = MRETURN;
	_key[SDLK_ESCAPE] = ESCAPE;
}