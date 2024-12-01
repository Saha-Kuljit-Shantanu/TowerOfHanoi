# include "iGraphics.h"
# include<windows.h>
#include<mmsystem.h>
#include<math.h>
int a[3]={300,600,900},diff=25,co=6,bnum=0,bcnt=0,page=1;
char strco[2];
typedef struct{
       int len1;
       int len2;
       int br1;
       int br2;
       int midlen;
       int colx;
       int coly;
       int colz;
}block;
block b[16];
typedef struct{
       int u;
       int v;
       int w;

}Towerof;
typedef struct{
        int countA;
        int countB;
        int countC;

}rodstr;
Towerof* br;
rodstr rod[300];
Towerof* hanoi(int n,int fr,int tr,int ar)
{
    if(n==0)
    {
        br[bnum]={0,fr,tr};
        bnum++;
        return br;
    }
    hanoi(n-1,fr,ar,tr);
    br[bnum]={n,fr,tr};
    bnum++;
    hanoi(n-1,ar,tr,fr);
}
void blockstr()
{

    for(int i=0;i<co;i++)
    {
       if(co<=6){
                b[i].len1=100+25*(1+co-i);
                b[i].len2=400-50*(1+co-i);
                }
        else    {
                b[i].len1=100+25*(1+co-i)-5*co;
                b[i].len2=400-50*(1+co-i)+10*co;
                }
        b[i].br1=100+25*(co-i-1);
        b[i].br2=25;
        b[i].midlen=b[i].len1+0.5*b[i].len2;
        b[i].colx=44+rand()%121;
        b[i].coly=77+rand()%71;
        b[i].colz=49+rand()%190;
    }
}

void f()
{
    if(page==2)
     {
        if(bcnt== pow(2,co)-1)
            page=3;
        else if(b[br[bcnt].u].br1!=650 && b[br[bcnt].u].midlen!=br[bcnt].w)
            b[br[bcnt].u].br1+=25;
        else if(b[br[bcnt].u].br1==650 && b[br[bcnt].u].midlen!=br[bcnt].w)
        {
            b[br[bcnt].u].br1+=0;
            b[br[bcnt].u].len1+=(br[bcnt].w-br[bcnt].v)/50;
            b[br[bcnt].u].midlen+=(br[bcnt].w-br[bcnt].v)/50;
        }
        else if((br[bcnt].w==300 && b[br[bcnt].u].br1==100+25*rod[bcnt].countA)
        ||(br[bcnt].w==600 && b[br[bcnt].u].br1==100+25*rod[bcnt].countB)
        ||(br[bcnt].w==900 && b[br[bcnt].u].br1==100+25*rod[bcnt].countC))
        {
            b[br[bcnt].u].br1+=0;
            bcnt++;
        // f();
        }

        else if(b[br[bcnt].u].midlen==br[bcnt].w)
        {
            b[br[bcnt].u].br1-=25;
        }


     }

}
void iDraw()
{
    iClear();
    if (page==1)
    {
        iShowBMP(0,0,"tower of hanoi.bmp");
        iSetColor(150,10,200);
        iText(300,525,"how many blocks for tower of hanoi?(3 to 8)",GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle (750,525,100,25);
        iText(760,525,strco,GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if (page==2)
    {

        iShowBMP(0,0,"bg1.bmp");

        iSetColor(250,0,0);
        iLine(300,100,300,600);
        iLine(600,100,600,600);
        iLine(900,100,900,600);
        iLine(10,100,1190,100);
        iSetColor(255,0,0);
        iText(500,50,"Tower of Hanoi by Saha Kuljit Shantanu",GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0;i<co;i++)
        {
            glColor4ub(b[i].colx,b[i].coly,b[i].colz,450);
            iFilledRectangle(b[i].len1,b[i].br1,b[i].len2,b[i].br2);
        }

    }
    if(page==3)
    {
        Sleep(500);
        iShowBMP(0,0,"tfw.bmp");

    }

}
void iKeyboard(unsigned char key)
{
     if(key>'2'&& key<='6')
    {
        strco[0]=key;
        co=atoi(strco);
    }
    if(key==8)
    {
        strco[0]='\0';
    }

      if(key == 13 && page==1)
       {
           page =2;
           blockstr();
           Towerof* bricks;

           br=(Towerof*)malloc(pow(2,co)*(sizeof(Towerof)));
           bricks=hanoi(co-1,a[0],a[2],a[1]);
           rod[0]={co,0,0};
            for(int i=0;i<pow(2,co);i++)
            {
                printf("%d %d %d\n",bricks[i].u,bricks[i].v,bricks[i].w);
                if (bricks[i].w==300 && bricks[i].v==600)
                {
                    rod[i+1].countA=rod[i].countA+1;
                    rod[i+1].countB=rod[i].countB-1;
                    rod[i+1].countC=rod[i].countC;
                }
            if (bricks[i].w==300 && bricks[i].v==900)
            {
                rod[i+1].countA=rod[i].countA+1;
                rod[i+1].countC=rod[i].countC-1;
                rod[i+1].countB=rod[i].countB;
            }
            if (bricks[i].w==600 && bricks[i].v==300)
            {
                rod[i+1].countB=rod[i].countB+1;
                rod[i+1].countA=rod[i].countA-1;
                rod[i+1].countC=rod[i].countC;
            }
            if (bricks[i].w==600 && bricks[i].v==900)
            {
                rod[i+1].countB=rod[i].countB+1;
                rod[i+1].countC=rod[i].countC-1;
                rod[i+1].countA=rod[i].countA;
            }
            if (bricks[i].w==900 && bricks[i].v==600)
            {
                rod[i+1].countC=rod[i].countC+1;
                rod[i+1].countB=rod[i].countB-1;
                rod[i+1].countA=rod[i].countA;
            }
            if (bricks[i].w==900 && bricks[i].v==300)
            {
                rod[i+1].countC=rod[i].countC+1;
                rod[i+1].countA=rod[i].countA-1;
                rod[i+1].countB=rod[i].countB;
            }
            printf("%d %d %d\n",rod[i].countA,rod[i].countB,rod[i].countC);
            }
        }
}
void iMouse(int button,int state,int mx,int my)
{

}
void iMouseMove(int mx,int my)
{

}
void iSpecialKeyboard(unsigned char key)
{

}
int main()
{
    iSetTimer(25,f);
    PlaySound("fts.wav",NULL,SND_ASYNC|SND_LOOP);
    iInitialize(1200,700,"Tower Of Hanoi");
}
