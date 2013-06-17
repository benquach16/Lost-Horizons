// losthorizons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <fstream>

#include "baseapplication.h"

void getCmdArgs(int argc, char *argv[], CommandLineArgs &args)
{
	for(unsigned i = 0; i < argc; i ++)
	{
		if(argv[i] == "-fullscreen")
		{
		}
	}
}

void getConfigFile(const std::string &filename, ConfigArgs &config_args)
{
	std::ifstream file(filename.c_str());

	while(file)
	{
		//read in line by line ofc
		std::string input;
		while(getline(file,input))
		{
			
		}
	}
}

int main(int argc, char* argv[])
{
	//We can get command line arguments here
	CommandLineArgs args;
	ConfigArgs config_args;

	CBaseApplication app;
	return 0;
}

