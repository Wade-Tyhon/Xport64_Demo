
#ifndef _TITLEMANAGER_H
#define _TITLEMANAGER_H
/*
#include <assert.h>
#include <nusys.h>
#include <nualsgi_n.h>

#include "main.h"
#include "graphic.h"
#include "font.h"
#include "para.h"
*/
#include "common.h"
#include "levelDefs.h"

GameMode gameMode_Title; //formerly lvlMenu
extern void gameTitleGFX(unsigned int pendingGfx);
extern void maketitleDL(void);
extern void updateTitle(void);
extern void DrawTitle( void );
extern void InitTitle(void);



/*------------nusys-----------*/
extern u32 nuScRetraceCounter;    // The retrace counter  

/*------------main.c----------*/
extern NUContData ContTriger[];
volatile extern int stage;

/*-------gamepakrwerr.c-------*/
extern int ReadFlg;

/* view.c */
extern void MenuViewMtx( Dynamic* dynamicp );

//menu states
#define menuState_fade_BlackToBrew	0
#define menuState_wait_Brew			1	
#define menuState_fade_BrewToBlack	2
#define menuState_fade_blackToTeam 	3
#define menuState_wait_Team 		4
#define menuState_fade_teamToBlack 	5
#define menuState_fade_BlackToMenu 	6
#define menuState_wait_MenuInput 	7
#define menuState_fade_MenuToGame 	8




#endif