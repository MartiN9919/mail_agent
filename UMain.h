//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdIMAP4.hpp>
#include <IdMessage.hpp>
#include <IdMessageClient.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdThreadComponent.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.MPlayer.hpp>
#include <IdMailBox.hpp>
#include <Vcl.Dialogs.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdSMTP.hpp>
#include <IdSMTPBase.hpp>
#include <IdAttachmentFile.hpp>
//---------------------------------------------------------------------------
#include <deque>
#include "USettings.h"
//---------------------------------------------------------------------------
class TFMyMailAgent : public TForm
{
__published:	// IDE-managed Components
	TIdIMAP4 *IdIMAP41;
	TRichEdit *RichEditBody;
	TIdThreadComponent *IdThreadComponent1;
	TPopupMenu *PopupMenu1;
	TSplitter *Splitter1;
	TProgressBar *ProgressBar1;
	TListBox *ListBox1;
	TStatusBar *StatusBar1;
	TRichEdit *RichEditLog;
	TSplitter *Splitter2;
	TTrayIcon *TrayIcon1;
	TActionList *ActionList1;
	TAction *AcSelect;
	TAction *AcUpdate;
	TAction *AcRun;
	TAction *AcStop;
	TAction *AcExit;
	TAction *AcStayOnTop;
	TAction *AcClear;
	TAction *AcLoadCommon;
	TAction *AcLoadUser;
	TAction *AcSaveUser;
	TAction *AcSaveCommon;
	TAction *AcSettings;
	TImageList *ImageList1;
	TPopupMenu *PopupMenu2;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N8;
	TMediaPlayer *MediaPlayer1;
	TBalloonHint *BalloonHint1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N5;
	TMenuItem *N7;
	TMenuItem *N12;
	TMenuItem *N2;
	TMenuItem *N14;
	TMenuItem *N15;
	TMenuItem *N13;
	TMenuItem *N4;
	TMenuItem *N3;
	TCoolBar *CoolBar1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton6;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton8;
	TPanel *Panel1;
	TLabel *Label7;
	TLabel *Label8;
	TMenuItem *N16;
	TToolButton *ToolButton3;
	TAction *AcVoice;
	TAction *AcAbout;
	TMenuItem *N17;
	TAction *AcRestore;
	TMenuItem *N9;
	TMenuItem *N18;
	TMenuItem *N20;
	TMenuItem *N19;
	TMenuItem *N21;
	TMenuItem *N6;
	TMenuItem *N22;
	TToolButton *ToolButton7;
	TAction *AcSaveAs;
	TAction *AcSaveAll;
	TMenuItem *N23;
	TMenuItem *N24;
	TSaveDialog *SaveDialog1;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TIdSMTP *IdSMTP1;
	TIdMessage *IdMessage1;
	TButton *Button1;
	void __fastcall IdThreadComponent1Run(TIdThreadComponent *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AcRunExecute(TObject *Sender);
	void __fastcall AcStopExecute(TObject *Sender);
	void __fastcall AcExitExecute(TObject *Sender);
	void __fastcall AcStayOnTopExecute(TObject *Sender);
	void __fastcall AcSelectExecute(TObject *Sender);
	void __fastcall IdIMAP41WorkBeginForPart(TObject *ASender, TWorkMode AWorkMode,
          __int64 AWorkCountMax);
	void __fastcall IdIMAP41WorkForPart(TObject *ASender, TWorkMode AWorkMode, __int64 AWorkCount);
	void __fastcall AcClearExecute(TObject *Sender);
	void __fastcall AcSettingsExecute(TObject *Sender);
	void __fastcall AcSaveUserExecute(TObject *Sender);
	void __fastcall AcLoadUserExecute(TObject *Sender);
	void __fastcall IdThreadComponent1Terminate(TIdThreadComponent *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TrayIcon1Click(TObject *Sender);
	void __fastcall AcVoiceExecute(TObject *Sender);
	void __fastcall AcSaveCommonExecute(TObject *Sender);
	void __fastcall AcLoadCommonExecute(TObject *Sender);
	void __fastcall AcAboutExecute(TObject *Sender);
	void __fastcall AcRestoreExecute(TObject *Sender);
	void __fastcall AcSaveAllExecute(TObject *Sender);
	void __fastcall AcSaveAsExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);


private:	// User declarations
	 TFSettings* FSettings; // ���� ��������

	 std::deque<TIdMessage*> Box; // ��������� � ��������
	 TCriticalSection *CS;  // ��� ���������. ������� � ���������� � ��������

	 // ����� ������ � ������
	 size_t MsgCount;
	 size_t	ErrorCount;
	 String ErrorMsg;

	 //
	 String Dir;    // ���� � ����� � ������ ��������
	 String UserFile;   // ��� ����� �������� ������������
	 String CommonFile;   // ��� ����� ����� ��������
	 String Downloads;   // ����� ��� ��������
	 //
	 void __fastcall UpdateData(); // ���������� �����
	 //  ����������� �������� ��������
	 __int64 Max;
	 __int64 Current;

	 void __fastcall Progress();
	 void __fastcall ProgressBegin();
	 void __fastcall ProgressEnd();
	 // ����� ���������� � ��������� ����� ����������� � �������
	 void __fastcall ShowInfo();
	 // ���������� �������� � ������
	 void __fastcall Wait(unsigned second);

	 // �������� � ������ �����
	 void __fastcall WMSysCommand(TWMSysCommand&);
	 // ����� ��������� � ������� ������ ��������
	 BEGIN_MESSAGE_MAP
	 MESSAGE_HANDLER(WM_SYSCOMMAND,TWMSysCommand,WMSysCommand);
	 END_MESSAGE_MAP(TComponent);
	 // ��� ��������� ������� �� ������
	 void __fastcall WndProc(Messages::TMessage &Message);
	 void __fastcall ClearBox();

public:		// User declarations

	 // ���������
	 int Interval;
	 String From;
	 String MailBox;
	 TIdMessageFlagsSet FlagsSet;

	 String VoiceFile;
	 String VoiceFile1;
	 String VoiceFile2;

	__fastcall TFMyMailAgent(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMyMailAgent *FMyMailAgent;
//---------------------------------------------------------------------------
#endif
