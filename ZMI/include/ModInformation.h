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


	const short FVersion = 1;

	// Basic data
	std::wstring Name;
	std::wstring Description;
	std::vector<std::wstring> Authors;
	double ModVersion;

	// Image
	ByteArr ImgData;

	// Files
	ByteArr ZipData;

public:
	ModInformation();
    ZMIErrorCodes::Enum Open(const std::wstring & inName);
	ZMIErrorCodes::Enum Save(const std::wstring& inName);
	
	ZModInfo GetBasicInfo();
	void SetBasicInfo(const ZModInfo& Minf);

	ByteArr& GetImageData() { return ImgData; }
	ByteArr& GetZipData() { return ZipData; }

	~ModInformation();
};

