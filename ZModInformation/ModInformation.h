#pragma once
/*
##################################################################################
  __  __           _ _____        __                           _   _
 |  \/  |         | |_   _|      / _|                         | | (_)
 | \  / | ___   __| | | |  _ __ | |_ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __
 | |\/| |/ _ \ / _` | | | | '_ \|  _/ _ \| '__| '_ ` _ \ / _` | __| |/ _ \| '_ \
 | |  | | (_) | (_| |_| |_| | | | || (_) | |  | | | | | | (_| | |_| | (_) | | | |
 |_|  |_|\___/ \__,_|_____|_| |_|_| \___/|_|  |_| |_| |_|\__,_|\__|_|\___/|_| |_|

###################################################################################
# Description: Main ZMI_API class that holds and handles everything related to mod 
# (.ZMI) files.
#
###################################################################################
*/



#include "ZMI_DLL.h"

#include <iostream>
#include <string>
#include <vector>
#include "ByteArr.h"
#include "ZDFS.h"


struct ZModInfo {
	
	std::wstring ModName;
	std::wstring ModDescription;
	std::vector<std::wstring> ModAuthors;
	double ModVersion;
};

namespace ZMIErrorCodes {
	enum Enum {
		CannotOpenFile = 0,
		InvalidFile,
		InvalidData,
		NoError

	};
}


class ZMI_API ModInformation
{
private:

	// Version history:
	// 2
	// 3: Added mod folder size
	const static short FVersion = 3;
	ZDFS FileSys;
	// Basic data
	std::wstring Name;
	std::wstring Description;
	std::vector<std::wstring> Authors;
	double ModVersion;

	
	std::vector<SItemW> ModFolder;

	// Image
	ByteArr ImgData;

	// Files
	ByteArr ZipData;

	UINT64 ModFilesSize;

public:
	ModInformation();
    ZMIErrorCodes::Enum Open(const std::wstring & inName);
	ZMIErrorCodes::Enum Save(const std::wstring& inName);
	
	ZModInfo GetBasicInfo();
	void SetBasicInfo(const ZModInfo& Minf);

	UINT64 GetTotalSize() { return ModFilesSize; }

	ByteArr& GetImageData() { return ImgData; }
	ByteArr& GetZipData() { return ZipData; }

	std::vector<SItemW>& GetFileSysData() { return ModFolder; }

	void SetModFolder(const std::wstring& Folder);

	~ModInformation();
};

/*For loading simple Mod Information (.mi) files. */
namespace SiModInfo {

	struct ModInfo {
		ZModInfo BasicInfo;
		ByteArr ImgData;
		UINT64 FolderSz;
		ModInfo() {
			
		}

		ModInfo(ModInformation& Minf) {
			BasicInfo = Minf.GetBasicInfo();
			FolderSz = Minf.GetTotalSize();
			if (Minf.GetImageData().Size())
				ImgData.Assign(Minf.GetImageData());


		}

		ZModInfo GetBasic() const {
			return BasicInfo;
		};

		const ByteArr& GetImage() const{
			return ImgData;
		}
		UINT64 GetFolderSz() const {
			return FolderSz;

		}
	};

	bool ZMI_API OpenMI(const std::wstring& FName,ModInfo& out_Info);
	bool ZMI_API SaveMI(const std::wstring& outName, const ModInfo& in_SaveInfo);
}
