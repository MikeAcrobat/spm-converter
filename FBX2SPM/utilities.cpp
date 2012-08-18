#include "utilities.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayHierarchy(FbxScene* pScene)
{
	int i;
	FbxNode* lRootNode = pScene->GetRootNode();

	for( i = 0; i < lRootNode->GetChildCount(); i++)
	{
		DisplayHierarchy(lRootNode->GetChild(i), 0);
	}
}

void DisplayHierarchy(FbxNode* pNode, int pDepth)
{
	FbxString lString;
	int i;

	for(i = 0; i < pDepth; i++)
	{
		lString += "     ";
	}

	lString += pNode->GetName();
	lString += "\n";

	FBXSDK_printf(lString.Buffer());

	for(i = 0; i < pNode->GetChildCount(); i++)
	{
		DisplayHierarchy(pNode->GetChild(i), pDepth + 1);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMetaDataConnections(FbxObject* pObject)
{
	int nbMetaData = pObject->GetSrcObjectCount(FbxCriteria::ObjectType(FbxObjectMetaData::ClassId));
	if (nbMetaData > 0)
		DisplayString("    MetaData connections ");

	for (int i = 0; i < nbMetaData; i++)
	{
		FbxObjectMetaData* metaData = (FbxObjectMetaData*)pObject->GetSrcObject(FbxCriteria::ObjectType(FbxObjectMetaData::ClassId), i);
		DisplayString("        Name: ", (char*)metaData->GetName());
	}
}

void DisplayString(const char* pHeader, const char* pValue /* = "" */, const char* pSuffix /* = "" */)
{
	FbxString lString;

	lString = pHeader;
	lString += pValue;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void DisplayBool(const char* pHeader, bool pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;

	lString = pHeader;
	lString += pValue ? "true" : "false";
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void DisplayInt(const char* pHeader, int pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;

	lString = pHeader;
	lString += pValue;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void DisplayDouble(const char* pHeader, double pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;
	FbxString lFloatValue = (float) pValue;

	lFloatValue = pValue <= -HUGE_VAL ? "-INFINITY" : lFloatValue.Buffer();
	lFloatValue = pValue >=  HUGE_VAL ?  "INFINITY" : lFloatValue.Buffer();

	lString = pHeader;
	lString += lFloatValue;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void Display2DVector(const char* pHeader, FbxVector2 pValue, const char* pSuffix  /* = "" */)
{
	FbxString lString;
	FbxString lFloatValue1 = (float)pValue[0];
	FbxString lFloatValue2 = (float)pValue[1];

	lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
	lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
	lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
	lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();

	lString = pHeader;
	lString += lFloatValue1;
	lString += ", ";
	lString += lFloatValue2;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void Display3DVector(const char* pHeader, FbxVector4 pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;
	FbxString lFloatValue1 = (float)pValue[0];
	FbxString lFloatValue2 = (float)pValue[1];
	FbxString lFloatValue3 = (float)pValue[2];

	lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
	lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
	lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
	lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();
	lFloatValue3 = pValue[2] <= -HUGE_VAL ? "-INFINITY" : lFloatValue3.Buffer();
	lFloatValue3 = pValue[2] >=  HUGE_VAL ?  "INFINITY" : lFloatValue3.Buffer();

	lString = pHeader;
	lString += lFloatValue1;
	lString += ", ";
	lString += lFloatValue2;
	lString += ", ";
	lString += lFloatValue3;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}

void Display4DVector(const char* pHeader, FbxVector4 pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;
	FbxString lFloatValue1 = (float)pValue[0];
	FbxString lFloatValue2 = (float)pValue[1];
	FbxString lFloatValue3 = (float)pValue[2];
	FbxString lFloatValue4 = (float)pValue[3];

	lFloatValue1 = pValue[0] <= -HUGE_VAL ? "-INFINITY" : lFloatValue1.Buffer();
	lFloatValue1 = pValue[0] >=  HUGE_VAL ?  "INFINITY" : lFloatValue1.Buffer();
	lFloatValue2 = pValue[1] <= -HUGE_VAL ? "-INFINITY" : lFloatValue2.Buffer();
	lFloatValue2 = pValue[1] >=  HUGE_VAL ?  "INFINITY" : lFloatValue2.Buffer();
	lFloatValue3 = pValue[2] <= -HUGE_VAL ? "-INFINITY" : lFloatValue3.Buffer();
	lFloatValue3 = pValue[2] >=  HUGE_VAL ?  "INFINITY" : lFloatValue3.Buffer();
	lFloatValue4 = pValue[3] <= -HUGE_VAL ? "-INFINITY" : lFloatValue4.Buffer();
	lFloatValue4 = pValue[3] >=  HUGE_VAL ?  "INFINITY" : lFloatValue4.Buffer();

	lString = pHeader;
	lString += lFloatValue1;
	lString += ", ";
	lString += lFloatValue2;
	lString += ", ";
	lString += lFloatValue3;
	lString += ", ";
	lString += lFloatValue4;
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void DisplayColor(const char* pHeader, FbxPropertyT<FbxDouble3> pValue, const char* pSuffix /* = "" */)

{
	FbxString lString;

	lString = pHeader;
	//lString += (float) pValue.mRed;
	//lString += (double)pValue.GetArrayItem(0);
	lString += " (red), ";
	//lString += (float) pValue.mGreen;
	//lString += (double)pValue.GetArrayItem(1);
	lString += " (green), ";
	//lString += (float) pValue.mBlue;
	//lString += (double)pValue.GetArrayItem(2);
	lString += " (blue)";
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}


void DisplayColor(const char* pHeader, FbxColor pValue, const char* pSuffix /* = "" */)
{
	FbxString lString;

	lString = pHeader;
	lString += (float) pValue.mRed;

	lString += " (red), ";
	lString += (float) pValue.mGreen;

	lString += " (green), ";
	lString += (float) pValue.mBlue;

	lString += " (blue)";
	lString += pSuffix;
	lString += "\n";
	FBXSDK_printf(lString);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayAnimation(FbxScene* pScene)
{
	int i;
	int stacCount = pScene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxAnimStack::ClassId));
	for (i = 0; i < stacCount; i++)
	{
		FbxAnimStack* lAnimStack = FbxCast<FbxAnimStack>(pScene->GetSrcObject(FbxCriteria::ObjectType(FbxAnimStack::ClassId), i));

		FbxString lOutputString = "Animation Stack Name: ";
		lOutputString += lAnimStack->GetName();
		lOutputString += "\n\n";
		FBXSDK_printf(lOutputString);

		//DisplayAnimation(lAnimStack, pScene->GetRootNode(), true);
		DisplayAnimation(lAnimStack, pScene->GetRootNode());
	}
}

void DisplayAnimation(FbxAnimStack* pAnimStack, FbxNode* pNode, bool isSwitcher)
{
	int l;
	int nbAnimLayers = pAnimStack->GetMemberCount(FbxCriteria::ObjectType(FbxAnimLayer::ClassId));
	FbxString lOutputString;

	lOutputString = "Animation stack contains ";
	lOutputString += nbAnimLayers;
	lOutputString += " Animation Layer(s)\n";
	FBXSDK_printf(lOutputString);

	for (l = 0; l < nbAnimLayers; l++)
	{
		FbxAnimLayer* lAnimLayer = (FbxAnimLayer*)pAnimStack->GetMember(FbxCriteria::ObjectType(FbxAnimLayer::ClassId), l);

		lOutputString = "AnimLayer ";
		lOutputString += l;
		lOutputString += "\n";
		FBXSDK_printf(lOutputString);

		DisplayAnimation(lAnimLayer, pNode, isSwitcher);
	}
}

void DisplayAnimation(FbxAnimLayer* pAnimLayer, FbxNode* pNode, bool isSwitcher)
{
	int lModelCount;
	FbxString lOutputString;

	lOutputString = "     Node Name: ";
	lOutputString += pNode->GetName();
	lOutputString += "\n\n";
	FBXSDK_printf(lOutputString);

	DisplayChannels(pNode, pAnimLayer, DisplayCurveKeys, DisplayListCurveKeys, isSwitcher);
	FBXSDK_printf ("\n");

	for(lModelCount = 0; lModelCount < pNode->GetChildCount(); lModelCount++)
	{
		DisplayAnimation(pAnimLayer, pNode->GetChild(lModelCount), isSwitcher);
	}
}


void DisplayChannels(FbxNode* pNode, FbxAnimLayer* pAnimLayer, void (*DisplayCurve) (FbxAnimCurve* pCurve), void (*DisplayListCurve) (FbxAnimCurve* pCurve, FbxProperty* pProperty), bool isSwitcher)
{
	FbxAnimCurve* lAnimCurve = NULL;

	// Display general curves.
	if (!isSwitcher)
	{
		lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
		if (lAnimCurve)
		{
			FBXSDK_printf("        TX\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (lAnimCurve)
		{
			FBXSDK_printf("        TY\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = pNode->LclTranslation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (lAnimCurve)
		{
			FBXSDK_printf("        TZ\n");
			DisplayCurve(lAnimCurve);
		}

		lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
		if (lAnimCurve)
		{
			FBXSDK_printf("        RX\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (lAnimCurve)
		{
			FBXSDK_printf("        RY\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = pNode->LclRotation.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (lAnimCurve)
		{
			FBXSDK_printf("        RZ\n");
			DisplayCurve(lAnimCurve);
		}

		lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_X);
		if (lAnimCurve)
		{
			FBXSDK_printf("        SX\n");
			DisplayCurve(lAnimCurve);
		}    
		lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);
		if (lAnimCurve)
		{
			FBXSDK_printf("        SY\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = pNode->LclScaling.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COMPONENT_Z);
		if (lAnimCurve)
		{
			FBXSDK_printf("        SZ\n");
			DisplayCurve(lAnimCurve);
		}
	}

	// Display curves specific to a light or marker.
	FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

	if (lNodeAttribute)
	{
		lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_RED);
		if (lAnimCurve)
		{
			FBXSDK_printf("        Red\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_GREEN);
		if (lAnimCurve)
		{
			FBXSDK_printf("        Green\n");
			DisplayCurve(lAnimCurve);
		}
		lAnimCurve = lNodeAttribute->Color.GetCurve(pAnimLayer, FBXSDK_CURVENODE_COLOR_BLUE);
		if (lAnimCurve)
		{
			FBXSDK_printf("        Blue\n");
			DisplayCurve(lAnimCurve);
		}

		// Display curves specific to a light.
		FbxLight* light = pNode->GetLight();
		if (light)
		{
			lAnimCurve = light->Intensity.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Intensity\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = light->OuterAngle.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Outer Angle\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = light->Fog.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Fog\n");
				DisplayCurve(lAnimCurve);
			}
		}

		// Display curves specific to a camera.
		FbxCamera* camera = pNode->GetCamera();
		if (camera)
		{
			lAnimCurve = camera->FieldOfView.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Field of View\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = camera->FieldOfViewX.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Field of View X\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = camera->FieldOfViewY.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Field of View Y\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = camera->OpticalCenterX.GetCurve(pAnimLayer);
			if (lAnimCurve)
			{
				FBXSDK_printf("        Optical Center X\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = camera->OpticalCenterY.GetCurve(pAnimLayer);
			if(lAnimCurve)
			{
				FBXSDK_printf("        Optical Center Y\n");
				DisplayCurve(lAnimCurve);
			}

			lAnimCurve = camera->Roll.GetCurve(pAnimLayer);
			if(lAnimCurve)
			{
				FBXSDK_printf("        Roll\n");
				DisplayCurve(lAnimCurve);
			}
		}

		// Display curves specific to a geometry.
		if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh ||
			lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs ||
			lNodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch)
		{
			FbxGeometry* lGeometry = (FbxGeometry*) lNodeAttribute;

			int lBlendShapeDeformerCount = lGeometry->GetDeformerCount(FbxDeformer::eBlendShape);
			for(int lBlendShapeIndex = 0; lBlendShapeIndex<lBlendShapeDeformerCount; ++lBlendShapeIndex)
			{
				FbxBlendShape* lBlendShape = (FbxBlendShape*)lGeometry->GetDeformer(lBlendShapeIndex, FbxDeformer::eBlendShape);

				int lBlendShapeChannelCount = lBlendShape->GetBlendShapeChannelCount();
				for(int lChannelIndex = 0; lChannelIndex<lBlendShapeChannelCount; ++lChannelIndex)
				{
					FbxBlendShapeChannel* lChannel = lBlendShape->GetBlendShapeChannel(lChannelIndex);
					const char* lChannelName = lChannel->GetName();

					lAnimCurve = lGeometry->GetShapeChannel(lBlendShapeIndex, lChannelIndex, pAnimLayer, true);
					if(lAnimCurve)
					{
						FBXSDK_printf("        Shape %s\n", lChannelName);
						DisplayCurve(lAnimCurve);
					}
				}
			}
		}
	}

	// Display curves specific to properties
	FbxProperty lProperty = pNode->GetFirstProperty();
	while (lProperty.IsValid())
	{
		if (lProperty.GetFlag(FbxPropertyAttr::eUser))
		{
			FbxString lFbxFCurveNodeName  = lProperty.GetName();
			FbxAnimCurveNode* lCurveNode = lProperty.GetCurveNode(pAnimLayer);

			if (!lCurveNode){
				lProperty = pNode->GetNextProperty(lProperty);
				continue;
			}

			FbxDataType lDataType = lProperty.GetPropertyDataType();
			if (lDataType.GetType() == eFbxBool || lDataType.GetType() == eFbxDouble || lDataType.GetType() == eFbxFloat || lDataType.GetType() == eFbxInt)
			{
				FbxString lMessage;

				lMessage =  "        Property ";
				lMessage += lProperty.GetName();
				if (lProperty.GetLabel().GetLen() > 0)
				{
					lMessage += " (Label: ";
					lMessage += lProperty.GetLabel();
					lMessage += ")";
				};

				DisplayString(lMessage.Buffer());

				for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
				{
					lAnimCurve = lCurveNode->GetCurve(0U, c);
					if (lAnimCurve)
						DisplayCurve(lAnimCurve);
				}
			}
			else if(lDataType.GetType() == eFbxDouble3 || lDataType.GetType() == eFbxDouble4 || lDataType.Is(FbxColor3DT) || lDataType.Is(FbxColor4DT))
			{
				char* lComponentName1 = (lDataType.Is(FbxColor3DT) ||lDataType.Is(FbxColor4DT)) ? (char*)FBXSDK_CURVENODE_COLOR_RED : (char*)"X";
				char* lComponentName2 = (lDataType.Is(FbxColor3DT) ||lDataType.Is(FbxColor4DT)) ? (char*)FBXSDK_CURVENODE_COLOR_GREEN : (char*)"Y";
				char* lComponentName3 = (lDataType.Is(FbxColor3DT) ||lDataType.Is(FbxColor4DT)) ? (char*)FBXSDK_CURVENODE_COLOR_BLUE  : (char*)"Z";
				FbxString      lMessage;

				lMessage =  "        Property ";
				lMessage += lProperty.GetName();
				if (lProperty.GetLabel().GetLen() > 0)
				{
					lMessage += " (Label: ";
					lMessage += lProperty.GetLabel();
					lMessage += ")";
				}
				DisplayString(lMessage.Buffer());

				for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
				{
					lAnimCurve = lCurveNode->GetCurve(0U, c);
					if (lAnimCurve)
					{
						DisplayString("        Component ", lComponentName1);
						DisplayCurve(lAnimCurve);
					}
				}

				for( int c = 0; c < lCurveNode->GetCurveCount(1U); c++ )
				{
					lAnimCurve = lCurveNode->GetCurve(1U, c);
					if (lAnimCurve)
					{
						DisplayString("        Component ", lComponentName2);
						DisplayCurve(lAnimCurve);
					}
				}

				for( int c = 0; c < lCurveNode->GetCurveCount(2U); c++ )
				{
					lAnimCurve = lCurveNode->GetCurve(2U, c);
					if (lAnimCurve)
					{
						DisplayString("        Component ", lComponentName3);
						DisplayCurve(lAnimCurve);
					}
				}
			}
			else if (lDataType.GetType() == eFbxEnum)
			{
				FbxString lMessage;

				lMessage =  "        Property ";
				lMessage += lProperty.GetName();
				if (lProperty.GetLabel().GetLen() > 0)
				{
					lMessage += " (Label: ";
					lMessage += lProperty.GetLabel();
					lMessage += ")";
				};
				DisplayString(lMessage.Buffer());

				for( int c = 0; c < lCurveNode->GetCurveCount(0U); c++ )
				{
					lAnimCurve = lCurveNode->GetCurve(0U, c);
					if (lAnimCurve)
						DisplayListCurve(lAnimCurve, &lProperty);
				}                
			}
		}

		lProperty = pNode->GetNextProperty(lProperty);
	} // while

}


static int InterpolationFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eInterpolationConstant) == FbxAnimCurveDef::eInterpolationConstant ) return 1;
	if( (flags & FbxAnimCurveDef::eInterpolationLinear) == FbxAnimCurveDef::eInterpolationLinear ) return 2;
	if( (flags & FbxAnimCurveDef::eInterpolationCubic) == FbxAnimCurveDef::eInterpolationCubic ) return 3;
	return 0;
}

static int ConstantmodeFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eConstantStandard) == FbxAnimCurveDef::eConstantStandard ) return 1;
	if( (flags & FbxAnimCurveDef::eConstantNext) == FbxAnimCurveDef::eConstantNext ) return 2;
	return 0;
}

static int TangentmodeFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eTangentAuto) == FbxAnimCurveDef::eTangentAuto ) return 1;
	if( (flags & FbxAnimCurveDef::eTangentAutoBreak)== FbxAnimCurveDef::eTangentAutoBreak ) return 2;
	if( (flags & FbxAnimCurveDef::eTangentTCB) == FbxAnimCurveDef::eTangentTCB ) return 3;
	if( (flags & FbxAnimCurveDef::eTangentUser) == FbxAnimCurveDef::eTangentUser ) return 4;
	if( (flags & FbxAnimCurveDef::eTangentGenericBreak) == FbxAnimCurveDef::eTangentGenericBreak ) return 5;
	if( (flags & FbxAnimCurveDef::eTangentBreak) == FbxAnimCurveDef::eTangentBreak ) return 6;
	return 0;
}

static int TangentweightFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eWeightedNone) == FbxAnimCurveDef::eWeightedNone ) return 1;
	if( (flags & FbxAnimCurveDef::eWeightedRight) == FbxAnimCurveDef::eWeightedRight ) return 2;
	if( (flags & FbxAnimCurveDef::eWeightedNextLeft) == FbxAnimCurveDef::eWeightedNextLeft ) return 3;
	return 0;
}

static int TangentVelocityFlagToIndex(int flags)
{
	if( (flags & FbxAnimCurveDef::eVelocityNone) == FbxAnimCurveDef::eVelocityNone ) return 1;
	if( (flags & FbxAnimCurveDef::eVelocityRight) == FbxAnimCurveDef::eVelocityRight ) return 2;
	if( (flags & FbxAnimCurveDef::eVelocityNextLeft) == FbxAnimCurveDef::eVelocityNextLeft ) return 3;
	return 0;
}

void DisplayCurveKeys(FbxAnimCurve* pCurve)
{
	static char* interpolation[] = { "?", "constant", "linear", "cubic"};
	static char* constantMode[] =  { "?", "Standard", "Next" };
	static char* cubicMode[] =     { "?", "Auto", "Auto break", "Tcb", "User", "Break", "User break" };
	static char* tangentWVMode[] = { "?", "None", "Right", "Next left" };

	FbxTime   lKeyTime;
	float   lKeyValue;
	char    lTimeString[256];
	FbxString lOutputString;
	int     lCount;

	int lKeyCount = pCurve->KeyGetCount();

	for(lCount = 0; lCount < lKeyCount; lCount++)
	{
		lKeyValue = static_cast<float>(pCurve->KeyGetValue(lCount));
		lKeyTime  = pCurve->KeyGetTime(lCount);

		lOutputString = "            Key Time: ";
		lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));
		lOutputString += ".... Key Value: ";
		lOutputString += lKeyValue;
		lOutputString += " [ ";
		lOutputString += interpolation[ InterpolationFlagToIndex(pCurve->KeyGetInterpolation(lCount)) ];
		if ((pCurve->KeyGetInterpolation(lCount)&FbxAnimCurveDef::eInterpolationConstant) == FbxAnimCurveDef::eInterpolationConstant)
		{
			lOutputString += " | ";
			lOutputString += constantMode[ ConstantmodeFlagToIndex(pCurve->KeyGetConstantMode(lCount)) ];
		}
		else if ((pCurve->KeyGetInterpolation(lCount)&FbxAnimCurveDef::eInterpolationCubic) == FbxAnimCurveDef::eInterpolationCubic)
		{
			lOutputString += " | ";
			lOutputString += cubicMode[ TangentmodeFlagToIndex(pCurve->KeyGetTangentMode(lCount)) ];
			lOutputString += " | ";
			lOutputString += tangentWVMode[ TangentweightFlagToIndex(pCurve->KeyGet(lCount).GetTangentWeightMode()) ];
			lOutputString += " | ";
			lOutputString += tangentWVMode[ TangentVelocityFlagToIndex(pCurve->KeyGet(lCount).GetTangentVelocityMode()) ];
		}
		lOutputString += " ]";
		lOutputString += "\n";
		FBXSDK_printf (lOutputString);
	}
}

void DisplayListCurveKeys(FbxAnimCurve* pCurve, FbxProperty* pProperty)
{
	FbxTime   lKeyTime;
	int     lKeyValue;
	char    lTimeString[256];
	FbxString lListValue;
	FbxString lOutputString;
	int     lCount;

	int lKeyCount = pCurve->KeyGetCount();

	for(lCount = 0; lCount < lKeyCount; lCount++)
	{
		lKeyValue = static_cast<int>(pCurve->KeyGetValue(lCount));
		lKeyTime  = pCurve->KeyGetTime(lCount);

		lOutputString = "            Key Time: ";
		lOutputString += lKeyTime.GetTimeString(lTimeString, FbxUShort(256));
		lOutputString += ".... Key Value: ";
		lOutputString += lKeyValue;
		lOutputString += " (";
		lOutputString += pProperty->GetEnumValue(lKeyValue);
		lOutputString += ")";

		lOutputString += "\n";
		FBXSDK_printf (lOutputString);
	}
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMaterial(FbxGeometry* pGeometry)
{
	int lMaterialCount = 0;
	FbxNode* lNode = NULL;
	if(pGeometry){
		lNode = pGeometry->GetNode();
		if(lNode)
			lMaterialCount = lNode->GetMaterialCount();    
	}

	if (lMaterialCount > 0)
	{
		FbxPropertyT<FbxDouble3> lKFbxDouble3;
		FbxPropertyT<FbxDouble> lKFbxDouble1;
		FbxColor theColor;

		for (int lCount = 0; lCount < lMaterialCount; lCount ++)
		{
			DisplayInt("        Material ", lCount);

			FbxSurfaceMaterial *lMaterial = lNode->GetMaterial(lCount);

			DisplayString("            Name: \"", (char *) lMaterial->GetName(), "\""); 

			//Get the implementation to see if it's a hardware shader.
			const FbxImplementation* lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_HLSL);
			FbxString lImplemenationType = "HLSL";
			if(!lImplementation)
			{
				lImplementation = GetImplementation(lMaterial, FBXSDK_IMPLEMENTATION_CGFX);
				lImplemenationType = "CGFX";
			}
			if(lImplementation)
			{
				//Now we have a hardware shader, let's read it
				FBXSDK_printf("            Hardware Shader Type: %s\n", lImplemenationType.Buffer());
				FbxBindingTable const* lRootTable = lImplementation->GetRootTable();
				FbxString lFileName = lRootTable->DescAbsoluteURL.Get();
				FbxString lTechniqueName = lRootTable->DescTAG.Get(); 


				FbxBindingTable const* lTable = lImplementation->GetRootTable();
				size_t lEntryNum = lTable->GetEntryCount();

				for(int i=0;i <(int)lEntryNum; ++i)
				{
					const FbxBindingTableEntry& lEntry = lTable->GetEntry(i);
					const char* lEntrySrcType = lEntry.GetEntryType(true); 
					FbxProperty lFbxProp;


					FbxString lTest = lEntry.GetSource();
					FBXSDK_printf("            Entry: %s\n", lTest.Buffer());


					if ( strcmp( FbxPropertyEntryView::sEntryType, lEntrySrcType ) == 0 )
					{   
						lFbxProp = lMaterial->FindPropertyHierarchical(lEntry.GetSource()); 
						if(!lFbxProp.IsValid())
						{
							lFbxProp = lMaterial->RootProperty.FindHierarchical(lEntry.GetSource());
						}


					}
					else if( strcmp( FbxConstantEntryView::sEntryType, lEntrySrcType ) == 0 )
					{
						lFbxProp = lImplementation->GetConstants().FindHierarchical(lEntry.GetSource());
					}
					if(lFbxProp.IsValid())
					{
						if( lFbxProp.GetSrcObjectCount( FbxCriteria::ObjectType(FbxTexture::ClassId) ) > 0 )
						{
							//do what you want with the textures
							for(int j=0; j<lFbxProp.GetSrcObjectCount(FbxCriteria::ObjectType(FbxFileTexture::ClassId)); ++j)
							{
								FbxFileTexture *lTex = (FbxFileTexture *)lFbxProp.GetSrcObject(FbxCriteria::ObjectType(FbxFileTexture::ClassId),j);
								FBXSDK_printf("           File Texture: %s\n", lTex->GetFileName());
							}
							for(int j=0; j<lFbxProp.GetSrcObjectCount(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId)); ++j)
							{
								FbxLayeredTexture *lTex = (FbxLayeredTexture *)lFbxProp.GetSrcObject(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId),j);
								FBXSDK_printf("        Layered Texture: %s\n", lTex->GetName());
							}
							for(int j=0; j<lFbxProp.GetSrcObjectCount(FbxCriteria::ObjectType(FbxProceduralTexture::ClassId)); ++j)
							{
								FbxProceduralTexture *lTex = (FbxProceduralTexture *)lFbxProp.GetSrcObject(FbxCriteria::ObjectType(FbxProceduralTexture::ClassId),j);
								FBXSDK_printf("     Procedural Texture: %s\n", lTex->GetName());
							}
						}
						else
						{
							FbxDataType lFbxType = lFbxProp.GetPropertyDataType();
							FbxString blah = lFbxType.GetName();
							if(FbxBoolDT == lFbxType)
							{
								DisplayBool("                Bool: ", lFbxProp.Get<FbxBool>() );
							}
							else if ( FbxIntDT == lFbxType ||  FbxEnumDT  == lFbxType )
							{
								DisplayInt("                Int: ", lFbxProp.Get<FbxInt>());
							}
							else if ( FbxFloatDT == lFbxType)
							{
								DisplayDouble("                Float: ", lFbxProp.Get<FbxFloat>());

							}
							else if ( FbxDoubleDT == lFbxType)
							{
								DisplayDouble("                Double: ", lFbxProp.Get<FbxDouble>());
							}
							else if ( FbxStringDT == lFbxType
								||  FbxUrlDT  == lFbxType
								||  FbxXRefUrlDT  == lFbxType )
							{
								DisplayString("                String: ", lFbxProp.Get<FbxString>().Buffer());
							}
							else if ( FbxDouble2DT == lFbxType)
							{
								FbxDouble2 lDouble2 = lFbxProp.Get<FbxDouble2>();
								FbxVector2 lVect;
								lVect[0] = lDouble2[0];
								lVect[1] = lDouble2[1];

								Display2DVector("                2D vector: ", lVect);
							}
							else if ( FbxDouble3DT == lFbxType || FbxColor3DT == lFbxType)
							{
								FbxDouble3 lDouble3 = lFbxProp.Get<FbxDouble3>();


								FbxVector4 lVect;
								lVect[0] = lDouble3[0];
								lVect[1] = lDouble3[1];
								lVect[2] = lDouble3[2];
								Display3DVector("                3D vector: ", lVect);
							}

							else if ( FbxDouble4DT == lFbxType || FbxColor4DT == lFbxType)
							{
								FbxDouble4 lDouble4 = lFbxProp.Get<FbxDouble4>();
								FbxVector4 lVect;
								lVect[0] = lDouble4[0];
								lVect[1] = lDouble4[1];
								lVect[2] = lDouble4[2];
								lVect[3] = lDouble4[3];
								Display4DVector("                4D vector: ", lVect);
							}
							else if ( FbxDouble4x4DT == lFbxType)
							{
								FbxDouble4x4 lDouble44 = lFbxProp.Get<FbxDouble4x4>();
								for(int j=0; j<4; ++j)
								{

									FbxVector4 lVect;
									lVect[0] = lDouble44[j][0];
									lVect[1] = lDouble44[j][1];
									lVect[2] = lDouble44[j][2];
									lVect[3] = lDouble44[j][3];
									Display4DVector("                4x4D vector: ", lVect);
								}

							}
						}

					}   
				}
			}
			else if (lMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				// We found a Phong material.  Display its properties.

				// Display the Ambient Color
				lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Ambient;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Ambient: ", theColor);

				// Display the Diffuse Color
				lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Diffuse;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Diffuse: ", theColor);

				// Display the Specular Color (unique to Phong materials)
				lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Specular;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Specular: ", theColor);

				// Display the Emissive Color
				lKFbxDouble3 =((FbxSurfacePhong *) lMaterial)->Emissive;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Emissive: ", theColor);

				//Opacity is Transparency factor now
				lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->TransparencyFactor;
				DisplayDouble("            Opacity: ", 1.0-lKFbxDouble1.Get());

				// Display the Shininess
				lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->Shininess;
				DisplayDouble("            Shininess: ", lKFbxDouble1.Get());

				// Display the Reflectivity
				lKFbxDouble1 =((FbxSurfacePhong *) lMaterial)->ReflectionFactor;
				DisplayDouble("            Reflectivity: ", lKFbxDouble1.Get());
			}
			else if(lMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) )
			{
				// We found a Lambert material. Display its properties.
				// Display the Ambient Color
				lKFbxDouble3=((FbxSurfaceLambert *)lMaterial)->Ambient;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Ambient: ", theColor);

				// Display the Diffuse Color
				lKFbxDouble3 =((FbxSurfaceLambert *)lMaterial)->Diffuse;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Diffuse: ", theColor);

				// Display the Emissive
				lKFbxDouble3 =((FbxSurfaceLambert *)lMaterial)->Emissive;
				theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);
				DisplayColor("            Emissive: ", theColor);

				// Display the Opacity
				lKFbxDouble1 =((FbxSurfaceLambert *)lMaterial)->TransparencyFactor;
				DisplayDouble("            Opacity: ", 1.0-lKFbxDouble1.Get());
			}
			else
				DisplayString("Unknown type of Material");

			FbxPropertyT<FbxString> lString;
			lString = lMaterial->ShadingModel;
			DisplayString("            Shading Model: ", lString.Get().Buffer());
			DisplayString("");
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayMesh(FbxNode* pNode)
{
	FbxMesh* lMesh = (FbxMesh*) pNode->GetNodeAttribute ();

	DisplayString("Mesh Name: ", (char *) pNode->GetName());
	DisplayMetaDataConnections(lMesh);
	DisplayControlsPoints(lMesh);
	DisplayPolygons(lMesh);
	DisplayMaterialMapping(lMesh);
	DisplayMaterial(lMesh);
	DisplayTexture(lMesh);
	DisplayMaterialConnections(lMesh);
	DisplayLink(lMesh);
	DisplayShape(lMesh);
}


void DisplayControlsPoints(FbxMesh* pMesh)
{
	int i, lControlPointsCount = pMesh->GetControlPointsCount();
	FbxVector4* lControlPoints = pMesh->GetControlPoints();

	DisplayString("    Control Points");

	for (i = 0; i < lControlPointsCount; i++)
	{
		DisplayInt("        Control Point ", i);
		Display3DVector("            Coordinates: ", lControlPoints[i]);

		for (int j = 0; j < pMesh->GetElementNormalCount(); j++)
		{
			FbxGeometryElementNormal* leNormals = pMesh->GetElementNormal( j);
			if (leNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{
				char header[100];
				FBXSDK_sprintf(header, 100, "            Normal Vector: "); 
				if (leNormals->GetReferenceMode() == FbxGeometryElement::eDirect)
					Display3DVector(header, leNormals->GetDirectArray().GetAt(i));
			}
		}
	}

	DisplayString("");
}


void DisplayPolygons(FbxMesh* pMesh)
{
	int i, j, lPolygonCount = pMesh->GetPolygonCount();
	FbxVector4* lControlPoints = pMesh->GetControlPoints(); 
	char header[100];

	DisplayString("    Polygons");

	int vertexId = 0;
	for (i = 0; i < lPolygonCount; i++)
	{
		DisplayInt("        Polygon ", i);
		int l;

		for (l = 0; l < pMesh->GetElementPolygonGroupCount(); l++)
		{
			FbxGeometryElementPolygonGroup* lePolgrp = pMesh->GetElementPolygonGroup(l);
			switch (lePolgrp->GetMappingMode())
			{
			case FbxGeometryElement::eByPolygon:
				if (lePolgrp->GetReferenceMode() == FbxGeometryElement::eIndex)
				{
					FBXSDK_sprintf(header, 100, "        Assigned to group: "); 
					int polyGroupId = lePolgrp->GetIndexArray().GetAt(i);
					DisplayInt(header, polyGroupId);
					break;
				}
			default:
				// any other mapping modes don't make sense
				DisplayString("        \"unsupported group assignment\"");
				break;
			}
		}

		int lPolygonSize = pMesh->GetPolygonSize(i);

		for (j = 0; j < lPolygonSize; j++)
		{
			int lControlPointIndex = pMesh->GetPolygonVertex(i, j);

			Display3DVector("            Coordinates: ", lControlPoints[lControlPointIndex]);

			for (l = 0; l < pMesh->GetElementVertexColorCount(); l++)
			{
				FbxGeometryElementVertexColor* leVtxc = pMesh->GetElementVertexColor( l);
				FBXSDK_sprintf(header, 100, "            Color vertex: "); 

				switch (leVtxc->GetMappingMode())
				{
				case FbxGeometryElement::eByControlPoint:
					switch (leVtxc->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
						DisplayColor(header, leVtxc->GetDirectArray().GetAt(lControlPointIndex));
						break;
					case FbxGeometryElement::eIndexToDirect:
						{
							int id = leVtxc->GetIndexArray().GetAt(lControlPointIndex);
							DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
						}
						break;
					default:
						break; // other reference modes not shown here!
					}
					break;

				case FbxGeometryElement::eByPolygonVertex:
					{
						switch (leVtxc->GetReferenceMode())
						{
						case FbxGeometryElement::eDirect:
							DisplayColor(header, leVtxc->GetDirectArray().GetAt(vertexId));
							break;
						case FbxGeometryElement::eIndexToDirect:
							{
								int id = leVtxc->GetIndexArray().GetAt(vertexId);
								DisplayColor(header, leVtxc->GetDirectArray().GetAt(id));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
					break;

				case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
				case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
				case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
					break;
				}
			}
			for (l = 0; l < pMesh->GetElementUVCount(); ++l)
			{
				FbxGeometryElementUV* leUV = pMesh->GetElementUV( l);
				FBXSDK_sprintf(header, 100, "            Texture UV: "); 

				switch (leUV->GetMappingMode())
				{
				case FbxGeometryElement::eByControlPoint:
					switch (leUV->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
						Display2DVector(header, leUV->GetDirectArray().GetAt(lControlPointIndex));
						break;
					case FbxGeometryElement::eIndexToDirect:
						{
							int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
							Display2DVector(header, leUV->GetDirectArray().GetAt(id));
						}
						break;
					default:
						break; // other reference modes not shown here!
					}
					break;

				case FbxGeometryElement::eByPolygonVertex:
					{
						int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
						switch (leUV->GetReferenceMode())
						{
						case FbxGeometryElement::eDirect:
						case FbxGeometryElement::eIndexToDirect:
							{
								Display2DVector(header, leUV->GetDirectArray().GetAt(lTextureUVIndex));
							}
							break;
						default:
							break; // other reference modes not shown here!
						}
					}
					break;

				case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
				case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
				case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
					break;
				}
			}
			for( l = 0; l < pMesh->GetElementNormalCount(); ++l)
			{
				FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal( l);
				FBXSDK_sprintf(header, 100, "            Normal: "); 

				if(leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (leNormal->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
						Display3DVector(header, leNormal->GetDirectArray().GetAt(vertexId));
						break;
					case FbxGeometryElement::eIndexToDirect:
						{
							int id = leNormal->GetIndexArray().GetAt(vertexId);
							Display3DVector(header, leNormal->GetDirectArray().GetAt(id));
						}
						break;
					default:
						break; // other reference modes not shown here!
					}
				}

			}
			for( l = 0; l < pMesh->GetElementTangentCount(); ++l)
			{
				FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent( l);
				FBXSDK_sprintf(header, 100, "            Tangent: "); 

				if(leTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (leTangent->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
						Display3DVector(header, leTangent->GetDirectArray().GetAt(vertexId));
						break;
					case FbxGeometryElement::eIndexToDirect:
						{
							int id = leTangent->GetIndexArray().GetAt(vertexId);
							Display3DVector(header, leTangent->GetDirectArray().GetAt(id));
						}
						break;
					default:
						break; // other reference modes not shown here!
					}
				}

			}
			for( l = 0; l < pMesh->GetElementBinormalCount(); ++l)
			{

				FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal( l);

				FBXSDK_sprintf(header, 100, "            Binormal: "); 
				if(leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (leBinormal->GetReferenceMode())
					{
					case FbxGeometryElement::eDirect:
						Display3DVector(header, leBinormal->GetDirectArray().GetAt(vertexId));
						break;
					case FbxGeometryElement::eIndexToDirect:
						{
							int id = leBinormal->GetIndexArray().GetAt(vertexId);
							Display3DVector(header, leBinormal->GetDirectArray().GetAt(id));
						}
						break;
					default:
						break; // other reference modes not shown here!
					}
				}
			}
			vertexId++;
		} // for polygonSize
	} // for polygonCount


	//check visibility for the edges of the mesh
	for(int l = 0; l < pMesh->GetElementVisibilityCount(); ++l)
	{
		FbxGeometryElementVisibility* leVisibility=pMesh->GetElementVisibility(l);
		FBXSDK_sprintf(header, 100, "    Edge Visibility : ");
		DisplayString(header);
		switch(leVisibility->GetMappingMode())
		{
			//should be eByEdge
		case FbxGeometryElement::eByEdge:
			//should be eDirect
			for(int j=0; j!=pMesh->GetMeshEdgeCount();++j)
			{
				DisplayInt("        Edge ", j);
				DisplayBool("              Edge visibility: ", leVisibility->GetDirectArray().GetAt(j));
			}

			break;
		}
	}
	DisplayString("");
}

void DisplayTextureNames( FbxProperty &pProperty, FbxString& pConnectionString )
{
	int lLayeredTextureCount = pProperty.GetSrcObjectCount(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId));
	if(lLayeredTextureCount > 0)
	{
		for(int j=0; j<lLayeredTextureCount; ++j)
		{
			FbxLayeredTexture *lLayeredTexture = FbxCast <FbxLayeredTexture>(pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId), j));
			int lNbTextures = lLayeredTexture->GetSrcObjectCount(FbxCriteria::ObjectType(FbxTexture::ClassId));
			pConnectionString += " Texture ";

			for(int k =0; k<lNbTextures; ++k)
			{
				//lConnectionString += k;
				pConnectionString += "\"";
				pConnectionString += (char*)lLayeredTexture->GetName();
				pConnectionString += "\"";
				pConnectionString += " ";
			}
			pConnectionString += "of ";
			pConnectionString += pProperty.GetName();
			pConnectionString += " on layer ";
			pConnectionString += j;
		}
		pConnectionString += " |";
	}
	else
	{
		//no layered texture simply get on the property
		int lNbTextures = pProperty.GetSrcObjectCount(FbxCriteria::ObjectType(FbxTexture::ClassId));

		if(lNbTextures > 0)
		{
			pConnectionString += " Texture ";
			pConnectionString += " ";

			for(int j =0; j<lNbTextures; ++j)
			{
				FbxTexture* lTexture = FbxCast <FbxTexture> (pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxTexture::ClassId),j));
				if(lTexture)
				{
					pConnectionString += "\"";
					pConnectionString += (char*)lTexture->GetName();
					pConnectionString += "\"";
					pConnectionString += " ";
				}
			}
			pConnectionString += "of ";
			pConnectionString += pProperty.GetName();
			pConnectionString += " |";
		}
	}
}

