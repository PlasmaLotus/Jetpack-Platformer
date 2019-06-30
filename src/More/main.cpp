#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdint>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>


//Using SDL and standard IO
#include <SDL.h>
#include "SDL_syswm.h"
#include <stdio.h>


#include "TweenHandler.h"
#include "RenderWheel.h"
#include "Settings\Utility.h"

/*
int main(int argc, char** argv){

	TweenHandler tHandler(Back::easeInOut, 1.0f, false);
	Tweenable tweenable;
	//tweenable.time
	tHandler.start();
	//tHandler.update(1.f/60.0f);
	//tHandler.percent();
	printf("Frame %d: Tween at %1.3f / %1.1f, at %1.4f %\n", -1, tHandler.timePlayed(), tHandler.timeTotal(), tHandler.percent());
	
	int fps = 60;
	for (int i = 0; i <= fps; ++i){
		//if (
		tHandler.update(1.f/(fps*1.f));
		tHandler.percent();
		printf("Frame %d: Tween at %1.3f / %1.1f, at %1.4f %\n", i, tHandler.timePlayed(), tHandler.timeTotal(), tHandler.percent());
	
	}
	static char ok = 'k';
	static char dim2[25];
	char (*idk)[25] ;
	char * idk_lol[25];

	char _array[25];
	unsigned char test;
	//idk[0] = &test;
	dim2[0] = 'a';

	idk = &dim2;
	ConsumableWheel wheel;
	wheel.mColor = 0xff0000ff;
	wheel.helper();

	HWND hwnd = GetDesktopWindow();
	int size = 4096;
	char* c = new char[size];
	std::string s = Utility::fromClipboard(hwnd, c, size);
	//std::string s2 = Utility::fromClipboard();
	printf("%s\n", s.c_str());

	return 0;
}
*/

// http://www.usrsb.in/How-Old-School-C-Programmers-Process-Arguments.html
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void renderStuffInSurface(SDL_Renderer* renderer, SDL_Surface* wSurface, SDL_Texture* target){
	bool renderTargetSupported = SDL_RenderTargetSupported(renderer);
	SDL_RendererInfo rendererInfo;
	SDL_GetRendererInfo(renderer, &rendererInfo);
	bool renderTextureSupported = ((rendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == SDL_RENDERER_TARGETTEXTURE);
	SDL_Texture* ogTexture;
	if (renderer != NULL){
		ogTexture = SDL_GetRenderTarget(renderer);
	}
	else{
		ogTexture = NULL;
	}
	Uint8 r,g,b,a;
	SDL_GetRenderDrawColor(renderer, &r,&g,&b,&a);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, wSurface);
	//SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, wSurface->w, wSurface->h);
	
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Last SDL ERROR: %s", SDL_GetError());
	if (texture == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create texture: %s", SDL_GetError());
	}

	SDL_SetRenderTarget(renderer, target);
	//SDL_RenderClear( renderer );

	//Render red filled quad
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );     
	SDL_RenderFillRect(renderer, &fillRect);

	//Render green outlined quad
  SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
  SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );        
  SDL_RenderDrawRect( renderer, &outlineRect );

	
	//SDL_UpdateTexture(
	//SDL_Texture* newTexture = 
	//SDL_SetRenderTarget(renderer, texture);

	
	int renderSuccess = SDL_RenderCopy(renderer, target, NULL, NULL);
	if (renderSuccess < 0){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to render to Texture: %s", SDL_GetError());
	}
	SDL_SetRenderTarget( renderer, ogTexture );
	//SDL_RenderPresent(renderer);
	
	//SDL_RenderPresent(renderer);
	
	SDL_DestroyTexture(texture);
}


