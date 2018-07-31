#include<stdio.h>
#include<time.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>
void display();
void res();
void changediff();
void move(char,char);
void welcom();
int wrongm();
void inti();
void rulesd();

int diff=5;// difficulty value (number of disks)
char name[20];// user's name

struct disk //disk color & size structure
{int clr;
int size;};
struct disk s[8];//source pole or A pole
struct disk im[8];//intermediate pole or B pole
struct disk d[8];//destination pole or C pole
int pos[8];//postion marker in pole
int top1,top2=-1,top3=-1;//top of pole value
char f,t;// move helpers (From ,To)
clock_t first,last;//clock variable for time calc
int i,mov=0;// move count
char msg[30],tim[20];//message variable & time variable


int main()
{ int c;
  int gd=EGA,gm=1; //graphic driver
  initgraph(&gd,&gm,"C:\\TC\\BGI"); //initialising graphics
  welcom();//welcome screen
  inti();

 st: //starting point
   display();//display screen before move
   setcolor(1);//character color
   sprintf(msg,"Enter your move:"); // getting move from user
   outtextxy(10,10,msg);

   f=getch();
   sprintf(msg,"%c ",f);
   outtextxy(140,10,msg);

   t=getch();
   sprintf(msg,"%c ",t);
   outtextxy(150,10,msg);
   getch();

 if(f=='r'&&t=='r') //reset option
  { inti();
    top2=-1;top3=-1;
     goto st;  }

 if(f=='e'&&t=='e') //exit at any option
 {closegraph();
   exit(0);}

   mov++; //move count
   move(f,t); //move function
   display();//display aft move
   c=(diff*10)-10; //final top value calculated value
 if(d[top3].size==c&&d[top3].clr==1&&pos[top3]==c)//finish point checker
      { last=clock(); //ending time
	getch();
	clearviewport();
	setbkcolor(5); //background color
	settextstyle(0,0,0);//font & style
	sprintf(msg,"Dear %s,",name);
	outtextxy(100,120,msg);
	sprintf(msg,"you have completed in %d moves and in % d seconds",mov,((last-first)/20));
	outtextxy(100,150,msg);
	res(); //iq predicting func
	getch();
	exit(0);  }
  else
    goto st;//recursive point

  getch();
  closegraph();//closing graphics
  return 0;
 }

 void display()
{ int i;
  clearviewport();
  setcolor(15);
  setbkcolor(14);
  setfillstyle(1,12);

  bar(45,290,610,300); //basepole
  bar(123,290,127,190);//A pole
  bar(323,290,327,190);//B pole
  bar(533,290,537,190);//C pole

  setfillstyle(1,13);
  bar(400,10,500,20); //move display box

  sprintf(msg,"MOVE : %d",mov);
  outtextxy(410,12,msg);

   setcolor(4);
  sprintf(msg,"A");
  outtextxy(125,310,msg);
  sprintf(msg,"B");
  outtextxy(325,310,msg);
  sprintf(msg,"C");
  outtextxy(535,310,msg);
  setcolor(15);

 for(i=0;i<diff;i++)
   {if(d[i].clr!=0)
     { setfillstyle(1,d[i].clr);
       bar(460+d[i].size,283-pos[i],610-d[i].size,290-pos[i]);
       }

   if(im[i].clr!=0)
     {setfillstyle(1,im[i].clr);
      bar(250+im[i].size,283-pos[i],400-im[i].size,290-pos[i]);
      }

    if(s[i].clr!=0)
     {setfillstyle(1,s[i].clr);
      bar(50+s[i].size,281-pos[i],200-s[i].size,290-pos[i]);
      }}}


int wrongm() // wrong move screen
{   clearviewport();
    setbkcolor(12);
    setfillstyle(1,4);
    bar(180,100,450,225);
    settextstyle(0,0,3);
    outtextxy(200,150,"WRONG MOVE ");
    settextstyle(0,0,1);
    getch();
    return 1;
 }

