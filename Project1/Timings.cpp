#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <conio.h>
#include <sstream>

using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_TICKS_PER_FRAME = 1000 / 60;
const int vel = 10;

class TimerClass {
private :
	Uint32 starttime;
	Uint32 pausedticks;
	bool started, paused;

public:
	TimerClass();
	void start();
	void pause();
	void unpause();
	void stop();
	bool iststarted();
	bool ispaused();
 
	Uint32 getticks();
}timer;

class sprite{
private:
	int posx;
	int posy;
	int velx;
	int vely;
public:
	sprite();
	void move(SDL_Event &e);
	void rmove(SDL_Event &e);
	void show(SDL_Renderer *r);
};
sprite::sprite() {
	posx = SCREEN_WIDTH / 2;
	posy = SCREEN_HEIGHT / 2;
	velx = 0;
	vely = 0;
}

void sprite::move(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: posy -= vel;
			break;
		case SDLK_DOWN:posy += vel;
			break;
		case SDLK_RIGHT:posx += vel;
			break;
		case SDLK_LEFT:posx -= vel;
			break;
		}
	}
}

void sprite::rmove(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: posy -= vel;
			break;
		case SDLK_DOWN:posy += vel;
			break;
		case SDLK_RIGHT:posx += vel;
			break;
		case SDLK_LEFT:posx -= vel;
			break;
		}
	}
}

void sprite::show(SDL_Renderer *r) {
	if (r != NULL) {
		SDL_SetRenderDrawColor(r, 201, 210, 32, 32);
		SDL_Rect r1;
		r1.x = posx;
		r1.y = posy;
		r1.w = 10;
		r1.h = 10;
		SDL_RenderDrawRect(r,&r1);

	}
}

class ltexture {
private:
	SDL_Texture* mtexture,*ntexture;
	SDL_Surface * screen;
	SDL_Surface * screen1;
	SDL_Window * window;
	SDL_Renderer * grender;
	TTF_Font * fnew;
	bool running;
	SDL_Event e;
	Uint32 timetext;
	stringstream text;
	SDL_Surface * update;
	int mwidth, mheight;
	int mousex, mousey;
	SDL_Color c;
	SDL_Rect rect1;
	SDL_Rect rect2;
	
	//	TTF_Font * gfont;
public:
	ltexture();
	void init();
	void loadmedia();
	void move();
	bool loadtext(string, SDL_Color);

	~ltexture();
};

ltexture::ltexture() {

	window = NULL;
	fnew = NULL;
	mtexture = NULL;
	ntexture = NULL;
	screen = NULL;
	screen1 = NULL;
	grender = NULL;
	running = false;
	mwidth = 0;
	mheight = 0;
	mousex = 0;
	mousey = 0;
	//	gfont = NULL;
	init();
	loadmedia();
}

bool ltexture::loadtext(string ch, SDL_Color col)
{
	SDL_Surface * s = TTF_RenderText_Solid(fnew,ch.c_str(),col);
	ntexture = SDL_CreateTextureFromSurface(grender, s);
	if (ntexture == NULL)
	{
		cout << SDL_GetError();
	}

	SDL_FreeSurface(s);
	return ntexture != NULL;
}


void ltexture::init()
{
	bool f1 = true, f2 = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "The SDl could not be initialised " << SDL_GetError();
	}
	window = SDL_CreateWindow("Brayan In Forest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		f1 = false;

	if (TTF_Init() < 0)
	{
		cout << TTF_GetError();
	}
}

