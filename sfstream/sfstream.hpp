#pragma once

#include <istream>
#include <string>
#include <ostream>
#include <ios>
#include <iostream>

#include <SDL.h>

class sfbuf : public std::streambuf {
	static constexpr std::size_t BufferSize=256;

	protected:
	SDL_RWops *m_File=nullptr;
	char *m_IBuffer=nullptr;
	char *m_OBuffer=nullptr;

	int_type sync() override;
	int_type overflow(int_type c) override;
	int_type underflow() override;
	std::streampos seekoff(std::streamoff off, std::ios::seekdir way, std::ios::openmode which=std::ios::in | std::ios::out) override;
	std::streampos seekpos(std::streampos pos, std::ios::openmode which=std::ios::in | std::ios::out) override;

	public:
	sfbuf() = default;
	sfbuf(SDL_RWops *File);
	sfbuf(std::string Filename, std::string FileOptions);
	~sfbuf() noexcept override;
	
	void open(SDL_RWops *File);
	void open(std::string Filename, std::string FileOptions);

};

class isfstream : private sfbuf, public std::istream {
	public:
	isfstream() = default;
	explicit isfstream(SDL_RWops *File);
	explicit isfstream(std::string Filename, std::string FileOptions);
	void open(SDL_RWops *File);
	void open(std::string Filename, std::string FileOptions);
};
class osfstream : private sfbuf, public std::ostream {
	public:
	isfstream() = default;
	explicit isfstream(SDL_RWops *File);
	explicit isfstream(std::string Filename, std::string FileOptions);
	void open(SDL_RWops *File);
	void open(std::string Filename, std::string FileOptions);
};