void DisplayMaterialTextureConnections( FbxSurfaceMaterial* pMaterial, char * header, int pMatId, int l )
{
	if(!pMaterial)
		return;

	FbxString lConnectionString = "            Material %d -- ";
	//Show all the textures

	FbxProperty lProperty;
	//Diffuse Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	DisplayTextureNames(lProperty, lConnectionString);

	//DiffuseFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuseFactor);
	DisplayTextureNames(lProperty, lConnectionString);

	//Emissive Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
	DisplayTextureNames(lProperty, lConnectionString);

	//EmissiveFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sEmissiveFactor);
	DisplayTextureNames(lProperty, lConnectionString);


	//Ambient Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sAmbient);
	DisplayTextureNames(lProperty, lConnectionString); 

	//AmbientFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sAmbientFactor);
	DisplayTextureNames(lProperty, lConnectionString);          

	//Specular Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
	DisplayTextureNames(lProperty, lConnectionString);  

	//SpecularFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sSpecularFactor);
	DisplayTextureNames(lProperty, lConnectionString);

	//Shininess Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sShininess);
	DisplayTextureNames(lProperty, lConnectionString);

	//Bump Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sBump);
	DisplayTextureNames(lProperty, lConnectionString);

	//Normal Map Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sNormalMap);
	DisplayTextureNames(lProperty, lConnectionString);

	//Transparent Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sTransparentColor);
	DisplayTextureNames(lProperty, lConnectionString);

	//TransparencyFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
	DisplayTextureNames(lProperty, lConnectionString);

	//Reflection Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sReflection);
	DisplayTextureNames(lProperty, lConnectionString);

	//ReflectionFactor Textures
	lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sReflectionFactor);
	DisplayTextureNames(lProperty, lConnectionString);

	//Update header with material info
	bool lStringOverflow = (lConnectionString.GetLen() + 10 >= MAT_HEADER_LENGTH); // allow for string length and some padding for "%d"
	if (lStringOverflow)
	{
		// Truncate string!
		lConnectionString = lConnectionString.Left(MAT_HEADER_LENGTH - 10);
		lConnectionString = lConnectionString + "...";
	}
	FBXSDK_sprintf(header, 100, lConnectionString.Buffer(), pMatId, l);
	DisplayString(header);
}

