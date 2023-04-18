#pragma once

#include <string>
#include "targetver.h"
#include "CMath.h"
#include "ft2build.h"
#include FT_FREETYPE_H

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef ANDROID	
#include <stdio.h>
#include <tchar.h>
#endif

// define game debug  -------------------	1: yes	0: no
#define GAME_DEBUG 1

class Globals
{
public:
	static int Globals::screenWidth;
	static int Globals::screenHeight;
	static int Globals::scale;
};

//class GS_Menu
#define MN_bgWidth 1422
#define MN_bgHeight 800
#define MN_deltaX 822
//class GameBoard:
#define GB_frameWidth 360
#define GB_frameHeight 360
#define GB_width 320
#define GB_height 320
#define GB_posX 140
#define GB_posY 100

//class Piece
#define Pi_size 40

//class StatusBar
#define SB_posX 20
#define SB_posY 700
#define SB_width 240
#define SB_height 80
#define SB_maxBarWidth 135
#define SB_barHeight 10
#define SB_posXOfBar (int)SB_posX+5*SB_width/16
#define SB_posYOfHpBar (int)SB_posY+4*SB_height/20 
#define SB_posYOfManaBar (int)SB_posY+9*SB_height/20 
#define SB_effectSize 30

//class GameField
#define GF_posXOfPlayer 100
#define GF_posYOfPlayer 550
#define GF_playerWidth 200
#define GF_playerHeight 200

//class PauseMenu
#define PM_width 150
#define PM_height 150


// define value
#define PI 3.14f
#define MAX_DEGREE 360
// define vetex 
#define VETEX_POSITION		(char*)0
#define VETEX_NORM			(char*)0+(sizeof(Vector3))
#define VETEX_BITTANGEN		(char*)0+2*(sizeof(Vector3))
#define VETEX_TANGEN		(char*)0+3*(sizeof(Vector3))
#define VETEX_UV			(char*)0+4*(sizeof(Vector3))

// define type of Models
#define NONE	111 
#define RAW		222 
#define NFG		333

#ifdef WIN32

#define FSCANF fscanf

#elif ANDROID

#define FSCANF fscanf

#endif

// for debug game

#ifdef WIN32 

#define LOGI(...) printf(__VA_ARGS__);
#define LOGE(...) printf(__VA_ARGS__);
#define LOGV(...) printf(__VA_ARGS__);
#define LOGD(...) printf(__VA_ARGS__);
#define LOGW(...) printf(__VA_ARGS__);
#define LOGF(...) printf(__VA_ARGS__);

#elif ANDROID

#include <android/log.h>
#define  LOG_TAG    "GAME"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)

#endif

#ifndef GAME_DEBUG
#define LOGI(...)
#define LOGE(...)
#define LOGV(...)
#define LOGD(...)
#define LOGW(...)
#define LOGF(...)
#endif

// KEY define 
#ifdef WIN32

#define KEY_BACK			VK_ESCAPE
#define KEY_LEFT			VK_LEFT
#define KEY_RIGHT			VK_RIGHT
#define KEY_UP				VK_UP
#define KEY_DOWN			VK_DOWN
#define KEY_MOVE_LEFT		'A'
#define KEY_MOVE_RIGHT		'D'
#define KEY_MOVE_FORWARD	'W'
#define KEY_MOVE_BACKWARD	'S'

#endif
