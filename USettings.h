//---------------------------------------------------------------------------

#ifndef USettingsH
#define USettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFSettings : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *EditUserName;
	TEdit *EditPassword;
	TEdit *EditHost;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *EditFrom;
	TEdit *EditInterval;
	TCheckBox *CheckBoxAsSeen;
	TButton *bApply;
	TButton *bCancel;
	TEdit *EditPort;
	TLabel *Label7;
	TCheckBox *CheckBoxAsDeleted;
	TLabel *Label8;
	TComboBox *ComboBoxMailBox;
	TComboBox *ComboBoxUseTLS;
	TLabel *Label9;
	void __fastcall bApplyClick(TObject *Sender);
	void __fastcall bCancelClick(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);

private:	// User declarations
public:		// User declarations
	__fastcall TFSettings(TComponent* Owner);

	enum { sApply,sCancel } State;
};
//---------------------------------------------------------------------------
extern PACKAGE TFSettings *FSettings;
//---------------------------------------------------------------------------
#endif
