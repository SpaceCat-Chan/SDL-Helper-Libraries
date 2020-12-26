#include "sfstream.hpp"

void sfbuf::open(SDL_RWops *File) {
	m_File = File;
	m_IBuffer = new char[BufferSize];
	m_OBuffer = new char[BufferSize];

	setg(m_IBuffer, m_IBuffer + BufferSize, m_IBuffer + BufferSize);
	setp(m_OBuffer, m_OBuffer + BufferSize);
}

void sfbuf::open(std::string Filename, std::string FileOptions) {
	m_File = SDL_RWFromFile(Filename.c_str(), FileOptions.c_str());
	if(m_File == nullptr) {
		std::cout << "Failed to open file " << Filename << "\nSDL_Error: " << SDL_GetError() << '\n';
		return;
	}

	m_IBuffer = new char[BufferSize];
	m_OBuffer = new char[BufferSize];

	setg(m_IBuffer, m_IBuffer + BufferSize, m_IBuffer + BufferSize);
	setp(m_OBuffer, m_OBuffer + BufferSize);
}

sfbuf::sfbuf(SDL_RWops *File) {
	open(File);
}

sfbuf::sfbuf(std::string Filename, std::string FileOptions) {
	open(Filename, FileOptions);
}

sfbuf::~sfbuf() noexcept {
		sync();
		if(SDL_RWclose(m_File) == -1) {
			//i dunno, something happened
		}
		if(m_IBuffer) {
			delete[] m_IBuffer;
		}
		if(m_OBuffer) {
			delete[] m_OBuffer;
		}
	}

sfbuf::int_type sfbuf::sync() {
	if(pptr() > pbase()) {
		size_t AmountWritten = SDL_RWwrite(m_File, m_OBuffer, sizeof(char), pptr() - pbase());
		if(AmountWritten < size_t(pptr() - pbase())) {
			std::cout << "sync failed, amount written: " << AmountWritten << ", SDL_Error: " << SDL_GetError() << '\n';
			return -1;
		}
		setp(m_OBuffer, m_OBuffer + BufferSize);
	}
	return 0;
}

sfbuf::int_type sfbuf::overflow(sfbuf::int_type c) {
	sync();
	if(c != EOF) {
		*pptr() = c;
		pbump(1);
	}
	return c;
}

sfbuf::int_type sfbuf::underflow() {
	if(gptr() < egptr()) {
		return *gptr();
	}

	size_t ReadAmount = SDL_RWread(m_File, m_IBuffer, sizeof(char), BufferSize);

	if(ReadAmount == 0) {
		return EOF;
	}

	setg(m_IBuffer, m_IBuffer, m_IBuffer + ReadAmount);
	return static_cast<unsigned char>(*gptr());
}

std::streampos sfbuf::seekoff(std::streamoff off, std::ios::seekdir way, std::ios::openmode which/*=std::ios::in | std::ios::out*/) {
	int whence;
	switch(way) {
		case std::ios::beg:
			whence = RW_SEEK_SET;
			break;

		case std::ios::cur:
			whence = RW_SEEK_CUR;
			break;
		
		case std::ios::end:
			whence = RW_SEEK_END;
			break;
		
		default: break;
	}
	Sint64 pos = SDL_RWseek(m_File, off, whence);
	if(pos == -1) {
		return -1;
	}
	setg(m_IBuffer, m_IBuffer + BufferSize, m_IBuffer + BufferSize);
	setp(m_OBuffer, m_OBuffer + BufferSize);

	return pos;
}

std::streampos sfbuf::seekpos(std::streampos pos, std::ios::openmode which/*=std::ios::in | std::ios::out*/) {
	return seekoff(pos, std::ios::beg, which);
}

isfstream::isfstream(SDL_RWops *File) : sfbuf(File), std::istream(this) {}

isfstream::isfstream(std::string Filename, std::string FileOptions) : sfbuf(Filename, FileOptions), std::istream(this) {}

void isfstream::open(SDL_RWops *File) {
	sfbuf::open(File);
}
void isfstream::open(std::string Filename, std::string FileOptions) {
	sfbuf::open(Filename, FileOptions);
}


osfstream::osfstream(SDL_RWops *File) : sfbuf(File), std::ostream(this) {}
osfstream::osfstream(std::string Filename, std::string FileOptions) : sfbuf(Filename, FileOptions), std::ostream(this) {}

void osfstream::open(SDL_RWops *File) {
	sfbuf::open(File);
}
void osfstream::open(std::string Filename, std::string FileOptions) {
	sfbuf::open(Filename, FileOptions);
}


iosfstream::iosfstream(SDL_RWops *File) : sfbuf(File), std::iostream(this) {}
iosfstream::iosfstream(std::string Filename, std::string FileOptions) : sfbuf(Filename, FileOptions), std::iostream(this) {}

void iosfstream::open(SDL_RWops *File) {
	sfbuf::open(File);
}
void iosfstream::open(std::string Filename, std::string FileOptions) {
	sfbuf::open(Filename, FileOptions);
}