ltexture :: ~ltexture()
{

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void ltexture::loadmedia() {

	grender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (SDL_SetRenderDrawColor(grender, 234, 34, 56, 98) < 0)
	{
		cout << "Color could not be loaded into the renderer";
	}

	if (grender == NULL)
	{
		cout << "Renderer could not be created";
	}
	
	screen = IMG_Load("background.jpg");
	fnew = TTF_OpenFont("text2.ttf",28);
	 c = {23,46,92,42};
	
	
	
	if (screen == NULL)
	{
		cout << "image could not be loaded";
	}

	SDL_SetColorKey(screen, SDL_TRUE, SDL_MapRGB(screen->format, 0, 255, 255));
	mtexture = SDL_CreateTextureFromSurface(grender, screen);

	loadtext("Once upon a time bryan was in forest", c);

	move();
    
}


void ltexture::move() {

	//	SDL_LockSurface(screen);
	TimerClass t;
	SDL_SetRenderDrawColor(grender, 210, 190, 180, 150);
	bool inside = true;
	int countedFrame = 0;
	sprite s1;
	rect1.x = SCREEN_WIDTH / 2;
	rect1.y = SCREEN_HEIGHT / 2;
	rect1.h = 20;
	rect1.w = 10;
	SDL_Rect  srect;
	srect.x = 0;
	srect.y = 0;
	srect.w = 640;
	srect.h = 50;
	float avg;

	timer.start();
	while (!running)
	{
		t.start();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = true;
			}

			/*if (e.type = SDL_KEYDOWN)
			{
				
				if (e.key.keysym.sym == SDLK_s)
				{
					if (timer.iststarted())
					{
						timer.stop();
					}
					else
					{
						timer.start();
					}
				}
				if (e.key.keysym.sym == SDLK_p)
				{
					if (timer.ispaused())
					{
						timer.unpause();
					}
					else
					{
						timer.pause();
					}
				}

			}*/
			if (e.key.repeat != 0)
				s1.move(e);
			else if (e.key.repeat == 0)
				s1.rmove(e);

			

			avg = countedFrame / (timer.getticks() / 1000.f);
			
			if (avg > 2000000)
			{
				avg = 0;
			}
			text.str("");
			text << "Frames Per Second" << avg<<" fps ";
			loadtext(text.str().c_str(), c);
			
				
		}
	    
		SDL_RenderClear(grender);
		
		SDL_RenderCopy(grender, mtexture, NULL, NULL);
		SDL_RenderCopy(grender, ntexture, NULL, &srect);
		s1.show(grender);
		SDL_RenderPresent(grender);
		++countedFrame;

		int frameticks = t.getticks();
		if (frameticks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameticks);
		}

	
	}


}

int main(int argv, char ** args)
{
	try {
		ltexture l;
	}
	catch (exception e)
	{
	}
	return 0;
}











/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Scene textures
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("22_timing/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		//Load prompt texture
		if (!gPromptTextTexture.loadFromRenderedText("Press Enter to Reset Start Time.", textColor))
		{
			printf("Unable to render prompt texture!\n");
			success = false;
		}
	}

	return success;
}

void close()
{
	//Free loaded images
	gTimeTextTexture.free();
	gPromptTextTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			//Current time start time
			Uint32 startTime = 0;

			//In memory text stream
			std::stringstream timeText;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Reset start time on return keypress
					else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
					{
						startTime = SDL_GetTicks();
					}
				}

				//Set text to be rendered
				timeText.str("");
				timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;

				//Render text
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
				{
					printf("Unable to render time texture!\n");
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render textures
				gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, 0);
				gTimeTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 2);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}*/

TimerClass::TimerClass()
{
	started = true;
	paused = false;
	starttime = 0;
	pausedticks = 0;
}

void TimerClass::start()
{
	started = true;
	paused = false;
	starttime = SDL_GetTicks();
	pausedticks = 0;
}

void TimerClass::pause()
{
	if (started == true && paused == false)
	{
		paused = true;
		pausedticks = SDL_GetTicks() - starttime;
		starttime = 0;
	}
}

void TimerClass::unpause()
{
	if (started == true && paused == true) {
		paused = false;
		starttime = SDL_GetTicks() - pausedticks;
		pausedticks = 0;
	}
}

void TimerClass::stop()
{
	paused = false;
	started = false;
	starttime = 0;
	pausedticks = 0;
}

bool TimerClass::iststarted()
{
	return started;
}

bool TimerClass::ispaused()
{
	return (started&&paused);
}

Uint32 TimerClass::getticks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = pausedticks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - starttime;
		}
	}

	return time;
}