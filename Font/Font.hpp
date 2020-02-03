#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

class Font final {
	std::string m_Fontname = "";
	size_t m_Fontsize = 0;
	TTF_Font *m_Font = nullptr;

	public:
	Font() = default;
	Font(const std::string &Fontname, size_t Fontsize);
	~Font();

	Font(const Font& Copy);
	Font(Font&& Move);

	const Font& operator=(const Font& Copy);
	const Font& operator=(Font&& Move);

	void open(const std::string &Fontname, size_t Fontsize);
	void close();

	TTF_Font *operator*() {return m_Font;}

	TTF_Font *get() { return m_Font; } //for interchangability with smart ptrs
	TTF_Font *Get() { return m_Font; } //for interchangability with my style
	std::string GetName() const { return m_Fontname; }
	size_t GetSize() const { return m_Fontsize; }
};
