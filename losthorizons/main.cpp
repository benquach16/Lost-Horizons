// losthorizons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>

#include "baseapplication.h"

void getCmdArgs(int argc, char *argv[], CommandLineArgs &args)
{
	for(int i = 0; i < argc; ++i)
	{
		if(argv[i] == "-fullscreen")
		{
		}
	}
}

int main(int argc, char* argv[])
{
	//We can get command line arguments here
	CommandLineArgs args;

	CBaseApplication app;

	return 0;
}
