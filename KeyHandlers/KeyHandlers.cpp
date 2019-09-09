#include "KeyHandlers.hpp"

KeyHandler::KeyHandler() {
	TimeSinceHold = 0;
	AutoRepeat_Speed = 0;
	AutoRepeat_Delay = 0;
	Repeat = false;
	BeingHeld = false;
}

void KeyHandler::Press() {
	BeingHeld = true;
}

void KeyHandler::UnPress() {
	BeingHeld = false;
	TimeSinceHold = 0;
}

void KeyHandler::SetValues(long AutoRepeat_SpeedSet, long AutoRepeat_DelaySet, bool RepeatSet) {
	AutoRepeat_Speed = AutoRepeat_SpeedSet;
	AutoRepeat_Delay = AutoRepeat_DelaySet;
	Repeat = RepeatSet;
}

bool KeyHandler::Tick(long Time) {
	if(BeingHeld == true) {
		if(TimeSinceHold == 0) {
			TimeSinceHold += Time;
			return true;
		}
		else {
			TimeSinceHold += Time;
			if((TimeSinceHold > AutoRepeat_Delay) && Repeat) {
				TimeSinceHold -= AutoRepeat_Speed;
				return true;
			}
			return false;
		}
	}
	return false;
}

bool KeyHandler::IsBeingHeld() {
	return BeingHeld;
}