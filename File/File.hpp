#ifndef FILE_HPP

#define FILE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_filesystem.h>

#include <string>

namespace FileModes{
	enum wawawa {
		Read=1,
		Write=2,
		Append=4,
		Binary=8,
		OverLoad=16,
	};
}

class File {
	SDL_RWops *CurrentFile=nullptr;
	std::string CurrentError="";
	public:
	
	File();

	~File();

	bool OpenFile(std::string FileName, int Mode, void *StanderdInfo=nullptr, int AmountOfInfo=0, int InfoSize=0);

	bool CloseFile();

	bool MoveLocation(Sint64 Offset, int Whence);

	bool Read(void* ReadTo, int Size, int Amount);

	bool Write(void* WriteFrom, int Size, int Amount);

	std::string GetError();
};

#ifndef FILE_CPP

#define OpenFile(FileName, Mode, StanderdInfo, AmountOfInfo, InfoSize) OpenFile(FileName, Mode, StanderdInfo, AmountOfInfo, sizeof(InfoSize))
#define Read(ReadTo, Size, Amount) Read(ReadTo, sizeof(Size), Amount)
#define Write(WriteFrom, Size, Amount) Write(WriteFrom, sizeof(Size), Amount)

#endif

#endif