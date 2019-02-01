#include "sdafx.hpp"
#include "ByteArr.h"
using namespace std;

void ByteArr::Realloc(const size_t & newSize)
{
	if (newSize < DataSz)
		return;

	BYTE* NewDat = new BYTE[newSize];





	smemcpy(NewDat, newSize, Data, DataSz);

	DataSz = newSize;

	delete[] Data;

	Data = NewDat;


}

void ByteArr::Init()
{
	Data = nullptr;
	DataSz = 0;
	CurrentPos = 0;
}

ByteArr::ByteArr()
{
	Init();
}

ByteArr::ByteArr(const size_t & InitSz)
{
	Init();
	CAlloc(InitSz);
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
	CurrentPos = Cpy.Pos();
}

ByteArr::ByteArr(const std::vector<BYTE>& CpyBv)
{
	Init();
	Assign(CpyBv);
}
#ifdef _QT
ByteArr::ByteArr(const QByteArray &InitBar)
{
	Init();
	Assign(InitBar);
}
#endif
void ByteArr::Request(const size_t &reqSz)
{
	const size_t oReq = CurrentPos + reqSz;

	if (oReq > DataSz)
		IncreaseSize(reqSz);

}

std::vector<BYTE> ByteArr::ToVector()
{
	return std::vector<BYTE>(Data, Data + DataSz);

}

const BYTE * ByteArr::CoData() const
{
	return Data;
}

BYTE &ByteArr::operator[](const size_t &Pos)
{
	return Data[Pos];

}

const BYTE &ByteArr::operator[](const size_t &cPos) const
{
	return Data[cPos];

}

void ByteArr::Advance(const size_t &adv)
{
	CurrentPos += adv;

}


void ByteArr::Assign(BYTE * cpyArr, const size_t & cpySz)
{
	if (Data)
		delete[] Data;

	Data = new BYTE[cpySz];

	smemcpy(Data, cpySz, cpyArr, cpySz);
	DataSz = cpySz;

}

void ByteArr::Assign(const std::vector<BYTE>& CByteVec)
{
	CAlloc(CByteVec.size());

	smemcpy(Data, DataSz, CByteVec.data(), CByteVec.size());

}

void ByteArr::Assign(const ByteArr & CpyByte)
{
	CAlloc(CpyByte.Size());

	smemcpy(Data, DataSz, CpyByte.CoData(), CpyByte.Size());



}

void ByteArr::Seek(const size_t &To)
{
	if (To > DataSz)
		throw std::invalid_argument("Tried to seek out of bounds!");

	CurrentPos = To;

}

void ByteArr::Add(void * inDat, const size_t & DatSz)
{
	const size_t Req = CurrentPos + DatSz;

	if (Req > DataSz)
		IncreaseSize(DatSz);

	smemcpy(Data + CurrentPos, DataSz, inDat, DatSz);

	CurrentPos += DatSz;
}

size_t ByteArr::Read(void *OutDat, const size_t &oDatSz)
{
	const size_t oReq = CurrentPos + oDatSz;

	if (oReq > DataSz)
		throw std::invalid_argument("Tried to read out of bounds!");

	smemcpy(OutDat, oDatSz, Data + CurrentPos, oDatSz);

	CurrentPos = oReq;

	return CurrentPos;

}

void ByteArr::CAlloc(const size_t & SetSize)
{
	if (Data)
		delete[] Data;

	CurrentPos = 0;

	Data = new BYTE[SetSize];

	DataSz = SetSize;

}

void ByteArr::operator>>(ByteArr &BaEx)
{
	// We explicitly export and import sizes in unsigned 64 bits to make sure
	// there are no compatibility problems between 32 and 64 bit architectures

	// Get the size
	UINT64 tmpSize = 0;
	(*this) >> tmpSize;

	// Request the size from the other byte array

	BaEx.Request((size_t)tmpSize);

	// Perform a copy directly onto the other array
	smemcpy(BaEx.Data + BaEx.Pos(), BaEx.Size(), Data + CurrentPos, (size_t)tmpSize);


	// Advance those positions
	BaEx.Advance(tmpSize);
	CurrentPos += tmpSize;



}

void ByteArr::operator<<(const ByteArr &BaAdd)
{

	// We explicitly export and import sizes in unsigned 64 bits to make sure
	// there are no compatibility problems between 32 and 64 bit architectures


	(*this) << (UINT64)BaAdd.Size();
	Add(BaAdd.Data, BaAdd.Size());





}

// QT Functions ##########################################################
#ifdef _QT


void ByteArr::Assign(const QByteArray &QBar)
{
	CAlloc((size_t)QBar.size());

	smemcpy(Data, DataSz, QBar.data(), (size_t)QBar.size());

}

QByteArray ByteArr::ToQByteArr()
{
	QByteArray QB((const char*)Data, (int)DataSz);
	return QB;

}

void ByteArr::operator<<(const QByteArray &QBarEx)
{
	ByteArr Temp;
	Temp.Assign(QBarEx);

	(*this) << Temp;

}

void ByteArr::operator>>(QByteArray &QBarry)
{

	ByteArr Temp1;
	(*this) >> Temp1;

	QBarry.append(Temp1.ToQByteArr());


}

#endif
// QT Functions ##########################################################


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
#ifndef _WIN32
void smemcpy(void* dest, const size_t& destsz, const void* src, const size_t& count) {

	if (count > destsz)
		throw std::invalid_argument("memcpy_s, destionation size is lower than the source!!");

	memcpy(dest, src, count);


}
#endif
#ifdef _WIN32
void smemcpy(void* dest, const size_t& destsz, const void* src, const size_t& count) {

	memcpy_s(dest, destsz, src, count);

}
#endif