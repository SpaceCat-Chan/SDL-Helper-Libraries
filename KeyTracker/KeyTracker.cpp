#include "KeyTracker.hpp"

KeyTracker::KeyTracker() {
	int TempAmountOfKeys;
	SDL_GetKeyboardState(&TempAmountOfKeys);
	AmountOfKeys = TempAmountOfKeys;

	KeyClick.resize(AmountOfKeys);
	KeyActive.resize(AmountOfKeys);
	KeyPressLength.resize(AmountOfKeys);
	KeyRepeating.resize(AmountOfKeys);
	KeyRepeatList.resize(AmountOfKeys);

	for(Uint32 i=0; i < AmountOfKeys; i++) {
		KeyClick[i] = false;
		KeyActive[i] = false;
		KeyPressLength[i] = 0;
		KeyRepeating[i] = false;
		KeyRepeatList[i].Delay = 0;
		KeyRepeatList[i].Repeat = 0;
	}
}

KeyTracker::~KeyTracker() {
}

bool KeyTracker::operator[](Uint32 Key) {
	return KeyClicked(Key, Scancode);
}

bool KeyTracker::operator|(Uint32 Key) {
	return KeyClicked(Key, Keycode);
}

bool KeyTracker::KeyClicked(Uint32 Key, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	return KeyClick[Key];
}

bool KeyTracker::IsPressed(Uint32 Key, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	return KeyActive[Key];
}

Uint32 KeyTracker::TimeSinceLastPress(Uint32 Key, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	if(KeyRepeating[Key]) {
		return KeyPressLength[Key]-KeyRepeatList[Key].Delay;
	}
	else {
		return KeyPressLength[Key];
	}
}

void KeyTracker::SetRepeat(Uint32 Key, KeyRepeat RepeatInfo, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	KeyRepeatList[Key] = RepeatInfo;
}

KeyRepeat KeyTracker::GetRepeat(Uint32 Key, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	return KeyRepeatList[Key];
}

bool KeyTracker::IsRepeating(Uint32 Key, Uint8 ScanOrKey/*=Scancode*/) {
	if(ScanOrKey == Keycode) {
		Key = SDL_GetScancodeFromKey(Key);
	}
	return KeyRepeating[Key];
}

void KeyTracker::Update(Uint32 Time) {
	for(Uint16 i=0; i < AmountOfKeys; i++) {
		if(KeyActive[i]) {
			KeyPressLength[i] += Time;
			if(KeyPressLength[i] > KeyRepeatList[i].Delay && KeyRepeatList[i].Delay != 0 && KeyRepeatList[i].Repeat != 0) {
				KeyRepeating[i] = true;
				KeyClick[i] = true;
				KeyPressLength[i] -= KeyRepeatList[i].Repeat;
			}
			else {
				KeyClick[i] = false;
			}
		}
	}
}

void KeyTracker::UpdateKey(SDL_Event *Key) {
	if(Key->type == SDL_KEYDOWN) {
		if(!Key->key.repeat) {
			KeyActive[Key->key.keysym.scancode] = true;
			KeyClick[Key->key.keysym.scancode] = true;
		}
	}
	else if(Key->type == SDL_KEYUP) {
		KeyActive[Key->key.keysym.scancode] = false;
		KeyClick[Key->key.keysym.scancode] = false;
		KeyRepeating[Key->key.keysym.scancode] = false;
		KeyPressLength[Key->key.keysym.scancode] = 0;
	}
}