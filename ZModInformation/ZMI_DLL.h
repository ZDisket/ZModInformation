#pragma once
#ifdef ZMI_EXPORT
#define ZMI_API __declspec(dllexport)
#else
#define ZMI_API __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib,"ZModInformation_d.lib")
#else
#pragma comment(lib,"ZModInformation.lib")
#endif
#include <ModInformation.h>

#endif