void DisplayMaterialConnections(FbxMesh* pMesh)
{
	int i, l, lPolygonCount = pMesh->GetPolygonCount();

	char header[MAT_HEADER_LENGTH];

	DisplayString("    Polygons Material Connections");

	//check whether the material maps with only one mesh
	bool lIsAllSame = true;
	for (l = 0; l < pMesh->GetElementMaterialCount(); l++)
	{

		FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial(l);
		if( lMaterialElement->GetMappingMode() == FbxGeometryElement::eByPolygon) 
		{
			lIsAllSame = false;
			break;
		}
	}

	//For eAllSame mapping type, just out the material and texture mapping info once
	if(lIsAllSame)
	{
		for (l = 0; l < pMesh->GetElementMaterialCount(); l++)
		{

			FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial( l);
			if( lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame) 
			{
				FbxSurfaceMaterial* lMaterial = pMesh->GetNode()->GetMaterial(lMaterialElement->GetIndexArray().GetAt(0));    
				int lMatId = lMaterialElement->GetIndexArray().GetAt(0);
				if(lMatId >= 0)
				{
					DisplayInt("        All polygons share the same material in mesh ", l);
					DisplayMaterialTextureConnections(lMaterial, header, lMatId, l);
				}
			}
		}

		//no material
		if(l == 0)
			DisplayString("        no material applied");
	}

	//For eByPolygon mapping type, just out the material and texture mapping info once
	else
	{
		for (i = 0; i < lPolygonCount; i++)
		{
			DisplayInt("        Polygon ", i);

			for (l = 0; l < pMesh->GetElementMaterialCount(); l++)
			{

				FbxGeometryElementMaterial* lMaterialElement = pMesh->GetElementMaterial( l);
				FbxSurfaceMaterial* lMaterial = NULL;
				int lMatId = -1;
				lMaterial = pMesh->GetNode()->GetMaterial(lMaterialElement->GetIndexArray().GetAt(i));
				lMatId = lMaterialElement->GetIndexArray().GetAt(i);

				if(lMatId >= 0)
				{
					DisplayMaterialTextureConnections(lMaterial, header, lMatId, l);
				}
			}
		}
	}
}