//#include <cstdint>
int main( int argc, char* args[] )
{
	int sdl_return_error;
	SDL_Color colors[256];
	int i;
  // Fill colors with color information 
  for(i=0;i<256;i++){
		colors[i].r = colors[i].g = colors[i].b = (Uint8)i;
    //colors[i].r=i;
    //colors[i].g=i;
    //colors[i].b=i;
  }
	SDL_PixelFormat *fmt;
	SDL_Color* color;
	Uint32 temp, pixel;
	Uint8 red, green, blue, alpha;
	const char* quote = "Get off my lawn!";
	printf("DB: client disconnected\n");
	fprintf(stderr, "ER: SDLNet_TCP_Recv: %s\n", quote);


	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Renderer* gRenderer = NULL;

	SDL_Texture* mainTexture = NULL;
	
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(gRenderer);
			//SDL_Surface pTexture= SDL_CreateTextureFromSurface( SDL_GetRenderer(window), screenSurface );
			SDL_Rect r;
			r.w = 100;
      r.h = 50;
			mainTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, screenSurface->w, screenSurface->h);
			SDL_SetRenderTarget(gRenderer, mainTexture);
      SDL_SetRenderDrawColor(gRenderer, 0x30, 0x30, 0x30, 0x00);
      SDL_RenderClear(gRenderer);
      SDL_RenderDrawRect(gRenderer,&r);
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0x00);
      SDL_RenderFillRect(gRenderer, &r);
      SDL_SetRenderTarget(gRenderer, NULL);
      //SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
			//SDL_RenderPresent(gRenderer);
			
			
			//Fill the surface white
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xEE, 0x00, 0xFF ) );
			//SDL_SetRenderDrawColor(gRenderer, 0xEE, 0x00, 0xFF, 0xFF);
			//SDL_RenderClear(gRenderer);
			//SDL_RenderPresent( gRenderer );
			//SDL_UpdateWindowSurface( window );
			//SDL_SetSurfaceColorMod(screenSurface, 0xEE, 0x00, 0xFF);
			renderStuffInSurface(gRenderer, screenSurface, mainTexture);


			//Update the surface
			
			//
			SDL_SetRenderTarget(gRenderer, NULL);
			SDL_RenderCopy(gRenderer, mainTexture, NULL, NULL);
			SDL_RenderPresent(gRenderer);
			//SDL_UpdateWindowSurface( window );


			//Wait two seconds
			SDL_Delay( 2000 );
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "End", "This is a message box", window);
		}
	}
	SDL_DestroyRenderer(gRenderer);
	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


/*
// variable declarations
#define MUS_PATH "boing_1.wav"
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

void my_audio_callback(void *userdata, Uint8 *stream, int len) {
	
	if (audio_len ==0)
		return;
	
	len = ( len > audio_len ? audio_len : len );
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another
	
	audio_pos += len;
	audio_len -= len;
}


int main(int argc, char* argv[]){

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
			return 1;

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music
	
	
	// Load the WAV 
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL ){
		fprintf(stderr, "Couldn't Load the Wav: %s\n", SDL_GetError());
	  return 1;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length
	
	// Open the audio device 
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}
	
	// Start playing 
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while ( audio_len > 0 ) {
		SDL_Delay(100); 
	}
	
	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

	return 0;
}
*/



//#include "SDL.h"
//Get window Information
/*
int main(int argc, char *argv[]) {
  SDL_Window* window;
  SDL_SysWMinfo info;
	LPDWORD  _pid = 0;
	DWORD dword = 0;
  SDL_Init(0);

  window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
	//window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  SDL_VERSION(&info.version); // initialize info structure with SDL version info 

  if(SDL_GetWindowWMInfo(window,&info)) { // the call returns true on success
    // success 
    const char *subsystem = "an unknown system!";
    switch(info.subsystem) {
      case SDL_SYSWM_UNKNOWN:   break;
      case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows(TM)";  break;
      case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
      case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
#endif
      case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
      case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
      case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
      case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
      case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
      case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
      case SDL_SYSWM_VIVANTE:   subsystem = "Vivante";                break;
#endif
    }
		
		//info.info.win.window
		dword = GetWindowThreadProcessId(info.info.win.window, _pid);
		//GetWindowThreadProcessId
    SDL_Log("This program is running SDL version %d.%d.%d on %s",
        (int)info.version.major,
        (int)info.version.minor,
        (int)info.version.patch,
        subsystem);
  } else {
    // call failed
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
*/


//Actual main
/*
int main(int argc, char** argv)
{
	int exitCode = 0;
	//PL::Engine* engine = new PL::Engine();

	return exitCode;
}
*/

