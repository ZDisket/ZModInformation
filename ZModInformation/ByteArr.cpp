#include "sdafx.hpp"
#include "ByteArr.h"


void ByteArr::Realloc(const size_t & newSize)
{
	if (newSize < DataSz)
		return;

	BYTE* NewDat = new BYTE[newSize];

	memcpy_s(NewDat, newSize, Data, DataSz);

	DataSz = newSize;

	delete[] Data;

	Data = NewDat;


}

void ByteArr::Init()
{
	Data = NULL;
	DataSz = 0;
	CurrentPos = 0;
}

ByteArr::ByteArr()
{
	Init();
}

ByteArr::ByteArr(BYTE * CopyArr, const size_t & ArrSz)
{
	Init();
	Assign(CopyArr, ArrSz);

}

ByteArr::ByteArr(const ByteArr & Cpy)
{
	Init();
	Assign(Cpy);
}

ByteArr::ByteArr(const std::vector<BYTE>& CpyBv)
{
	Init();
	Assign(CpyBv);
}

const BYTE * ByteArr::CoData() const
{
	return Data;
}


void ByteArr::Assign(BYTE * cpyArr, const size_t & cpySz)
{
	if (Data)
		delete[] Data;

	Data = new BYTE[cpySz];

	memcpy_s(Data, cpySz, cpyArr, cpySz);
	DataSz = cpySz;

}

void ByteArr::Assign(const std::vector<BYTE>& CByteVec)
{
	CAlloc(CByteVec.size());

	memcpy_s(Data, DataSz, CByteVec.data(), CByteVec.size());

}

void ByteArr::Assign(const ByteArr & CpyByte)
{
	CAlloc(CpyByte.Size());

	memcpy_s(Data, DataSz, CpyByte.CoData(), CpyByte.Size());


}

void ByteArr::Add(void * inDat, const size_t & DatSz)
{
	const size_t Req = CurrentPos + DatSz;

	if (Req > DataSz)
		IncreaseSize(Req - DataSz);

	memcpy_s(Data + CurrentPos, DataSz, inDat, DatSz);

	CurrentPos += DatSz;
}

void ByteArr::CAlloc(const size_t & SetSize)
{
	if (Data)
		delete[] Data;

	CurrentPos = 0;

	Data = new BYTE[SetSize];

	DataSz = SetSize;

}

ByteArr::~ByteArr()
{
	try {
		if (Data)
			delete[] Data;
	
	}
	catch (...) {
	// Who the hell gives a shit about exceptions here???
	
	}

}
