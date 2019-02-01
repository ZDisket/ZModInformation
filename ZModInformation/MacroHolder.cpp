#include "sdafx.hpp"
#include "MacroHolder.h"
using namespace std;

MacroHolder::MacroHolder()
{
}


MacroHolder::~MacroHolder()
{
}

bool MacroHolder::Open(const std::wstring & Filename)
{
	ZFile File;
	if (!File.Open(Filename, EZFOpenMode::BinaryRead))
		return false;

	File >> Macros;

	File.Close();
	return true;
}

bool MacroHolder::Save(const std::wstring & SFilename)
{
	ZFile Out;

	if (!Out.Open(SFilename, EZFOpenMode::BinaryWrite))
		return false;

	Out << Macros;

	Out.Close();

	return true;
}
