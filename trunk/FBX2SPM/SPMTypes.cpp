#include "SPMTypes.h"

spmSubmesh CreateObject( FbxNode * node )
{
	spmSubmesh subMesh;
	FbxMesh * mesh = node->GetMesh();

	if (!mesh) return spmSubmesh();
	mesh->ComputeVertexNormals(true);
	int materialCount = node->GetMaterialCount();
	// 1 material = 1 sub mesh
	subMesh.surfaces.resize(materialCount);
	subMesh.flags = MDLSPM_CHUNK_GOURAUDSHADING;
	subMesh.reservedDataSize = 0;
	subMesh.name = node->GetName();
	// we need to have at least 1 material mapping
	FbxGeometryElementMaterial * mapping = mesh->GetElementMaterial();
	if (!mapping) return spmSubmesh();

	/************************************************************************/
	/*                                Geometry                              */
	/************************************************************************/
	int mappingArrayCount = mapping->GetIndexArray().GetCount();
	int polyCount = mesh->GetPolygonCount();
	for (int i = 0; i < polyCount; ++i) 
	{
		int surfaceId = 0;
		if (i <= mappingArrayCount)
			surfaceId = mapping->GetIndexArray().GetAt(i);
		spmSurface & surface = subMesh.surfaces[surfaceId];
		int surfaceSize = mesh->GetPolygonSize(i);

		std::stringstream str;
		str << "Surface" << i;
		surface.name = str.str();
		
		surface.textureDimensions[0] = 2;
		surface.textureDimensions[1] = 0;
		surface.textureDimensions[2] = 0;
		surface.textureDimensions[3] = 0;
		surface.textureDimensions[4] = 0;
		surface.textureDimensions[5] = 0;
		surface.textureDimensions[6] = 0;
		surface.textureDimensions[7] = 0;

		surface.flags = MDLSPM_CHUNK_VERTEXNORMAL;
		// first triangle
		spmTriangle f_tri;
		f_tri.indexes[0] = surface.triangles.size() * 3 + 0;
		f_tri.indexes[1] = surface.triangles.size() * 3 + 1;
		f_tri.indexes[2] = surface.triangles.size() * 3 + 2;
		surface.triangles.push_back(f_tri);	

		surface.vertexes.push_back( GetVertex(mesh, i, 0) );
		surface.vertexes.push_back( GetVertex(mesh, i, 2) );
		surface.vertexes.push_back( GetVertex(mesh, i, 1) );

		// second triangle
		if (surfaceSize == 4) 
		{
			spmTriangle s_tri;
			s_tri.indexes[0] = surface.triangles.size() * 3 + 0;
			s_tri.indexes[1] = surface.triangles.size() * 3 + 1;
			s_tri.indexes[2] = surface.triangles.size() * 3 + 2;
			surface.triangles.push_back(s_tri);

			surface.vertexes.push_back( GetVertex(mesh, i, 0) );
			surface.vertexes.push_back( GetVertex(mesh, i, 3) );
			surface.vertexes.push_back( GetVertex(mesh, i, 2) );
		}
	}
	
	/************************************************************************/
	/*                            Materials                                 */
	/************************************************************************/
	for (int m = 0; m < materialCount; m++)
	{
		spmSurface & surface = subMesh.surfaces[m];
		FbxSurfaceMaterial * lMaterial = (FbxSurfaceMaterial *)node->GetSrcObject(FbxCriteria::ObjectType(FbxSurfaceMaterial::ClassId), m);
		if (lMaterial)
			surface.textures.push_back( GetTexture(lMaterial) );		
	}
	return subMesh;
}

spmVertex GetVertex( FbxMesh * mesh, int poly, int vert)
{
	spmVertex vertex;
	FbxDouble3 scaling = mesh->GetNode()->LclScaling.Get();
	int vertIndex = mesh->GetPolygonVertex(poly, vert);
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	FbxVector4 pos = mesh->GetControlPointAt(vertIndex);
	vertex.position.x = float(  pos[0] * scaling[0]);
	vertex.position.y = float(  pos[1] * scaling[1]);
	vertex.position.z = float(- pos[2] * scaling[2]);
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	FbxVector4 normal;
	if (mesh->GetPolygonVertexNormal(poly, vert, normal)) 
	{
		vertex.normal.x = (float)normal[0];
		vertex.normal.y = (float)normal[1];
		vertex.normal.z = (float)normal[2];
	}
	else 
	{
		vertex.normal.x = 0;
		vertex.normal.y = 0;
		vertex.normal.z = 0;
	}
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	FbxVector2 UV;
	FbxGeometryElementUV * uv_set = mesh->GetElementUV();
	if (uv_set) 
	{
		textureUV texUV = {0, 0};
		if (mesh->GetPolygonVertexUV(poly, vert, uv_set->GetName(), UV)) 
		{
			texUV.U = float(   UV[0] );
			texUV.V = float( - UV[1] );
		}		
		vertex.UVs.push_back(texUV);
	} 
	else 
	{
		textureUV texUV = {0, 0};
		vertex.UVs.push_back(texUV);
	}
	return vertex;
}

spmTexture GetTexture( FbxSurfaceMaterial * material )
{
	spmTexture tex;
	int lTextureIndex = 0;
	FbxProperty lProperty = material->FindProperty(FbxLayerElement::sTextureChannelNames[lTextureIndex]);
	FbxCriteria textureClass = FbxCriteria::ObjectType(FbxTexture::ClassId);
	FbxCriteria layeredTextureClass = FbxCriteria::ObjectType(FbxLayeredTexture::ClassId);
	if (lProperty.IsValid())
	{
		int lTextureCount = lProperty.GetSrcObjectCount(textureClass);
		for (int j = 0; j < lTextureCount; j++)
		{
			FbxTexture * lTexture = FbxCast <FbxTexture> (lProperty.GetSrcObject(textureClass, j));
			if (lTexture)
			{
				FbxFileTexture * lFileTexture = FbxCast<FbxFileTexture>(lTexture);
				if (lFileTexture) tex.fileName = lFileTexture->GetFileName();
			}
		}
	}
	tex.fileName = tex.fileName.substr( tex.fileName.find_last_of("/") + 1 );
	tex.fileName = tex.fileName.substr( tex.fileName.find_last_of("\\") + 1 );
	return tex;
}
