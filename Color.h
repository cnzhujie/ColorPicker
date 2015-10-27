//---------------------------------------------------------------------------

#ifndef ColorH
#define ColorH

#include <vcl.h>

class MixedColor
{
public:
        MixedColor(){}
        ~MixedColor(){}
        void setColor(COLORREF clr1)
        {
             clr = clr1;
             b=GetBValue(clr);
             g=GetGValue(clr);
             r=GetRValue(clr);
        }

        AnsiString getRGB()
        {
            return AnsiString("#")+IntToHex(r,2) + IntToHex(g,2) + IntToHex(b,2);
        }
        AnsiString getRGBNUM()
        {
            return IntToStr(r)+","+IntToStr(g)+","+IntToStr(b);
        }
        AnsiString getCMYK()
        {
                float cyan = 255 - r;
                float magenta = 255 - g;
                float yellow = 255 - b;
                float black = cyan;
                if(black>magenta)black=magenta;  
                if(black>yellow)black=yellow;

                if(black==255)
                {
                    cyan=0;
                    magenta=0;
                    yellow=0;
                }
                else
                {
                    cyan = (cyan - black) / (255 - black) * 255;
                    magenta = (magenta - black) / (255 - black) * 255;
                    yellow = (yellow - black) / (255 - black) * 255;
                }

                return IntToStr(folatToInt(cyan/255*100))+","+
                        IntToStr(folatToInt(magenta/255*100))+","+
                        IntToStr(folatToInt(yellow/255*100))+","+
                        IntToStr(folatToInt(black/255*100));
        }
        AnsiString getHSB()
        {
                int max=b;
                int min=b;
                if(max<g)max=g;
                if(max<r)max=r;
                if(min>g)min=g;
                if(min>r)min=r;
                
                float hsbB = max / 255.0;  
                float hsbS = max == 0 ? 0 : (max - min) / (float) max;  
  
                float hsbH = 0;
                if(max==min){
                    hsbH = 0;    
                }else if (max == r && g >= b) {  
                    hsbH = (g - b) * 60.0 / (max - min) + 0;
                } else if (max == r && g < b) {
                    hsbH = (g - b) * 60.0 / (max - min) + 360;
                } else if (max == g) {
                    hsbH = (b - r) * 60.0 / (max - min) + 120;
                } else if (max == b) {
                    hsbH = (r - g) * 60.0 / (max - min) + 240;
                }

                return IntToStr(folatToInt(hsbH))+","+IntToStr(folatToInt(hsbS*100))+","+IntToStr(folatToInt(hsbB*100));
        }

        int folatToInt(double d)
        {
             int i = (int)d;
             if(d-i>=0.5)i++;
             return i;
        }

        TColor getTColor()
        {
            return StrToInt("$00"+IntToHex(b,2) + IntToHex(g,2) + IntToHex(r,2));
        }
        TColor getBackTColor()
        {
            return StrToInt("$00"+IntToHex(255-b,2) + IntToHex(255-g,2) + IntToHex(255-r,2)); 
        }
public:
        COLORREF clr;
        int b;
        int g;
        int r;
};

//---------------------------------------------------------------------------
#endif