void DisplayMaterialMapping(FbxMesh* pMesh)
{
	char* lMappingTypes[] = { "None", "By Control Point", "By Polygon Vertex", "By Polygon", "By Edge", "All Same" };
	char* lReferenceMode[] = { "Direct", "Index", "Index to Direct"};

	int lMtrlCount = 0;
	FbxNode* lNode = NULL;
	if(pMesh){
		lNode = pMesh->GetNode();
		if(lNode)
			lMtrlCount = lNode->GetMaterialCount();    
	}

	for (int l = 0; l < pMesh->GetElementMaterialCount(); l++)
	{
		FbxGeometryElementMaterial* leMat = pMesh->GetElementMaterial( l);
		if (leMat)
		{
			char header[100];
			FBXSDK_sprintf(header, 100, "    Material Element %d: ", l); 
			DisplayString(header);


			DisplayString("           Mapping: ", lMappingTypes[leMat->GetMappingMode()]);
			DisplayString("           ReferenceMode: ", lReferenceMode[leMat->GetReferenceMode()]);

			int lMaterialCount = 0;
			FbxString lString;

			if (leMat->GetReferenceMode() == FbxGeometryElement::eDirect ||
				leMat->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				lMaterialCount = lMtrlCount;
			}

			if (leMat->GetReferenceMode() == FbxGeometryElement::eIndex ||
				leMat->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
			{
				int i;

				lString = "           Indices: ";

				int lIndexArrayCount = leMat->GetIndexArray().GetCount(); 
				for (i = 0; i < lIndexArrayCount; i++)
				{
					lString += leMat->GetIndexArray().GetAt(i);

					if (i < lIndexArrayCount - 1)
					{
						lString += ", ";
					}
				}

				lString += "\n";

				printf(lString);
			}
		}
	}

	DisplayString("");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayTextureInfo(FbxTexture* pTexture, int pBlendMode)
{
	FbxFileTexture *lFileTexture = FbxCast<FbxFileTexture>(pTexture);
	FbxProceduralTexture *lProceduralTexture = FbxCast<FbxProceduralTexture>(pTexture);

	DisplayString("            Name: \"", (char *) pTexture->GetName(), "\"");
	if (lFileTexture)
	{
		DisplayString("            Type: File Texture");
		DisplayString("            File Name: \"", (char *) lFileTexture->GetFileName(), "\"");
	}
	else if (lProceduralTexture)
	{
		DisplayString("            Type: Procedural Texture");
	}
	DisplayDouble("            Scale U: ", pTexture->GetScaleU());
	DisplayDouble("            Scale V: ", pTexture->GetScaleV());
	DisplayDouble("            Translation U: ", pTexture->GetTranslationU());
	DisplayDouble("            Translation V: ", pTexture->GetTranslationV());
	DisplayBool("            Swap UV: ", pTexture->GetSwapUV());
	DisplayDouble("            Rotation U: ", pTexture->GetRotationU());
	DisplayDouble("            Rotation V: ", pTexture->GetRotationV());
	DisplayDouble("            Rotation W: ", pTexture->GetRotationW());

	char* lAlphaSources[] = { "None", "RGB Intensity", "Black" };

	DisplayString("            Alpha Source: ", lAlphaSources[pTexture->GetAlphaSource()]);
	DisplayDouble("            Cropping Left: ", pTexture->GetCroppingLeft());
	DisplayDouble("            Cropping Top: ", pTexture->GetCroppingTop());
	DisplayDouble("            Cropping Right: ", pTexture->GetCroppingRight());
	DisplayDouble("            Cropping Bottom: ", pTexture->GetCroppingBottom());

	char* lMappingTypes[] = { "Null", "Planar", "Spherical", "Cylindrical", 
		"Box", "Face", "UV", "Environment" };

	DisplayString("            Mapping Type: ", lMappingTypes[pTexture->GetMappingType()]);

	if (pTexture->GetMappingType() == FbxTexture::ePlanar)
	{
		char* lPlanarMappingNormals[] = { "X", "Y", "Z" };

		DisplayString("            Planar Mapping Normal: ", lPlanarMappingNormals[pTexture->GetPlanarMappingNormal()]);
	}

	char* lBlendModes[]   = { "Translucent", "Add", "Modulate", "Modulate2" };   
	if(pBlendMode >= 0)
		DisplayString("            Blend Mode: ", lBlendModes[pBlendMode]);
	DisplayDouble("            Alpha: ", pTexture->GetDefaultAlpha());

	if (lFileTexture)
	{
		char* lMaterialUses[] = { "Model Material", "Default Material" };
		DisplayString("            Material Use: ", lMaterialUses[lFileTexture->GetMaterialUse()]);
	}

	char* pTextureUses[] = { "Standard", "Shadow Map", "Light Map", 
		"Spherical Reflexion Map", "Sphere Reflexion Map", "Bump Normal Map" };

	DisplayString("            Texture Use: ", pTextureUses[pTexture->GetTextureUse()]);
	DisplayString("");                

}

void FindAndDisplayTextureInfoByProperty(FbxProperty pProperty, bool& pDisplayHeader, int pMaterialIndex){

	if( pProperty.IsValid() )
	{
		int lTextureCount = pProperty.GetSrcObjectCount(FbxCriteria::ObjectType(FbxTexture::ClassId));

		for (int j = 0; j < lTextureCount; ++j)
		{
			//Here we have to check if it's layeredtextures, or just textures:
			FbxLayeredTexture *lLayeredTexture = FbxCast <FbxLayeredTexture>(pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId), j));
			if (lLayeredTexture)
			{
				DisplayInt("    Layered Texture: ", j);
				FbxLayeredTexture *lLayeredTexture = FbxCast <FbxLayeredTexture>(pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxLayeredTexture::ClassId), j));
				int lNbTextures = lLayeredTexture->GetSrcObjectCount(FbxCriteria::ObjectType(FbxTexture::ClassId));
				for(int k =0; k<lNbTextures; ++k)
				{
					FbxTexture* lTexture = FbxCast <FbxTexture> (lLayeredTexture->GetSrcObject(FbxCriteria::ObjectType(FbxTexture::ClassId),k));
					if(lTexture)
					{

						if(pDisplayHeader){                    
							DisplayInt("    Textures connected to Material ", pMaterialIndex);
							pDisplayHeader = false;
						}

						//NOTE the blend mode is ALWAYS on the LayeredTexture and NOT the one on the texture.
						//Why is that?  because one texture can be shared on different layered textures and might
						//have different blend modes.

						FbxLayeredTexture::EBlendMode lBlendMode;
						lLayeredTexture->GetTextureBlendMode(k, lBlendMode);
						DisplayString("    Textures for ", pProperty.GetName());
						DisplayInt("        Texture ", k);  
						DisplayTextureInfo(lTexture, (int) lBlendMode);   
					}

				}
			}
			else
			{
				//no layered texture simply get on the property
				FbxTexture* lTexture = FbxCast <FbxTexture> (pProperty.GetSrcObject(FbxCriteria::ObjectType(FbxTexture::ClassId),j));
				if(lTexture)
				{
					//display connected Material header only at the first time
					if(pDisplayHeader){                    
						DisplayInt("    Textures connected to Material ", pMaterialIndex);
						pDisplayHeader = false;
					}             

					DisplayString("    Textures for ", pProperty.GetName());
					DisplayInt("        Texture ", j);  
					DisplayTextureInfo(lTexture, -1);
				}
			}
		}
	}//end if pProperty

}


