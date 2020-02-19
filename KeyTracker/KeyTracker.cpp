#include "KeyTracker.hpp"

KeyTracker::KeyTracker() {
	int TempAmountOfKeys;
	SDL_GetKeyboardState(&TempAmountOfKeys);
	AmountOfKeys = TempAmountOfKeys;

	Keys.resize(AmountOfKeys);
}

KeyTracker::~KeyTracker() {
}

KeyInfo KeyTracker::operator[](Uint32 Key) {
	return Keys[Key];
}

KeyInfo KeyTracker::operator()(Uint32 Key) {
	Uint16 Scancode = SDL_GetScancodeFromKey(Key);
	return Keys[Scancode];
}

void KeyTracker::SetRepeat(Uint32 Key, KeyRepeat RepeatInfo, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	Keys[Key].Repeat = RepeatInfo;
}

void KeyTracker::Update(Uint32 Time) {
	for(Uint16 i=0; i < AmountOfKeys; i++) {
		if(Keys[i].Active) {
			Keys[i].PressLength += Time;
			if(Keys[i].PressLength > Keys[i].Repeat.Delay && Keys[i].Repeat.Delay != 0 && Keys[i].Repeat.Repeat != 0) {
				Keys[i].Repeating = true;
				Keys[i].Clicked = true;
				Keys[i].PressLength -= Keys[i].Repeat.Repeat;
			}
			else {
				Keys[i].Clicked = false;
			}
		}
	}
}

void KeyTracker::UpdateKey(SDL_Event *Key) {
	if(Key->type == SDL_KEYDOWN) {
		if(!Key->key.repeat) {
			Keys[Key->key.keysym.scancode].Active = true;
			Keys[Key->key.keysym.scancode].Clicked = true;
		}
	}
	else if(Key->type == SDL_KEYUP) {
		Keys[Key->key.keysym.scancode].Active = false;
		Keys[Key->key.keysym.scancode].Clicked = false;
		Keys[Key->key.keysym.scancode].Repeating = false;
		Keys[Key->key.keysym.scancode].PressLength = 0;
	}
}