#define COMBINE_HEX(U, V) ((((s32)U) << 16) & 0xFFFF0000) | (((s32)V) & 0x0000FFFF)

//Custom shaders
#define G_CC_SHADEFADEA             0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT
#define	G_CC_DECALFADE              0, 0, 0, TEXEL0, 0, 0, 0, ENVIRONMENT
#define	G_CC_DECALFADEA             0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0
#define	G_CC_TRANSTEXTUREFOG        TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0
#define	G_CC_TRANSTEXTUREFOG2 		0, 0, 0, COMBINED, 0, 0, 0, COMBINED

#define G_CC_VTXSHADER				0,	0, PRIMITIVE,	ENVIRONMENT,	0, 0, PRIMITIVE, ENVIRONMENT
#define G_CC_MULPRIMSHADE           PRIMITIVE,0,SHADE,0,PRIMITIVE,0,SHADE,0		

#define MY_MORPH TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0
#define	G_RM_PASS2		GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)
		
//Graphics Macros
#define u8 unsigned char
#define u16 unsigned short

//------------------Typical Texture Resolution (RES) Sizes------------------
#define RES_32x32 32,32
#define RES_64x64 64,64
#define RES_32x64 32,64
#define RES_32x128 32,128
#define RES_64x32 64,32
#define RES_128x32 128,32
#define RES_136x16 136,16

//------------------Typical Scale/Mask (SCL) Sizes------------------
//Specifies the wrap position of your texture. Think of it as an artboard scale for your texture (as related to S,T coordinates)
//To wrap a 32x32 texture, you would set to SCL_5x5 (2^5 x 2^5)
//To wrap a 32x128 texture, you would set to SCL_5x7 (2^5 x 2^7)
//Like an artboard, you can use this to mask/crop a larger image as well. 
//If you want to mask/crop a 64x64 texture to 32x64, you can set to SCL_S5xT6 (2^5 x 2^6)
//You can use this in conjunction with LOD to get precision positioning and a large number of wraps
//If your 64x64 texture is applied to a model with SCL_5x5 (32x32 px) S,T coordinates, 
//you can then left bitshift once in order to correct the wrap and scale

#define SCL_0x0 0,0
#define SCL_1x1 1,1
#define SCL_2x2 2,2
#define SCL_3x3 3,3
#define SCL_4x4 4,4
#define SCL_5x5 5,5
#define SCL_6x6 6,6
#define SCL_7x7 7,7

#define SCL_5x6 5,6
#define SCL_5x7 5,7
#define SCL_5x8 5,8
#define SCL_4x6 4,6
#define SCL_4x7 4,7
#define SCL_4x8 4,8

#define SCL_6x5 6,5
#define SCL_7x5 7,5
#define SCL_8x5 8,5
#define SCL_6x4 6,4
#define SCL_7x4 7,4
#define SCL_8x4 8,4

//------------------Typical Level of Detail (LOD) Bitshift for S,T coordinates------------------
//Bit shift the S,T coordinates for your model. 0-10 is a right shift 11-15 is a left shift
//This can be used for mip mapping or as a means of getting higher levels of precision in your texture mapping
#define RSFT_0_0 	G_TX_NOLOD, G_TX_NOLOD
#define RSFT_1_1 	1, 1
#define RSFT_2_2 	2, 2
#define RSFT_3_3 	3, 3
#define RSFT_4_4 	4, 4
#define RSFT_5_5 	5, 5
#define LSFT_1_1	15, 15
#define LSFT_2_2	14, 14
#define LSFT_3_3 	13, 13
#define LSFT_4_4 	12, 12
#define LSFT_5_5 	11, 11



//TO DO NOTE: Continue setting up materials. Decide how to manage them...
// Update exporter to use new commands for RES, SCL, and SFT


//NOTE: Standard lit object material using normals (no vector colors): 
#define MAT_FOG_LIGHT(dl,r,g,b,a,min,max){\
	gDPPipeSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_CULL_BACK | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetFogColor(dl++, r,g,b,a);\
	gSPFogPosition(dl++, min, max);\
	gDPSetColorDither(dl++, G_CD_BAYER);\
}

//NOTE: For transparent objects that can be seen from all sides and have multiple alpha steps. Do not cull back. 
#define MAT_TRANSP_FOG_LIGHT(dl,r,g,b,a,min,max){\
	gDPPipeSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetFogColor(dl++, r,g,b,a);\
	gSPFogPosition(dl++, min, max);\
	gDPSetColorDither(dl++, G_CD_BAYER);\
}

