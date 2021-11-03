#include "common.h"

#include "levelDefs.h"
#include "level01.h"
#include "level00.h"
#include "titlemanager.h"

extern GameMode gameMode_Main; //formerly lvlGameMain

extern void gameManagerGFX(unsigned int pendingGfx);
extern void InitMode_Main( void );
extern void UpdateGame(void);
extern void MakeGameDL(void);
extern void DrawGameUI(void);

extern void loadGameMode(unsigned int Index); //formerly loadLevel
extern void initGameModes(void); //formerly initLevel


extern void initMainCamera();

