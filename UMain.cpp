//---------------------------------------------------------------------------
#include <vcl.h>
#include <inifiles.hpp>
#include <Vcl.FileCtrl.hpp>
#pragma hdrstop

#include "UMain.h"
#include "UDebug.h"
#include "my_functions.h"
#include "ABOUT.h"
#include <string>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;
TFMyMailAgent *FMyMailAgent;

//---------------------------------------------------------------------------
__fastcall TFMyMailAgent::TFMyMailAgent(TComponent* Owner)
	: TForm(Owner)
{
	CS= new TCriticalSection;

	Max= 0;
	Current= 0;

	MsgCount= 0;
	ErrorCount= 0;

	// Выделение  гиперссылок
	unsigned mask = SendMessage(RichEditBody->Handle, EM_GETEVENTMASK, 0, 0);
	SendMessage(RichEditBody->Handle, EM_SETEVENTMASK, 0, mask | ENM_LINK);
	SendMessage(RichEditBody->Handle, EM_AUTOURLDETECT, true, 0);

	Dir= "Настройки";
	Downloads ="Загрузки";

	if(! DirectoryExists(Dir) )  Dir= "..\\Настройки";
	if(! DirectoryExists(Dir) )  Dir= "Настройки";

	UserFile= "Пользователь.ini";
	CommonFile= "Общие.ini";

	VoiceFile1= Dir+"\\Ошибка.mp3";
	VoiceFile2= Dir+"\\Получены новые сообщения.mp3";

}
//----------------------------------------------------------------------------
void __fastcall TFMyMailAgent::FormCreate(TObject *Sender)
{
	AcClear->Execute();
	AcLoadUser->Execute();
	AcLoadCommon->Execute();

	// Параметры  командной строки для автозапуска
	if(ParamCount()>0)
		{  // Свернуть
			if(ParamStr(1)=="-hide" || ParamCount()==2 && ParamStr(2)=="-hide")
				{
					Application->ShowMainForm= false;
					Visible= false;
				} // Запустить
			if(ParamStr(1)=="-run" || ParamCount()==2 && ParamStr(2)=="-run")
				{
					AcRun->Execute();
				}
 }

#ifdef _DEBUG      // Окно отладки  ( только в Debug сборке )
	 FDebug= new TFDebug(Application);
#endif
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcRunExecute(TObject *Sender)
{
	AcRun->Enabled=  false;
	AcStop->Enabled= true;

	IdThreadComponent1->Start();
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcStopExecute(TObject *Sender)
{

	AcRun->Enabled=  true;
	AcStop->Enabled= false;

	IdThreadComponent1->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcClearExecute(TObject *Sender)
{
	ClearBox();

	Label8->Caption="";
	Label7->Caption="";
	RichEditBody->Clear();
	RichEditLog->Clear();
	ListBox1->Clear();
}
//---------------------------------------------------------------------------
// Поверх других окон
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcStayOnTopExecute(TObject *Sender)
{                 	// Поверх всех окон
	if(AcStayOnTop->Checked) FormStyle= fsStayOnTop;
	else                     FormStyle= fsNormal;

	AcStayOnTop->ImageIndex= AcStayOnTop->Checked ? 4 : 3;
}
//---------------------------------------------------------------------------
// Выделение темы письма в ListBox1
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSelectExecute(TObject *Sender)
{
	if( ListBox1->ItemIndex <0 ) return;

	CS->Acquire();
	try
		{
			RichEditBody->Lines->Assign( Box[ListBox1->ItemIndex]->Body );
			RichEditBody->SelStart= 0;

			Label7->Caption= my::WinToUnicode(Box[ListBox1->ItemIndex]->From->Text);
			Label8->Caption= Box[ListBox1->ItemIndex]->Date.DateTimeString();
			StatusBar1->Panels->Items[0]->Text=
											 my::WinToUnicode(Box[ListBox1->ItemIndex]->Subject);
		}
	__finally
		{
			CS->Release();
		}
}
//--------------------------------------- -------------------------------
// Подмена оконной процедуры для перехода по гиперссылокам
//--------------------------------------- -------------------------------
void __fastcall TFMyMailAgent::WndProc(Messages::TMessage &Message)
{
	if(Message.Msg == WM_NOTIFY)   // #1
		{
			if(((LPNMHDR)Message.LParam)->code == EN_LINK)    // #2
				{
					ENLINK* p = (ENLINK *)Message.LParam;
					if(p->msg == WM_LBUTTONDOWN)       // #3
						{
							SendMessage(RichEditBody->Handle, EM_EXSETSEL, 0, (LPARAM)&(p->chrg));
							ShellExecuteW(Handle,L"open",RichEditBody->SelText.w_str(),0, 0, SW_SHOWNORMAL);
						} // IF  3
				}// IF  2
		} // IF 1
	TForm::WndProc(Message);
}
//---------------------------------------------------------------------------
// Окно настроек
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSettingsExecute(TObject *Sender) // Вызов окна настроек
{
	TFormStyle FStyle=  FormStyle;
	FormStyle= fsNormal;

	bool Active = IdThreadComponent1->Active;

	if( Active ) IdThreadComponent1->Terminate();  // Останавливаем  поток
			 //  Окно настроек
	std::auto_ptr<TFSettings> FSettings(new TFSettings(Application));

	FSettings->EditUserName->Text= IdIMAP41->Username;
	FSettings->EditPassword->Text= IdIMAP41->Password;
	FSettings->EditPort->Text= IntToStr(IdIMAP41->Port);
	FSettings->EditHost->Text= IdIMAP41->Host;
	FSettings->ComboBoxUseTLS->ItemIndex= (int)IdIMAP41->UseTLS;

	FSettings->ComboBoxMailBox->Text= MailBox;
	FSettings->EditInterval->Text= IntToStr(Interval);
	FSettings->EditFrom->Text= From;

	FSettings->CheckBoxAsSeen->Checked= FlagsSet.Contains(mfSeen);
	FSettings->CheckBoxAsDeleted->Checked= FlagsSet.Contains(mfDeleted);

	if(FSettings->ShowModal()== mrOk)   // Применить
		{
			IdIMAP41->Username= FSettings->EditUserName->Text;
			IdIMAP41->Password= FSettings->EditPassword->Text;
			IdIMAP41->Port= FSettings->EditPort->Text.ToIntDef(143);
			IdIMAP41->Host= FSettings->EditHost->Text;
			IdIMAP41->UseTLS= (TIdUseTLS) FSettings->ComboBoxUseTLS->ItemIndex;

			MailBox= FSettings->ComboBoxMailBox->Text;
			Interval= FSettings->EditInterval->Text.ToIntDef(60);
			From= FSettings->EditFrom->Text;

			FlagsSet.Clear();

			if(FSettings->CheckBoxAsSeen->Checked)    FlagsSet<<mfSeen;
			if(FSettings->CheckBoxAsDeleted->Checked) FlagsSet<<mfDeleted;
		}

	if( Active ) IdThreadComponent1->Start();  // Запускаем  поток

	FormStyle= FStyle;
}
//---------------------------------------------------------------------------
// Сохранение общих настроек
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSaveCommonExecute(TObject *Sender)
{
	if( WindowState==wsMaximized )
		{
			Visible= false;
			WindowState= wsMinimized;
		}

	if(!DirectoryExists(Dir))  MkDir(Dir);

	std::auto_ptr<TIniFile>IniFile(new TIniFile(Dir+"\\"+CommonFile) );

	IniFile->WriteInteger("Положение","Слева", Left);
	IniFile->WriteInteger("Положение","Сверху", Top);
	IniFile->WriteInteger("Положение","Ширина", Width);
	IniFile->WriteInteger("Положение","Высота", Height);
	IniFile->WriteInteger("Положение","Ширина списка", ListBox1->Width);
	IniFile->WriteInteger("Положение","Высота лога", RichEditLog->Height);

	IniFile->WriteBool("Вид","Поверх всех окон", AcStayOnTop->Checked);

	IniFile->WriteBool("Аудио","Не воспроизводить", AcVoice->Checked);
	IniFile->WriteString("Аудио","Файл1", VoiceFile1);
	IniFile->WriteString("Аудио","Файл2", VoiceFile2);
}
//---------------------------------------------------------------------------
// Загрузка общих настроек
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcLoadCommonExecute(TObject *Sender)
{
	if(!FileExists(Dir+"\\"+CommonFile) )
		{
			RichEditLog->Lines->Add(
				Time().TimeString()+" Не удалось открыть файл \""+Dir+"\\"+CommonFile+"\""
												 );
			return;
		}

	std::auto_ptr<TIniFile>IniFile(new TIniFile(Dir+"\\"+CommonFile) );
	std::auto_ptr<TStringList>SL(new TStringList);

	IniFile->ReadSectionValues("Положение",SL.get() );

	Left= SL->Values["Слева"].ToIntDef(Left);
	Top= SL->Values["Сверху"].ToIntDef(Top);
	Width= SL->Values["Ширина"].ToIntDef(Width);
	Height= SL->Values["Высота"].ToIntDef(Height);
	ListBox1->Width= SL->Values["Ширина списка"].ToIntDef(ListBox1->Width);

	RichEditLog->Height= SL->Values["Высота лога"].ToIntDef(RichEditLog->Height);
	// Хитрость для сохранения взаимного расположения компонет
	RichEditLog->Top= 0;
	Splitter2->Top= 0;
	ProgressBar1->Top= Width;
	StatusBar1->Top= Width;

	IniFile->ReadSectionValues("Вид",SL.get() );

	AcStayOnTop->Checked= SL->Values["Поверх всех окон"].ToIntDef(0);
	AcStayOnTopExecute(Sender);

	IniFile->ReadSectionValues("Аудио",SL.get() );

	AcVoice->Checked= SL->Values["Не воспроизводить"].ToIntDef(0);
	AcVoice->ImageIndex= AcVoice->Checked ? 14 : 13;

	VoiceFile1=  SL->Values["Файл1"];
	VoiceFile2=  SL->Values["Файл2"];
}
//---------------------------------------------------------------------------
// Сохранение пользовательских настроек
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSaveUserExecute(TObject *Sender)
{
	if(!DirectoryExists(Dir))  MkDir(Dir);

	std::auto_ptr<TIniFile>IniFile(new TIniFile(Dir+"\\"+UserFile) );

	IniFile->WriteString("Почтовый ящик","Логин",IdIMAP41->Username);
	IniFile->WriteString("Почтовый ящик","Пароль",IdIMAP41->Password);
	IniFile->WriteString("Почтовый ящик","Хост",IdIMAP41->Host);
	IniFile->WriteInteger("Почтовый ящик","Порт",IdIMAP41->Port);
	IniFile->WriteInteger("Почтовый ящик","Поддержка TLS",IdIMAP41->UseTLS);

	IniFile->WriteString("Поиск","Ящик",MailBox);
	IniFile->WriteInteger("Поиск","Интервал",Interval);
	IniFile->WriteString("Поиск","От",From);

	IniFile->WriteBool("Отмечать письма","Прочтенными", FlagsSet.Contains(mfSeen)    );
	IniFile->WriteBool("Отмечать письма","Удаленными",  FlagsSet.Contains(mfDeleted) );
}
//---------------------------------------------------------------------------
// Загрузка пользовательских настроек
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcLoadUserExecute(TObject *Sender)
{
	if(!FileExists(Dir+"\\"+UserFile) )
		{
			RichEditLog->Lines->Add(
				Time().TimeString()+" Не удалось открыть файл \""+Dir+"\\"+UserFile+"\""
													 );
			return;
		}

	std::auto_ptr<TIniFile>IniFile(new TIniFile(Dir+"\\"+UserFile) );
	std::auto_ptr<TStringList>SL(new TStringList);

	IniFile->ReadSectionValues("Почтовый ящик",SL.get() );

	IdIMAP41->Username= SL->Values["Логин"];
	IdIMAP41->Password=  SL->Values["Пароль"];
	IdIMAP41->Host= SL->Values["Хост"];
	IdIMAP41->Port= SL->Values["Порт"].ToIntDef(143);
	IdIMAP41->UseTLS= SL->Values["Поддержка TLS"].ToIntDef(0);

	IniFile->ReadSectionValues("Поиск",SL.get() );
	MailBox=  SL->Values["Ящик"];
	Interval= SL->Values["Интервал"].ToIntDef(60);
	From=     SL->Values["От"];

	IniFile->ReadSectionValues("Отмечать письма",SL.get() );

	bool  Seen=  SL->Values["Прочтенными"].ToIntDef(1);
	bool  Deleted= SL->Values["Удаленными"].ToIntDef(0);

	if(Seen)    FlagsSet<<mfSeen;
	if(Deleted) FlagsSet<<mfDeleted;
}
//---------------------------------------------------------------------------
// Выход из программы
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcExitExecute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Сохранить настройки
	AcSaveUser->Execute();
	AcSaveCommon->Execute();

	// Остановить поток
	if( IdThreadComponent1->Active )
			IdThreadComponent1->TerminateAndWaitFor(); // Ждать пока не остановится поток

	// Почистить память
	ClearBox();
	delete CS;
}
//---------------------------------------------------------------------------
//    Методы для потока
//  ( только внутри потока IdThreadComponent  )
//------------------------ Обновление данных (новые письма)------------------
void __fastcall TFMyMailAgent::UpdateData()
{
	ListBox1->Items->Clear();

	for(size_t i=0; i< Box.size(); i++)
		{
			ListBox1->Items->Add( my::WinToUnicode( Box[i]->Subject ) );
		}

	if(ListBox1->ItemIndex<0 && ListBox1->Items->Count)
		{
			ListBox1->ItemIndex= 0;
			AcSelectExecute(ListBox1);
		}
}
//--------------------- Вывод информации -------------------------------------
void __fastcall TFMyMailAgent::ShowInfo()
{
	String Line;

	if(!ErrorCount)// Нет ошибок
		{
			if(MsgCount)// Новые сообщения
				{
					Line= "Получено "+String(MsgCount)+" новых сообщений";

					TrayIcon1->BalloonFlags= bfInfo;
					TrayIcon1->BalloonTitle= From;
					MediaPlayer1->FileName= VoiceFile2;
				}
			else Line ="Нет новых сообщений";
		}
	else// Ошибка
		{
			TrayIcon1->BalloonTitle="Ошибка";
			TrayIcon1->BalloonFlags= bfError;
			MediaPlayer1->FileName= VoiceFile1;
			Line= "Возникла ошибка: \""+my::ReplaceCRLF(ErrorMsg)+"\"";
		}
	// Уведомление  в трее
	if(MsgCount || ErrorCount == 1)
		{
			TrayIcon1->BalloonHint=  Line;
			TrayIcon1->ShowBalloonHint();
		}
	// Голос
	if(!AcVoice->Checked && (MsgCount || ErrorCount==1) )
		{
		 try
			 {
				 MediaPlayer1->Open();
				 MediaPlayer1->Play();
			 }
		 catch(...)
			 {
				 Line+= "\nНе удалось открыть аудио файл :\""+MediaPlayer1->FileName+"\"";
			 }
		}
	// Лог
	RichEditLog->Lines->Add(Time().TimeString()+" "+Line);
	RichEditLog->Perform(WM_KEYDOWN,VK_NEXT,0);
	// Статус  панель
	StatusBar1->Panels->Items[0]->Text= Line;
}
//--------------------- Ожидание --------------------------------------------
void __fastcall TFMyMailAgent::Wait(unsigned second)
{
	int k= 10*second;

	while( !IdThreadComponent1->Terminated && k)
		{
			Sleep(100);
			k--;
		}
}
//------------- Поток для опроса данных с почтового ящика ---------------------
void __fastcall TFMyMailAgent::IdThreadComponent1Run(TIdThreadComponent *Sender)
{
try
	{
		 if( !IdIMAP41->Connected() && !IdThreadComponent1->Terminated)   // Если есть конект и поток не останавливается
			{
				IdIMAP41->Connect();
			}

		 if( IdIMAP41->ConnectionState!= csSelected && !IdThreadComponent1->Terminated)  // Если не выделен ящик и поток не останавливается
			{
				IdIMAP41->SelectMailBox(MailBox);
			}

		 TIdIMAP4SearchRec SR[2];     // параметры поиска
		 SR[0].SearchKey= skFrom;     // письма  от ...
		 SR[0].Text= From;
		 SR[1].SearchKey= skUnseen;   // Не прочтенные письма

		 MsgCount= 0;

		 IdIMAP41->CheckMailBox();

		 if( IdIMAP41->SearchMailBox(SR,2) )
			 {
				MsgCount = IdIMAP41->MailBox->SearchResult.Length;
				for (size_t i=0; i<MsgCount; i++)
				 {
					 if(IdThreadComponent1->Terminated) return;

					 TIdMessage* IdMessageX = new TIdMessage(NULL);
					 IdIMAP41->Retrieve(IdIMAP41->MailBox->SearchResult[i],IdMessageX);

					 CS->Acquire();
					 try
						 {
							 Box.push_front(IdMessageX);
						 }
					 __finally
						 {
							 CS->Release();
						 }

						if( !FlagsSet.Empty() )
								IdIMAP41->StoreFlags( &IdIMAP41->MailBox->SearchResult[i],1,sdAdd,FlagsSet);
					} // FOR
			 } // IF

		if(MsgCount)
			{
				Sender->Synchronize( &UpdateData );
			}
		IdIMAP41->CloseMailBox();

		ErrorCount= 0;
	 }
catch(EIdException &E)
	{
		if(IdThreadComponent1->Terminated) return;
		else IdIMAP41->Disconnect(false);

		ErrorCount++;
		ErrorMsg = E.Message;
	}

if(IdThreadComponent1->Terminated) return;

Sender->Synchronize( &ShowInfo );
Sender->Synchronize( &ProgressEnd );
Wait(Interval);
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::IdThreadComponent1Terminate(TIdThreadComponent *Sender)
{
	IdIMAP41->Disconnect(true);
}
//---------------------------------------------------------------------------
//  Обработчики процесса загрузки  IdIMAP41
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::IdIMAP41WorkBeginForPart(TObject *ASender, TWorkMode AWorkMode,
					__int64 AWorkCountMax)
{
	if(AWorkMode == wmRead)
		{
			Max= AWorkCountMax;
			IdThreadComponent1->Synchronize(&ProgressBegin);
		}
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::IdIMAP41WorkForPart(TObject *ASender, TWorkMode AWorkMode,
					__int64 AWorkCount)
{
	if(AWorkMode == wmRead)
		{
			Current =  AWorkCount;
			IdThreadComponent1->Synchronize(&Progress);
		}
}
//---------------------------------------------------------------------------
//  Методы для отображение прогресса    ( вызов только через Syncronyze() )
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::ProgressBegin()
{
	ProgressBar1->Max= Max;
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::Progress()
{
	ProgressBar1->Position= Current;
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::ProgressEnd()
{
	Current= 0;
	ProgressBar1->Position= 0;
}
//---------------------------------------------------------------------------
//  Реализация сворачивания/разворачивания окна трей
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::WMSysCommand(TWMSysCommand& Msg)
{           // Кнопка свернуть
	if (Msg.CmdType == SC_MINIMIZE) Visible= false;
	else DefWindowProc(Handle,WM_SYSCOMMAND,Msg.CmdType,MAKELPARAM(Msg.XPos,Msg.YPos));

	Msg.Result= 0;
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::TrayIcon1Click(TObject *Sender)
{
	Visible= !Visible;
	if(Visible) SetForegroundWindow(Handle);
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcRestoreExecute(TObject *Sender)
{
	Visible= true;
	SetForegroundWindow(Handle);
}
//---------------------------------------------------------------------------
// Голосовое уведомление
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcVoiceExecute(TObject *Sender)
{
	AcVoice->ImageIndex= ( AcVoice->Checked ) ? 14 : 13;
}
//---------------------------------------------------------------------------
// Очистка контейнера писем
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::ClearBox()
{
	CS->Acquire();
	try
		{
			for(size_t i=0; i<Box.size(); i++) delete Box[i];
			Box.clear();
		}
	__finally
		{
			CS->Release();
    }
}
//---------------------------------------------------------------------------
// Окно "О программе"
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcAboutExecute(TObject *Sender)
{
	TFormStyle FStyle=  FormStyle;
	FormStyle= fsNormal;
	AboutBox->ShowModal();
	FormStyle= FStyle;
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSaveAllExecute(TObject *Sender)
{
	TFormStyle FStyle=  FormStyle;
	FormStyle= fsNormal;

	if(!DirectoryExists(Downloads) ) MkDir(Downloads);

	String FileName,ChosenDir;

	CS->Acquire();
	try
		{
			if( SelectDirectory("Выберите директорию:",ExtractFilePath(Application->ExeName),ChosenDir ) )
			for(size_t index=0; index<Box.size(); index++)
				{
						{
							FileName=
								my::GenFileName(my::WinToUnicode(Box.at(index)->Subject))+
								" ("+Box.at(index)->Date.FormatString("hh-mm-ss DD.MM.YYYY")+").msg";

							Box.at(index)->SaveToFile(ChosenDir+"\\"+FileName);
						}
				}
	 }
 __finally
	 {
		 CS->Release();
	 }

	FormStyle= FStyle;
}
//---------------------------------------------------------------------------
void __fastcall TFMyMailAgent::AcSaveAsExecute(TObject *Sender)
{
	if(ListBox1->ItemIndex>=0)
		{
			TFormStyle FStyle=  FormStyle;
			FormStyle= fsNormal;
			if(!DirectoryExists(Downloads) ) MkDir(Downloads);
			SaveDialog1->InitialDir= ExtractFilePath(Application->ExeName)+Downloads;

			CS->Acquire();
			try
				{


					for(size_t index=0; index<Box.size(); index++)
						{
							if(ListBox1->Selected[index])
								{
									SaveDialog1->FileName=
										my::GenFileName(my::WinToUnicode(Box.at(index)->Subject))+
										" ("+Box.at(index)->Date.FormatString("hh-mm-ss DD.MM.YYYY")+")";

									if(SaveDialog1->Execute() )
										 Box.at(index)->SaveToFile(SaveDialog1->FileName);
								}  // if selected
						}// for
				}
		 __finally
				{
					CS->Release();
				}
			FormStyle= FStyle;
		 }// Index>=0
}
//---------------------------------------------------------------------------
  bool Send_SMTP(string host, int port, string username, string password, string email, string body, string subject, string file)
{

TIdSMTP* SMTP = new TIdSMTP(FMyMailAgent);
SMTP->Host = host.c_str();
SMTP->Port = port;
SMTP->AuthType = satDefault;
SMTP->Username = username.c_str();
SMTP->Password = password.c_str();


TIdSSLIOHandlerSocketOpenSSL* SSLOpen = new TIdSSLIOHandlerSocketOpenSSL(NULL);
SSLOpen->Host = SMTP->Host;
SSLOpen->Port = SMTP->Port;
SSLOpen->DefaultPort = 0;
SSLOpen->SSLOptions->Method = sslvSSLv23;
SSLOpen->SSLOptions->Mode = sslmUnassigned;

SMTP->IOHandler = SSLOpen;
SMTP->UseTLS = utUseImplicitTLS;


TIdMessage* msg = new TIdMessage(FMyMailAgent);
msg->CharSet = "windows-1251";
msg->Body->Text = body.c_str();
msg->Subject = subject.c_str();
msg->From->Address = SMTP->Username;
msg->From->Name = "Anonymous";
msg->Recipients->EMailAddresses = email.c_str();
msg->IsEncoded = True;

TIdAttachment* att = new TIdAttachmentFile(msg->MessageParts, file.c_str());
msg->MessageParts->Add();
msg->MessageParts->Items[0] = att;



SMTP->Connect();
if (SMTP->Connected())
{
SMTP->Send(msg);
return true;
} else{return false;}


SMTP->Disconnect();
SMTP->Free();
SSLOpen->Free();
msg->Free();
}



void __fastcall TFMyMailAgent::Button1Click(TObject *Sender)
{
if (Send_SMTP("smtp.gmail.com",465,"andrey.martsynkevich@gmail.com","7132070+","andrey.martsynkevich@gmail.com","Test send","Hello World","C:\\1.txt") == True )
{
ShowMessage("Cообщение отправлено!");
}
else
{
ShowMessage("Ошибка отправки.");
}
}
//---------------------------------------------------------------------------

