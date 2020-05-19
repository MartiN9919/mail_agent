//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "USettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFSettings *FSettings;
//---------------------------------------------------------------------------
__fastcall TFSettings::TFSettings(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFSettings::bApplyClick(TObject *Sender)
{
//

}
//---------------------------------------------------------------------------

void __fastcall TFSettings::bCancelClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFSettings::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
					bool &Resize)
{
Resize= false;
}
//---------------------------------------------------------------------------


