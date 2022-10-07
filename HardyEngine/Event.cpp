#include "Event.h"

Event::Event(Type type, char code):
type(type),
code(code)
{

	x = 0;
	y = 0;
}

//Event::Event(Type type, int x, int y, bool left, bool right) :
//	type(type),
//	x(x),
//	y(y),
//	leftPressed(left),
//	rightPressed(right)
//{
//	is_mouse = true;
//
//}

bool Event::IsPressed()
{
	if (type == MOUSE_LEFT_PRESSED ||
		type == MOUSE_RIGHT_PRESSED ||
		type == MOUSE_MIDDLE_PRESSED ||
		type == KEY_PRESSED)
	{
		return true;
	}
	return false;
	
}

bool Event::IsReleased()
{
	if (type == MOUSE_LEFT_RELEASED ||
		type == MOUSE_RIGHT_RELEASED ||
		type == MOUSE_MIDDLE_RELEASED ||
		type == KEY_PRESSED)
	{
		return true;
	}
	return false;
	return false;
}

unsigned char Event::GetCode()
{
	return code;
}

bool Event::isValid()
{
	return type != Type::INVALID;
}
