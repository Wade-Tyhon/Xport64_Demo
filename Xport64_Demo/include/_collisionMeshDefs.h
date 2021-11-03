#ifndef __COLLISIONMESHDEFS_H
#define __COLLISIONMESHDEFS_H

	//full common.h is not needed for these simple scripts

	#include <ultra64.h>
	#include <stdlib.h>

	#include "transformDefs.h"
	#include "objectDefs.h"
	
	/*TO DO NOTES: 1/22/2021 Set up a function to combine all collision data into regions
		For Example
		Region 1 consists of multiple Scenes: Landing zone, courtyard, cave system, and canyon areas
		Each Scene consists of multiple Sections containing collision objects such as trees, ground, water, walls, etc
		Set up a hierarchical check in the collision data  
			- very large bounding box for regions (simple distance check)
			- multiple smaller boundary boxes for scenes (simple distance check)
			- within each scene, divide up the environment object into Sections with a boundary box (simple distance check)
			- if all of the above collision checks return true down to each Sector, check collision against all objects in that sector 
			
		
	*/
	
	extern MeshColliderTri *env00_courtyard_wall_MeshTri[1]; //pointer for storing all level collision data 
	extern MeshCollider *env00_courtyard_walls_MeshVtx[1]; //pointer for storing all level collision data
	
	
	
#endif // _COMMON_H