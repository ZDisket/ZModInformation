#pragma once
#include "ZMI_DLL.h"
#include <string>
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
	// Create a new byte arr by copying and REPLACING the contents
	ByteArr(BYTE* CopyArr, const size_t& ArrSz);

	// Get a const reference to the raw array
	const BYTE* CoData() const;

	BYTE* GetData() { return Data; }

	// Assign a raw BYTE* by copy and REPLACE the contents
	void Assign(BYTE* cpyArr, const size_t& cpySz);

	// Get the size of the array
	inline size_t Size() { return DataSz; }

	inline void IncreaseSize(const size_t& Add) { Realloc(DataSz + Add); }

	inline size_t Pos() { return CurrentPos; }

	// Add something raw to the byte array. It's highly recommended 
	// that you instead use the overloaded operator <<
	void Add(void* inDat, const size_t& DatSz);

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

		Add((void*)Str.data(), Str.size());


	
	}


	~ByteArr();
};

