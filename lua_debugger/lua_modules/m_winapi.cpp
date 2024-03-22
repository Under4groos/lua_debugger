 
#include "../include.h"
#include "m_winapi.h"
#define LUA_ERROR 1

int ___GetDesktopWindow = (int)GetDesktopWindow();





extern "C" int test(lua_State * L) {
	size_t* size{};
	const char* name = lua_tolstring(L, 1, size);
	cout << name << endl;

	lua_pushboolean(L, true);

	return 1;
}

extern "C" int _GetDesktopWindow(lua_State * L) {


	lua_pushnumber(L, ___GetDesktopWindow);

	return 1;
}

extern "C" int _FindWindowEx(lua_State * L) {

	int hWndParent = lua_tointeger(L, 1);
 	int hWndChildAfter = lua_tointeger(L, 2);
	const char* lpszClass = lua_tostring(L, 3);
	const char* lpszWindow = lua_tostring(L, 4);


	cout << "Debug:\n  Parent: " << hWndParent << " hWndChildAfter: " << hWndChildAfter  << endl;
	cout << "  lpszClass: " <<  lpszClass  <<  endl;
	int hwnd_ = (int)FindWindowEx((HWND)hWndParent, (HWND)hWndChildAfter, lpszClass, lpszWindow);
	lua_pushnumber(L, hwnd_);

	return 1;
}


