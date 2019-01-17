#include "sdafx.hpp"
#include "ModInformation.h"
#include "ZFile.h"

ModInformation::ModInformation()
{
	

}

ZMIErrorCodes::Enum ModInformation::Open(const std::wstring & inName)
{
	ZFile File;
	if (!File.Open(inName, EZFOpenMode::BinaryRead)) {
		return ZMIErrorCodes::CannotOpenFile;
	}
	short CurrentVer = 0;
	File >> CurrentVer;

	File >> Name;
	File >> Description;
	File >> Authors;
	File >> ModVersion;
	try {
		File >> ImgData;

		File >> ZipData;

	}
	catch (...) {
		return ZMIErrorCodes::InvalidFile;
	}


	File >> ModFolder;

	if (CurrentVer > 2)
		File >> ModFilesSize;
	else
		ModFilesSize = FileSys.GetSize(ModFolder);

	
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
	sFile << ModFilesSize;
	
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
	ModFilesSize = FileSys.GetSize(ModFolder);

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
	MiOpen >> out_Info.FolderSz;

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
	MiSave << in_SaveInfo.GetFolderSz();

	MiSave.Close();

	return true;
}
