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
}

ZMIErrorCodes::Enum ModInformation::Open(const std::wstring & Name,ZModInfo& omInf)
{
	ZFile File;
	if (!File.Open(Name, EZFOpenMode::BinaryRead)) {
		return ZMIErrorCodes::CannotOpenFile;
	}

	File.Read(omInf.FVersion);

	File.Read(omInf.Name);
	File.Read(omInf.Description);
	File.Read(omInf.Authors);
	File.Read(omInf.ModVersion);

	File.Read(omInf.ImgDataSz);

	omInf.ImgData = new BYTE[omInf.ImgDataSz];
	
	File.Read(&omInf.ImgData, omInf.ImgDataSz);

	File.Read(omInf.ZipSize);

	omInf.ZipData = new BYTE[omInf.ZipSize];
	File.Read(&omInf.ZipData, omInf.ZipSize);

	File.Close();



	return ZMIErrorCodes::NoError;
}

ZMIErrorCodes::Enum ModInformation::Save(const std::wstring & Name, ZModInfo & InfSave)
{
	ZFile sFile;

	if (!sFile.Open(Name, EZFOpenMode::BinaryWrite))
		return ZMIErrorCodes::CannotOpenFile;

	sFile.Write(InfSave.FVersion);

	sFile.Write(InfSave.Name);
	sFile.Write(InfSave.Description);
	sFile.Write(InfSave.Authors);
	sFile.Write(InfSave.ModVersion);

	sFile.Write(InfSave.ImgDataSz);

	sFile.Write(&InfSave.ImgData, InfSave.ImgDataSz);

	sFile.Write(InfSave.ZipSize);

	sFile.Write(&InfSave.ZipData, InfSave.ZipSize);
	
	sFile.Close();

	return ZMIErrorCodes::NoError;
}


ModInformation::~ModInformation()
{
}
