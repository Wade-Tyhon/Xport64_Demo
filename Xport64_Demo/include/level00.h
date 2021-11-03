#ifndef _LEVEL00_H
#define _LEVEL00_H


//Initiate Courtyard Environment
/*--------------------------------------------------------------------------*/
/*------------------------------From level00.c------------------------------*/
/*--------------------------------------------------------------------------*/

extern SceneManager scene_Courtyard;

extern void init_lvl00_Courtyard();
extern void update_lvl00_DemoScene();
extern void render_lvl00_Courtyard();
extern void render_lvl00_transparent();
extern void enemies_lvl00_Courtyard();
extern void objects_lvl00_Courtyard();
//extern void render_grate();
void lvl00_collision_scenes(); 
void lvl00_collision_walls();

extern SectorTrigger lvl00_CourtyardSectorTrig[3];
extern SceneTrigger lvl00_SceneTrig[1];
extern LevelTrigger lvl00Triggers[];


/*--------------------------------------------------------------------------*/
/*--------------------From lvl01_environments_Mesh.c--------------------*/
/*--------------------------------------------------------------------------*/
extern Vtx lvl00_Courtyard_Wall_VertList_0 [];
extern Vtx lvl00_Courtyard_Ground_VertList_0 [];
extern Vtx lvl00_Courtyard_Trees_VertList_0 [];
extern Vtx lvl00_Courtyard_Arches_VertList_0 [];
extern Vtx lvl00_Courtyard_BreakRock02_VertList_0 [];
extern Vtx lvl00_Courtyard_BreakRock01_VertList_0 [];
extern Vtx lvl00_Courtyard_Waterfall_VertList_0 [];
extern Vtx lvl00_Courtyard_River01_VertList_0 [];
extern Vtx lvl00_Courtyard_River02_VertList_0 [];
extern Vtx lvl00_Courtyard_RiverWalk_VertList_0 [];

//Trigger boxes for geometry
extern TriggerBox env01_courtyard_geom_trigger00; 
extern TriggerBox env01_courtyard_geom_trigger01;


/*--------------------------------------------------------------------------*/
/*--------------------From lvl01_environments_Animator.c--------------------*/
/*--------------------------------------------------------------------------*/
extern void lvl00_Courtyard_Wall_PolyList(u8 animFrame);
extern void lvl00_Courtyard_Ground_PolyList(u8 animFrame);
extern void lvl00_Courtyard_Trees_PolyList(u8 animFrame);
extern void lvl00_Courtyard_Arches_PolyList(u8 animFrame);
extern void lvl00_Courtyard_BreakRock02_PolyList(u8 animFrame);
extern void lvl00_Courtyard_BreakRock01_PolyList(u8 animFrame);
extern void lvl00_Courtyard_River01_PolyList(u8 animFrame);
extern void lvl00_Courtyard_River02_PolyList(u8 animFrame);
extern void lvl00_Courtyard_RiverWalk_PolyList(u8 animFrame);
extern void lvl00_Courtyard_Waterfall_PolyList(u8 animFrame);


/*--------------------------------------------------------------------------*/
/*--------------------From scn00_cave1_env_animator.c--------------------*/
/*--------------------------------------------------------------------------*/

extern void lvl01_env00_loadzone01_entrance_PolyList(u8 animFrame);
extern void lvl01_env00_loadzone01_walls_PolyList(u8 animFrame);
extern void lvl01_env00_loadzone01_entrance_ground_PolyList(u8 animFrame);
extern void lvl01_env00_loadzone01_ground_PolyList(u8 animFrame);
extern void env01_loadzone01_arches002_PolyList(u8 animFrame);

/*--------------------------------------------------------------------------*/
/*--------------------From scn00_cave1_env_mesh.c--------------------*/
/*--------------------------------------------------------------------------*/

extern Vtx lvl01_env00_loadzone01_entrance_VertList_0 [];
extern Vtx lvl01_env00_loadzone01_walls_VertList_0 [];
extern Vtx lvl01_env00_loadzone01_entrance_ground_VertList_0 [];
extern Vtx lvl01_env00_loadzone01_ground_VertList_0 [];
extern Vtx env01_loadzone01_arches002_VertList_0 [];

/*--------------------------------------------------------------------------*/
/*--------------------From scn00_col_cave1_walls.c--------------------*/
/*--------------------------------------------------------------------------*/

extern TriggerBox scn00_col_cave1_walls;




/*--------------------------------------------------------------------------*/
/*---------------------From env00_col_courtyard_walls.c---------------------*/
/*--------------------------------------------------------------------------*/

//Sector 0:
extern TriggerBox  lvl00_courtyard_col_wall01_TrigBox;
extern MeshCollider lvl00_courtyard_col_wall01_MeshVtx[];
extern MeshColliderTri lvl00_courtyard_col_wall01_MeshTri[];
extern MeshColObj lvl00_courtyard_col_wall01_Object[];
extern	MeshCollider lvl00_courtyard_col_ground01_MeshVtx [];
extern	MeshColliderTri lvl00_courtyard_col_ground01_MeshTri[];
extern	MeshColObj lvl00_courtyard_col_ground01_Object[];

