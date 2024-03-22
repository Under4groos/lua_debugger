


#include "include.h"

 
#include "lua_modules/m_winapi.h"
#include <string>

 

std::string _lua_data = "";
int i_ = 0;
KEY_EVENT_RECORD key;
lua_State* lua;
LPARAM _LPARAM = 0;
void add_function( const char* name , lua_CFunction f) {
	lua_register(lua, name, f);
}
std::string file_read(const char* path) {
	std::string __line;
	std::ifstream file(path);
	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			__line += line;
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}
	return __line;
}
extern "C" int RunLua(lua_State * L) {
	size_t* size{};
	const char* name = lua_tolstring(L, 1, size);
	_lua_data += "\n" + file_read(name);
	lua_pushboolean(L, true);
	return 1;
}

static void fatal(const char* message) {
	fprintf(stderr, "%s\n", message);
	 
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	HWND hNextWin;
	hNextWin = FindWindowExA(hwnd, 0, "SHELLDLL_DefView", 0);
	if (hNextWin) {
		*(HWND*)lParam = hwnd;
		return false;
	}
	return true;
}



extern "C" int _FindWindowSHELLDLLDefView(lua_State * L) {

	lua_pushnumber(L, (int)_LPARAM);

	return 1;
}


const char* _luafile = "lua/main.lua";
char fullPath[MAX_PATH];
int main(const char* args) {

	 
	 
	while (true)
	{
		_lua_data = "";
		lua = luaL_newstate();
		
		
		luaL_openlibs(lua);
		add_function("_GetDesktopWindow", _GetDesktopWindow);
		add_function("test", test);
		add_function("_FindWindowEx", _FindWindowEx);
		add_function("RunLua", RunLua);
		add_function("_FindWindowSHELLDLLDefView", _FindWindowSHELLDLLDefView);

		if (GetFullPathNameA(_luafile, MAX_PATH, fullPath, NULL)) {	
			 
			cout << "Read file: " <<  fullPath << endl;

			//_lua_data = file_read(fullPath);

			try
			{
				int error = luaL_dofile(lua, fullPath);
				if (error == 1) {
					fatal(lua_tostring(lua, -1));
				}
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
			}
		
				 
			 
		}
		else {
			DWORD errCode = GetLastError();
			std::cerr << "Error " << errCode << " occurred." << std::endl;
		}
		

		lua_close(lua);

		Console::getconchar( key);
		cout << "\n--------------\n" << endl;
	}
	

	return 0;
}