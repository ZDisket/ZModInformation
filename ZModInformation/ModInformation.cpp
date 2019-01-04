#include "stdafx.h"
#include "ModInformation.h"
#include "extdeps/ZFile.h"

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
	ImgData = NULL;
	ZipData = NULL;

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

	File >> ImgDataSz;

	ImgData = new BYTE[ImgDataSz];
	
	File.Read(ImgData, ImgDataSz);

	File >> ZipSize;

	ZipData = new BYTE[ZipSize];
	File.Read(ZipData, ZipSize);
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

	sFile << ImgDataSz;

	sFile.Write(ImgData, ImgDataSz);

	sFile << ZipSize;

	sFile.Write(ZipData, ZipSize);
	
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


ModInformation::~ModInformation()
{
}
