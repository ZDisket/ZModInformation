#pragma once
/*
###################################################

  ____        _
 |  _ \      | |         /\
 | |_) |_   _| |_ ___   /  \   _ __ _ __
 |  _ <| | | | __/ _ \ / /\ \ | '__| '__|
 | |_) | |_| | ||  __// ____ \| |  | |
 |____/ \__, |\__\___/_/    \_\_|  |_|
		 __/ |
		|___/
###################################################
# Description: Holds ByteArr stuff
# Author: ZDisket
# Copyright (C) 2019 YOUR MOM GAY LOLOLOL
####################################################
*/


#include "ZMI_DLL.h"
#include <string>
#include <vector>


typedef unsigned char BYTE;

// Incomplete class meant to simplify interactions with dynamic size byte arrays
// Right now it can only safely store
class ZMI_API ByteArr
{
private:
	BYTE* Data;
	size_t DataSz;

	size_t CurrentPos;
	void Realloc(const size_t& newSize);

	inline void Init();

public:
	ByteArr();

	// Initialize with a certain size.
	ByteArr(const size_t& InitSz);

	// Create a new byte arr by copying and REPLACING the contents
	ByteArr(BYTE* CopyArr, const size_t& ArrSz);
	// Create a byte array from another byte array
	ByteArr(const ByteArr& Cpy);

	// Create a byte array from a vector of bytes
	ByteArr(const std::vector<BYTE>& CpyBv);

	// Copy the Byte Array into a vector.
	std::vector<BYTE> ToVector();
	
	// Get a const reference to the raw array
	const BYTE* CoData() const;

	BYTE* GetData() { return Data; }

	// Assign a raw BYTE* by copy and REPLACE the contents
	void Assign(BYTE* cpyArr, const size_t& cpySz);

	// Assign a vector of bytes.
	void Assign(const std::vector<BYTE>& CByteVec);

	// Assign a byte array and copy contents.
	void Assign(const ByteArr& CpyByte);

	// Get the size of the array
	inline size_t Size() const { return DataSz; }


	inline void IncreaseSize(const size_t& Add) { Realloc(DataSz + Add); }

	inline size_t Pos() { return CurrentPos; }

	// Add something raw to the byte array. It's highly recommended 
	// that you instead use the overloaded operator <<
	void Add(void* inDat, const size_t& DatSz);

	// REPLACE the array and allocate a new one with specified size.
	void CAlloc(const size_t& SetSize);

	// Add a simple data type to the bytearr
	template<typename Ty>
	void operator<<(const Ty& In) {
		const size_t SzIn = sizeof(In);
		const size_t Req = CurrentPos + SzIn;

		if (Req > DataSz)
			IncreaseSize(Req - DataSz);

		memcpy_s(Data + CurrentPos, DataSz, &In, SzIn);

		CurrentPos += SzIn;
	
	}
	
	template<typename Char>
	void operator<<(const std::basic_string<Char>& Str) {
		// Add the size 
		(*this) << Str.size();

		Add((void*)Str.data(), Str.size() * sizeof(Char));


	
	}


	~ByteArr();
};

