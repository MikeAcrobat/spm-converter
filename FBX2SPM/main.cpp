#include <windows.h>
#include <fbxsdk.h>
#include "utilities.h"
#include "SPMExpoter.h"
#include "SPMTypes.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("input", po::value<std::string>(), "input file")
		("output", po::value<std::string>(), "path with file prefix")
		("name", po::value<std::string>(), "export named model")
		("local", "export in local axis")
		("h", "display hierarchy")
		("m", "display mesh data")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	std::cout << desc << "\n";
	
	std::string input;
	std::string output;
	std::string namedModel;
	bool displyHierarchy = false;
	bool displayMeshData = false;
	localSpace = false;

	if (vm.count("input"))	input = vm["input"].as<std::string>();
	if (vm.count("output"))	output = vm["output"].as<std::string>();
	if (vm.count("name"))	namedModel = vm["name"].as<std::string>();
	if (vm.count("h"))		displyHierarchy = true;
	if (vm.count("m"))		displayMeshData = true;
	if (vm.count("local"))	localSpace = true;

	SPMExporter exporter;
	FbxManager* lSdkManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);
	FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");	
	if (!lImporter->Initialize(input.c_str(), -1, lSdkManager->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetLastErrorString());
		exit(-1);
	}	
	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
	lImporter->Import(lScene);	
	lImporter->Destroy();
	FbxNode* lRootNode = lScene->GetRootNode();

	if (displyHierarchy) DisplayHierarchy(lScene);

	if (!output.empty()) 
	{		
		spmObject obj;
		if (!namedModel.empty())
		{
			FbxNode * child = lRootNode->FindChild(namedModel.c_str());
			if (child)
			{
				DisplayString("Exporting ", child->GetName());
				spmSubmesh sbmesh = CreateObject(child);
				obj.subMeshes.push_back(sbmesh);
			}
		}
		else
		{
			int childCount = lRootNode->GetChildCount();
			for (int i = 0; i < childCount; i++)
			{
				FbxNode * child = lRootNode->GetChild(i);
				if (child->GetMesh())
				{
					DisplayString("Exporting ", child->GetName());
					if (displayMeshData) DisplayMesh(child);
					spmSubmesh sbmesh = CreateObject(child);
					obj.subMeshes.push_back(sbmesh);
				}
				else
				{
					DisplayString("Skipping ", child->GetName());
				}
			}		
		}
		exporter.exportObject(obj, output);
	}

	lSdkManager->Destroy();	
	return 0;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return main(__argc, __argv);
}

