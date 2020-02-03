#include "Font.hpp"

Font::Font(const std::string &Fontname, size_t Fontsize) {
	open(Fontname, Fontsize);
}

Font::~Font() {
	close();
}

Font::Font(const Font &Copy) : m_Fontname(Copy.m_Fontname), m_Fontsize(Copy.m_Fontsize) {
	m_Font = TTF_OpenFont(m_Fontname.c_str(), m_Fontsize);
}

void Font::open(const std::string &Fontname, size_t Fontsize) {
	m_Fontname = Fontname;
	m_Fontsize = Fontsize;
	m_Font = TTF_OpenFont(Fontname.c_str(), Fontsize);
}

void Font::close() {
	if(!m_Font) return;
	TTF_CloseFont(m_Font);
	m_Font = nullptr;
}

Font::Font(const Font& Copy) {
	close();
	open(Copy.m_Fontname, Copy.m_Fontsize);
}

Font::Font(Font&& Move) {
	close();
	m_Font = std::move(Move.m_Font);
}

const Font& Font::operator=(const Font& Copy) {
	close();
	open(Copy.m_Fontname, Copy.m_Fontsize);

	return *this;
}

const Font& Font::operator=(Font&& Move) {
	close();
	m_Font = std::move(Move.m_Font);

	return *this;
}