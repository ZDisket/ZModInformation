#pragma once

#include "ZMI_DLL.h"
#include "ZFile.h"

// Defines a chat macro
// Not to be confused with President Macron of France.
class ZMI_API Macro
{
private:

	// Where are the arguments?
	std::vector<size_t> ArgPos;
	std::wstring Text;
	std::wstring Command;
public:
	Macro();
	Macro(const Macro& Cpy);
	Macro(const std::wstring& InText, const std::vector<size_t>& APos);
	Macro(const std::wstring& InText, const std::wstring& insCmd, const std::vector<size_t>& APos);

	Macro(const std::wstring& InTxt, const std::wstring& inCmd);

	// Return a formed string with the following arguments.
	// Invalid vector (size disparity) will return empty string.
	std::wstring Make(const std::vector<std::wstring>& Args);

	// Return the string without passing arguments if there aren't any
	// If the macro takes arguments, will return empty string.
	std::wstring Make();

	std::wstring GetBasicText() const { return Text; }
	std::wstring GetCommand() const { return Command; }
	void SetCommand(const std::wstring& inCmdS);

	inline void SetText(const std::wstring& Txt) { Text = Txt; }

	inline std::vector<size_t>& GetArgs() { return ArgPos; }
	std::vector<size_t> GetArgs() const { return ArgPos; }

	inline void SetArgs(const std::vector<size_t>& inArgs) { ArgPos = inArgs; }

	~Macro();
};




ZFile& operator<<(ZFile& right, const Macro& op);
	



ZFile& operator>>(ZFile& right, Macro& op);


