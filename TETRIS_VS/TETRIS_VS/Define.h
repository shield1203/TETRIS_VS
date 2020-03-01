#pragma once
extern HANDLE g_screenBuffer[2];
extern short g_bufferIndex;

#define PORT_NUM 21524
#define MAX_MSG_LEN 2937
#define MAX_DATA_LEN 2929 // 테트리스에서 최대 블록 개수일 때 데이터크기
#define SERVER_IP "203.232.193.170" // 연구실 내 컴자리

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