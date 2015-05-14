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
#include <ComCtrls.hpp>
#include "Color.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TTimer *tmr;
        TPanel *pnlInfo;
        TPanel *pnlIMG;
        TStatusBar *stat;
        TPanel *pnlColor;
        TPanel *pnlColorValue;
        TPanel *pnlRGB;
        TImage *imgLock;
        TPanel *pnlHSB;
        TPanel *pnlCMYK;
        void __fastcall tmrTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall pnlRGBClick(TObject *Sender);
public:	// User declarations
        void startWatch();
        void endWatch();
        void showCursorImg(int cx,int cy);
        void copyColor();
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);

        int CW;
        int CH;
        POINT crossCenter;
        MixedColor color;
        HDC hMemDC;
        HBITMAP hBitMapMem;
        HHOOK hKBHook;
};

LRESULT CALLBACK KB_Hook_fn(int nCode,WPARAM wParam,LPARAM lParam);
void ShowError(HWND hwnd);

//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
