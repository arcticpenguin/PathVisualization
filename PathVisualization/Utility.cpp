#include "Utility.h"

void Debug::Error(string msg)
{
	cout << "[ERROR] " << msg << endl;
}

void Debug::Log(string msg)
{
	cout << "[LOG] " << msg << endl;
}
