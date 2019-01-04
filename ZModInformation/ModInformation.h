#pragma once
#include "ZMI_DLL.h"

#include <iostream>
#include <string>
#include <vector>

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
	short FVersion;

	// Basic data
	std::wstring Name;
	std::wstring Description;
	std::vector<std::wstring> Authors;
    double ModVersion;

	// Image
	INT64 ImgDataSz;
	BYTE* ImgData;

	// Files
	INT64 ZipSize;
	BYTE* ZipData;

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
	ZModInfo ModInfo;


public:
	ModInformation();
    ZMIErrorCodes::Enum Open(const std::wstring & Name, ZModInfo & omInf);
	ZMIErrorCodes::Enum Save(const std::wstring& Name, ZModInfo& InfSave);
	~ModInformation();
};
