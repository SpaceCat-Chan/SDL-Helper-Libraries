#include "Image.hpp"

void Image::Free() {
	ImageFile.reset();
	Width = 0;
	Height = 0;
}

Image::Image() {
	Height = 0;
	Width = 0;
	ImageFile = nullptr;
}

Image::Image(Image &CopyImage) {
	Height = CopyImage.Height;
	Width = CopyImage.Width;
	ImageFile = CopyImage.ImageFile;
}

Image::Image(const Image &CopyImage) {
	Height = CopyImage.Height;
	Width = CopyImage.Width;
	ImageFile = CopyImage.ImageFile;
}

Image::~Image() {
	Free();
}

Image &Image::operator=(Image &CopyImage) {
	Width = CopyImage.Width;
	Height = CopyImage.Height;
	ImageFile = CopyImage.ImageFile;
	return *this;
}

Image &Image::operator=(const Image &CopyImage) {
	Width = CopyImage.Width;
	Height = CopyImage.Height;
	ImageFile = CopyImage.ImageFile;
	return *this;
}

Image &Image::operator=(Image &&CopyImage) {
	Width = CopyImage.Width;
	Height = CopyImage.Height;
	ImageFile = std::move(CopyImage.ImageFile);
	return *this;
}


bool Image::LoadImage(std::string Path, SDL_Renderer* Render) {
	ProfileFunction();

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
			ImageFile = std::shared_ptr<SDL_Texture>(OptimizedTemp, [](SDL_Texture *ptr) {SDL_DestroyTexture(ptr);});
			SDL_FreeSurface(TempImage);
			return true;
		}
	}
}

bool Image::LoadFromText(std::string Text, TTF_Font *Font, SDL_Renderer* Render, SDL_Color Color) {
	ProfileFunction();

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
			ImageFile = std::shared_ptr<SDL_Texture>(OptimizedTemp, [](SDL_Texture *ptr) {SDL_DestroyTexture(ptr);});
			SDL_FreeSurface(TempImage);
			return true;
		}
	}
}

bool Image::LoadFromText(std::string Text, Font& FontToUse, SDL_Renderer* Render, SDL_Color Color) {
	LoadFromText(Text, FontToUse.Get(), Render, Color);
}

void Image::Draw(int x, int y, SDL_Renderer* Render, SDL_Rect DST_Quad, SDL_Rect* clip, double Angle, SDL_Point* Center, SDL_RendererFlip Flip) {
	#ifdef DeepDebug
	ProfileFunction();
	#endif
	//Set rendering space and render to screen
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
	SDL_RenderCopyEx( Render, ImageFile.get(), clip, &renderQuad, Angle, Center, Flip );
}

void Image::SetColor(long r, long g, long b) {
	SDL_SetTextureColorMod(ImageFile.get(), r, g, b);
}

void Image::SetAlpha(long a) {
	SDL_SetTextureAlphaMod(ImageFile.get(), a);
}

void Image::SetBlendMode(SDL_BlendMode BlendMode) {
	SDL_SetTextureBlendMode(ImageFile.get(), BlendMode);
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

bool Image::operator==(const Image &rhs) const {
	return rhs.Width == Width && Height == rhs.Height && ImageFile == rhs.ImageFile;
}
bool Image::operator!=(const Image &rhs) const {
	return !(rhs.Width == Width && Height == rhs.Height && ImageFile == rhs.ImageFile);
}
