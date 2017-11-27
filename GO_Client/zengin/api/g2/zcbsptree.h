/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __ZCBSPTREE_H_INCLUDED__
#define __ZCBSPTREE_H_INCLUDED__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"

class zCBspNode;
class zCBspLeaf;
class zCBspSector;
class zCCBspTree;
class zCVob;
class zCVobLight;
class zCBspSector;
class zCBspBase;
class zCMesh;
class zCPolygon;

enum zTBspTreeMode    
{   
	zBSP_MODE_INDOOR, 
	zBSP_MODE_OUTDOOR, 
	zBSP_MODE_FORCEINT	= 0x7FFFFFFF
};

enum zTWld_RenderMode
{ 
	zWLD_RENDER_MODE_VERT_LIGHT,        
	zWLD_RENDER_MODE_LIGHTMAPS,
	zWLD_RENDER_MODE_FORCEINT	= 0x7FFFFFFF
};

/** Insert description */
class zCBspTree
{
	zCBspNode*				actNodePtr;
	zCBspLeaf*				actLeafPtr;

	zCBspBase*				bspRoot;
	zCMesh*					mesh;
	zCPolygon**				treePolyList;
	zCBspNode*				nodeList;
	zCBspLeaf*				leafList;
	int						numNodes;   
	int						numLeafs;     
	int						numPolys;       

	zCArray<zCVob*>			renderVobList;
	zCArray<zCVobLight*>    renderLightList;
	zCArray<zCBspSector*>	sectorList;
	zCArray<zCPolygon*>     portalList;                                                

	zTBspTreeMode			bspTreeMode; 
	zTWld_RenderMode		worldRenderMode;
	float					vobFarClipZ;             

	struct zTPlane
	{
		float distance;
		zPOINT3 normal;
	};

	zTPlane					vobFarPlane;
	int						vobFarPlaneSignbits;                       
	int 					drawVobBBox3D;            
	int 					leafsRendered;                  
	int 					vobsRendered;                
	int 					m_bRenderedFirstTime;        
	zTFrameCtr 				masterFrameCtr;
	zCPolygon** 			actPolyPtr;
	int 					compiled;
};

#undef  __G2EXT_API_HEADER

#endif //__ZCBSPTREE_H_INCLUDED__