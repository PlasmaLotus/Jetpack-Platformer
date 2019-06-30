#ifndef _UTILITY_H
#define _UTILITY_H

#include <Windows.h>
#include <string>
namespace Utility{

void toClipboard(const std::string &s, HWND hwnd = NULL){
	if(OpenClipboard(hwnd)){
		EmptyClipboard();	
		HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
		if (!hg){
			CloseClipboard();
			return;
		}
		memcpy(GlobalLock(hg),s.c_str(),s.size()+1);

		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT,hg);
		CloseClipboard();
		//GlobalFree(hg);
	}
}

void toClipboard(const char* c, size_t size, HWND hwnd = NULL){

	if (OpenClipboard(hwnd)){
		EmptyClipboard();	
		HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,size);
		if (!hg){
			CloseClipboard();
			return;
		}
		memcpy(GlobalLock(hg),c,size);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT,hg);
		CloseClipboard();
		//GlobalFree(hg);
	}
}

//HWND hwnd = GetDesktopWindow()
std::string fromClipboard(HWND hwnd = NULL, char* c = nullptr, size_t size = 4096){

	std::string str;
	LPTSTR lptstr;
	//char* __c = new char[size + 1];
	if (OpenClipboard(hwnd)){
		if (::IsClipboardFormatAvailable(CF_TEXT)
			|| ::IsClipboardFormatAvailable(CF_OEMTEXT))
			//|| ::IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			// Retrieve the Clipboard data (specifying that 
			// we want ANSI text (via the CF_TEXT value).
			HANDLE hClipboardData = GetClipboardData(CF_TEXT);

			// Call GlobalLock so that to retrieve a pointer
			// to the data associated with the handle returned
			// from GetClipboardData.
			char *pchData = (char*)GlobalLock(hClipboardData);

			// Set a local CString variable to the data
			// and then update the dialog with the Clipboard data
			str = pchData;
			//memcpy(__c, pchData, size);
			memcpy(c, pchData, size);
			//CString strFromClipboard = pchData;
			//m_edtFromClipboard.SetWindowText(strFromClipboard);

			// Unlock the global memory.
			GlobalUnlock(hClipboardData);


		
		}
		else{
			//Log "there is no text data on the clipboard"
		}
		// Finally, when finished I simply close the Clipboard
		// which has the effect of unlocking it so that other
		// applications can examine or modify its contents.
		CloseClipboard();
	}
	else{
		//Log "Cannot opem the clipboard"
	}

	//delete[] __c;
	return str;
}

} /*End Namespace Utility*/
#endif 