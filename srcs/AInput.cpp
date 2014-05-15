# include "AInput.hpp"

AInput::AInput(gdl::Input &input, inputType t) :
	_input(input)
{
	_ptrFunct[KEY1] = &AInput::createPlayer1Key;
	_ptrFunct[KEY2] = &AInput::createPlayer2Key;
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

void	AInput::createPlayer1Key()
{
	_key[SDLK_UP] = P1UP;
	_key[SDLK_DOWN] = P1DOWN;
	_key[SDLK_LEFT] = P1LEFT;
	_key[SDLK_RIGHT] = P1RIGHT;
}

void	AInput::createPlayer2Key()
{
	_key[SDLK_z] = P2UP;
	_key[SDLK_s] = P2DOWN;
	_key[SDLK_q] = P2LEFT;
	_key[SDLK_d] = P2RIGHT;	
}

/*int 	AInput::menuEvent()
{

}*/