#include "sdafx.hpp"
#include "Macro.h"


Macro::Macro()
{

	Text = L"";
	Command = L"";
}

Macro::Macro(const Macro & Cpy)
{
	Command = Cpy.Command;
	Text = Cpy.Text;
	ArgPos = Cpy.ArgPos;
}

Macro::Macro(const std::wstring & InText, const std::vector<size_t>& APos)
{
	Text = InText;
	ArgPos = APos;

}

Macro::Macro(const std::wstring & InText, const std::wstring & insCmd, const std::vector<size_t>& APos)
{
	Text = InText;
	ArgPos = APos;
	Command = insCmd;

}

Macro::Macro(const std::wstring & InTxt, const std::wstring& inCmd)
{
	Text = InTxt;
	Command = inCmd;
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

void Macro::SetCommand(const std::wstring & inCmdS)
{
	Command = inCmdS;
}


Macro::~Macro()
{
}

ZFile & operator<<(ZFile & right, const Macro & op)
{
	right << op.GetCommand();
	right << op.GetBasicText();
	right << op.GetArgs();
	return right;
}

ZFile & operator>>(ZFile & right, Macro & op)
{
	std::wstring tmcommand;
	right >> tmcommand;
	op.SetCommand(tmcommand);

	std::wstring tmp;
	right >> tmp;
	op.SetText(tmp);

	std::vector<size_t> targs;


	right >> targs;

	op.SetArgs(targs);
	return right;
}