//NOTE: The following is Intensity textures (doubles as alpha value) good for effects like mist, fog, blood etc
#define TEX_4B_I_EFFECT(dl, texture, pal, RES, SCL, SFT) {\
	gDPPipeSync(dl++);\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetTextureLUT(dl++, G_TT_IA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_I,\
		RES,	0, G_TX_WRAP, G_TX_WRAP,\
		SCL, SFT);\
	gDPSetCombineLERP(dl++,	TEXEL0, 0, PRIMITIVE, 0,\
						TEXEL0, 0, TEXEL0, 0,\
						1, 0, 0, COMBINED,\
						TEXEL0, 0, 0, COMBINED);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetRenderMode(dl++,G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2)\
}

//NOTE: The following is for partially transparent textures. Alpha is controlled by fog and primitive color alpha. Primitive color default is set here of 125. 
//To change, use gDPSetPrimColor again with the preferred color and alpha after using this macros.
#define TEX_4B_CI_LIQUID(dl, texture, pal, RES, SCL, SFT) {\
	gDPPipeSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,\
		RES,	0, G_TX_WRAP, G_TX_WRAP,\
		SCL, SFT);\
	gDPSetCombineMode(dl++,G_CC_TRANSTEXTUREFOG, G_CC_TRANSTEXTUREFOG2);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetPrimColor(dl++, 0, 255, 255, 255, 255, 125);\
	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A,G_RM_ZB_XLU_SURF2)\
}

//NOTE: The following is for a single bit of alpha. This is useful for things such as fences, decals, grates, UI elements, item pickups etc.
//GeometryMode is re-set here
#define TEX_4B_CI_EDGETRANSP(dl, texture, pal, resolution, scale, lod) {\
	gDPPipeSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
	gDPSetCycleType(dl++, G_CYC_1CYCLE);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
    gDPLoadTLUT_pal16(dl++, 0, pal);\
    gDPLoadTextureBlock_4b(dl++, texture, G_IM_FMT_CI,\
		resolution, 0, G_TX_WRAP, G_TX_WRAP,\
		scale, scale, lod, lod );\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetCombineMode(dl++,G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);\
	gDPSetRenderMode(dl++,G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2)\
}



//to animate a texture, send it the w and h of the texture and the starting S,T coordinate offset from 0,0
#define TEX_ANIM_OFFSET(dl, texWidth, texHeight, offsetS, offsetT) {\
	gDPSetTileSize(glistp++, G_TX_RENDERTILE, offsetS, offsetT, offsetS+texWidth, offsetT+texHeight);\
}







//-------------------Light and Fog Settings----------------------

#define TEXTURE_FOG_LIGHT(dl,r,g,b,a,min,max){\
	gDPPipeSync(dl++);\
    gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER|G_CULL_BACK | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_LIGHTING );\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetFogColor(dl++, r,g,b,a);\
	gSPFogPosition(dl++, min+130, max+130);\
	gSPSetGeometryMode(dl++,G_FOG);\
	gDPSetCombineMode(dl++, G_CC_MODULATERGB, G_CC_PASS2);\
	gDPSetRenderMode(dl++, G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)\
}



//NOTE: The following is for VTX colors without using lighting
#define TEXTURE_FOG_VTXCOL(dl,r,g,b,a,min,max){\
	gDPPipeSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER|G_CULL_BACK | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
	gDPSetCycleType(dl++,G_CYC_2CYCLE);\
	gDPSetFogColor(dl++, r,g,b,a);\
	gSPFogPosition(dl++, min, max);\
	gDPSetColorDither(dl++, G_CD_BAYER);\
	gDPSetCombineMode(dl++, G_CC_MODULATERGBA, G_CC_PASS2);\
	gDPSetRenderMode(dl++, G_RM_FOG_SHADE_A, G_RM_RA_ZB_OPA_SURF2)\
}


//-------------------Speciality Settings----------------------

//NOTE: the following is for 4B "edge" textures that have a 1bit alpha (on or off). Used for objects such as fences
#define TEXTURE_4B_I(dl, texture, pal, resolution, scale, lod) {\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_I,\
		resolution,	0, G_TX_WRAP, G_TX_WRAP,\
		scale, lod, lod);\
	gDPSetCombineLERP(dl++,	TEXEL0, 0, PRIMITIVE, 0,\
						TEXEL0, 0, PRIMITIVE, 0,\
						0, 0, 0, COMBINED,\
						TEXEL0, 0, 0, COMBINED);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetRenderMode(dl++,G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2)\
}

//NOTE: the following is for 4B "edge" textures that have a 1bit alpha (on or off). Used for objects such as fences
#define TEXTURE_4B_EDGE(dl, texture, pal, resolution, scale, lod) {\
	gDPPipeSync(dl++);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
    gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++, texture, G_IM_FMT_CI,\
		resolution, 0, G_TX_WRAP, G_TX_WRAP,\
		scale, scale, lod, lod );\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH );\
    gDPSetCycleType(dl++, G_CYC_1CYCLE);\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetCombineMode(dl++,G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);\
	gDPSetRenderMode(dl++,G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2)\
}

