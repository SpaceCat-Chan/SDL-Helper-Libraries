# SDL-Helper-Libraries


## Image
a class that handles varios image loading and drawing, cleans up after itself too

supports: 
* loading images of varios types
* loading text into an image
* automatic image cleanup

dependancies:
* SDL2
* SDL2_image
* SDL2_ttf


## KeyTracker
a class that keeps track almost everything related to the keyboard

example use:

	SDL_Event Event_Handler;
	KeyTracker Keyboard;
    Uint32 LastTime = SDL_GetTicks();
  
	while(!quit) {
		Uint32 Temp, Time;
		Temp = SDL_GetTicks();
		Time = Temp - LastTime;
		LastTime = Temp;

		Keyboard.Update(Time);

		while(SDL_PollEvent(&Event_Handler)) {
			Keyboard.UpdateKey(&Event_Handler);
		}
    
    	if(Keyboard[SDL_SCANCODE_UP]) {
    		std::cout << "you pressed the up button\n";
		}
	}

dependancies:
* SDL2


## sfstream
a small wrapper on SDL_RWops that allows you to use it like an iostream

supports:
* almost everything that fstream supports

dependancies:
* SDL2
