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

class KeyTracker {
	std::vector<bool> KeyClick;
	std::vector<bool> KeyActive;
	std::vector<Uint32> KeyPressLength;
	std::vector<bool> KeyRepeating;
	std::vector<KeyRepeat> KeyRepeatList;
	Uint16 AmountOfKeys=0;

	public:
	KeyTracker();
	~KeyTracker();

	void UpdateKey(SDL_Event *Key);
	bool KeyClicked(Uint32 Key, Uint8 ScanOrKey=Scancode);
	bool IsPressed(Uint32 Key, Uint8 ScanOrKey=Scancode);
	Uint32 TimeSinceLastPress(Uint32 Key, Uint8 ScanOrKey=Scancode);

	void SetRepeat(Uint32 Key, KeyRepeat RepeatInfo, Uint8 ScanOrKey=Scancode);
	KeyRepeat GetRepeat(Uint32 Key, Uint8 ScanOrKey=Scancode);
	bool IsRepeating(Uint32 Key, Uint8 ScanOrKey=Scancode);

	/*
	do Update BEFORE UpdateKey
	*/
	void Update(Uint32 Time);
};


#endif