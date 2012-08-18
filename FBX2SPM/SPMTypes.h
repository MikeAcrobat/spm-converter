#pragma once
#include <fbxsdk.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include "utilities.h"

#define MAX_COUNT_OF_TEXTURES			8

#define SPM_VERSION_NUMBER				0x2000

#define MDLSPM_CHUNK_NONE				0x0000

#define MDLSPM_CHUNK_INDEX32BIT			0x0001
#define MDLSPM_CHUNK_VERTEXCOLOR		0x0002
#define MDLSPM_CHUNK_VERTEXFOG			0x0004
#define MDLSPM_CHUNK_VERTEXNORMAL		0x0008

#define MDLSPM_CHUNK_GOURAUDSHADING		0x0008
#define MDLSPM_CHUNK_NODE_ANIM			0x0010
#define MDLSPM_CHUNK_MORPHTARGET_ANIM	0x0020
#define MDLSPM_CHUNK_SKELETAL_ANIM		0x0040

#define MDLSPM_CHUNK_TEXTUREINTERN		0x0010
#define MDLSPM_CHUNK_TEXTUREMATRIX		0x0020

struct textureUV 
{
	float U;
	float V;
};

struct spmVector
{
	float x, y, z;
};

struct spmQuaternion
{
	float x, y, z, w;
};

struct spmTexture
{
	std::string fileName;
};

struct spmVertex
{
	spmVector position;
	std::vector<textureUV> UVs;
	spmVector normal;
	// animation needs
	int vertexId;
	int surfaceId;
	int controlPointId;
};

struct spmTriangle
{
	int indexes[3];
};

struct spmSurface 
{
	std::string name;
	short flags;
	char textureDimensions[MAX_COUNT_OF_TEXTURES];
	std::vector<spmTexture> textures;
	std::vector<spmVertex> vertexes;
	std::vector<spmTriangle> triangles;
};

struct spmJointKeyframe
{
	int frame;
	spmVector position;
	spmQuaternion rotation;
	spmVector scale;
};

struct spmJointVertexWeight
{
	int sufraceId;
	int vertexIndex;
	float weight;
};

struct spmAnimationJoint
{
	std::string name;
	int index;
	int parentIndex;
	spmVector position;
	spmQuaternion rotation;
	spmVector scale;
	std::vector<spmJointVertexWeight> vertexes;
	std::vector<spmJointKeyframe> keyFrames;
};

struct spmSkeletalAnimation
{
	std::string name;
	std::vector<spmAnimationJoint> joints;
};

struct spmSubmesh
{
	std::string name;
	short flags;
	int reservedDataSize;
	std::vector<spmSurface> surfaces;
	spmSkeletalAnimation animation;
};

struct spmObject
{
	std::vector<spmSubmesh> subMeshes;
};

extern bool localSpace;

spmSubmesh				CreateObject(FbxNode * node);
spmVertex				GetVertex(FbxMesh * mesh, int poly, int vert, int surfaceId, int vertexId);
spmTexture				GetTexture(FbxSurfaceMaterial * material);
bool					IsAnimationExist(FbxGeometry * geometry);
spmSkeletalAnimation	GetAnimation(FbxSkin * skin, const std::vector<spmSurface> & surfaces);
void					FillBoneList(std::vector<spmAnimationJoint> & list, std::vector<std::pair<FbxNode *, FbxCluster *>> & links, FbxNode * node, int index = -1);
void					FillJoint(spmAnimationJoint & joint, std::pair<FbxNode *, FbxCluster *> pair);
FbxAMatrix				GetMatrix(FbxNode * node, FbxTime time = FBXSDK_TIME_INFINITE);
void					FixWeights(spmAnimationJoint & joint, const std::vector<spmSurface> & surfaces);