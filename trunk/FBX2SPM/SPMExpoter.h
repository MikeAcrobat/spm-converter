#include <fbxsdk.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <algorithm>
#include "SPMTypes.h"

class SPMExporter 
{
public:
	SPMExporter();
	~SPMExporter();
	void exportObject(spmObject & object, const std::string & filename);
private:
	void writeChunkSubmesh(spmSubmesh & submesh);
	void writeChunkSurface(spmSurface & surface);
	void writeChunkTexture(spmTexture & texture);
	void writeChunkVertex(spmVertex & vertex);
	void writeChunkTriangle(spmTriangle & tri);
	void writeChunkAnimation(spmSkeletalAnimation & animation);
	void writeChunkAnimationJoint(spmAnimationJoint & joint);
	void writeChunkWeight(spmJointVertexWeight & weight);
	void writeChunkKeyFrame(spmJointKeyframe & frame);

	void writeInt(int i);
	void writeUInt(unsigned int i);
	void writeShort(short i);
	void writeString(const std::string & string);
	void writeByte(unsigned char byte);
	void writeFloat(float i);

	std::ofstream stream;
};