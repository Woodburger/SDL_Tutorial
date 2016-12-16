//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>


//Key press surfaces constants
enum KeyPressSurfaces {
	
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL

};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

//The window we'll render to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//Start up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//Current display image
SDL_Surface* gStretchedSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

int main(int argc, char* args[]) {

	//Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	}
	else {

		//load media
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gStretchedSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			//While application is running
			while(!quit) {
				
				//Handle events on queue
				while(SDL_PollEvent (&e) != 0)
				{

					//User requests quit
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					
					//User presses a key
					else if(e.type == SDL_KEYDOWN) {
						
						//Select surfaces based on key press
						switch(e.key.keysym.sym) {
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				//Apply the image stretched
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
			
				
			
			}
		}
	}
		//Free resources and close SDL
		close();

	return 0;
}

bool init() {
	
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create Window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {

	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("stretch.bmp");
	
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load Down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	//load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}

	return success;
}

SDL_Surface* loadSurface(std::string path) {
	
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if(optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

void close() {
	
	//Deallocate Surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}