//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::LinkLabel1LinkClick(TObject *Sender, const UnicodeString Link,
          TSysLinkType LinkType)
{
	ShellExecuteW(Handle,L"open",Link.w_str(),NULL,NULL,SW_RESTORE);
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::ProgramIconClick(TObject *Sender)
{
	ShellExecuteW(Handle,L"open",L"https://vk.com/m0101101",NULL,NULL,SW_RESTORE);
}
//---------------------------------------------------------------------------







