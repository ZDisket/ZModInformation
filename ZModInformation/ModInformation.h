#pragma once

#ifdef ZMI_EXPORT
#define ZMI_API __declspec(dllexport)
#else
#define ZMI_API __declspec(dllimport)
#endif


class ZMI_API ModInformation
{
public:
	ModInformation();
	~ModInformation();
};

