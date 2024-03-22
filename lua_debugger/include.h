#pragma once
#include <iostream>
#include <windows.h>
 
#pragma comment(lib , "lua5.1.lib")
#pragma comment(lib , "lua51.lib")
extern "C" {
#include "Lua/include/lua.h"
#include "Lua/include/lualib.h"
#include "Lua/include/lauxlib.h"

}
 
#include <fstream>
#include <cstdio>
#include "Console.h";


using namespace std;