void move(char f,char t)
{  int e=0;//error
    if(f!='a'&&t!='a')  //invalid character checker
      if(f!='b'&&t!='b')
	if(f!='c'&&t!='c')
	 {  clearviewport();
	    printf("invalid move");
	    getch();
	    mov--;return;  }


   if (f=='a'&&t=='b') // A to B pole move
      {if(top2!=-1)
	if(im[top2].clr<s[top1].clr)//wrong check condition
	    e=wrongm(); //wrong move display
       if(e==1)
	return ;
       else{if(s[top1].clr!=0)
	    {im[top2+1].clr=s[top1].clr;
	     im[top2+1].size=s[top1].size;
	     s[top1].clr=s[top1].clr=0;
	     top1--;top2++; sound(2000);
    delay(100);
	     }}}

 if(f=='a'&&t=='c')// A to C pole move
     {if(top3!=-1)
       if(d[top3].clr<s[top1].clr)
	    e=wrongm();
      if(e==1)
	return;
      else{if(s[top1].clr!=0)
	    {d[top3+1].clr=s[top1].clr;
	     d[top3+1].size=s[top1].size;
	     s[top1].clr=s[top1].clr=0;
	     top1--;top3++; sound(2000);
    delay(100);}}}

  if(f=='b'&&t=='a') // B to A pole move
      {if(top1!=-1)
	if(s[top1].clr<im[top2].clr)
	    e=wrongm();
       if(e==1)
	return;
       else {if(im[top2].clr!=0)
	     {s[top1+1].clr=im[top2].clr;
	      s[top1+1].size=im[top2].size;
	      im[top2].clr=im[top2].clr=0;
	       top2--;top1++; sound(2000);
    delay(100);}}}


  if(f=='b'&&t=='c') // B to C pole move
       {if(top3!=-1)
	 if(d[top3].clr<im[top2].clr)
	    e=wrongm();
	if(e==1)
	 return;
	else {if(im[top2].clr!=0)
	       {d[top3+1].clr=im[top2].clr;
		d[top3+1].size=im[top2].size;
		im[top2].clr=im[top2].clr=0;
		top2--;top3++; sound(2000);
    delay(100);}}}

   if(f=='c'&&t=='a') // C to A pole move
	{if(top1!=-1)
	 if(s[top1].clr<d[top3].clr)
	    e=wrongm();
	 if(e==1)
	   return;
	 else {if(d[top3].clr!=0)
	       {s[top1+1].clr=d[top3].clr;
		s[top1+1].size=d[top3].size;
		d[top3].clr=d[top3].clr=0;
		top3--;top1++; sound(2000);
    delay(100);}}}

   if(f=='c'&&t=='b')// C to B pole move
	{if(top2!=-1)
	  if(im[top2].clr<d[top3].clr)
		 e=wrongm();
	 if(e==1)
	  return;
	 else{if(d[top3].clr!=0)
	    {im[top2+1].clr=d[top3].clr;
	     im[top2+1].size=d[top3].size;
	     d[top3].clr=d[top3].clr=0;
	     top3--;top2++; sound(2000);
    delay(100);}}}  nosound();

 }

void welcom()
{  char ch=97;
   int s=0;
   sprintf(msg,"welcome to Towers of Hanoi puzzle game");
   setbkcolor(15);
   setcolor(1);
   outtextxy(150,150,msg);

   sprintf(msg,"Developed by");
   outtextxy(420,295,msg);
   sprintf(msg,"DreamerzZ");
   outtextxy(420,310,msg);

   getch();
   rulesd();
   sprintf(msg,"Enter your name:");
   outtextxy(200,170,msg);
   while(((ch>96)&&(ch<123))||(ch==32)||(ch==8))
      { ch=getch();
	if(ch!=13)
	name[s]=ch;
	if(ch==8)
	 { name[s]=0;
	   name[s-1]=0;
	   s=s-2;  }
	clearviewport();
	outtextxy(200,170,msg);
	outtextxy(330,170,name);
	s++;
       }


   sprintf(msg,"Default difficulty level:Easy");
   outtextxy(150,190,msg);
   sprintf(msg,"Do want to change(y/n): ");
   outtextxy(160,210,msg);
   ch=getch();
   sprintf(msg,"%c ",ch);
   outtextxy(345,210,msg);
   getch();
    if (ch=='y')
       changediff(); // level changing function


}


void inti()//initialsation
{  int j=diff;
  for (i=0;i<diff;i++)
   {s[i].clr=j;
    s[i].size=(i*10);
    pos[i]=(i*10);
    im[i].clr=0;
    im[i].size=0;
    d[i].clr=0;
    d[i].size=0;
    j--;}
    mov=0;
    top1=diff-1;
    first=clock();//starting time
     }

void changediff()//dificulty level changer
{ char ch;
  clearviewport();
  setbkcolor(14);
  setcolor(4);
  sprintf(msg,"Enter difficulty level (h/m/e): ");
  outtextxy(50,50,msg);
  ch=getch();
  sprintf(msg,"%c ",ch);
  outtextxy(300,50,msg);
  if(ch=='h')
    diff=7;
  if(ch=='m')
    diff=6;
  if(ch=='e')
    diff=5;
  }
void res()
{ int r;
  r=pow(2,diff)-1;
   if(r==mov)
    sprintf(msg,"You  have a Excellent IQ");
   else
    {if(mov<(r+10))
      sprintf(msg,"You have a Good IQ");
     else
      sprintf(msg,"Even a MONKEY has better IQ than you,%s",name);
      }
   outtextxy(100,170,msg);
 }



void rulesd()
{clearviewport();
 setbkcolor(15);
 setcolor(1);
 sprintf(msg,"INSTRUCTIONS");
 outtextxy(255,47,msg);
 sprintf(msg,"-> There will be three poles namely A B C  ");
 outtextxy(40,70,msg);
 sprintf(msg,"-> You have to arrange all disks in ascending order in pole C using pole B ");
 outtextxy(40,90,msg);
 sprintf(msg,"-> To move a disk from one pole to another press the pole name (A,B,C) ");
 outtextxy(40,110,msg);
 sprintf(msg,"RULES");
 outtextxy(255,147,msg);
 sprintf(msg,"* Only one disk can be moved at a time ");
 outtextxy(40,170,msg);
 sprintf(msg,"* Only disks at the top of pole can be moved ");
 outtextxy(40,190,msg);
 sprintf(msg,"* No disk can be placed on top of a smaller disk ");
 outtextxy(40,210,msg);






 sprintf(msg,"Press any key to continue ");
 outtextxy(250,250,msg);

 getch();
 cleardevice();

 }


