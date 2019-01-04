#include "stdafx.h"
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

void ByteArr::Add(void * inDat, const size_t & DatSz)
{
	const size_t Req = CurrentPos + DatSz;

	if (Req > DataSz)
		IncreaseSize(Req - DataSz);

	memcpy_s(Data + CurrentPos, DataSz, inDat, DatSz);

	CurrentPos += DatSz;
}

ByteArr::~ByteArr()
{
	if (Data)
		delete[] Data;
}
