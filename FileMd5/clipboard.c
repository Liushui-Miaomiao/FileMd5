#include <string.h>
#include <Windows.h>

#include "clipboard.h"

static BOOL CleanClipboard(void);

BOOL WriteClipboard(char* data) {
	if (!CleanClipboard()) {
		return FALSE;
	}

	HGLOBAL hMen;
	hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(data) + 1) * sizeof(TCHAR)));

	if (!hMen) {
		CloseClipboard();
		return FALSE;
	}

	//Locked memory.
	LPSTR lpStr = (LPSTR)GlobalLock(hMen);
	if (!lpStr) {
		return FALSE;
	}
	memcpy(lpStr, data, ((strlen(data)) * sizeof(TCHAR)));
	lpStr[strlen(data)] = (TCHAR)0;

	//Unlocked memory.
	GlobalUnlock(hMen);
	SetClipboardData(CF_TEXT, hMen);
	CloseClipboard();

	return TRUE;
}

static BOOL CleanClipboard(void) {
	return OpenClipboard(NULL) && EmptyClipboard();
}