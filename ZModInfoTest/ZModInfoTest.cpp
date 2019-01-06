// ZModInfoTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <ZMI_DLL.h>
#include <ZipperInclude.hpp>
#include <ZFile.h>


using namespace std;
using namespace zipper;
typedef std::vector<BYTE> ByteVec;
typedef std::wstring String;
typedef std::vector<String> StringVector;
typedef unsigned long long uint64_t;


/*
Str8 outta StackOverFlow
*/
bool IsBrowsePath(const String& path)
{
	return (path == L"." || path == L"..");
}
uint64_t CalculateDirSize(const String &path, StringVector *errVect = NULL, uint64_t size = 0)
{
	WIN32_FIND_DATA data;
	HANDLE sh = NULL;
	sh = FindFirstFile((path + L"\\*").c_str(), &data);

	if (sh == INVALID_HANDLE_VALUE)
	{
		//if we want, store all happened error  
		if (errVect != NULL)
			errVect->push_back(path);
		return size;
	}

	do
	{
		// skip current and parent
		if (!IsBrowsePath(data.cFileName))
		{
			// if found object is ...
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
				// directory, then search it recursievly
				size = CalculateDirSize(path + L"\\" + data.cFileName, NULL, size);
			else
				// otherwise get object size and add it to directory size
				size += (uint64_t)(data.nFileSizeHigh * (MAXDWORD)+data.nFileSizeLow);
		}

	} while (FindNextFile(sh, &data)); // do

	FindClose(sh);

	return size;
}




int main()
{

ModInformation Info1;
	const wstring foldername = L"A World DIvided";
	ByteVec Buf;
	Buf.reserve((size_t)CalculateDirSize(foldername));

	Zipper Zip1(Buf);

	Zip1.add("A World DIvided");
	Zip1.close();

	ZModInfo Track;

	cout << "zip size " << Buf.size();

	Track.ModAuthors.push_back(L"Your mom");
	Track.ModAuthors.push_back(L"Her lover");

	Track.ModDescription = L"AAAAAAAAAAAAAA";

	Track.ModName = foldername;

	Track.ModVersion = 1.2;

	Info1.SetBasicInfo(Track);

	
	Info1.GetZipData().Assign(Buf);


	ZFile Image;
	if (!Image.Open(foldername + L"\\photo.jpg", EZFOpenMode::BinaryRead))
		return -1;

	ByteArr ImgDa = Image.ReadEntireFile();
	Info1.GetImageData().Assign(ImgDa);

	Image.Close();
	Info1.SetModFolder(foldername);
	Info1.Save(foldername + L".zmi");


	






	ModInformation InfEx;
	InfEx.Open(L"A World DIvided.zmi");
	ZModInfo Info = InfEx.GetBasicInfo();

	cout << "Opening mod" << endl;
	wcout << L"Mod name: " << Info.ModName << endl;
	wcout << L"Mod description: " << Info.ModDescription << endl;
	wcout << L"Version: " << Info.ModVersion << endl;




	cout << "Mod authors: " << endl;

	auto It = Info.ModAuthors.begin();

	while (It != Info.ModAuthors.end())
	{
		
		wcout << *It << endl;
		++It;
	}

	wcout << L"Extracting mod files..." << endl;
	
	ByteVec Byv = InfEx.GetZipData().ToVector();
	Unzipper Unz(Byv);
	Unz.extract();

	wcout << L" Done! " << endl;

	system("pause");


	return 0;
}

