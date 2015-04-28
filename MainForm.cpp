//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                       
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}  
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{       
        //��������
        SetForegroundWindow(this->Handle);
        SetWindowPos(this->Handle,HWND_TOPMOST,0,0,0,0,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
        //����ʵ��
        HINSTANCE hinstance=(HINSTANCE)GetWindowLong(this->Handle,GWL_HINSTANCE);
        //ע�ṳ��
        hKBHook=SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)KB_Hook_fn,hinstance,0);
        //��ʼ�������ƶ�
        startWatch();
} 
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
      //ע������
      UnhookWindowsHookEx(hKBHook);
}
//---------------------------------------------------------------------------
void TFormMain::startWatch()
{//��ʼ�������ƶ�
        imglock->Hide();
        tmr->Interval = 100;
        tmr->Enabled = True;
}
//---------------------------------------------------------------------------
void TFormMain::endWatch()
{//ֹͣ�������ƶ�
        imglock->Show();
        tmr->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::tmrTimer(TObject *Sender)
{//����ƶ����
       static int x,y,cx,cy; 
       static POINT pt,pt2;
       static int b,g,r;

       //��ȡ��ǰ���λ��
       GetCursorPos(&pt);

       HWND hCurrentWin=WindowFromPoint(pt);
       if(hCurrentWin==this->Handle || hCurrentWin==pnlcn->Handle
                || hCurrentWin==pnlimg->Handle)return;

       //��ȡ����hdc
       HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);
       //��ȡ��ǰ��������ֵ
       COLORREF clr = GetPixel(hDeskTopDC, pt.x, pt.y);
       b=GetBValue(clr);
       g=GetGValue(clr);
       r=GetRValue(clr);
       AnsiString str = IntToHex(r,2) + IntToHex(g,2) + IntToHex(b,2);
       pnlcn->Caption = "#"+str;
       str = IntToHex(b,2) + IntToHex(g,2) + IntToHex(r,2);
       pnlcn->Font->Color = StrToInt("$00"+str);
       str = IntToHex(255-b,2) + IntToHex(255-g,2) + IntToHex(255-r,2);
       pnlcn->Color = StrToInt("$00"+str); 

       //��ʾ��긽����ͼ��
       HDC hImgCursorDC = GetDC(pnlimg->Handle);
       cx = pnlimg->Width/2;
       cy = pnlimg->Height/2;
       x = pt.x - CW/2;
       y = pt.y - CH/2;
       if(x<0)
       {        
            cx+=x*pnlimg->Width/CW;
            x=0;
       }
       if(y<0)
       {        
            cy+=y*pnlimg->Height/CH;
            y=0;
       }
       StretchBlt(hImgCursorDC,0,0,pnlimg->Width,pnlimg->Height,hDeskTopDC,x,y,CW,CH,SRCCOPY | CAPTUREBLT);//������һ������ֻ��SRCCOPY�Ļ������ܽص���͸������,����CAPTUREBLT����˼���ǰ�����͸������
       //�������λ��
       HPEN hPen=CreatePen(PS_SOLID,1,RGB(255-r,255-g,255-b));
       HPEN hPenOld = ( HPEN )SelectObject(hImgCursorDC,hPen);
       
       pt2.x = cx; pt2.y = cy - 2;
       MoveToEx(hImgCursorDC,pt2.x,pt2.y,NULL);
       pt2.y -= 5;
       LineTo(hImgCursorDC,pt2.x,pt2.y);
       pt2.x = cx; pt2.y = cy + 2;
       MoveToEx(hImgCursorDC,pt2.x,pt2.y,NULL);
       pt2.y += 5;
       LineTo(hImgCursorDC,pt2.x,pt2.y);   
       pt2.x = cx-2; pt2.y = cy;
       MoveToEx(hImgCursorDC,pt2.x,pt2.y,NULL);
       pt2.x -= 5;
       LineTo(hImgCursorDC,pt2.x,pt2.y);
       pt2.x = cx+2; pt2.y = cy;
       MoveToEx(hImgCursorDC,pt2.x,pt2.y,NULL);
       pt2.x += 5;
       LineTo(hImgCursorDC,pt2.x,pt2.y);

       SelectObject (hImgCursorDC , hPenOld);
       DeleteObject ( hPen );
       //�ͷ�dc
       ReleaseDC(pnlimg->Handle,hImgCursorDC);
       DeleteDC(hDeskTopDC);
} 
//---------------------------------------------------------------------------

