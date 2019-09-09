#ifndef KeyHandler_HPP
#define KeyHandler_HPP something

#include <iostream>

class KeyHandler {
	long TimeSinceHold, AutoRepeat_Speed, AutoRepeat_Delay;
	bool BeingHeld, Repeat;
	public:
	KeyHandler();

	void Press();

	void UnPress();

	void SetValues(long AutoRepeat_SpeedSet, long AutoRepeat_DelaySet, bool RepeatSet);

	bool Tick(long Time);

	bool IsBeingHeld();
};

#endif