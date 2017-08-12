#include <SDL.h>
#include <iostream>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char ** argv)
{
	   //game code eventually goes here
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << " error" << SDL_GetError();
	}
	window = SDL_CreateWindow("deepak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == NULL)
	{
		cout << "Error" << SDL_GetError();
	}
	else
	{
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xAF, 0XAF, 0));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(2000);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}