#pragma once

#include <list>
#include <glm/gtc/type_precision.hpp>

namespace	gdl
{
	// Handle the inputs
	class Input
	{
	private:
		std::list<int>	_inputs;
		std::list<int>	_keyInputs;
		glm::i8vec2		_mousePosition;
		glm::i8vec2		_mouseDelta;
		glm::i8vec2		_mouseWheelDelta;

	public:
		Input();
		virtual ~Input();

		// Do not use this functions, they are called by the context to update the inputs
		void 				clearInputs();
		void 				addInput(int input);
		void 				addKeyInput(int input);
		void 				removeKeyInput(int input);
		void 				setMousePosition(glm::i8vec2 const &pos, glm::i8vec2 const &rel);
		void				setMouseWheel(glm::i8vec2 const &delta);

		// Returns the mouse position
		glm::i8vec2 const  	&getMousePosition();
		// Returns the mouse movement since the last update
		glm::i8vec2 const  	&getMouseDelta();
		// Returns the mouse wheel movement since the last update
		glm::i8vec2 const  	&getMouseWheel();

		// Returns true if the input passed as parameter has been detected
		bool 				getInput(int input, bool handled = false);
		// Returns true if the Key passed as parameter is currently pressed
		bool 				getKey(int input, bool handled = false);
	};

}
