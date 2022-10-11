#pragma once
class Event
{

public:

	enum Type
	{
		MOUSE_LEFT_PRESSED,
		MOUSE_LEFT_RELEASED,
		MOUSE_RIGHT_PRESSED,
		MOUSE_RIGHT_RELEASED,
		MOUSE_MIDDLE_PRESSED,
		MOUSE_MIDDLE_RELEASED,
		MOUSE_WHEEL_UP,
		MOUSE_WHEEL_DOWN,
		KEY_PRESSED,
		KEY_RELEASED,
		INVALID
	};

	
private:
	Type type = Type::INVALID;
	unsigned char code;
	bool rightPressed,leftPressed;
	int x, y;
	bool is_mouse;
public:
	Event(Type type,char code);
	Event(Type type, int x, int y, bool left, bool right);
	bool IsMouse() 
	{
		
		return is_mouse;
		
	}
	bool IsRight()
	{
		return type == Type::MOUSE_RIGHT_PRESSED || type== Type::MOUSE_RIGHT_RELEASED;
	}
	bool IsLeft()
	{
		return type == MOUSE_LEFT_PRESSED || type == Type::MOUSE_LEFT_RELEASED;
	}
	void SetPos(int x, int y);
	bool IsPressed();
	bool IsReleased();
	unsigned char GetCode();
	bool isValid();


};

