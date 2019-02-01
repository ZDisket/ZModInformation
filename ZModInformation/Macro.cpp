#include "sdafx.hpp"
#include "Macro.h"


Macro::Macro()
{

	Text = L"";
}

Macro::Macro(const Macro & Cpy)
{
	Text = Cpy.Text;
	ArgPos = Cpy.ArgPos;
}

Macro::Macro(const std::wstring & InText, const std::vector<size_t>& APos)
{
	Text = InText;
	ArgPos = APos;

}

Macro::Macro(const std::wstring & InTxt)
{
	Text = InTxt;

}

std::wstring Macro::Make(const std::vector<std::wstring>& Args)
{
	if (Args.size() != ArgPos.size())
		return L"";

	std::wstring RetTxt = Text;

	size_t p = 0;
	auto It = Args.begin();
	while (It != Args.end()) {

		RetTxt.insert(ArgPos[p], *It);

		++p;
		++It;
	}

	return RetTxt;

}

std::wstring Macro::Make()
{
	if (ArgPos.empty())
		return Text;
	else
		return L""; // Bad boy!!
}


Macro::~Macro()
{
}

ZFile & operator<<(ZFile & right, const Macro & op)
{
	right << op.GetBasicText();
	right << op.GetArgs();
	return right;
}

ZFile & operator>>(ZFile & right, Macro & op)
{

	std::wstring tmp;
	right >> tmp;
	op.SetText(tmp);

	right >> op.GetArgs();

	return right;
}
