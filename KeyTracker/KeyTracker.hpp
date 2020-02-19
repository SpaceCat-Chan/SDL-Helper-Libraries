#ifndef KEYTRACKER_HPP
#define KEYTRACKER_HPP

#include <SDL.h>
#include <vector>

struct KeyRepeat {
	Uint32 Delay, Repeat;
};

enum {
	Scancode,
	Keycode
};

struct KeyInfo {
	bool Clicked = false;
	bool Active = false;
	Uint32 PressLength = 0;
	bool Repeating;
	KeyRepeat Repeat;
};

class KeyTracker {
	std::vector<KeyInfo> Keys;
	Uint16 AmountOfKeys=0;

	public:
	KeyTracker();
	~KeyTracker();

	/*
	Scancodes
	*/
	KeyInfo operator[](Uint32 Key);
	
	/*
	Keycodes
	*/
	KeyInfo operator()(Uint32 Key);

	void UpdateKey(SDL_Event *Key);

	void SetRepeat(Uint32 Key, KeyRepeat RepeatInfo, Uint8 ScanOrKey=Scancode);

	/*
	do Update BEFORE UpdateKey
	*/
	void Update(Uint32 Time);
};


#endif