void __fastcall TFormMain::pnlimgClick(TObject *Sender)
{//���
       static POINT pt;
       static int b,g,r;
       //��ȡ��ǰ���λ��
       GetCursorPos(&pt);
       
       //��ȡ����hdc
       HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);
       //��ȡ��ǰ��������ֵ
       COLORREF clr = GetPixel(hDeskTopDC, pt.x, pt.y);
       b=GetBValue(clr);
       g=GetGValue(clr);
       r=GetRValue(clr);
       AnsiString str = IntToHex(r,2) + IntToHex(g,2) + IntToHex(b,2);
       pnlcn->Caption = "#"+str;
       str = IntToHex(b,2) + IntToHex(g,2) + IntToHex(r,2);
       pnlcn->Font->Color = StrToInt("$00"+str);
       str = IntToHex(255-b,2) + IntToHex(255-g,2) + IntToHex(255-r,2);
       pnlcn->Color = StrToInt("$00"+str);

       DeleteDC(hDeskTopDC);

       copyColor();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::pnlcnClick(TObject *Sender)
{//������ɫֵ
            copyColor();
}
//=====================================================================
void TFormMain::copyColor()
{
        if (!::OpenClipboard(this->Handle) || !::EmptyClipboard())
        {
             ShowMessage("����ʧ��");
             return;
        }
        AnsiString str = pnlcn->Caption;
        //���ݻ���������ȡ���ݳ���
        size_t cbStr = (str.Length() + 1) * sizeof(char);

        //�ڶ��϶�̬�������ֽ�Ϊ��λ��ȫ���ڴ����򡣳ɹ���ָ����ڴ棬ʧ��NULL��������1.�����ڴ����ԣ�2.��С
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr);

        if (hMem == NULL)
        {
             //�رռ��а�,�ͷż��а�����Ȩ���رպ�Ͳ���д������
             CloseClipboard();
             ShowMessage("����ʧ��");
             return;
        }
        //������GlobalAlloc������ڴ棬�����ڴ���������������+1���ɹ�����ָ���ڴ������ʼ��ַ��ָ�롣ʧ��NULL
        LPTSTR lpDest = (LPTSTR)GlobalLock(hMem);
        /*
        ϵͳΪÿ��ȫ���ڴ����ά��һ����������������ʼΪ0��GlobalLockʹ������+1��
        */

        //�������ݵ��������ڴ档
        memcpy(lpDest, str.c_str(), cbStr);

        //����ڴ�������������ΪGMEM_MOVEABLE���ڴ���������-1.
        GlobalUnlock(hMem);
        /*
        GlobalUnLock������-1.һ��������ֵ����0������ڴ����򽫲������ƶ���ɾ����ֻ
        �е�Ϊ0ʱ���Ž��������ڴ���������������ʱGMEM_FIXED���ԣ�������һֱΪ0
        */

        //���ݻ��������������ݸ�ʽ
        UINT uiFormat = CF_TEXT;

        //�������ݵ������塣ִ�гɹ����������ݾ�������򷵻�NULL
        SetClipboardData(uiFormat, hMem);
        CloseClipboard();
}
//---------------------------------------------------------------------------
//���̹��Ӻ���
LRESULT CALLBACK KB_Hook_fn(int nCode,WPARAM wParam,LPARAM lParam)
{
    if(HC_ACTION==nCode)
    {                                                                                                                       
        KBDLLHOOKSTRUCT * pkbHookStruct=(KBDLLHOOKSTRUCT *)lParam;
        if(wParam==WM_KEYDOWN)
        {
            if(pkbHookStruct->vkCode==32)
            {//�ո��
                if(FormMain->tmr->Enabled)
                {
                        FormMain->copyColor();
                        FormMain->endWatch();
                }
                else
                {
                        FormMain->startWatch();
                }
            }
            else if(pkbHookStruct->vkCode==VK_UP)
            {
                 POINT pt;
                 GetCursorPos(&pt);
                 pt.y-=1;
                 SetCursorPos(pt.x,pt.y);
            }
            else if(pkbHookStruct->vkCode==VK_DOWN)
            { 
                 POINT pt;
                 GetCursorPos(&pt);
                 pt.y+=1;
                 SetCursorPos(pt.x,pt.y);
            }
            else if(pkbHookStruct->vkCode==VK_LEFT)
            {   
                 POINT pt;
                 GetCursorPos(&pt);
                 pt.x-=1;
                 SetCursorPos(pt.x,pt.y);
            }
            else if(pkbHookStruct->vkCode==VK_RIGHT)
            {   
                 POINT pt;
                 GetCursorPos(&pt);
                 pt.x+=1;
                 SetCursorPos(pt.x,pt.y);
            }
        }
    }
    return CallNextHookEx(FormMain->hKBHook,nCode,wParam,lParam);
}
//---------------------------------------------------------------------------
void ShowError(HWND hwnd)
{
    TCHAR *lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//��ʾһ�¼���������״̬
        NULL,//��ʶ��Ϣ�����λ�ã�ֻ�е�һ����������FORMAT_MESSAGE_FROM_HMODULE��FORMAT_MESSAGE_FROM_STRING������
        GetLastError(),//��ϢID,�����һ��������FORMAT_MESSAGE_FROM_STRING�򱻺���
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//��������ID���˴���ʾʹ��ϵͳȱʡ����
        (LPTSTR)&lpMsgBuf,//��Ϣ������
        0,NULL);

    MessageBox(hwnd,lpMsgBuf,TEXT("����"),MB_ICONERROR);
}
//---------------------------------------------------------------------------

