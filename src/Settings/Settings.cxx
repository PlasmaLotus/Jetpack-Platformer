#include "Settings.h"


Settings::Settings(){
}

Settings::~Settings(){
}

void Settings::parseArgs(int args, char** argv){
	//Parse config file
	//config.ini


}
void Settings::logSystenInformation(SDL_Window* window){
	//SDL_Window* window;
  SDL_SysWMinfo info;
	LPDWORD  _pid = 0;
	DWORD dword = 0;
  //SDL_Init(0);
	
  //window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
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

  //SDL_DestroyWindow(window);
  //SDL_Quit();
}
Settings& Settings::getInstance(){
	static Settings instance;
	return instance;
	/*
	if (!instance){
		instance = new Settings;
	}

	return instance;
	*/
}

namespace Utility {

	const char* boolToChar(const bool b, Utility::Typeface flag = Utility::Typeface::Default){
		const char* whatAmIEvenDoingWithMyLife = nullptr;
		if(b){
			switch(flag){
			case Utility::Typeface::AllCap:{
				whatAmIEvenDoingWithMyLife = "TRUE";
							}
			case Utility::Typeface::Minuscule:{
				whatAmIEvenDoingWithMyLife = "true";
							}
			case Utility::Typeface::FirstLetterCap:
			case Utility::Typeface::Default:
			default:{
				whatAmIEvenDoingWithMyLife = "True";
							}
			}//sw
		}
		else
		{
			switch(flag){
			case Utility::Typeface::AllCap:{
				whatAmIEvenDoingWithMyLife = "FALSE";
							}
			case Utility::Typeface::Minuscule:{
				whatAmIEvenDoingWithMyLife = "false";
							}
			case Utility::Typeface::FirstLetterCap:
			case Utility::Typeface::Default:
			default:{
				whatAmIEvenDoingWithMyLife = "False";
							}
			}//sw
		}
		return whatAmIEvenDoingWithMyLife;
	}

}// namespace Utility