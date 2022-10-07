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

        keyBuffer.push(event);
    }
    else
    {
        throw std::invalid_argument("keyboard input recieving mouse input");
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
        leftMouse = event.IsLeftPressed();
        rightMouse = event.IsRightPressed();
    }
}

void Input::OnMouseButtonRelease(Event event)
{
}

