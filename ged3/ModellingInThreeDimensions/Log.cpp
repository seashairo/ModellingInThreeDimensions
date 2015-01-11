#include "stdafx.h"
#include "Log.h"
using namespace std;

/**
 * How to use this class:
 * Call Log::InitConsole() in the main function (already done) to
 * create the console.
 *
 * Use Log::COut(string output) to output a log message to the
 * console, and to a log file which will be located in the 
 * DebugFiles folder, with a name generated from the current date
 * and the time the program was run at.
 */

// string to store the log file location
string logFileName;

bool Log::InitConsole(){
	// No need to initialise the console if we're not debugging!
	if(!Enabled) return false;

	// Creates a console window to output to.
	bool retVal = AllocConsole();

	// Move the console to the left side of the screen.
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, consoleWidth, consoleHeight, true);

	// Get the time to make the file name
	time_t now = time(0); // Get current time
    struct tm tstruct;
    char buf[80]; // Create a buffer to hold the time
    tstruct = *localtime(&now); // Convert time to localtime
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct); // Put time into buffer
	logFileName = buf; // set filename to buffer contents
	logFileName += ".txt";
	logFileName = "DebugFiles\\" + logFileName;

	freopen("CONOUT$", "w", stdout);
	COut("Console initialized.");
	COut("Log file for this session at: " + logFileName);
	NewLine();

	return retVal;
}

// If logging is enabled, and the console has been initialised, then
// output to our console!
void Log::COut(string s){
	if(!Enabled) return;

	// Output message to console
	cout << s << endl;

	// Also output message to log file
	ofstream outStream; // Create a filestream
	outStream.open(logFileName, ofstream::app); // Open the log file in append mode
	outStream << s << endl; // Add the log message to the file
	outStream.close(); // Close the stream
}

// Break line
void Log::NewLine(){
	cout << endl;
}