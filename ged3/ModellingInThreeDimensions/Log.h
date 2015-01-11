////////////////////////////////////////////////////////////////////////////////
// Filename: Log.h
////////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////
// INCLUDES //
//////////////
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Class name: Log
////////////////////////////////////////////////////////////////////////////////
class Log
{
public:
	// If this isn't true, we don't want to do anything.
	static const bool Enabled = true;

	// The height and width of the console.
	static const int consoleWidth = 480;
	static const int consoleHeight = 1050;

	// Initialise console.
	static bool InitConsole();

	// Output to console.
	static void COut(string output);
	static void NewLine();

private:
};