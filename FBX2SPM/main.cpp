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
		("in", po::value<std::string>(), "input file")
		("out", po::value<std::string>(), "output file")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	//if (vm.count("help")) {
		std::cout << desc << "\n";
	//	return 1;
	//}

	std::string input;
	std::string output;

	if (vm.count("in"))
		input = vm["in"].as<std::string>();

	if (vm.count("out"))
		output = vm["out"].as<std::string>();

	if (input.empty()) return 1;

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
	if (!output.empty()) 
	{
		spmObject obj;
		int childCount = lRootNode->GetChildCount();
		for (int i = 0; i < childCount; i++)
		{
			spmSubmesh sbmesh = CreateObject(lRootNode->GetChild(i));
			obj.subMeshes.push_back(sbmesh);
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

