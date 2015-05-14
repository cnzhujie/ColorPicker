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
        //将桌面的DC复制到内存DC
        HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);
        hMemDC=CreateCompatibleDC(hDeskTopDC);
        hBitMapMem=CreateCompatibleBitmap(hDeskTopDC,CW,CH);
        SelectObject(hMemDC,hBitMapMem);
        DeleteDC(hDeskTopDC);
        
        //窗口最上
        SetForegroundWindow(this->Handle);
        SetWindowPos(this->Handle,HWND_TOPMOST,0,0,0,0,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOSIZE);
        //程序实例
        HINSTANCE hinstance=(HINSTANCE)GetWindowLong(this->Handle,GWL_HINSTANCE);
        //注册钩子
        hKBHook=SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)KB_Hook_fn,hinstance,0);
        //开始监控鼠标移动
        startWatch();
} 
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
      //注销钩子
      UnhookWindowsHookEx(hKBHook);
      
      DeleteDC(hMemDC);
      DeleteObject(hBitMapMem);
}
//---------------------------------------------------------------------------
void TFormMain::startWatch()
{//开始检测鼠标移动
        imgLock->Hide();
        tmr->Interval = 100;
        tmr->Enabled = True;
}
//---------------------------------------------------------------------------
void TFormMain::endWatch()
{//停止检测鼠标移动
        imgLock->Show();
        tmr->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::tmrTimer(TObject *Sender)
{//鼠标移动检测      
       static int x,y,cx,cy;
       static POINT pt,lastpt;

       //获取当前鼠标位置
       GetCursorPos(&pt);
       if(pt.x == lastpt.x && pt.y==lastpt.y)return;
       lastpt = pt;
       stat->Panels->Items[0]->Text = IntToStr(pt.x)+","+IntToStr(pt.y);
       //获取鼠标处的图像
       HDC hDeskTopDC=CreateDC("DISPLAY",NULL,NULL,NULL);

       //获取鼠标附近的图像
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
       //StretchBlt(hMemDC,0,0,pnlimg->Width,pnlimg->Height,hDeskTopDC,x,y,CW,CH,SRCCOPY | CAPTUREBLT);//如果最后一个参数只是SRCCOPY的话，不能截到半透明窗体,参数CAPTUREBLT的意思就是包含半透明窗体
       DeleteDC(hDeskTopDC);
       //显示
       showCursorImg(cx,cy);
}
//---------------------------------------------------------------------------

void TFormMain::showCursorImg(int cx,int cy)
{      
       static POINT pt2;
       crossCenter.x = cx;
       crossCenter.y = cy;
       HDC hImgCursorDC = GetDC(pnlIMG->Handle);

       StretchBlt(hImgCursorDC,0,0,pnlIMG->Width,pnlIMG->Height,hMemDC,0,0,CW,CH,SRCCOPY | CAPTUREBLT);//如果最后一个参数只是SRCCOPY的话，不能截到半透明窗体,参数CAPTUREBLT的意思就是包含半透明窗体

       //获取鼠标处的颜色值
       color.setColor( GetPixel(hImgCursorDC, cx, cy )); 
       //显示像素值
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
       //释放dc
       ReleaseDC(pnlIMG->Handle,hImgCursorDC);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::pnlRGBClick(TObject *Sender)
{//复制颜色值
       copyColor();
}
//=====================================================================
void TFormMain::copyColor()
{
        if (!::OpenClipboard(this->Handle) || !::EmptyClipboard())
        {
             ShowMessage("复制失败");
             return;
        }
        AnsiString str = color.getRGB();
        //根据环境变量获取数据长度
        size_t cbStr = (str.Length() + 1) * sizeof(char);

        //在堆上动态分配以字节为单位的全局内存区域。成功则指向该内存，失败NULL。参数：1.分配内存属性，2.大小
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr);

        if (hMem == NULL)
        {
             //关闭剪切板,释放剪切板所有权，关闭后就不能写入数据
             CloseClipboard();
             ShowMessage("复制失败");
             return;
        }
        //锁定由GlobalAlloc分配的内存，并将内存对象的锁定计数器+1；成功返回指向内存对象起始地址的指针。失败NULL
        LPTSTR lpDest = (LPTSTR)GlobalLock(hMem);
        /*
        系统为每个全局内存对象维护一个锁定计数器，初始为0，GlobalLock使计数器+1，
        */

        //拷贝数据到剪贴板内存。
        memcpy(lpDest, str.c_str(), cbStr);

        //解除内存锁定，将属性为GMEM_MOVEABLE的内存对象计数器-1.
        GlobalUnlock(hMem);
        /*
        GlobalUnLock计数器-1.一旦计数器值大于0，这块内存区域将不允许被移动或删除，只
        有当为0时，才解除对这块内存的锁定。如果分配时GMEM_FIXED属性，计数器一直为0
        */

        //根据环境变量设置数据格式
        UINT uiFormat = CF_TEXT;

        //设置数据到剪贴板。执行成功，返回数据句柄，否则返回NULL
        SetClipboardData(uiFormat, hMem);
        CloseClipboard();
}
//---------------------------------------------------------------------------
//键盘钩子函数
LRESULT CALLBACK KB_Hook_fn(int nCode,WPARAM wParam,LPARAM lParam)
{
    if(HC_ACTION==nCode)
    {                                                                                                                       
        KBDLLHOOKSTRUCT * pkbHookStruct=(KBDLLHOOKSTRUCT *)lParam;
        if(wParam==WM_KEYDOWN)
        {
            if(pkbHookStruct->vkCode==32)
            {//空格键
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
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,//表示一下几个参数的状态
        NULL,//标识消息定义的位置，只有第一个参数中有FORMAT_MESSAGE_FROM_HMODULE或FORMAT_MESSAGE_FROM_STRING才有用
        GetLastError(),//消息ID,如果第一个参数有FORMAT_MESSAGE_FROM_STRING则被忽略
        MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//设置语言ID，此处表示使用系统缺省语言
        (LPTSTR)&lpMsgBuf,//消息缓冲区
        0,NULL);

    MessageBox(hwnd,lpMsgBuf,TEXT("错误"),MB_ICONERROR);
}
//---------------------------------------------------------------------------