#define TEXTURE_4B_TLUT_VTXCOL(dl, texture, pal, resolution, scale, lod) {\
	gDPPipeSync(dl++);\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);\
	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)\
}

#define TEXTURE_4B_TLUT_MIRRORX(dl, texture, pal, scale, lod) {\
	gDPPipeSync(dl++);\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_MIRROR, G_TX_WRAP,	scale, scale, lod, lod);\
	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)\
}

#define TEXTURE_4B_TLUT_CLAMP(texture, pal, scale, lod) {\
	gDPPipeSync(glistp++); gSPTexture(glistp++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetTextureLUT(glistp++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(glistp++, 0, pal);\
	gDPLoadTextureBlock_4b(glistp++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_CLAMP, G_TX_CLAMP,	scale, scale, lod, lod);\
	gDPSetCombineMode(glistp++,G_CC_MODULATERGB, G_CC_PASS2);\
	gDPSetTextureFilter(glistp++, G_TF_BILERP);\
	gDPSetRenderMode(glistp++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)\
}

#define TEXTURE_4B_TLUT_TRANSP(dl, texture, pal, resolution, scale, lod) {\
	gDPPipeSync(dl++);\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,\
		resolution,	0, G_TX_WRAP, G_TX_WRAP,\
		scale, scale, lod, lod);\
	gDPSetCombineMode(dl++,G_CC_TRANSTEXTUREFOG, G_CC_TRANSTEXTUREFOG2);\
	gDPSetTextureFilter(dl++, G_TF_BILERP);\
	gDPSetPrimColor(dl++, 0, 255, 255, 255, 255, 90);\
	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A,G_RM_ZB_XLU_SURF2)\
}




#define TEXTURE_4B_TLUT(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(dl++, G_TF_AVERAGE);	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)
#define TEXTURE_4B_TLUT_BILERP(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(dl++, G_TF_BILERP);	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)
#define TEXTURE_4B_TLUT_POINT(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(dl++, G_TF_POINT);	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)


	


	
	
	
	
	
	
	
	
//NOTE: Old unused versions below:	
	
	
#define S_TEXTURE_FOG_LIGHT {\
	gsDPPipeSync(),\
	gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),\
	gsDPLoadTextureBlock(Dark_Texture_Wall_1,	G_IM_FMT_RGBA,	G_IM_SIZ_16b,	32, 32,	0, G_TX_WRAP, G_TX_WRAP,	5, 5, G_TX_NOLOD, G_TX_NOLOD),\
	gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),\
	gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)\
}


	
#define TEXTURE_TRANSPARENT(dl,r,g,b,a) {\
	gDPPipeSync(dl++);\
	gDPSetCycleType(dl++,G_CYC_1CYCLE)\
}

#define PRIM_TRANSPARENT(dl) {\
	gDPPipeSync(dl++);\
	gDPTileSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
	gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_LIGHTING );\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_OFF);\
	gDPSetCombineMode(dl++,G_CC_PRIMITIVE, G_CC_PRIMITIVE);\
	gDPSetRenderMode(dl++,G_RM_AA_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2)\
}

#define PRIM_TRANSPARENT_PENITRATE_SURF(dl) {\
	gDPPipeSync(dl++);\
	gDPTileSync(dl++);\
	gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_OFF);\
	gDPSetCombineMode(dl++,G_CC_PRIMITIVE, G_CC_PRIMITIVE);\
	gDPSetRenderMode(dl++,G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2)\
}

#define TEXTURE_4B_TRANSPARENT_OVERLAY(dl, texture, pal, scale, lod) {\
	gDPPipeSync(dl++);\
	gDPTileSync(dl++);\
	gSPClearGeometryMode(dl++,0xFFFFFFFF);\
    gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_LIGHTING );\
	gDPSetCycleType(dl++, G_CYC_1CYCLE);\
    gDPSetCombineMode(dl++,G_CC_BLENDRGBDECALA, G_CC_BLENDRGBDECALA);\
	gSPTexture(dl++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);\
	gDPSetTextureFilter(dl++, G_TF_AVERAGE);\
	gDPSetRenderMode(dl++, G_RM_AA_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);\
	gDPSetTextureLUT(dl++, G_TT_RGBA16);\
	gDPLoadTLUT_pal16(dl++, 0, pal);\
	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod)\
}

