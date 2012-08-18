#include "SPMTypes.h"

bool localSpace = false;
bool meshOnly = false;

spmSubmesh CreateObject( FbxNode * node )
{
	spmSubmesh subMesh;
	FbxMesh * mesh = node->GetMesh();
	
	if (!mesh) return spmSubmesh();

	DisplayString("collecting data ", node->GetName());

	int materialCount = node->GetMaterialCount();
	// 1 material = 1 sub mesh
	subMesh.surfaces.resize(materialCount);
	subMesh.flags = MDLSPM_CHUNK_GOURAUDSHADING;
	subMesh.reservedDataSize = 0;
	subMesh.name = node->GetName();

	bool animExist = IsAnimationExist(mesh);
	if (animExist)
		subMesh.flags |= MDLSPM_CHUNK_SKELETAL_ANIM;
	
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

		surface.vertexes.push_back( GetVertex(mesh, i, 0, surfaceId, surface.vertexes.size()) );
		surface.vertexes.push_back( GetVertex(mesh, i, 2, surfaceId, surface.vertexes.size()) );
		surface.vertexes.push_back( GetVertex(mesh, i, 1, surfaceId, surface.vertexes.size()) );

		// second triangle
		if (surfaceSize == 4) 
		{
			spmTriangle s_tri;
			s_tri.indexes[0] = surface.triangles.size() * 3 + 0;
			s_tri.indexes[1] = surface.triangles.size() * 3 + 1;
			s_tri.indexes[2] = surface.triangles.size() * 3 + 2;
			surface.triangles.push_back(s_tri);

			surface.vertexes.push_back( GetVertex(mesh, i, 0, surfaceId, surface.vertexes.size()) );
			surface.vertexes.push_back( GetVertex(mesh, i, 3, surfaceId, surface.vertexes.size()) );
			surface.vertexes.push_back( GetVertex(mesh, i, 2, surfaceId, surface.vertexes.size()) );
		}
	}
	
	/************************************************************************/
	/*                            Materials                                 */
	/************************************************************************/
	for (int m = 0; m < materialCount; m++)
	{
		spmSurface & surface = subMesh.surfaces[m];

		std::stringstream str;
		str << "Surface" << m;
		surface.name = str.str();

		FbxSurfaceMaterial * lMaterial = (FbxSurfaceMaterial *)node->GetSrcObject(FbxCriteria::ObjectType(FbxSurfaceMaterial::ClassId), m);
		if (lMaterial)
			surface.textures.push_back( GetTexture(lMaterial) );		
	}
	
	/************************************************************************/
	/*                          Animation                                   */
	/************************************************************************/
	if (animExist) 
	{
		FbxGeometry * geom = node->GetGeometry();
		FbxSkin * skin = (FbxSkin*)geom->GetDeformer(0, FbxDeformer::eSkin);
		subMesh.animation = GetAnimation(skin, subMesh.surfaces );
	}
	return subMesh;
}

