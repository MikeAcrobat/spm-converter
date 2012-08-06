#include <fbxsdk.h>
#define MAT_HEADER_LENGTH 200
/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayHierarchy(FbxNode* pNode, int pDepth);
void DisplayHierarchy(FbxScene* pScene);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMetaDataConnections(FbxObject* pNode);
void DisplayString(const char* pHeader, const char* pValue  = "", const char* pSuffix  = "");
void DisplayBool(const char* pHeader, bool pValue, const char* pSuffix  = "");
void DisplayInt(const char* pHeader, int pValue, const char* pSuffix  = "");
void DisplayDouble(const char* pHeader, double pValue, const char* pSuffix  = "");
void Display2DVector(const char* pHeader, FbxVector2 pValue, const char* pSuffix  = "");
void Display3DVector(const char* pHeader, FbxVector4 pValue, const char* pSuffix  = "");
void DisplayColor(const char* pHeader, FbxColor pValue, const char* pSuffix  = "");
void Display4DVector(const char* pHeader, FbxVector4 pValue, const char* pSuffix  = "");

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayAnimation(FbxScene* pScene);
void DisplayDefaultAnimation(FbxNode* pNode);
void DisplayAnimation(FbxAnimStack* pAnimStack, FbxNode* pNode, bool isSwitcher = false);
void DisplayAnimation(FbxAnimLayer* pAnimLayer, FbxNode* pNode, bool isSwitcher = false);
void DisplayChannels(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void (*DisplayCurve) (FbxAnimCurve* pCurve), void (*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher);
void DisplayCurveKeys(FbxAnimCurve* pCurve);
void DisplayListCurveKeys(FbxAnimCurve* pCurve, FbxProperty* pProperty);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMaterial(FbxGeometry* pGeometry);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMesh(FbxNode* pNode);
void DisplayControlsPoints(FbxMesh* pMesh);
void DisplayPolygons(FbxMesh* pMesh);
void DisplayMaterialMapping(FbxMesh* pMesh);
void DisplayTextureMapping(FbxMesh* pMesh);
void DisplayTextureNames( FbxProperty &pProperty, FbxString& pConnectionString );
void DisplayMaterialConnections(FbxMesh* pMesh);
void DisplayMaterialTextureConnections( FbxSurfaceMaterial* pMaterial, char * header, int pMatId, int l );

/************************************************************************/
/*                                                                      */
/************************************************************************/
void FindAndDisplayTextureInfoByProperty(FbxProperty pProperty, bool& pDisplayHeader, int pMaterialIndex);
void DisplayTexture(FbxGeometry* pGeometry);
void DisplayTextureInfo(FbxTexture* pTexture, int pBlendMode);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayLink(FbxGeometry* pGeometry);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayShape(FbxGeometry* pGeometry);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayGenericInfo(FbxScene* pScene);
void DisplayProperties(FbxObject* pObject);
void DisplayGenericInfo(FbxNode* pNode, int pDepth);