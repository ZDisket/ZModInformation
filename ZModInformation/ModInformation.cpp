#include "sdafx.hpp"
#include "ModInformation.h"
#include "ZFile.h"

/*
zmi modinfo struc:
short fversion

wstring name
wstring description
wstringvec authors
double version

int64 imgdatasz
BYTE[] imgData // Will be QImage data later on

int64 zipsz
BYTE[] zipdata

*/

ModInformation::ModInformation()
{
	

}

ZMIErrorCodes::Enum ModInformation::Open(const std::wstring & inName)
{
	ZFile File;
	if (!File.Open(inName, EZFOpenMode::BinaryRead)) {
		return ZMIErrorCodes::CannotOpenFile;
	}

	File >> FVersion;

	File >> Name;
	File >> Description;
	File >> Authors;
	File >> ModVersion;

	File >> ImgData;

	File >> ZipData;
	
	File.Close();



	return ZMIErrorCodes::NoError;
}

ZMIErrorCodes::Enum ModInformation::Save(const std::wstring & inName)
{
	ZFile sFile;

	if (!sFile.Open(inName, EZFOpenMode::BinaryWrite))
		return ZMIErrorCodes::CannotOpenFile;

	sFile << FVersion;

	sFile << Name;
	sFile << Description;
	sFile << Authors;
	sFile << ModVersion;

	sFile << ImgData;

	sFile << ZipData;
	
	sFile.Close();

	return ZMIErrorCodes::NoError;
}

ZModInfo ModInformation::GetBasicInfo()
{
	ZModInfo Inf1;

	Inf1.ModAuthors = Authors;
	Inf1.ModDescription = Description;
	Inf1.ModName = Name;
	Inf1.ModVersion = ModVersion;

	return Inf1;

}

void ModInformation::SetBasicInfo(const ZModInfo & Minf)
{
	Authors = Minf.ModAuthors;
	Description = Minf.ModDescription;
	Name = Minf.ModName;
	ModVersion = Minf.ModVersion;
}


ModInformation::~ModInformation()
{
	

}
