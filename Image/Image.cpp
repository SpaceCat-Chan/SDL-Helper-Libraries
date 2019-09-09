#include "Image.hpp"

void Image::Free() {
	if(ImageFile == nullptr) {
		SDL_free(ImageFile);
		ImageFile = nullptr;
		Width = 0;
		Height = 0;
	}
}

Image::Image() {
	Height = 0;
	Width = 0;
	ImageFile = nullptr;
}

Image::~Image() {
	Free();
}

bool Image::LoadImage(std::string Path, SDL_Renderer* Render) {
	Free();
	SDL_Surface* TempImage = NULL;
	SDL_Texture* OptimizedTemp = NULL;
	TempImage = IMG_Load(Path.c_str());
	if(TempImage == NULL) {
		SDL_Log("Image could not be loaded, SDL_ERROR: %s\nPATH: %s\n",SDL_GetError(), Path.c_str());
		return false;
	}
	else {
		OptimizedTemp = SDL_CreateTextureFromSurface(Render, TempImage);
		if(OptimizedTemp == NULL) {
			SDL_Log("unable to Create Texture, SDL_ERROR: %s\nPath: %s\n", SDL_GetError(), Path.c_str());
			SDL_FreeSurface(TempImage);
			return false;
		}
		else {
			Width = TempImage->w;
			Height = TempImage->h;
			ImageFile = OptimizedTemp;
			SDL_FreeSurface(TempImage);
			return true;
		}
	}
}

bool Image::LoadFromText(std::string Text, TTF_Font *Font, SDL_Renderer* Render, SDL_Color Color) {
	Free();
	SDL_Surface* TempImage = NULL;
	SDL_Texture* OptimizedTemp = NULL;
	TempImage = TTF_RenderUTF8_Blended(Font, Text.c_str(), Color);
	if(TempImage == NULL) {
		SDL_Log("Image could not be created from text, TTF_ERROR: %s\n Text: %s\n", TTF_GetError(), Text.c_str());
		return false;
	}
	else {
		OptimizedTemp = SDL_CreateTextureFromSurface(Render, TempImage);
		if(OptimizedTemp == NULL) {
			SDL_Log("unable to Create Texture, SDL_ERROR: %s\nText: %s\n", SDL_GetError(), Text.c_str());
			SDL_FreeSurface(TempImage);
			return false;
		}
		else {
			Width = TempImage->w;
			Height = TempImage->h;
			ImageFile = OptimizedTemp;
			SDL_FreeSurface(TempImage);
			return true;
		}
	}
}

void Image::Draw(int x, int y, SDL_Renderer* Render, SDL_Rect DST_Quad, SDL_Rect* clip, double Angle, SDL_Point* Center, SDL_RendererFlip Flip) {
	//Set rendering space and render to screen
	if(this) {
		SDL_Rect renderQuad = { x, y, Width, Height };

		//Set clip rendering dimensions
		if( clip != NULL )
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		renderQuad.w *= DST_Quad.w / 100.0;
		renderQuad.h *= DST_Quad.h / 100.0;

		//Render to screen
		SDL_RenderCopyEx( Render, ImageFile, clip, &renderQuad, Angle, Center, Flip );
	}
	else {
		SDL_Log("ERROR, this = nullptr, unable to draw\n");
	}
}

void Image::SetColor(long r, long g, long b) {
	SDL_SetTextureColorMod(ImageFile, r, g, b);
}

void Image::SetAlpha(long a) {
	SDL_SetTextureAlphaMod(ImageFile, a);
}

void Image::SetBlendMode(SDL_BlendMode BlendMode) {
	SDL_SetTextureBlendMode(ImageFile, BlendMode);
}

SDL_Rect Image::GetSize() {
	SDL_Rect Return;
	Return.w = Width;
	Return.h = Height;
	return Return;
}

bool Image::InsideImage(int DrawX, int DrawY, int CheckX, int CheckY) {
	return CheckX > DrawX && CheckX < DrawX + Width && CheckY > DrawY && CheckY < DrawY + Height;
}