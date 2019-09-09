#ifndef Image_HPP
#define Image_HPP

#ifdef PCSet
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif
#include <iostream>

class Image {
	SDL_Texture* ImageFile;
	int Width, Height;
	public:
	void Free();

	Image();

	~Image();

	/*
	Loads and image
	*/
	bool LoadImage(std::string Path, SDL_Renderer* Render);

	/*
	creates and load an image using text

	Text: a string, the text that should be loaded
	Font: a pointer to the font that should be used
	Render: a render, needed for optimisation
	Color: the color that should be used

	Return: whether or not the function was successful
	*/
	bool LoadFromText(std::string Text, TTF_Font *Font, SDL_Renderer* Render, SDL_Color Color);

	void Draw(int x, int y, SDL_Renderer* Render, SDL_Rect DST_Quad={0,0,100,100}, SDL_Rect* clip = nullptr, double Angle = 0.0, SDL_Point* Center = nullptr, SDL_RendererFlip Flip = SDL_FLIP_NONE);

	void SetColor(long r, long g, long b);

	void SetAlpha(long a);
	
	void SetBlendMode(SDL_BlendMode BlendMode);

	SDL_Rect GetSize();

	bool InsideImage(int DrawX, int DrawY, int CheckX, int CheckY);
};

#endif