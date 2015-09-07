#include "DataOutput.h"

void DataOutput::flush(string fileName)
{
	ofstream os(fileName);
	os << _outputFlow;
	os.close();
}

void DataOutput::appendOutput(string op)
{
	_outputFlow += op;
}

