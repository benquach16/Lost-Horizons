// losthorizons.cpp : Defines the entry point for the console application.
//

#include <string>
#include "stdafx.h"
#include "baseapplication.h"

void getCmdArgs(int argc, char *argv[], CommandLineArgs &args)
{
	for (int i = 0; i < argc; ++i) {
		if (argv[i] == "-fullscreen") {
			args.fullscreen = true;
		}
		if (argv[i] == "-debug") {
			args.debug = true;
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
