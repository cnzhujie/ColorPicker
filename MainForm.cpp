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
        crossCenter.x = crossCenter.y = 0;
        CW = 30;
        CH = 30;
        //�������DC���Ƶ��ڴ�DC
        HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);
        hMemDC=CreateCompatibleDC(hDeskTopDC);
        hBitMapMem=CreateCompatibleBitmap(hDeskTopDC,CW,CH);
        SelectObject(hMemDC,hBitMapMem);
        DeleteDC(hDeskTopDC);
        
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
      
      DeleteDC(hMemDC);
      DeleteObject(hBitMapMem);
}
//---------------------------------------------------------------------------
void TFormMain::startWatch()
{//��ʼ�������ƶ�
        imgLock->Hide();
        tmr->Interval = 100;
        tmr->Enabled = True;
}
//---------------------------------------------------------------------------
void TFormMain::endWatch()
{//ֹͣ�������ƶ�
        imgLock->Show();
        tmr->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::tmrTimer(TObject *Sender)
{//����ƶ����      
       static int x,y,cx,cy;
       static POINT pt,lastpt;

       //��ȡ��ǰ���λ��
       GetCursorPos(&pt);
       if(pt.x == lastpt.x && pt.y==lastpt.y)return;
       lastpt = pt;
       stat->Panels->Items[0]->Text = IntToStr(pt.x)+","+IntToStr(pt.y);
       //��ȡ��괦��ͼ��
       HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);

       //��ȡ��긽����ͼ��
       cx = pnlIMG->Width/2;
       cy = pnlIMG->Height/2;
       x = pt.x - CW/2;
       y = pt.y - CH/2;
       if(x<0)
       {
             cx+=x*pnlIMG->Width/CW;
             x=0;
       }
       if(y<0)
       {
             cy+=y*pnlIMG->Height/CH;
             y=0;
       }
       BitBlt(hMemDC,0,0,pnlIMG->Width,pnlIMG->Height,hDeskTopDC,x,y,SRCCOPY | CAPTUREBLT);
       //StretchBlt(hMemDC,0,0,pnlimg->Width,pnlimg->Height,hDeskTopDC,x,y,CW,CH,SRCCOPY | CAPTUREBLT);//������һ������ֻ��SRCCOPY�Ļ������ܽص���͸������,����CAPTUREBLT����˼���ǰ�����͸������
       DeleteDC(hDeskTopDC);
       //��ʾ
       showCursorImg(cx,cy);
}
//---------------------------------------------------------------------------

void TFormMain::showCursorImg(int cx,int cy)
{      
       static POINT pt2;
       crossCenter.x = cx;
       crossCenter.y = cy;
       HDC hImgCursorDC = GetDC(pnlIMG->Handle);

       StretchBlt(hImgCursorDC,0,0,pnlIMG->Width,pnlIMG->Height,hMemDC,0,0,CW,CH,SRCCOPY | CAPTUREBLT);//������һ������ֻ��SRCCOPY�Ļ������ܽص���͸������,����CAPTUREBLT����˼���ǰ�����͸������

       //��ȡ��괦����ɫֵ
       color.setColor( GetPixel(hImgCursorDC, cx, cy )); 
       //��ʾ����ֵ
       pnlRGB->Caption = color.getRGB();
       pnlHSB->Caption = color.getHSB();
       pnlCMYK->Caption = color.getCMYK();
       stat->Panels->Items[1]->Text = color.getRGB();
       pnlColor->Color = color.getTColor();

       HPEN hPen=CreatePen(PS_SOLID,1,RGB(255-color.r,255-color.g,255-color.b));
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
       ReleaseDC(pnlIMG->Handle,hImgCursorDC);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::pnlRGBClick(TObject *Sender)
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
        AnsiString str = color.getRGB();
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
                 FormMain->crossCenter.y-=1;
                 FormMain->showCursorImg(FormMain->crossCenter.x,FormMain->crossCenter.y);
            }
            else if(pkbHookStruct->vkCode==VK_DOWN)
            {
                 FormMain->crossCenter.y+=1;
                 FormMain->showCursorImg(FormMain->crossCenter.x,FormMain->crossCenter.y);
            }
            else if(pkbHookStruct->vkCode==VK_LEFT)
            {
                 FormMain->crossCenter.x-=1;
                 FormMain->showCursorImg(FormMain->crossCenter.x,FormMain->crossCenter.y);
            }
            else if(pkbHookStruct->vkCode==VK_RIGHT)
            {
                 FormMain->crossCenter.x+=1;
                 FormMain->showCursorImg(FormMain->crossCenter.x,FormMain->crossCenter.y);
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

