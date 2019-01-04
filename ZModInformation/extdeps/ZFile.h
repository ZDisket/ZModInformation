#pragma once
#include "../ZMI_DLL.h"

//* ZFile: Class for reading files
#include <fstream>
#include <string>
#include <vector>

/*

__if_not_exists (INT64) {
#ifndef INT64
#define INT64 long long
#endif // !INT64

};

__if_not_exists (BYTE) {

#ifndef BYTE
#define BYTE unsigned char
#endif // !BYTE

};


*/





namespace EZFOpenMode {
	enum Enum {
		BinaryRead = 0,
		TextRead,
		BinaryWrite,
		TextWrite
	};
}
/*
Why is this here? Just use sizeof()!

*/
namespace DataSizes {
	enum Sz {
		FLOAT_SZ = 4,
		DOUBLE_SZ = 8,
		LONG_DOUBLE_SZ = 10,
		SIZE_T_SZ = 4,
		INT64_SZ = 8,
		LONG_SZ = 4,
		INT32_SZ = 4,
		INT16_SZ = 2,
		CHAR_SIZE = 1,
		WCHAR_SIZE = 2
	};
}
class ZMI_API ZFile
{
private:
	BYTE * m_pData;
	bool FileOpened;
	std::fstream Stream;

	EZFOpenMode::Enum OpenMode;

	int EZFOpenModeToIos(const EZFOpenMode::Enum& input);

public:
	bool Open(const std::string& in_sFileName,const EZFOpenMode::Enum& in_Mode);
	bool Open(const std::wstring& in_sFileName, const EZFOpenMode::Enum& in_Mode);

	void Seek(const INT64& in_Pos);
	INT64 GetPos();
	
	
	
	// Reads from the file
	// Please pass a pointer to this
	void Read(void* out, const INT64& count);
	// Writes to the file
	// Please pass a pointer
	void Write(void* in, const INT64& incount);

	
	
	// Write with template argument to not pass size.
	// Only works with Plain Old Datatypes (PODs)
    template <typename Dat>
	void Write(const Dat& dta)
	{
		Stream.write((char*)&dta, sizeof(dta));
		
	
	}

	// Read with template argument to not pass size.
   // Only works with Plain Old Datatypes (PODs)
	template <typename Dat>
	void Read(Dat& dta)
	{
		Stream.read((char*)&dta, sizeof(dta));


	}

	

	// Write a string
	template<typename chardat>
	void Write(const std::basic_string<chardat>& Str) {
		// Write the size first
		Write(Str.size());
		Stream.write((char*)Str.data(), Str.size());
	
	}

	// Read a string
	template<typename chardat>
	void Read(std::basic_string<chardat>& Str) {
		size_t datSz = 0;
		Read(datSz);
		chardat* dpBuffer = new chardat[datSz];


		Stream.read((char*)&dpBuffer, datSz);

		Str.assign(dpBuffer);
		delete[] dpBuffer;

	}

	// Write a vector
	template<typename vdat>
	void Write(const std::vector<vdat>& Vec) {
		Write(Vec.size());
		auto It = Vec.begin();
		
		while (It != Vec.end()) {
			Write(*It);
			++It;
		}

	
	}

	// Read a vector
	template<typename vdat>
	void Read(std::vector<vdat>& Vec) {
		size_t vSz = 0;
		Read(vSz);
		
		Vec.reserve(vSz);

		size_t i = 0;

		while (i < vSz) {
			Read(Vec[i]);
		
			++i;
		}


	}

	// Write some stuff
	template<typename Ty>
	void operator<<(const Ty& In) {
		Write(In);
	
	}

	template<typename MTy>
	void operator>>(MTy& mIn) {
		Read(mIn);
	}
	
	void Close();


	ZFile();
	~ZFile();
};

