#pragma once
#include <fbxsdk.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>

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

struct spmTexture
{
	std::string fileName;
};

struct spmVertex
{
	spmVector position;
	std::vector<textureUV> UVs;
	spmVector normal;
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

struct spmSubmesh
{
	std::string name;
	short flags;
	int reservedDataSize;
	std::vector<spmSurface> surfaces;
};

struct spmObject
{
	std::vector<spmSubmesh> subMeshes;
};

spmSubmesh CreateObject(FbxNode * node);
spmVertex GetVertex(FbxMesh * mesh, int poly, int vert);
spmTexture GetTexture(FbxSurfaceMaterial * material);