void DisplayTexture(FbxGeometry* pGeometry)
{
	int lMaterialIndex;
	FbxProperty lProperty;
	if(pGeometry->GetNode()==NULL)
		return;
	int lNbMat = pGeometry->GetNode()->GetSrcObjectCount(FbxCriteria::ObjectType(FbxSurfaceMaterial::ClassId));
	for (lMaterialIndex = 0; lMaterialIndex < lNbMat; lMaterialIndex++){
		FbxSurfaceMaterial *lMaterial = (FbxSurfaceMaterial *)pGeometry->GetNode()->GetSrcObject(FbxCriteria::ObjectType(FbxSurfaceMaterial::ClassId), lMaterialIndex);
		bool lDisplayHeader = true;

		//go through all the possible textures
		if(lMaterial){

			int lTextureIndex;
			FBXSDK_FOR_EACH_TEXTURE(lTextureIndex)
			{
				lProperty = lMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[lTextureIndex]);
				FindAndDisplayTextureInfoByProperty(lProperty, lDisplayHeader, lMaterialIndex); 
			}

		}//end if(lMaterial)

	}// end for lMaterialIndex     
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayLink(FbxGeometry* pGeometry)
{
	//Display cluster now

	//int i, lLinkCount;
	//FbxCluster* lLink;

	int i, j;
	int lSkinCount=0;
	int lClusterCount=0;
	FbxCluster* lCluster;

	lSkinCount=pGeometry->GetDeformerCount(FbxDeformer::eSkin);



	//lLinkCount = pGeometry->GetLinkCount();
	for(i=0; i!=lSkinCount; ++i)
	{
		lClusterCount = ((FbxSkin *) pGeometry->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
		for (j = 0; j != lClusterCount; ++j)
		{
			DisplayInt("    Cluster ", i);

			lCluster=((FbxSkin *) pGeometry->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);
			//lLink = pGeometry->GetLink(i);    

			char* lClusterModes[] = { "Normalize", "Additive", "Total1" };

			DisplayString("    Mode: ", lClusterModes[lCluster->GetLinkMode()]);

			if(lCluster->GetLink() != NULL)
			{
				DisplayString("        Name: ", (char *) lCluster->GetLink()->GetName());
			}

			FbxString lString1 = "        Link Indices: ";
			FbxString lString2 = "        Weight Values: ";

			int k, lIndexCount = lCluster->GetControlPointIndicesCount();
			int* lIndices = lCluster->GetControlPointIndices();
			double* lWeights = lCluster->GetControlPointWeights();

			for(k = 0; k < lIndexCount; k++)
			{
				lString1 += lIndices[k];
				lString2 += (float) lWeights[k];

				if (k < lIndexCount - 1)
				{
					lString1 += ", ";
					lString2 += ", ";
				}
			}

			lString1 += "\n";
			lString2 += "\n";

			FBXSDK_printf(lString1);
			FBXSDK_printf(lString2);

			DisplayString("");

			FbxAMatrix lMatrix;

			lMatrix = lCluster->GetTransformMatrix(lMatrix);
			Display3DVector("        Transform Translation: ", lMatrix.GetT());
			Display3DVector("        Transform Rotation: ", lMatrix.GetR());
			Display3DVector("        Transform Scaling: ", lMatrix.GetS());

			lMatrix = lCluster->GetTransformLinkMatrix(lMatrix);
			Display3DVector("        Transform Link Translation: ", lMatrix.GetT());
			Display3DVector("        Transform Link Rotation: ", lMatrix.GetR());
			Display3DVector("        Transform Link Scaling: ", lMatrix.GetS());

			if (lCluster->GetAssociateModel() != NULL)
			{
				lMatrix = lCluster->GetTransformAssociateModelMatrix(lMatrix);
				DisplayString("        Associate Model: ", (char *) lCluster->GetAssociateModel()->GetName());
				Display3DVector("        Associate Model Translation: ", lMatrix.GetT());
				Display3DVector("        Associate Model Rotation: ", lMatrix.GetR());
				Display3DVector("        Associate Model Scaling: ", lMatrix.GetS());
			}

			DisplayString("");
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayShape(FbxGeometry* pGeometry)
{
	int lBlendShapeCount, lBlendShapeChannelCount, lTargetShapeCount;
	FbxBlendShape* lBlendShape;
	FbxBlendShapeChannel* lBlendShapeChannel;
	FbxShape* lShape;

	lBlendShapeCount = pGeometry->GetDeformerCount(FbxDeformer::eBlendShape);

	for (int lBlendShapeIndex = 0; lBlendShapeIndex < lBlendShapeCount; ++lBlendShapeIndex)
	{
		lBlendShape = (FbxBlendShape*) pGeometry->GetDeformer(lBlendShapeIndex, FbxDeformer::eBlendShape);   
		DisplayString("    BlendShape ", (char *) lBlendShape->GetName());

		lBlendShapeChannelCount = lBlendShape->GetBlendShapeChannelCount();
		for(int lBlendShapeChannelIndex = 0;  lBlendShapeChannelIndex < lBlendShapeChannelCount; ++lBlendShapeChannelIndex)
		{
			lBlendShapeChannel = lBlendShape->GetBlendShapeChannel(lBlendShapeChannelIndex);
			DisplayString("    BlendShapeChannel ", (char *) lBlendShapeChannel->GetName());
			DisplayDouble("    Default Deform Value: ", lBlendShapeChannel->DeformPercent.Get());

			lTargetShapeCount = lBlendShapeChannel->GetTargetShapeCount();
			for (int lTargetShapeIndex = 0; lTargetShapeIndex < lTargetShapeCount; ++lTargetShapeIndex)
			{
				lShape = lBlendShapeChannel->GetTargetShape(lTargetShapeIndex);
				DisplayString("    TargetShape ", (char *) lShape->GetName());

				int j, lControlPointsCount = lShape->GetControlPointsCount();
				FbxVector4* lControlPoints = lShape->GetControlPoints();
				FbxLayerElementArrayTemplate<FbxVector4>* lNormals = NULL;    
				bool lStatus = lShape->GetNormals(&lNormals); 

				for(j = 0; j < lControlPointsCount; j++)
				{
					DisplayInt("        Control Point ", j);
					Display3DVector("            Coordinates: ", lControlPoints[j]);

					if (lStatus && lNormals && lNormals->GetCount() == lControlPointsCount)
					{
						Display3DVector("            Normal Vector: ", lNormals->GetAt(j));
					}
				}

				DisplayString("");
			}
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DisplayGenericInfo(FbxScene* pScene)
{
	int i;
	FbxNode* lRootNode = pScene->GetRootNode();

	for( i = 0; i < lRootNode->GetChildCount(); i++)
	{
		DisplayGenericInfo(lRootNode->GetChild(i), 0);
	}

	//Other objects directly connected onto the scene
	for( i = 0; i < pScene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxObject::ClassId)); ++i )
	{
		DisplayProperties(pScene->GetSrcObject(FbxCriteria::ObjectType(FbxObject::ClassId), i));
	}
}


void DisplayGenericInfo(FbxNode* pNode, int pDepth)
{
	FbxString lString;
	int i;

	for(i = 0; i < pDepth; i++)
	{
		lString += "     ";
	}

	lString += pNode->GetName();
	lString += "\n";

	DisplayString(lString.Buffer());

	//Display generic info about that Node
	DisplayProperties(pNode);
	DisplayString("");
	for(i = 0; i < pNode->GetChildCount(); i++)
	{
		DisplayGenericInfo(pNode->GetChild(i), pDepth + 1);
	}
}

void DisplayProperties(FbxObject* pObject)
{

	DisplayString("Name: ", (char *)pObject->GetName());

	// Display all the properties
	int i,  lCount = 0;
	FbxProperty lProperty = pObject->GetFirstProperty();
	while (lProperty.IsValid())
	{
		lCount++;
		lProperty = pObject->GetNextProperty(lProperty);
	}

	FbxString lTitleStr = "    Property Count: ";

	if (lCount == 0)
		return; // there are no properties to display

	DisplayInt(lTitleStr.Buffer(), lCount);

	i=0;
	lProperty = pObject->GetFirstProperty();
	while (lProperty.IsValid())
	{
		// exclude user properties

		FbxString lString;
		DisplayInt("        Property ", i);
		lString = lProperty.GetLabel();
		DisplayString("            Display Name: ", lString.Buffer());
		lString = lProperty.GetName();
		DisplayString("            Internal Name: ", lString.Buffer());
		lString = lProperty.GetPropertyDataType().GetName();
		DisplayString("            Type: ",lString.Buffer());
		if (lProperty.HasMinLimit()) DisplayDouble("            Min Limit: ", lProperty.GetMinLimit());
		if (lProperty.HasMaxLimit()) DisplayDouble("            Max Limit: ", lProperty.GetMaxLimit());
		DisplayBool  ("            Is Animatable: ", lProperty.GetFlag(FbxPropertyAttr::eAnimatable));
		DisplayBool  ("            Is Temporary: ", lProperty.GetFlag(FbxPropertyAttr::eTemporary));


		switch (lProperty.GetPropertyDataType().GetType())
		{
		case eFbxBool:
			DisplayBool("            Default Value: ", lProperty.Get<FbxBool>());
			break;

		case eFbxDouble:
			DisplayDouble("            Default Value: ", lProperty.Get<FbxDouble>());
			break;

		case eFbxDouble4:
			{
				FbxColor lDefault;
				char      lBuf[64];

				lDefault = lProperty.Get<FbxColor>();
				FBXSDK_sprintf(lBuf, 64, "R=%f, G=%f, B=%f, A=%f", lDefault.mRed, lDefault.mGreen, lDefault.mBlue, lDefault.mAlpha);
				DisplayString("            Default Value: ", lBuf);
			}
			break;

		case eFbxInt:
			DisplayInt("            Default Value: ", lProperty.Get<FbxInt>());
			break;

		case eFbxDouble3:
			{
				FbxDouble3 lDefault;
				char   lBuf[64];

				lDefault = lProperty.Get<FbxDouble3>();
				FBXSDK_sprintf(lBuf, 64, "X=%f, Y=%f, Z=%f", lDefault[0], lDefault[1], lDefault[2]);
				DisplayString("            Default Value: ", lBuf);
			}
			break;

			//case FbxEnumDT:
			//    DisplayInt("            Default Value: ", lProperty.Get<FbxEnum>());
			//    break;

		case eFbxFloat:
			DisplayDouble("            Default Value: ", lProperty.Get<FbxFloat>());
			break;
		case eFbxString:
			lString = lProperty.Get<FbxString>();
			DisplayString("            Default Value: ", lString.Buffer());
			break;

		default:
			DisplayString("            Default Value: UNIDENTIFIED");
			break;
		}
		i++;
		lProperty = pObject->GetNextProperty(lProperty);
	}
}