#define TEXTURE_4B_TLUT_ANIMATED(dl, texture, pal, s, t, scale, lod) 	gDPPipeSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureTile_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	s,t, 63, 63, 0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(dl++, G_TF_POINT);	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)

#define TEXTURE_4B_TLUT_INTER(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(dl++, G_TF_BILERP);	gDPSetRenderMode(dl++,G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_INTER)






/*
#define TEXTURE_4B_TLUT_INTER(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++);  gSPClearGeometryMode(dl++,0xFFFFFFFF); gSPSetGeometryMode(dl++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_LIGHTING ); gDPSetCycleType(dl++,G_CYC_1CYCLE); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_SHADE, G_CC_SHADE);	gDPSetTextureFilter(dl++, G_TF_BILERP);	gDPSetRenderMode(dl++,G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_INTER2)
#define TEXTURE_4B_TLUT_CLAMP(texture, pal, scale, lod) 	gDPPipeSync(glistp++); gSPTexture(glistp++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(glistp++, G_TT_RGBA16);	gDPLoadTLUT_pal16(glistp++, 0, pal);	gDPLoadTextureBlock_4b(glistp++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_CLAMP, G_TX_CLAMP,	scale, scale, lod, lod);	gDPSetCombineMode(glistp++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(glistp++, G_TF_BILERP);	gDPSetRenderMode(glistp++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)
#define TEXTURE_4B_TLUT_CLAMP_GEIST(texture, pal, scale, lod) 	gDPPipeSync(glistp++); gDPSetCycleType(glistp++, G_CYC_2CYCLE);	gDPSetTextureLUT(glistp++, G_TT_RGBA16); gDPLoadTLUT_pal16(glistp++, 0, pal); gDPLoadTextureBlock_4b(glistp++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_CLAMP, G_TX_CLAMP,	scale, scale, lod, lod);	gDPSetCombineMode(glistp++,G_CC_MODULATERGB, G_CC_PASS2); 	gDPSetTextureFilter(glistp++, G_TF_BILERP);	gSPSetGeometryMode(glistp++, G_ZBUFFER|G_CULL_BACK|G_SHADE|G_FOG|G_LIGHTING );		gDPSetRenderMode(glistp++,G_RM_FOG_SHADE_A, G_RM_RA_ZB_OPA_SURF2)   //gSPTexture(glistp++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);


#define TEXTURE_4B_TRANSPARENT_TLUT(dl, texture, pal, scale, lod) 	gDPPipeSync(dl++); gDPTileSync(dl++); gSPTexture(dl++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(dl++, G_TT_RGBA16);	gDPLoadTLUT_pal16(dl++, 0, pal);	gDPLoadTextureBlock_4b(dl++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_WRAP, G_TX_WRAP,	scale, scale, lod, lod);	gDPSetCombineMode(dl++,G_CC_BLENDRGBDECALA, G_CC_BLENDRGBDECALA);	gDPSetTextureFilter(dl++, G_TF_AVERAGE);	gDPSetRenderMode(dl++,G_RM_AA_ZB_XLU_INTER, G_RM_AA_ZB_XLU_INTER2)
*/



//#define TEXTURE_SPECULAR(texture, pal, scale, lod) 	gSPTexture(glistp++,0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);	gDPSetTextureLUT(glistp++, G_TT_RGBA16);	gDPLoadTLUT_pal16(glistp++, 0, pal);	gDPLoadTextureBlock_4b(glistp++,texture,	G_IM_FMT_CI,	64, 64,	0, G_TX_CLAMP, G_TX_CLAMP,	scale, scale, lod, lod);	gDPSetCombineMode(glistp++,G_CC_MODULATERGB, G_CC_PASS2);	gDPSetTextureFilter(glistp++, G_TF_BILERP);	gDPSetRenderMode(glistp++,G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2)

//#define S_TEXTURE_FOG_LIGHT(r,g,b,a,min,max) 	gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),	gsDPLoadTextureBlock(Dark_Texture_Wall_1,	G_IM_FMT_RGBA,	G_IM_SIZ_16b,	32, 32,	0, G_TX_WRAP, G_TX_WRAP,	5, 5, G_TX_NOLOD, G_TX_NOLOD),	gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),	gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_OPA_SURF2),

/*
#define	FBUF_ADRS(x,y)		(FBUF_TOP+((x)+(y)*SCREEN_WD)*2)
#define	canvas_cursor(x,y)	__cursor = (u16 *)FBUF_ADRS((x),(y))
#define	canvas_center(x,y)	canvas_cursor((SCREEN_WD-(x)*FONT_WSKIP)/2,(y))
#define	canvas_wskip(x)		__cursor += (x);
#define	canvas_putstr(n,fg,bg)	canvas_puts((n), sizeof(n)-1, (fg), (bg))
*/