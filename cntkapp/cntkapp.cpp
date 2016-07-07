// cntkapp.cpp : Defines the entry point for the console application.
//

//many CNTK include paths contains "stdafx.h", be aware of it
#include "pch.h"

//CNTK headers
#include <ComputationNetwork.h>
#include <direct.h>
#include <actions.h>


using namespace Microsoft::MSR::CNTK;


//need for correct linkage
bool g_shareNodeValueMatrices = false;

//read string from filename
string slurp(const string &fileName); 


int _tmain(int argc, _TCHAR* argv[])
{

    ConfigParameters config;

    string cntk_root_dir=getenv("CNTK_ROOT_DIR");

    string config_path = cntk_root_dir + "/Examples/Other/Simple2d/Config/";

    chdir(config_path.c_str());
    auto config_content = slurp(config_path + "simple.cntk");

    config.Parse(config_content);

    auto deviceId=DeviceFromConfig(config);


    wstring  outputNodeNameConfig;
    std::vector<wstring> outputNodeNamesVector;

    auto net = GetModelFromConfig<ConfigParameters, float>(config, outputNodeNameConfig,
        outputNodeNamesVector);

    if (net == nullptr)
    {
        LogicError("Unable to construct network from description");
        return -1;
    }
    else
    {
        printf("ook\n");
    }

	return 0;
}




//from http://stackoverflow.com/questions/116038/what-is-the-best-way-to-slurp-a-file-into-a-stdstring-in-c
string slurp(const string &fileName)
{
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(&bytes[0], fileSize);

    return string(&bytes[0], fileSize);
};