spmVertex GetVertex( FbxMesh * mesh, int poly, int vert, int surfaceId, int vertexId)
{
	spmVertex vertex;
	vertex.surfaceId = surfaceId;
	vertex.vertexId = vertexId;
	int vertIndex = mesh->GetPolygonVertex(poly, vert);
	vertex.controlPointId = vertIndex; 
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	FbxVector4 pos;
	if (localSpace)
	{
		pos = mesh->GetControlPointAt(vertIndex) * mesh->GetNode()->LclScaling.Get();
	}
	else
	{
		FbxAnimEvaluator * evaluator = mesh->GetScene()->GetEvaluator();
		FbxAMatrix matrix = evaluator->GetNodeGlobalTransform(mesh->GetNode());
		pos = matrix.MultT( mesh->GetControlPointAt(vertIndex) );
	}
	vertex.position.x = float(  pos[0] );
	vertex.position.y = float(  pos[1] );
	vertex.position.z = float(- pos[2] );
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	FbxVector4 normal;
	if (mesh->GetPolygonVertexNormal(poly, vert, normal)) 
	{
		vertex.normal.x =   (float)normal[0];
		vertex.normal.y =   (float)normal[1];
		vertex.normal.z = - (float)normal[2];
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

bool IsAnimationExist( FbxGeometry * geometry )
{
	int skinCount = geometry->GetDeformerCount(FbxDeformer::eSkin);
	return skinCount > 0;
}

spmSkeletalAnimation GetAnimation( FbxSkin * skin, const std::vector<spmSurface> & surfaces )
{
	spmSkeletalAnimation animation;
	int clusterCount = skin->GetClusterCount();
	if (clusterCount > 0)
	{
		/************************************************************************/
		/*                 Find Root                                            */
		/************************************************************************/
		FbxNode * skeletonRoot;
		{
			FbxCluster * cluster = skin->GetCluster(0);
			FbxNode * bone = cluster->GetLink();
			while (bone->GetParent() && bone->GetParent()->GetSkeleton()) bone = bone->GetParent();
			skeletonRoot = bone;
		}
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		animation.name = skeletonRoot->GetName();
		std::vector<std::pair<FbxNode *, FbxCluster *>> links;
		FillBoneList(animation.joints, links, skeletonRoot);
		for (int i = 0; i < clusterCount; i++)
		{
			FbxCluster * cluster = skin->GetCluster(i);
			FbxNode * link = cluster->GetLink();
			for (unsigned int j = 0; j < links.size(); j++)
			{
				std::pair<FbxNode *, FbxCluster *> & pair = links[j];
				if (pair.first == link)
					pair.second = cluster;
			}
		}
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		for (unsigned int i = 0; i < links.size(); i++)
		{
			FillJoint(animation.joints[i], links[i]);
			FixWeights(animation.joints[i], surfaces);
		}
	}
	return animation;
}

void FillBoneList( std::vector<spmAnimationJoint> & list, std::vector<std::pair<FbxNode *, FbxCluster *>> & links, FbxNode * node, int index)
{
	spmAnimationJoint joint;
	joint.parentIndex = index;
	joint.name = node->GetName();
	joint.index = list.size();
	list.push_back(joint);
	links.push_back( std::pair<FbxNode *, FbxCluster *>(node, nullptr) );
	int childCount = node->GetChildCount();
	for (int i = 0; i < childCount; i++)
	{
		FbxNode * child = node->GetChild(i);
		if (child->GetSkeleton())
			FillBoneList(list, links, child, joint.index);
	}
}

void FillJoint( spmAnimationJoint & joint, std::pair<FbxNode *, FbxCluster *> pair )
{
	FbxNode * node = pair.first;
	FbxAMatrix matrix = GetMatrix(node);

	joint.position.x =   float(matrix.GetT()[0]);
	joint.position.y =   float(matrix.GetT()[1]);
	joint.position.z = - float(matrix.GetT()[2]);
	joint.rotation.x =   float(matrix.GetQ()[0]);
	joint.rotation.y =   float(matrix.GetQ()[1]);
	joint.rotation.z = - float(matrix.GetQ()[2]);
	joint.rotation.w =   float(matrix.GetQ()[3]);
	joint.scale.x =      float(matrix.GetS()[0]);
	joint.scale.y =      float(matrix.GetS()[1]);
	joint.scale.z =      float(matrix.GetS()[2]);

	/************************************************************************/
	/*                   animation                                          */
	/************************************************************************/

	FbxTimeSpan timeSpan;
	const FbxGlobalSettings & globalSettings = node->GetScene()->GetGlobalSettings();
	globalSettings.GetTimelineDefaultTimeSpan(timeSpan);
	
	int lS = 0;
	int lE = int(timeSpan.GetDuration().GetFrameCount());
	
	for (int i = lS; i < lE; i++)
	{
		FbxTime time;
		time.SetFrame(i);
		FbxAMatrix anim = GetMatrix(node, time);
		spmJointKeyframe frame;
		frame.frame = i;
		frame.position.x =   float(anim.GetT()[0]);
		frame.position.y =   float(anim.GetT()[1]);
		frame.position.z = - float(anim.GetT()[2]);
		frame.rotation.x =   float(anim.GetQ()[0]);
		frame.rotation.y =   float(anim.GetQ()[1]);
		frame.rotation.z = - float(anim.GetQ()[2]);
		frame.rotation.w =   float(anim.GetQ()[3]);
		frame.scale.x =      float(anim.GetS()[0]);
		frame.scale.y =      float(anim.GetS()[1]);
		frame.scale.z =      float(anim.GetS()[2]);
		joint.keyFrames.push_back(frame);
	}

	/************************************************************************/
	/*                  skinning                                            */
	/************************************************************************/
	if (pair.second)
	{
		FbxCluster * cluster = pair.second;
		int lIndexCount = cluster->GetControlPointIndicesCount();
		int* lIndices = cluster->GetControlPointIndices();
		double* lWeights = cluster->GetControlPointWeights();
	
		for (int k = 0; k < lIndexCount; k++)
		{
			int index = lIndices[k];
			float weight = (float) lWeights[k];
			if (weight > 0.000001)
			{
				spmJointVertexWeight v;
				v.vertexIndex = index;	// << not valid at the moment
				v.weight = weight;
				v.sufraceId = 0;		// << not valid at this moment
				joint.vertexes.push_back(v);
			}
		}
	}
}

FbxAMatrix GetMatrix( FbxNode * node, FbxTime time )
{
	/************************************************************************/
	/*                  magic                                               */
	/************************************************************************/
	FbxAnimEvaluator * evaluator = node->GetScene()->GetEvaluator();
	FbxNode * parent = node->GetParent();
	FbxAMatrix res = evaluator->GetNodeLocalTransform(node, time);
	if (parent && !parent->GetSkeleton() && !localSpace)
		res = evaluator->GetNodeGlobalTransform(node, time);
	return res;
}

void FixWeights( spmAnimationJoint & joint, const std::vector<spmSurface> & surfaces )
{
	std::vector<spmJointVertexWeight> newWeights;
	for (unsigned int i = 0; i < joint.vertexes.size(); i++)
	{
		spmJointVertexWeight & weight = joint.vertexes[i];
		for (unsigned int j = 0; j < surfaces.size(); j++)
		{
			spmSurface surface = surfaces[j];
			for (unsigned int v = 0; v < surface.vertexes.size(); v++)
			{
				spmVertex vertex = surface.vertexes[v];
				if (weight.vertexIndex == vertex.controlPointId)
				{
					spmJointVertexWeight w2(weight);
					w2.vertexIndex = vertex.vertexId;
					w2.sufraceId = vertex.surfaceId;
					newWeights.push_back(w2);
				}
				FbxMesh * mesh = 0;
			}
		}
	}
	joint.vertexes = newWeights;
}