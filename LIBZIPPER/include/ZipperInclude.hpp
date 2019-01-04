#pragma once

#ifdef _DEBUG
#pragma comment(lib,"zipper_d.lib")
#else
#pragma comment(lib,"zipper.lib")
#endif
#pragma comment(lib,"libz-static.lib")

#include <zlib.h>

#include <zipper.h>
#include <unzipper.h>
