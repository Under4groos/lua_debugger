

#define LUA_INTEGER long
#define LUA_NUMBER double

#include "include.h"
#include "Console.h";

#define LUA_ERROR 1

extern "C" int test(lua_State * L) {
	size_t* size{};
	const char* name = lua_tolstring(L, 1, size);
	cout << name << endl;

	lua_pushboolean(L, true);

	return 1;
}

int ___GetDesktopWindow = (int)GetDesktopWindow();

extern "C" int _GetDesktopWindow(lua_State * L) {
	
	
	lua_pushnumber(L, ___GetDesktopWindow);

	return 1;
}

extern "C" int _FindWindowEx(lua_State * L) {

	int hWndParent = lua_tointeger(L, 1);
	int hWndChildAfter = lua_tointeger(L, 2);
	const char* lpszClass = lua_tostring(L, 3);
	const char* lpszWindow = lua_tostring(L, 4);

	int hwnd_ = (int)FindWindowEx((HWND)hWndParent , (HWND)hWndChildAfter , (LPCWCHAR) lpszClass , (LPCWCHAR)lpszWindow);
	lua_pushnumber(L, hwnd_);

	return 1;
}







int i_ = 0;
KEY_EVENT_RECORD key;
lua_State* lua;
const char* _luafile = "main.lua";
char fullPath[MAX_PATH];
int main(const char* args) {


	cout << ___GetDesktopWindow << endl;
	
	while (true)
	{

		lua = luaL_newstate();

		
		luaL_openlibs(lua);
		lua_register(lua, "_GetDesktopWindow", _GetDesktopWindow);
		lua_register(lua, "test", test);
		lua_register(lua, "_FindWindowEx", _FindWindowEx);
		
		if (GetFullPathNameA(_luafile, MAX_PATH, fullPath, NULL)) {	
			 
			cout << fullPath << endl;

			int error = luaL_dofile(lua, fullPath);
			if(error == LUA_ERROR)
				cout << error << endl;

		}
		else {
			DWORD errCode = GetLastError();
			std::cerr << "Error " << errCode << " occurred." << std::endl;
		}
		

		lua_close(lua);

		Console::getconchar( key);
		 
	}
	

	return 0;
}