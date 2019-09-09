#define FILE_CPP
#include "File.hpp"

File::File() {

}

File::~File() {
	if(CurrentFile) {
		SDL_RWclose(CurrentFile);
		CurrentFile = nullptr;
	}
}

bool File::OpenFile(std::string FileName, int Mode, void *StanderdInfo, int AmountOfInfo, int InfoSize) {
	std::string OpenMode;
	if(Mode & FileModes::Read) {
		OpenMode += 'r';
	}
	else if(Mode & FileModes::Write) {
		OpenMode += 'w';
	}
	else {
		OpenMode += 'a';
	}

	if(Mode & FileModes::Binary) {
		OpenMode += 'b';
	}
	if(Mode & FileModes::OverLoad) {
		OpenMode += '+';
	}

	CurrentFile = SDL_RWFromFile(FileName.c_str(), OpenMode.c_str());
	if(CurrentFile == nullptr) {
		if(AmountOfInfo == 0 && !(Mode & (FileModes::Write | FileModes::Append))) {
			CurrentError = SDL_GetError();
			return false;
		}

		std::string ErrorMode="w";
		if(Mode & FileModes::Binary) {
			ErrorMode += 'b';
		}
		ErrorMode += '+';

		CurrentFile = SDL_RWFromFile(FileName.c_str(), ErrorMode.c_str());
		if(CurrentFile == nullptr) {
			CurrentError = SDL_GetError();
			return false;
		}

		int AmountWritten=0;
		AmountWritten = SDL_RWwrite(CurrentFile, StanderdInfo, InfoSize , AmountOfInfo);
		if(AmountWritten < AmountOfInfo) {
			SDL_RWclose(CurrentFile);
			CurrentFile = nullptr;
			CurrentError = SDL_GetError();
			return false;
		}
		if(SDL_RWclose(CurrentFile) < 0) {
			CurrentFile = nullptr;
			CurrentError = SDL_GetError();
			return false;
		}
		CurrentFile = SDL_RWFromFile(FileName.c_str(), OpenMode.c_str());
		if(CurrentFile == nullptr) {
			CurrentFile = nullptr;
			CurrentError = SDL_GetError();
			return false;
		}
	}
	return true;
}

bool File::CloseFile() {
	if(CurrentFile != nullptr) {
		if(!SDL_RWclose(CurrentFile)) {
			CurrentError = SDL_GetError();
			CurrentFile = nullptr;
			return false;
		}
	}
	return true;
}

bool File::MoveLocation(Sint64 Offset, int Whence) {
	SDL_RWseek(CurrentFile, Offset, Whence);
}

bool File::Read(void *ReadTo, int Size, int Amount) {
	if(CurrentFile) {
		if(SDL_RWread(CurrentFile, ReadTo, Size, Amount) < Amount) {
			CurrentError = SDL_GetError();
			return false;
		}
		return true;
	}
	else {
		CurrentError = "No file to read from";
		return false;
	}
	return true;
}

bool File::Write(void *WriteFrom, int Size, int Amount) {
	if(CurrentFile) {
		if(SDL_RWwrite(CurrentFile, WriteFrom, Size, Amount) < Amount) {
			CurrentError = SDL_GetError();
			return false;
		}
		return true;
	}
	else {
		CurrentError = "No file to write to";
		return false;
	}
}

std::string File::GetError() {
	return CurrentError;
}