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



#ifdef _QT
#include <QString>
#include <QByteArray>
#endif


typedef unsigned char BYTE;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef std::vector<BYTE> ByteVec;


void smemcpy(void* dest, const size_t& destsz, const void* src, const size_t& count);

// Almost complete class that serves as a "dynamic buffer" of sorts, being able to get and extract data.
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
#ifdef _QT
	ByteArr(const QByteArray& InitBar);
#endif
	// Request a certain amount of bytes to be allocated into the byte array.
	// If necessary, will resize.
	void Request(const size_t& reqSz);

	// Copy the Byte Array into a vector.
	std::vector<BYTE> ToVector();

	// Get a const reference to the raw array
	const BYTE* CoData() const;

	BYTE* GetData() { return Data; }

	BYTE& operator[](const size_t& Pos);
	const BYTE& operator[](const size_t& cPos) const;

	void Advance(const size_t& adv);

	// Assign a raw BYTE* by copy and REPLACE the contents
	void Assign(BYTE* cpyArr, const size_t& cpySz);

	// Assign a vector of bytes.
	void Assign(const std::vector<BYTE>& CByteVec);

	// Assign a byte array and copy contents.
	void Assign(const ByteArr& CpyByte);

	// Get the size of the array
	inline size_t Size() const { return DataSz; }



	inline void IncreaseSize(const size_t& Add) { Realloc(DataSz + Add); }

	inline size_t Pos() const { return CurrentPos; }
	void Seek(const size_t& To);

	// Add something raw to the byte array. It's highly recommended 
	// that you instead use the overloaded operator <<
	void Add(void* inDat, const size_t& DatSz);

	// Reads the array and returns the current position
	size_t Read(void* OutDat, const size_t& oDatSz);

	// REPLACE the array and allocate a new one with specified size.
	void CAlloc(const size_t& SetSize);
	inline void CAlloc(const INT64& SetSz) { CAlloc((size_t)SetSz); }
	// Add a simple data type to the bytearr
	template<typename Ty>
	void operator<<(const Ty& In) {

		Add((void*)&In, sizeof(In));

	}

	template<typename Char>
	void operator<<(const std::basic_string<Char>& Str) {
		// Add the size 
		(*this) << Str.size();

		Add((void*)Str.data(), Str.size() * sizeof(Char));





	}
	template<typename Tyo>
	void operator>> (Tyo& Out) {
		Read((void*)&Out, sizeof(Out));


	}
	template<typename Char>
	void operator>>(std::basic_string<Char>& oStr) {
		size_t rsz = 0;
		(*this) >> rsz;
		oStr.resize(rsz);

		Read((void*)oStr.data(), rsz * sizeof(Char));


	}
	template<typename V>
	void operator>>(std::vector<V>& OutVec) {

		size_t vsz = 0;
		(*this) >> vsz;

		OutVec.reserve(vsz);

		size_t p = 0;

		while (p != vsz) {
			V temp;
			(*this) >> temp;
			OutVec.push_back(temp);

			++p;
		}

	}

	template<typename V>
	void operator<<(const std::vector<V>& InVec) {

		(*this) << InVec.size();


		size_t p = 0;

		while (p != InVec.size()) {
			(*this) << InVec[p];

			++p;
		}

	}

	// Append a byte array
	void operator<<(const ByteArr& BaAdd);

	// Export a previously stored byte array. Note that it appends.
	void operator>>(ByteArr& BaEx);


#ifdef _QT
	// It's much  safer to use u32 string as we guarantee that all platforms will support it
	// equally.

	void operator<<(const QString& QsEx)
	{
		std::u32string StrEx = QsEx.toStdU32String();
		(*this) << StrEx;

	}
	void operator>>(QString& QsOut)
	{
		std::u32string StrOut;
		(*this) >> StrOut;
		QsOut = QString::fromStdU32String(StrOut);



	}

	void Assign(const QByteArray& QBar);
	QByteArray ToQByteArr();

	void operator<<(const QByteArray& QBarEx);


	void operator>>(QByteArray& QBarry);



#endif


	~ByteArr();
};

