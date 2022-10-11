#include <Windows.h>
#include "Input.h"




bool Input::IsKeyPressed(unsigned char keycode) const noexcept
{
    return keystates[keycode];
}

bool Input::IsKeyBufferEmpty() const
{
    return keyBuffer.empty();
}

bool Input::IsCharEmpty()
{
    return charBuffer.empty();
}

void Input::FlushChar()
{
    charBuffer =  std::queue<char>();
}

void Input::FlushKey()
{
    keyBuffer = std::queue<Event>();
}

void Input::FlushMouse()
{
    mouseBuffer = std::queue<Event>();
}

void Input::FlushKeyBoard()
{
    FlushChar();
    FlushKey();
}

std::optional<Event> Input::ReadChar()
{
    if (keyBuffer.size() > 0u) 
    {
        Event e = keyBuffer.front();
        if (e.IsMouse()) {
            throw std::invalid_argument("keyboard input recieving mouse input");
        }
        keyBuffer.pop();
        return e;
    }
    return {};
}

void Input::Flush()
{
    FlushKey();
    FlushChar();
    FlushMouse();
}
/// <summary>
/// Stores the into the keyboard buffer
/// </summary>
/// <param name="event">Key event to push onto the stack</param>
void Input::OnKeyPressed(Event event) 
{
    if (!event.IsMouse()) {
        keystates[event.GetCode()] = true;
        keyBuffer.push(event);
    }
}
/// <summary>
/// Stores the into the keyboard buffer
/// </summary>
/// <param name="event">Key event to push onto the stack</param>
void Input::OnKeyRelease(Event event)
{
    if (!event.IsMouse()) {
        keystates[event.GetCode()] = false;
        keyBuffer.push(event);
    }
    
}

void Input::OnCharPressed(char event)
{
    charBuffer.push(event);
}

void Input::OnMouseButtonPressed(Event event)
{
    if (event.IsMouse()) {
        mouseBuffer.push(event);
        if (event.IsRight()) {
            rightMouse = true;
        }
        else {
            leftMouse = true;
        }
    }
}

void Input::OnMouseButtonRelease(Event event)
{
    if (event.IsMouse()) {
        mouseBuffer.push(event);
        if (event.IsRight()) {
            rightMouse = false;
        }
        else {
            leftMouse = false;
        }
    }
}

void Input::GetPos(int& pX, int& pY)
{
    pX = x;
    pY = y;
}

void Input::SetPos(const int _x, const int _y)
{
    x = _x;
    y = _y;
}

void Input::OnWheelDelta(int delta) {
    WheelDeltaStep += delta;
    while (WheelDeltaStep >= WHEEL_DELTA) {
        MouseUp();
        WheelDeltaStep -= WheelDeltaStep;
    }
    while (WheelDeltaStep <= WHEEL_DELTA) {
        MouseDown();
        WheelDeltaStep += WheelDeltaStep;
    }
}

void Input::MouseUp()
{
}

void Input::MouseDown()
{
}
