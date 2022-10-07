#pragma once
#include "Event.h"

#include <queue>
#include <bitset>
#include <optional>
#include <stdexcept>

class Input
{
	friend class Window;
public:
#pragma region keyboard
	Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	bool IsKeyPressed(unsigned char key) const noexcept;
	bool IsKeyBufferEmpty() const;
	bool IsCharEmpty();
	void FlushChar();
	void FlushKey();
	void FlushMouse();
	void FlushKeyBoard();
	std::optional<Event> ReadChar();
	void Flush();
#pragma endregion
private:

	void OnKeyPressed(Event event) ;
	void OnKeyRelease(Event event);
	void OnCharPressed(char event);
	void OnMouseButtonPressed(Event event);
	void OnMouseButtonRelease(Event event);
	void GetPos(int& x, int& y);
	void SetPos(const int _x, const int _y);
private:

	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool leftMouse, rightMouse;
	int x, y;
	std::bitset<nKeys> keystates;
	std::queue<Event> keyBuffer;
	std::queue<Event> mouseBuffer;
	std::queue<char> charBuffer;
};

