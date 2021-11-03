#ifndef _LEVELDEFS_H
#define _LEVELDEFS_H

typedef enum LEVELS_t
{
	MODE_TITLE = 0u, //formerly MODE_MAINMENU
	MODE_MAIN, //formerly LEVEL_00
    LEVEL_01,
    LVLS_SIZE
}LEVELS;

//for declaring the current game mode such as title screen, main game, pause menu, etc
typedef struct
{
    void (*levelInit)(void);
    void (*levelGfx)(unsigned int pendingGfx);
}GameMode;

typedef struct
{	//stores scene data
	EnvObject *sceneEnvObjects;	
}SceneObject;

typedef struct
{	//stores level data
	SceneObject *regionScenes; //pointer to a collection of scenes	
}RegionObject;




typedef struct
{
	u8 currentlyActive;
    void (*sceneInit)(void);
    void (*sceneRender)(void);
	void (*enemiesRender)(void);
	void (*objectsRender)(void);	
	SceneTrigger *sceneTriggers; //pointer to sector trigger data for a scene... ex lvl00_SceneTrig[0] = courtyard scene
	SectorTrigger *sectorTriggers;
	MeshColObj *wallColObj;
	MeshColObj *groundColObj;
}SceneManager;




GameMode* gameModes[LVLS_SIZE];

SceneManager* scenes[2];


	//Level01(dynamicp);	
	//Level01_Enemies_DL(dynamicp);
	//Level01_Objects(dynamicp);
		//	UI_Target_Render();

#endif
