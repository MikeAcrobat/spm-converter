#include "SPMExpoter.h"

SPMExporter::SPMExporter()
{
}

SPMExporter::~SPMExporter()
{
}

void SPMExporter::exportObject(spmObject & object, const std::string & filename)
{
	stream.open(filename, std::ios::out | std::ios::binary);
	unsigned short magic = SPM_VERSION_NUMBER;
	stream.write(reinterpret_cast<char*>("SPMD"), 4);
	stream.write(reinterpret_cast<char*>(&magic), sizeof(unsigned short));
	int submeshes_size = object.subMeshes.size();
	writeInt(submeshes_size);
	for (int i = 0; i < submeshes_size; ++i)
		writeChunkSubmesh( object.subMeshes[i] );
}

void SPMExporter::writeChunkSubmesh(spmSubmesh & submesh)
{
	writeString(submesh.name);
	writeShort(submesh.flags);
	writeUInt(submesh.reservedDataSize);		// Reserved bytes (size for user data)
	int surfaceCount = submesh.surfaces.size();
	writeUInt(surfaceCount);
	for (int i = 0; i < surfaceCount; i++) 
		writeChunkSurface(submesh.surfaces[i]);	
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