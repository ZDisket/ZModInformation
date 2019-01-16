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

	File >> ModFolder;
	
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

	sFile << ModFolder;
	
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


void ModInformation::SetModFolder(const std::wstring & Folder)
{
	ModFolder = FileSys.RecursiveStuffInDirectory(Folder);
}

ModInformation::~ModInformation()
{
	

}

bool ZMI_API SiModInfo::OpenMI(const std::wstring & FName, ModInfo & out_Info)
{
	ZFile MiOpen;
	if (!MiOpen.Open(FName, EZFOpenMode::BinaryRead))
		return false;

	MiOpen >> out_Info.BasicInfo.ModAuthors;
	MiOpen >> out_Info.BasicInfo.ModDescription;
	MiOpen >> out_Info.BasicInfo.ModName;
	MiOpen >> out_Info.BasicInfo.ModVersion;

	MiOpen >> out_Info.ImgData;

	MiOpen.Close();

	return true;


}

bool ZMI_API SiModInfo::SaveMI(const std::wstring & outName, const ModInfo & in_SaveInfo)
{
	ZFile MiSave;

	if (!MiSave.Open(outName, EZFOpenMode::BinaryWrite))
		return false;

	ZModInfo Basic = in_SaveInfo.GetBasic();

	MiSave << Basic.ModAuthors;
	MiSave << Basic.ModDescription;
	MiSave << Basic.ModName;
	MiSave << Basic.ModVersion;

	MiSave << in_SaveInfo.GetImage();

	MiSave.Close();

	return true;
}
