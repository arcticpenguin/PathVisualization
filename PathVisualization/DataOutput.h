#include "Utility.h"

#ifndef _DATAOUTPUT_H_
#define _DATAOUTPUT_H_

class DataOutput
{
public:
	void appendOutput(string op);
	void flush(string fileName);
private:
	string _outputFlow;
};
#endif