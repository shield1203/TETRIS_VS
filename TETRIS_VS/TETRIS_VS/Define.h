#pragma once
extern HANDLE g_screenBuffer[2];
extern short g_bufferIndex;

#define PORT_NUM 21524
#define MAX_MSG_LEN 512
#define SERVER_IP "203.232.193.170"

/////////////
// LINKING //
/////////////
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib,"ws2_32")

//////////////
// INCLUDES //
//////////////
#include <WinSock2.h>
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
#include"inc/fmod.hpp"

using namespace FMOD;