#pragma once
#pragma warning(disable: 4251) // Class std::basic string blah blah needs to have dll-interface to be used by clients of class

#ifdef ZMI_EXPORT
#define ZMI_API __declspec(dllexport)
#else
       // God has spoken. He has come to bless your code with His divine macro.
#define ZMI_API __declspec(dllimport)

#ifndef ZDFS_MAN_INCLUDE
#define ZDFS_MAN_INCLUDE
#endif

#ifdef _DEBUG
#pragma comment(lib,"ZModInformation_d.lib")
#else
#pragma comment(lib,"ZModInformation.lib")
#endif
#include <ModInformation.h>

typedef unsigned char BYTE;
typedef __int64 INT64;

#endif