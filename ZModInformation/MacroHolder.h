#pragma once
#include "ZMI_DLL.h"
#include "Macro.h"
// MacroHolder: Holds and admins chat macro files
class ZMI_API MacroHolder
{
	std::vector<Macro> Macros;
public:
	MacroHolder();
	~MacroHolder();

	inline std::vector<Macro>& Data() { return Macros; }

	bool Open(const std::wstring& Filename);
	bool Save(const std::wstring& SFilename);
};

