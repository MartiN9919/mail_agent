//---------------------------------------------------------------------------
#pragma hdrstop
#include "my_functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
String my::ReplaceCRLF(String Text)
{
	return StringReplace(Text,"\r\n"," ",TReplaceFlags() );
}
//---------------------------------------------------------------------------
String my::WinToUnicode(const String St)
{
 String Result="";
 for (int i = 1; i <= St.Length(); i++)
 {
	if (int(St[i])>= 0x00C0 && int(St[i])<= 0x00FF)
		Result += wchar_t( int(St[i])+0x350);
	else Result += St[i];
 }
 return Result;
}
//---------------------------------------------------------------------------
String my::GenFileName(String Text)
{
	const size_t size= 9;
	const wchar_t chset[size]= L"\\/:?\"<>|";

	for(size_t i=1; i<=Text.Length(); i++)
		for(size_t j=0; j< size; j++)
		 if( Text[i]== chset[j] ) Text[i]=L'_';

return Text;
}
//---------------------------------------------------------------------------
