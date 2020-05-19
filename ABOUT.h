//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TLabel *Version;
	TButton *OKButton;
	TLinkLabel *LinkLabel1;
	TLinkLabel *LinkLabel3;
	TMemo *Memo1;
	TImage *ProgramIcon;
	void __fastcall LinkLabel1LinkClick(TObject *Sender, const UnicodeString Link, TSysLinkType LinkType);
	void __fastcall ProgramIconClick(TObject *Sender);

private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