//Sector 1:
extern TriggerBox lvl00_courtyard_col_wall02_TrigBox;
extern MeshCollider lvl00_courtyard_col_wall02_MeshVtx [];
extern MeshColliderTri lvl00_courtyard_col_wall02_MeshTri[];
extern MeshColObj lvl00_courtyard_col_wall02_Object[];
extern	MeshCollider lvl00_courtyard_col_ground02_MeshVtx [];
extern	MeshColliderTri lvl00_courtyard_col_ground02_MeshTri[];
extern	MeshColObj lvl00_courtyard_col_ground02_Object[];

//Sector 2:
extern TriggerBox lvl00_courtyard_col_wall03_TrigBox;
extern MeshCollider lvl00_courtyard_col_wall03_MeshVtx [];
extern MeshColliderTri lvl00_courtyard_col_wall03_MeshTri[];
extern MeshColObj lvl00_courtyard_col_wall03_Object[];
extern	MeshCollider lvl00_courtyard_col_ground03_MeshVtx [];
extern	MeshColliderTri lvl00_courtyard_col_ground03_MeshTri[];
extern	MeshColObj lvl00_courtyard_col_ground03_Object[];

/*----------------------------- env01_textures.c ---------------------------*/

//16b 32x64 textures
extern unsigned short lvl01_Grate_32x64[];

//4b 32x128 textures
extern unsigned char lvl01_waterfall01int_32x128[]; //intensity texture
extern unsigned short lvl01_waterfall01int_32x128_tlut[];
extern unsigned char lvl01_waterfall01_32x128[];
extern unsigned short lvl01_waterfall01_32x128_tlut[] ;
extern unsigned char lvl01_waterfall02_32x128[];
extern unsigned short lvl01_waterfall02_32x128_tlut[] ;

//32x32 4b IA
extern unsigned short tex_sky[];
extern unsigned short tx_gradIA16[];
extern unsigned char tx_highlight[];

//64x64 4b I
extern unsigned char lvl01_shadow[];
extern unsigned short lvl01_shadow_tlut[];

//4b 64x64 textures
extern unsigned char lvl01_grating[];
extern unsigned short lvl01_grating_tlut[];

extern unsigned char lvl01_bark[];
extern unsigned short lvl01_bark_tlut[];

extern unsigned char lvl01_tree_trunk[]; 
extern unsigned short lvl01_tree_trunk_tlut[]; 

extern unsigned char lvl01_ground[]; 
extern unsigned short lvl01_ground_tlut[];

extern unsigned char lvl01_ground_riverbed[];
extern unsigned short lvl01_ground_riverbed_tlut[];

extern unsigned char lvl01_pillar[];
extern unsigned short lvl01_pillar_tlut[];

extern unsigned char lvl01_pillar_broken[];
extern unsigned short lvl01_pillar_broken_tlut[];

extern unsigned char lvl01_pillar_detail1[];
extern unsigned short lvl01_pillar_detail1_tlut[];

extern unsigned char lvl01_pillar_detail2[];
extern unsigned short lvl01_pillar_detail2_tlut[];

extern unsigned char lvl01_wall[];
extern unsigned short lvl01_wall_tlut[];

extern unsigned char lvl01_wall_base[];
extern unsigned short lvl01_wall_base_tlut[];

extern unsigned char lvl01_wall_basev2[];
extern unsigned short lvl01_wall_basev2_tlut[];

extern unsigned char lvl01_wallv2[];
extern unsigned short lvl01_wallv2_tlut[];

extern unsigned char lvl01_wall_top[];
extern unsigned short lvl01_wall_top_tlut[];

extern unsigned char lvl01_water[];
extern unsigned short lvl01_water_tlut[];

extern unsigned char lvl01_waterfall[];
extern unsigned short lvl01_waterfall_tlut[];

extern unsigned char lvl01_tree_leaves[];
extern unsigned short lvl01_tree_leaves_tlut[];


extern unsigned char water_grey1[];
extern unsigned short water_grey1_tlut[];

extern unsigned char water_grey2[];
extern unsigned short water_grey2_tlut[];

extern unsigned char water_grey3[];
extern unsigned short water_grey3_tlut[];

extern unsigned char water_grey4[];
extern unsigned short water_grey4_tlut[];

extern unsigned char water_grey5[];
extern unsigned short water_grey5_tlut[];

extern unsigned char water_grey6[];
extern unsigned short water_grey6_tlut[];

extern unsigned char water_grey7[];
extern unsigned short water_grey7_tlut[];

extern unsigned char water_grey8[];
extern unsigned short water_grey8_tlut[];

extern unsigned char water_grey9[];
extern unsigned short water_grey9_tlut[];

extern unsigned char water_grey10[];
extern unsigned short water_grey10_tlut[];

extern unsigned char water_grey11[];
extern unsigned short water_grey11_tlut[];

extern unsigned char water_grey12[];
extern unsigned short water_grey12_tlut[];

extern	unsigned char RockDirtEdge[]	;
extern	unsigned short RockDirtEdge_tlut[]	;


#endif