#pragma once
extern HANDLE g_screenBuffer[2];
extern short g_bufferIndex;

/////////////
// LINKING //
/////////////
#pragma comment(lib, "vfw32.lib")
//#pragma comment(lib, "fmod_vc.lib")

//////////////
// INCLUDES //
//////////////
#include<Vfw.h>
#include<string>
#include<conio.h>
#include<cstring>
#include<vector>
#include<list>
#include<ctime>
#include<cstdlib>

using namespace std;

///////////////
//   SOUND   //
///////////////
//#include"inc/fmod.hpp"

//using namespace FMOD;