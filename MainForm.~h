//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TTimer *tmr;
        TPanel *pnlinfo;
        TPanel *pnlimg;
        TPanel *pnlcn;
        TImage *imglock;
        void __fastcall tmrTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall pnlcnClick(TObject *Sender);
        void __fastcall pnlimgClick(TObject *Sender);
public:	// User declarations
        void startWatch();
        void endWatch();
        void copyColor();
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
 
        HHOOK hKBHook;
};

#define CW      60
#define CH      60
LRESULT CALLBACK KB_Hook_fn(int nCode,WPARAM wParam,LPARAM lParam);
void ShowError(HWND hwnd);

//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
