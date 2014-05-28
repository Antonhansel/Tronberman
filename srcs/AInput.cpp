# include "AInput.hpp"

AInput::AInput(gdl::Input &input, inputType t) :
	_input(input), _type(t)
{
	_mode2 = false;
	_ptrFunct[KEY1] = &AInput::createPlayer1Key;
	_ptrFunct[KEY2] = &AInput::createPlayer2Key;
	_ptrFunct[MENU] = &AInput::createMenuKey;
	_ptrFunct[GAME] = &AInput::createGameKey;
	_ptrFunct[GENERATOR] = &AInput::createGeneratorKey;
	(this->*_ptrFunct[_type])();
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
	if (_mode2 == false)
		_key[SDLK_SPACE] = PBOMB;
	else
		_key[SDLK_KP_0] = PBOMB; 
}

void	AInput::createPlayer2Key()
{
	_key[SDLK_z] = PUP;
	_key[SDLK_s] = PDOWN;
	_key[SDLK_q] = PLEFT;
	_key[SDLK_d] = PRIGHT;
	_key[SDLK_SPACE] = PBOMB;
}

void	AInput::createMenuKey()
{
	_key[SDLK_UP] = MUP;
	_key[SDLK_LEFT] = MLEFT;
	_key[SDLK_RIGHT] = MRIGHT;
	_key[SDLK_DOWN] = MDOWN;
	_key[SDLK_RETURN] = MRETURN;
	_key[SDLK_ESCAPE] = ESCAPE;
	_key[SDLK_BACKSPACE] = MBACKSPACE;
	_key[SDLK_KP_0] = MZERO;
	_key[SDLK_KP_1] = MONE;
	_key[SDLK_KP_2] = MTWO;
	_key[SDLK_KP_3] = MTHREE;
	_key[SDLK_KP_4] = MFOUR;
	_key[SDLK_KP_5] = MFIVE;
	_key[SDLK_KP_6] = MSIX;
	_key[SDLK_KP_7] = MSEVEN;
	_key[SDLK_KP_8] = MHEIGHT;
	_key[SDLK_KP_9] = MNINE;
}

void	AInput::createGameKey()
{
	_key[SDLK_g] = FPSOFF;
	_key[SDLK_f] = FPSON;
	_key[SDLK_ESCAPE] = ESCAPE;
	_key[SDL_QUIT] = ESCAPE;
	_key[SDLK_o] = PSAVE;
}

void	AInput::createGeneratorKey()
{
	_key[SDLK_KP_PLUS] = GPLUS;
	_key[SDLK_KP_MINUS] = GMINUS;
	_key[SDLK_SPACE] = SPACE;
	_key[SDLK_KP_1] = KP1;
	_key[SDLK_KP_2] = KP2;
	_key[SDLK_UP] = PUP;
	_key[SDLK_DOWN] = PDOWN;
	_key[SDLK_LEFT] = PLEFT;
	_key[SDLK_RIGHT] = PRIGHT;
	_key[SDLK_ESCAPE] = ESCAPE;
	_key[SDLK_BACKSPACE] = MBACKSPACE;
	_key[SDL_QUIT] = ESCAPE;
}

void	AInput::setMode(bool nMod)
{
	_mode2 = nMod;
	_key.clear();
	(this->*_ptrFunct[_type])();
}