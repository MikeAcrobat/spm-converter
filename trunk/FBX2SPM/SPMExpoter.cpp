#include "SPMExpoter.h"

SPMExporter::SPMExporter()
{
}

SPMExporter::~SPMExporter()
{
}

void SPMExporter::exportObject(spmObject & object, const std::string & filename)
{
	DisplayString("Data collected, starting exporting");
	if (object.subMeshes.size() > 0)
	{
		for (unsigned int i = 0; i < object.subMeshes.size(); i++)
		{
			spmSubmesh & mesh = object.subMeshes[i];
			std::replace(mesh.name.begin(), mesh.name.end(), ':', '_');
			stream.open(filename + mesh.name + ".spm", std::ios::out | std::ios::binary);
			writeChunkSubmesh(mesh);
			stream.close();
			DisplayString(mesh.name.c_str(), " saved");
		}
	}	
}

void SPMExporter::writeChunkSubmesh(spmSubmesh & submesh)
{
	unsigned short magic = SPM_VERSION_NUMBER;
	stream.write(reinterpret_cast<char*>("SPMD"), 4);
	stream.write(reinterpret_cast<char*>(&magic), sizeof(unsigned short));
	writeInt(1);								// submesh count
	writeString(submesh.name);
	writeShort(submesh.flags);
	writeUInt(submesh.reservedDataSize);		// Reserved bytes (size for user data)
	int surfaceCount = submesh.surfaces.size();
	writeUInt(surfaceCount);
	for (int i = 0; i < surfaceCount; i++) 
		writeChunkSurface(submesh.surfaces[i]);	
	if (submesh.flags | MDLSPM_CHUNK_SKELETAL_ANIM)
		writeChunkAnimation(submesh.animation);
}

void SPMExporter::writeChunkSurface( spmSurface & surface )
{
	writeString(surface.name);
	writeShort(MDLSPM_CHUNK_VERTEXNORMAL);
	for (int i = 0; i < MAX_COUNT_OF_TEXTURES; i++)
		writeByte(surface.textureDimensions[i]);

	int textureCount = surface.textures.size();
	writeByte((unsigned char)textureCount);
	for (int i = 0; i < textureCount; i++)
		writeChunkTexture(surface.textures[i]);

	unsigned int vertexCount = surface.vertexes.size();
	writeUInt(vertexCount);
	writeUInt(0xFFFFFFFF);								// Color
	writeFloat(0);
	for (unsigned int i = 0; i < vertexCount; i++)
		writeChunkVertex(surface.vertexes[i]);

	unsigned int triCount = surface.triangles.size();
	writeUInt(triCount);
	for (unsigned int i = 0; i < triCount; i++)
		writeChunkTriangle(surface.triangles[i]);
}

void SPMExporter::writeChunkTexture(spmTexture & texture)
{
	writeByte((unsigned char)1);
	writeString(texture.fileName);
	writeShort(0);
	writeInt(0);
	writeInt(0);
	writeInt(0);
}

void SPMExporter::writeChunkVertex(spmVertex & vertex)
{
	writeFloat(vertex.position.x);
	writeFloat(vertex.position.y);
	writeFloat(vertex.position.z);
	writeFloat(vertex.UVs[0].U);
	writeFloat(vertex.UVs[0].V);
	writeFloat(vertex.normal.x);
	writeFloat(vertex.normal.y);
	writeFloat(vertex.normal.z);
}

void SPMExporter::writeChunkTriangle(spmTriangle & tri)
{
	for (int i = 0; i < 3; i++)
		writeShort(tri.indexes[i]);
}

void SPMExporter::writeChunkAnimation( spmSkeletalAnimation & animation )
{
	writeString(animation.name);
	unsigned int jointCount = animation.joints.size();
	writeUInt(jointCount);
	for (unsigned int i = 0; i < jointCount; i++)
		writeChunkAnimationJoint(animation.joints[i]);
}

void SPMExporter::writeChunkAnimationJoint( spmAnimationJoint & joint )
{
	writeString(joint.name);
	writeInt(joint.parentIndex);
	writeFloat(joint.position.x);
	writeFloat(joint.position.y);
	writeFloat(joint.position.z);
	writeFloat(joint.rotation.x);
	writeFloat(joint.rotation.y);
	writeFloat(joint.rotation.z);
	writeFloat(joint.rotation.w);
	writeFloat(joint.scale.x);
	writeFloat(joint.scale.y);
	writeFloat(joint.scale.z);
	unsigned int vertexCount = joint.vertexes.size();
	writeUInt(vertexCount);	// vertexes
	for (unsigned int i = 0; i < vertexCount; i++)
		writeChunkWeight(joint.vertexes[i]);
	unsigned int keyFramesCount = joint.keyFrames.size();
	writeUInt(keyFramesCount); // key frame count
	for (unsigned int i = 0; i < keyFramesCount; i++)
		writeChunkKeyFrame(joint.keyFrames[i]);
}

void SPMExporter::writeChunkWeight( spmJointVertexWeight & weight )
{
	writeUInt(weight.sufraceId);
	writeUInt(weight.vertexIndex);
	writeFloat(weight.weight);
}

void SPMExporter::writeChunkKeyFrame( spmJointKeyframe & frame )
{
	writeUInt(frame.frame);
	writeFloat(frame.position.x);
	writeFloat(frame.position.y);
	writeFloat(frame.position.z);
	writeFloat(frame.rotation.x);
	writeFloat(frame.rotation.y);
	writeFloat(frame.rotation.z);
	writeFloat(frame.rotation.w);
	writeFloat(frame.scale.x);
	writeFloat(frame.scale.y);
	writeFloat(frame.scale.z);
}

void SPMExporter::writeInt( int i )
{
	stream.write(reinterpret_cast<char*>(&i), sizeof(int));
}

void SPMExporter::writeUInt( unsigned int i )
{
	stream.write(reinterpret_cast<char*>(&i), sizeof(unsigned int));
}

void SPMExporter::writeShort( short i )
{
	stream.write(reinterpret_cast<char*>(&i), sizeof(short));
}

void SPMExporter::writeString( const std::string & string )
{
	writeInt(int(string.length()));
	stream.write(string.c_str(), string.length());
}

void SPMExporter::writeByte( unsigned char byte )
{
	stream.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
}


void SPMExporter::writeFloat( float i )
{
	stream.write(reinterpret_cast<char*>(&i), sizeof(float));
}