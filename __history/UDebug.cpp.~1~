//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UDebug.h"
#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFDebug *FDebug;
//---------------------------------------------------------------------------
__fastcall TFDebug::TFDebug(TComponent* Owner)
	: TForm(Owner)
{
RichEdit1->Clear();
Top=5;
Left= Screen->Width- Width-5;
FMyMailAgent->IdIMAP41->Intercept= IdLogEvent1;
Visible= true;
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::IdLogEvent1Sent(TComponent *ASender, const UnicodeString AText,
          const UnicodeString AData)
{
RichEdit1->Lines->Add(AData);
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::IdLogEvent1Status(TComponent *ASender, const UnicodeString AText)

{
RichEdit1->Lines->Add(AText);
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::ToolButton1Click(TObject *Sender)
{
RichEdit1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::ToolButton2Click(TObject *Sender)
{
SaveDialog1->Options= SaveDialog1->Options<<ofNoChangeDir;
SaveDialog1->InitialDir= ExtractFileDir(Application->ExeName);

SaveDialog1->FileName="log";
SaveDialog1->Filter="текстовый|*.txt";
SaveDialog1->DefaultExt="txt";

if(SaveDialog1->Execute() )
	{
	 RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::FindDialog1Find(TObject *Sender)
{
// Код взят со справки IDE "RichEdit" " FindText (C++) "
int FoundAt, StartPos, ToEnd;
  TSearchTypes mySearchTypes = TSearchTypes();
  // Begin the search after the current selection,
  // if there is one.
  // Otherwise, begin at the start of the text.
  if (FindDialog1->Options.Contains(frMatchCase))
        mySearchTypes << stMatchCase;
  if (FindDialog1->Options.Contains(frWholeWord))
        mySearchTypes << stWholeWord;
  if (RichEdit1->SelLength)
        StartPos = RichEdit1->SelStart + RichEdit1->SelLength;
  else
        StartPos = 0;
  // ToEnd is the length from StartPos
  // to the end of the text in the rich edit control.
  ToEnd = RichEdit1->Text.Length() - StartPos;
  FoundAt = RichEdit1->FindText(FindDialog1->FindText, StartPos, ToEnd, mySearchTypes);
  if (FoundAt != -1)
  {
        RichEdit1->SetFocus();
        RichEdit1->SelStart = FoundAt;
        RichEdit1->SelLength = FindDialog1->FindText.Length();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFDebug::ToolButton3Click(TObject *Sender)
{
FindDialog1->Execute();
}
//---------------------------------------------------------------------------

