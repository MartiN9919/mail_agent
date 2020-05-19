//---------------------------------------------------------------------------

#ifndef UDebugH
#define UDebugH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdIntercept.hpp>
#include <IdLogBase.hpp>
#include <IdLogEvent.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ToolWin.hpp>
//---------------------------------------------------------------------------
class TFDebug : public TForm
{
__published:	// IDE-managed Components
	TRichEdit *RichEdit1;
	TIdLogEvent *IdLogEvent1;
	TCoolBar *CoolBar1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TSaveDialog *SaveDialog1;
	TFindDialog *FindDialog1;
	TToolButton *ToolButton3;
	void __fastcall IdLogEvent1Sent(TComponent *ASender, const UnicodeString AText,
          const UnicodeString AData);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall FindDialog1Find(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall IdLogEvent1Status(TComponent *ASender, const UnicodeString AText);


private:	// User declarations
public:		// User declarations
	__fastcall TFDebug(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFDebug *FDebug;
//---------------------------------------------------------------------------
#endif
