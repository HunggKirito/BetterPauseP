#ifndef PCH_H
#define PCH_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Comdlg32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/Bindings.hpp>
// #include <cocos2d.h>
// #include <gd.h>

#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <thread>
#include <cmath>
#include <cfloat>
#include <utility>
#include <type_traits>
#include <list>
#include <deque>
#include <regex>
#include <string>
#include <iomanip>

#include <shellapi.h>
#include <consoleapi.h>
#include <commdlg.h>


#include <fmod.h>
#include <fmod.hpp>


#define RCAST(type, class) reinterpret_cast<type>(class)
#define SCAST(type, class) static_cast<type>(class)


#endif
