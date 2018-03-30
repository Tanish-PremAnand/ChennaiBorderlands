#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<bios.h>

#define UP 0x48
#define DOWN 0x50
void MENU();//prototype for menu function
void GAME_OVER()
{
	    delay(500);
	    cleardevice();
	    rectangle(5,5,getmaxx()-5,getmaxy()-5);
	    rectangle(10,10,getmaxx()-10,getmaxy()-10);
	    for(int i=0;i<6;i++)
	    {
	     delay(500);
	     setcolor(BLACK);
	     settextstyle(1,0,6);
	     outtextxy(getmaxx()/2-160,getmaxy()/2-40,"GAME OVER!!!");
	     delay(500);
	     setcolor(RED);
	     outtextxy(getmaxx()/2-160,getmaxy()/2-40,"GAME OVER!!");
	    }
 delay(1000);
 MENU();
}
void LOADING()
{
 setcolor(WHITE);
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 settextstyle(8,0,1);
 outtextxy(getmaxx()/2-120,getmaxy()-110,"YOU ARE PROCEEDING...");
 rectangle(getmaxx()/2-250,getmaxy()-70,getmaxx()/2+220,getmaxy()-50);
 int start=getmaxx()/2-240,end=getmaxx()/2-190;
 while(end<getmaxx()/2+260)
 {
  delay(250);
  setfillstyle(SOLID_FILL,RED);
  bar(start,getmaxy()-65,end,getmaxy()-55);
  start=end;
  end+=50;
 }
}
void ERROR_MSG(char *c)
{
  int a=rand()%5+1;
  switch(a)
  {
   case 1: gotoxy(3,wherey()+1);
	   cout<<"DONT REALLY KNOW WHAT YOU KNOW BY '"<<c<<"'";
	   break;
   case 2: gotoxy(3,wherey()+1);
	   cout<<"YOU CANNOT DO THAT";
	   break;
   case 3: gotoxy(3,wherey()+1);
	   cout<<"IF YOU ARE STUCK, TYPE </bot>";
	   break;
   case 4: gotoxy(3,wherey()+1);
	   cout<<"IT DOESN'T HURT TO MAKE SENSE...";
	   break;
   case 5: gotoxy(3,wherey()+1);
	   cout<<"I'M SORRY, BUT YOU ARE NOT MAKING SENSE";
	   break;
  }
  return;
}
int ACTION_CHECK(char a[])
{
 fstream x("actions.txt",ios::in);
 char ch[30];
 while(!x.eof())
 {
  x>>ch;
  if(strcmpi(ch,a)==0)
   return(1);
 }
 x.close();
}
struct player//player info. Attributes like health or hunger to be added.
{
 char pname[15];
}p;
struct INV//inventory structure.
{
  char iname[15];
};
void ADD(char a[])
{
 fstream x("inv.dat",ios::app|ios::binary);
 INV i;

 strcpy(i.iname,a);
 x.write((char*)&i,sizeof(i));
 x.close();
}
void DELETE(char *c)
{
 INV i;
 fstream x("inv.dat",ios::in|ios::binary);
 fstream y("newinv.dat",ios::out|ios::binary);
 while(!x.eof())
 {
  x.read((char*)&i,sizeof(i));
  if(strcmpi(c,i.iname)!=0)
   y.write((char*)&i,sizeof(i));
 }
 x.close();
 y.close();
 remove("inv.dat");
 rename("newinv.dat","inv.dat");
}
void DISP()//to display from inventory.NOT WORKING!!
{
 INV i;
 fstream x("inv.dat",ios::in|ios::binary);
 x.seekg(0,ios::end);
 int icode=0,b=x.tellg()/sizeof(i);
 x.seekg(0,ios::beg);
 while(x.tellg()!=b*sizeof(i))
 {
  gotoxy(8,wherey()+1);
  cout<<++icode;
  gotoxy(wherex()+5,wherey());
  x.read((char*)&i,sizeof(i));
  puts(i.iname);
 }
 x.close();
}
void LVL3();
void LVL4();
void LVL5();
void RIDDLE()
{
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];int num=1; char asr[20];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 outtextxy(getmaxx()/2-70,20,"BORDERLANDS");
 gotoxy(3,5);
 gotoxy(3,wherey()+1);
 rid:
  switch(num)
  {
   case 1:
       gotoxy(3,wherey()+1);
	   cout<<strupr("'You will always find me in the past. I can be created in the present, ");
	   gotoxy(3,wherey()+1);
	   cout<<strupr("But the future can never taint me. What am I?.'");
	   gotoxy(3,wherey()+2);
	   cout<<">";
	   gets(asr);
	   if(strcmpi(asr,"history")==0)
	   {
	    num++;
	    goto rid;
	   }
	   else
	    GAME_OVER();


   case 2:
       gotoxy(3,wherey()+1);
	   cout<<strupr("NEXT QUESTION-'What is big and yellow and comes in the morning,");
	   gotoxy(3,wherey()+1);
	   cout<<strupr("to brighten mom's day?.'");
	   gotoxy(3,wherey()+2);
	   cout<<">";
	   gets(asr);
	   if(strcmpi(asr,"school bus")==0)
	   {
	    num++;
	    goto rid;
	    break;
	   }
	   else
	    GAME_OVER();

   case 3:
       gotoxy(3,wherey()+1);
	   cout<<strupr("NEXT QUESTION-'Feed me and I live, yet give me a drink and I die.");
	   gotoxy(3,wherey()+1);
	   cout<<strupr("What am i ?'");
	   gotoxy(3,wherey()+2);
	   cout<<">";
	   gets(asr);
	   if(strcmpi(asr,"Fire")==0)
	   {
	    gotoxy(3,wherey()+1);
	    cout<<"NEXT LEVEL";
	    delay(500);
	    cleardevice();
	    LOADING();
	    LVL3();
	   }
	   else
	    GAME_OVER();
 }
}

void KILL_CHECK()
{
 delay(750);
 cleardevice();
 char c[20];
 int draw=0;
 gotoxy(3,4);
 cout<<"YOU MAY HAVE NOTICED THAT YOU HAVE A KNIFE IN YOUR INVENTORY FROM THE VERY ";
 gotoxy(3,wherey()+1);
 cout<<"BEGINNING OF THE GAME... YOU CAN USE THAT KNIFE TO KILL THE BEAST. <DRAW> ";
 gotoxy(3,wherey()+1);
 cout<<"THE KNIFE TO USE IT.";
 fstream y("HELP.txt",ios::in);
 char a[100];
 kc:
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto kc;
 }
 gotoxy(3,wherey()+2);
 cout<<"TYPE <DRAW> TO DRAW KNIFE";
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(strcmpi(c,"draw")==0)
 {
  draw=1;
 }
 if(draw==1)
 {
 delay(750);
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];int num=1; char asr[20];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 gotoxy(3,4);
 int tri=2,m;
 char atk[20];
 randomize();
 m=rand()%4+1;
 gotoxy(3,wherey()+1);
 cout<<"YOU CAN SEE THAT THE BEAST HAS 4 SPOTS THAT APPEAR TO BE WEEK. ";
 gotoxy(3,wherey()+1);
 cout<<"THE EYES, HEART, THROAT AND ITS SPINE. WHERE DO YOU WISH TO ";
 gotoxy(3,wherey()+1);
 cout<<"ATTACK?";
 kill:
 gotoxy(3,wherey()+2);
 cout<<"ENTER ATTACK";
 gotoxy(3,wherey()+1);
 cout<<">";
 gets(atk);
 if(tri<=3)
 {
 switch(m)
  {
 case 1: if(strcmpi(atk,"eye")==0|strcmpi(atk,"eyes")==0)
	 {
	  gotoxy(5,wherey()+3);
	  cout<<"YOU HAVE WON, THE BEAST DIED .......";
	  getch();
	  delay(2000);
	  MENU();
	 }
	 else
	 {
	  tri++;
	  gotoxy(3,wherey()+1);
	  cout<<"OOPS YOU MISSED THE BEAST DIDN'T DIE";
	  goto kill;
	 }
 case 2: if(strcmpi(atk,"heart")==0)
  {
  gotoxy(5,wherey()+3);
  cout<<"YOU WON THE BEAST DIED .......";
  getch();
  delay(2000);
  MENU();
  }
  else
  {
  tri++;
  gotoxy(3,wherey()+1);
  cout<<"OOP'S YOU MISSED THE BEAST DIDN'T DIE";
  goto kill;
  }
 case 3: if(strcmpi(atk,"throat")==0)
  {
  gotoxy(5,wherey()+3);
  cout<<"YOU WON THE BEAST DIED .......";
  getch();
  delay(2000);
  MENU();
  }
  else
  tri++;
  gotoxy(3,wherey()+1);
  cout<<"OOP'S YOU MISSED THE BEAST DIDN'T DIE";
  goto kill;
 case 4: if(strcmpi(atk,"spine")==0)
  {
  gotoxy(5,wherey()+3);
  cout<<"YOU WON THE BEAST DIED .......";
  getch();
  delay(2000);
  MENU();
  }
  else
  {
  tri++;
  gotoxy(3,wherey()+1);
  cout<<"OOP'S YOU MISSED THE BEAST DIDN'T DIE";
  goto kill;
  }
 }
 }
 else
 {
 gotoxy(3,wherey()+1);
 cout<<"THE BEAST DID NOT DIE... THE BEAST LUNGES ON YOU AND KILLS YOU...";
 delay(500);
 GAME_OVER();
 }
 }
 else if(strcmpi(c,"quit")==0)
 {
  char ch;
  yn:
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
   goto kc;
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto kc;
 }
else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto kc;
 }
 else
 {
  ERROR_MSG(c);
  goto kc;
 }
}
void LVL5()
{
 remove("inv.dat");
 ADD("knife");
 int insp=0, app=0;
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 gotoxy(3,5);
 cout<<strupr(name)<<": WELCOME TO THE 5th DUNGEON. THE ONE THING THAT STANDS BETWEEN";
 gotoxy(3,wherey()+1);
 cout<<"YOU AND YOUR FREEDOM!!. TYPE <INSPECT> TO LOOK AROUND";
 lvl5:
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto lvl5;
 }
 fstream y("HELP.txt",ios::in);
 char a[100],c[20];
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(ACTION_CHECK(c)==1)
 {
    if(strcmpi(c,"inspect")==0)
    {
     insp=1;
     gotoxy(3,wherey()+1);
     cout<<"YOU HEAR A FAINT SOUND FRON THE OTHER SIDE, SOMETHING MISTERIOUS ";
     gotoxy(3,wherey()+1);
     cout<<"DO YOU WISH TO <APPROACH>";
	 goto lvl5;
	}
	else if(strcmpi(c,"approach")==0)
	{
	 if(insp==1)
	 {
	 app=1;
	 gotoxy(3,wherey()+1);
	 cout<<"AS YOU MOVE CLOSER THE VOLUME INCREASES SUDDENLY YOU HEAR A ROAR";
	 gotoxy(3,wherey()+1);
	 cout<<"AND A FEARCE BEAST APPROACHING YOU. DO YOU WANT TO <ATTACK> OR <ESCAPE>";
	 goto lvl5;
	 }
	 else
	 {
	  gotoxy(3,wherey()+1);
	  cout<<"ALL YOU CAN HEAR IS A GROWLING SOUND...";
	 }
	}
    else if(strcmpi(c,"escape")==0)
	{
	 if(app==1)
	 {
	 gotoxy(3,wherey()+2);
	 cout<<"YOUR ESCAPE FAILED!!. THE BEASRT KILLED YOU";
	 delay(300);
	 GAME_OVER();
	 getch();
	 delay(2000);
	 MENU();
	 }
	 else
	 {
	  gotoxy(3,wherey()+1);
	  cout<<"ESCAPE FROM WHAT??";
	  goto lvl5;
	 }
	}
    else if(strcmpi(c,"attack")==0)
	if(app==1)
	{
	 KILL_CHECK();
	}
	else
	{
	 gotoxy(3,wherey()+1);
	 cout<<"DO YOU REALLY WANT TO ATTACK AIR?";
	 goto lvl5;
	}
   else
   {
	   ERROR_MSG(c);
	   goto lvl5;
   }
 }
 else if(strcmpi(c,"quit")==0)
 {
  char ch;
  yn:
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
   goto lvl5;
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto lvl5;
 }
else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto lvl5;
 }
else
{
    ERROR_MSG(c);
    goto lvl5;
}
 x.close();
 y.close();
}


void LVL4()
{
 remove("inv.dat");
 ADD("knife");
 int insp=0, comp=0;
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 gotoxy(3,5);
 cout<<strupr(name)<<": WELCOME TO THE 4th DUNGEON. AFTER DEFEATING THE DUNGEON MASTER.";
 gotoxy(3,wherey()+1);
 cout<<"TYPE <INSPECT> TO LOOK AROUND";
 lvl4:
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto lvl4;
 }
 fstream y("HELP.txt",ios::in);
 char a[100],c[20];
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(ACTION_CHECK(c)==1)
 {
  if(strcmpi(c,"inspect")==0)
  {
   insp=1;
   gotoxy(3,wherey()+1);
   cout<<"YOU FIND A BOOK WITH WRITINGS ON IT. DO YOU WISH TO <DECIPHER> IT";
   goto lvl4;
  }
  else if(strcmpi(c,"proceed")==0)
  {
   if(comp==1)
   {
    delay(1500);
    cleardevice();
    LOADING();
    LVL5();
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"CHEATER... REMEMBER, THE GAME KNOWS YOU...";
    goto lvl4;
   }
  }
  else if(strcmpi(c,"decipher")==0)
  {
   if(insp==1)
   {  
      delay(500);
	  cleardevice();
      gotoxy(3,3);
      cout<<"THE BOOK SAYS:";
      gotoxy(3,18);
      wrng:
      if(wherey()>21)
      {
       gotoxy(3,wherey()+1);
       cout<<"******************************* END OF LINE ********************************";
       getch();
       cleardevice();
       gotoxy(3,3);
       cout<<"THE BOOK SAYS:";
       gotoxy(3,18);
       goto wrng;
      }
      char ans[30];
      rectangle(5,5,getmaxx()-5,getmaxy()-5);
      rectangle(10,10,getmaxx()-10,getmaxy()-10);
      rectangle(getmaxx()/2-200,getmaxy()/2-100,getmaxx()/2+200,getmaxy()/2+50);
      settextstyle(3,0,1);
      outtextxy(getmaxx()/2-195,getmaxy()/2-95,"YOU ARE IN A ROOM WITH 3 MONKEYS,");
      outtextxy(getmaxx()/2-195,getmaxy()/2-70,"ONE HAS A BANANA AND ONE HAS A STICK,");
      outtextxy(getmaxx()/2-195,getmaxy()/2-45,"ONE HAS NOTHING. WHO IS THE SMARTEST");
      outtextxy(getmaxx()/2-195,getmaxy()/2-20,"PRIMATE?");
      gotoxy(3,wherey()+2);
      cout<<">";
      gets(ans);
      if(strcmpi(ans,"me")==0|strcmpi(ans,"you")==0)
      {
       comp=1;
       gotoxy(3,wherey()+2);
       cout<<"YOU HAVE SUCCESFULLY COMPLETED THIS DUNGEON! YOU CAN ";
       gotoxy(3,wherey()+1);
       cout<<"NOW <PROCEED> TO THE NEXT DUNGEON.";
       goto lvl4;
      }
      else if(strcmpi(ans,"quit")==0)
      {
       char ch;
       gotoxy(3,wherey()+1);
       cout<<"ARE YOU SURE?";
       gotoxy(3,wherey()+1);
       cout<<">";
       cin>>ch;
       if(ch=='y'|ch=='Y')
       {
	delay(1000);
	MENU();
       }
       else if(ch=='n'|ch=='N')
       {
	goto wrng;
       }
      }
       else if(strcmpi(ans,"/stats")==0)
       {
	 DISP();
	 goto wrng;
       }

       else
	goto wrng;


  }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"I'M NOT SURE YOU CAN DECIPHER AIR...";
   goto lvl4;
  }
  }
 else
 {
   ERROR_MSG(c);
   goto lvl4;
 }
 }
 else if(strcmpi(c,"quit")==0)
 {
  char ch;
  yn:
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
  {
   goto lvl4;
  }
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto lvl4;
 }
else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto lvl4;
 }
else
{
	ERROR_MSG(c);
	goto lvl4;
}
 x.close();
 y.close();
}
void LVL3()
{
 remove("inv.dat");
 ADD("knife");
 int insp=0, pick=0, app=0, talk=0, comp=0;
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 settextstyle(1,0,1);
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 gotoxy(3,5);
 cout<<strupr(name)<<": YOU FIND YOURSELF STANDING OPPOSITE A MAN WITH RAGGED CLOTHES ";
 gotoxy(3,wherey()+1);
 cout<<"AND AN AXE IN HIS HAND YOU FIND 2 SHINY OBJECTS ON OPPOSITE DIRECTIONS. TO";
 gotoxy(3,wherey()+1);
 cout<<"HAVE A CLOSER LOOK DO YOU WANT TO <INSPECT>?";
 game:
 char lor[5];
 char n;
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto game;
 }
 fstream y("HELP.txt",ios::in);
 char a[100],c[20];
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(ACTION_CHECK(c)==1)
 {
     if(strcmpi(c,"inspect")==0)
  {
   insp=1;
   gotoxy(3,wherey()+1);
   cout<<"ON CLOSER INSPECTION YOU FIND A SWORD TO YOUR LEFT AND A DIAMOND ON THE ";
   gotoxy(3,wherey()+1);
   cout<<"RIGHT. DO YOU WISH <PICK>?";
   goto game;
  }
  else if(strcmpi(c,"pick")==0)
  {
   if(insp==1)
   {
   pick:
   if(wherey()>21)
   {
   gotoxy(3,wherey()+1);
   cout<<"******************************* END OF LINE ********************************";
   getch();
   cleardevice();
   gotoxy(3,3);
   goto pick;
   }
   rectangle(5,5,getmaxx()-5,getmaxy()-5);
   rectangle(10,10,getmaxx()-10,getmaxy()-10);
   pick=1;
   gotoxy(3,wherey()+1);
   cout<<"LEFT OR RIGHT?";
   gotoxy(3,wherey()+1);
   cout<<">";gets(lor);
   if(strcmpi(lor,"left")==0)
   {
    gotoxy(3,wherey()+1);
    cout<<"PICKED UP SWORD. SWORD ADDED TO INVENTORY.";
    ADD("sword");
    gotoxy(3,wherey()+1);
    cout<<"DO YOU WANT TO APPROACH THE MAN?";
    goto game;
   }
   else if(strcmpi(lor,"right")==0)
   {
    gotoxy(3,wherey()+1);
    cout<<"PICKED UP DIAMOND. DIAMOND ADDED TO INVENTORY.";
    ADD("diamond");
     gotoxy(3,wherey()+1);
    cout<<"DO YOU WANT TO <APPROACH> THE MAN?";
    goto game;
   }
   else
    {
     ERROR_MSG(lor);
     goto pick;
    }
  }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"PICK WHAT?";
   goto game;
  }
  }
  else if(strcmpi(c,"approach")==0)
  {
   if(pick==1)
   {
   app=1;
   gotoxy(3,wherey()+1);
   cout<<"YOU HAVE APPROACHED THE MAN. YOU CAN <TALK> TO THE MAN.";
   goto game;
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"APPROACH WHOM?";
    goto game;
   }
  }
  else if(strcmpi(c,"talk")==0)
  {
   if(app==1)
   {
    talk=1;
    gotoxy(3,wherey()+1);
    cout<<"I AM FREYR, THE DUNGEON MASTER, THE KING OF BORDERLANDS ";// CHANGE EVERYTHING
    gotoxy(3,wherey()+1);
    cout<<"YOU MUST <GIVE> THE GODS AN OFFERING OR YOU SHALL <FIGHT> ME TO GET TO";
    gotoxy(3,wherey()+1);
    cout<<"THE NEXT DUNGEON.";
    goto game;
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"LOOKS LIKE THE DUNGEONS ARE TAKING A TOLL ON YOU SANITY...";
    goto game;
   }
  }
  else if(strcmpi(c,"give")==0|strcmpi(c,"fight")==0)
  {
   if(talk==1 && app==1 && insp==1)
   {
   if(pick==1)
   {
   if(strcmpi(c,"fight")==0)
   {
    if(strcmpi(lor,"right")==0)
    {
     gotoxy(3,wherey()+1);
     cout<<"YOU DO NOT HAVE ANY WEAPONS TO FIGHT WITH. TRY TO <GIVE> ANYTHING TO HIM.";
     goto game;
    }
    else
    {
     comp=1;
     gotoxy(3,wherey()+1);
     cout<<"YOU HAVE ATTACKED THE GUARDIAN. THE GUARDIAN IS NOW DEAD, BUT THE SWORD";
     gotoxy(3,wherey()+1);
     cout<<"IS NOW BROKEN. YOU CAN NOW <PROCEED> TO THE NEXT DUNGEON.";
     DELETE("sword");
     goto game;
    }
   }
    else if(strcmpi(c,"give")==0)
    {
     if(strcmpi(lor,"left")==0)
     {
      gotoxy(3,wherey()+1);
      cout<<"YOU HAVE NOTHING TO OFFER";
      goto game;
     }
     else
     {
      DELETE("diamond");
      gotoxy(3,wherey()+1);
      cout<<"YOU HAVE OFFERED THE DIAMOND TO THE GUARDIAN. THE GUARDIAN ";
      gotoxy(3,wherey()+1);
      cout<<"ACCEPTS IT AND IS WILLING TO LEAD YOU TO 5th LEVEL. ";
      delay(700);
      cleardevice();
      LOADING();
      LVL5();
     }
    }
   }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"FATE REQUIRES YOU TO <PICK> SOMETHING...";
   goto game;
  }
  }
   else
   {
    if(talk==0)
    {
     gotoxy(3,wherey()+1);
     cout<<"THE MAN IS STARING AT YOU. ANY MOVE WITHOUT PROPER APPROACH WOULD SEEM";
     gotoxy(3,wherey()+1);
     cout<<"HOSTILE.";
     goto game;
    }
    else if(app==0)
    {
     gotoxy(3,wherey()+1);
     cout<<c<<" WHOM?";
    }
    else if(insp==0)
    {
     gotoxy(3,wherey()+1);
     cout<<"DON'T REALLY KNOW WHAT YOU MEAN BY "<<c;
     goto game;
    }
   }
  }
  else if(strcmpi(c,"proceed")==0)
  {
   if(comp==1)
   {
   delay(500);
   cleardevice();
   LOADING();
   LVL4();
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"CHEATER.., THE GAME KNOWS YOU.";
    goto game;
   }
  }
  else 
  {
	  ERROR_MSG(c);
	  goto game;
  }
 }
 else if(strcmpi(c,"quit")==0)
 {
  char ch;
  yn:
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
   goto game;
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto game;
 }
else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto game;
 } 
else
{
	ERROR_MSG(c);
	goto game;
}
 x.close();
 y.close();
}

void LVL2()
{
 remove("inv.dat");
 ADD("knife");
 int insp=0, read=0, pick=0, proc=0;
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 gotoxy(3,5);
 cout<<strupr(name)<<": WELCOME TO THE 2nd DUNGEON. TYPE <INSPECT> TO LOOK AROUND";
 lvl2:
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto lvl2;
 }
 fstream y("HELP.txt",ios::in);
 char a[100],c[20];
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(ACTION_CHECK(c)==1)
 {
  if(strcmpi(c,"inspect")==0)
  {
   insp=1;
   gotoxy(3,wherey()+2);
   cout<<"YOU SEE THAT THE DOOR TO THE NEXT DUNGEON IS OPEN.";
   gotoxy(3,wherey()+1);
   cout<<"YOU ALSO SEE A PIECE OF PAPER. YOU CAN EITHER <PROCEED> TO THE DOOR OR";
   gotoxy(3,wherey()+1);
   cout<<"<PICK> UP THE PAPER";
   goto lvl2;
  }
  else if(strcmpi(c,"PROCEED")==0)
  {
   if(insp==1)
   {
    proc=1;
    gotoxy(3,wherey()+1);
    cout<<"DAMN! YOU GET CAUGHT IN TRAP. IT IS A QUICK SAND AND IS PULLING YOU IN.";
    gotoxy(3,wherey()+1);
    cout<<"YOU HEAR A VOICE. DO YOU WISH TO <LISTEN> ? ";
    goto lvl2;
  }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"DONT REALLY KNOW WHAT YOU MEAN BY PROCEED...";
   goto lvl2;
  }
  }
  else if(strcmpi(c,"listen")==0)
  {
   if(proc==1)
    {
    RIDDLE();
    }
    else
    {
     gotoxy(3,wherey()+1);
     cout<<"LISTEN TO WHAT?";
     goto lvl2;
    }
  }
  else if(strcmpi(c,"pick")==0)
  {
   if(insp==1)
   {
   pick=1;
   gotoxy(3,wherey()+1);
   cout<<strupr(name)<<" PICKED THE PAPER. TYPE <READ> TO READ IT.";
   ADD("paper");
   goto lvl2;
  }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"DON'T REALLY KNOW WHAT YOU MEAN BY 'PICK'";
   goto lvl2;
  }
  }
  else if(strcmpi(c,"read")==0)
  {
   if(pick==1)
   {
   read=1;
   gotoxy(3,wherey()+2);
   cout<<"RIDDLE ME THIS:";
   gotoxy(3,wherey()+1);
   cout<<"'WHAT OBJECT HAS KEYS THAT OPEN NO LOCKS, SPACE BUT NO ROOM AND ";
   gotoxy(3,wherey()+1);
   cout<<"YOU CAN ENTER, BUT NOT GO IN. WHAT IS IT?'";
   goto lvl2;
  }
  else
  {
   gotoxy(3,wherey()+1);
   cout<<"YOU HAVE NOTHING TO READ...";
   goto lvl2;
  }
  }
   else
   {
	   ERROR_MSG(c);
	   goto lvl2;
   }	   
 }

 else if(strcmpi(c,"keyboard")==0)
  {
   if(read==1)
   {
   gotoxy(3,wherey()+1);
   cout<<"A DOOR OPENS TO YOUR LEFT. YOU HAVE COMPLETED THE LEVEL.";
   delay(1000);
   cleardevice();
   LOADING();
   LVL3();
   getch();
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"YES, THAT IS WHAT YOU ARE TYPING ON...";
    goto lvl2;
   }
  }
 else if(strcmpi(c,"quit")==0)
 {
  yn:
  char ch;
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
  {
   goto lvl2;
  }
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto lvl2;
 }
 else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto lvl2;
 }
 else
 {
	 ERROR_MSG(c);
	 goto lvl2;
 }	
 x.close();
 getch();
 closegraph();
}
void LVL1()
{
 remove("inv.dat");
 ADD("knife");
 int insp=0, pick=0, comp=0;
 cleardevice();
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 settextstyle(1,0,1);
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 fstream x("PLAYERINFO.dat",ios::in|ios::binary);
 char name[15];
 x.seekg(-sizeof(p),ios::end);
 x.read((char*)&p,sizeof(p));
 strcpy(name,p.pname);
 gotoxy(3,5);
 cout<<strupr(name)<<": YOU ARE STANDING ALONE IN A ROOM. THE LIGHTING IN THE ROOM IS VERY ";
 gotoxy(3,wherey()+1);
 cout<<"DIM. DO YOU WANT TO <INSPECT>";
 gotoxy(3,6);
 game:
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,3);
  goto game;
 }
 fstream y("HELP.txt",ios::in);
 char a[100],c[20];
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 gotoxy(3,wherey()+2);
 cout<<">";
 gets(c);
 if(ACTION_CHECK(c)==1)
 {
  if(strcmpi(c,"inspect")==0)
  {
   insp=1;
   gotoxy(3,wherey()+1);
   cout<<"YOU INSPECT THE SCENE. THE ROOM IS DIM, BUT YOU CAN MAKE OUT A TABLE.";
   gotoxy(3,wherey()+1);
   cout<<"THERE ARE THREE KEYS ON THE TABLE. TYPE <PICK> TO PICK THEM UP";
   gotoxy(3,wherey()+1);
   cout<<"YOU CAN SEE A DOOR AT A FEW METERS AHEAD OF YOU. YOU CAN SEE THAT THERE ";
   gotoxy(3,wherey()+1);
   cout<<"IS A LOCK ON IT. PICK UP THE KEYS AND TYPE <GO> TO GO TO THE DOOR.";
   goto game;
  }
  else if(strcmpi(c,"pick")==0)
  {
   if(insp==1)
   {
   pick=1;
   gotoxy(3,wherey()+1);
   cout<<"PICKED KEYS. KEYS ADDED TO INVENTORY. TO CHECK, TYPE </STATS>";
   ADD("keys");
   goto game;
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"YOU HAVE TO <INSPECT> THE SCENE MORE CAREFULLY...";
    goto game;
   }
  }
  else if(strcmpi(c,"go")==0)
  {
   if(insp==1 && pick==1)
   {
    delay(500);
    cleardevice();
    char ch;
    rectangle(5,5,getmaxx()-5,getmaxy()-5);
    rectangle(10,10,getmaxx()-10,getmaxy()-10);
    rectangle(20,20,getmaxx()/2-200,getmaxy()/2-120);
    rectangle(getmaxx()/2-160,20,getmaxx()/2-60,getmaxy()/2-120);
    rectangle(getmaxx()/2-20,20,getmaxx()/2+80,getmaxy()/2-120);
    settextstyle(1,0,1);
    outtextxy(30,60,"KEY - 2");
    outtextxy(170,60,"KEY - 4");
    outtextxy(310,60,"KEY - 3");
    outtextxy(20,getmaxy()/2-100,"THE LOCK SAYS '1181'. ONLY ONE KEY WILL WORK.");
    outtextxy(20,getmaxy()/2-80,"REMEMBER, CIRCLES MATTER...");
    gotoxy(3,11);
    wrng:
    if(wherey()>21)
    {
     getch();
     gotoxy(3,10);
     cleardevice();
     rectangle(5,5,getmaxx()-5,getmaxy()-5);
     rectangle(10,10,getmaxx()-10,getmaxy()-10);
     rectangle(20,20,getmaxx()/2-200,getmaxy()/2-120);
     rectangle(getmaxx()/2-160,20,getmaxx()/2-60,getmaxy()/2-120);
     rectangle(getmaxx()/2-20,20,getmaxx()/2+80,getmaxy()/2-120);
     settextstyle(1,0,1);
     outtextxy(30,60,"KEY - 2");
     outtextxy(170,60,"KEY - 4");
     outtextxy(310,60,"KEY - 3");
     settextstyle(1,0,1);
     outtextxy(20,getmaxy()/2-100,"THE LOCK SAYS '1181'. ONLY ONE KEY WILL WORK");
     outtextxy(20,getmaxy()/2-80,"REMEMBER, CIRCLES MATTER...");
     goto wrng;
     }
    gotoxy(3,wherey()+3);
    cout<<">";
    cin>>ch;
    switch(ch)
    {
     case '2':comp=1;
	      gotoxy(3,wherey()+1);
	      cout<<"CONGRATS! YOU HAVE CLEARED THIS DUNGEON. TYPE <PROCEED> TO CONTINUE. ";
	      gotoxy(3,wherey()+1);
	      cout<<"OR, YOU CAN TYPE QUIT TO RETURN TO THE MAIN MENU.";
	      goto game;
	      break;

     case '3' :gotoxy(3,wherey()+1);
	       cout<<"THE LOCK IS STILL CLOSED. TRY AGAIN.";
	       goto wrng;
	       break;

     case '4':  gotoxy(3,wherey()+1);
	       cout<<"THE LOCK IS STILL CLOSED. TRY AGAIN.";
	       goto wrng;
	       break;
    case 'q':  delay(1000);
	       MENU();
	       break;

    default: gotoxy(3,wherey()+1);
	      cout<<"THE GAME KNOWS YOU. DON'T TRY TO MESS WITH IT.";
	      goto wrng;
	      break;
    }
   }
  else
  {
    if(insp!=1)
    {
     gotoxy(3,wherey()+1);
     cout<<"DON'T REALLY KNOW WHAT YOU MEAN BY 'GO'";
     goto game;
    }
    else if(pick!=1)
    {
     gotoxy(3,wherey()+1);
     cout<<"YOU HAVE TO <PICK> UP THE KEYS FIRST!!";
     goto game;
    }
  }
  }
  else if(strcmpi(c,"proceed")==0)
  {
   if(comp==1)
   {
   delay(500);
   cleardevice();
   LOADING();
   LVL2();
   }
   else
   {
    gotoxy(3,wherey()+1);
    cout<<"CHEATER... TRY TO BE MORE HONEST NEXT TIME.";
    goto game;
   }
  }
  else
  {
	  ERROR_MSG(c);
	  goto game;
  }	  
 }
 else if(strcmpi(c,"quit")==0)
 {
  yn:
  char ch;
  gotoxy(3,wherey()+2);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+1);
  cout<<">";
  cin>>ch;
  if(ch=='y'||ch=='Y')
  {
   delay(750);
   MENU();
  }
  else if(ch=='n'||ch=='N')
  {
   goto game;
  }
  else
   goto yn;
 }
 else if(strcmpi(c,"/stats")==0)
 {
  DISP();
  goto game;
 }
else if(strcmpi(c,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(a,100);
   gotoxy(3,wherey());
   puts(a);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  goto game;
 }
 else
 {
	 ERROR_MSG(c);
	 goto game;
 }
 x.close();
 y.close();
}
unsigned char GETARROW()//to check for arrow keys. used in MENU().
{
 if(kbhit())
 {
  unsigned char ch = getch();
  if(ch==0x00)
  ch=getch();
  switch(ch)
  {
   case UP: return ch;
   case DOWN: return ch;
  }
 return ch;
 }
}
int check(char a[], char b[])//to check password. used in LOGIN().
{
 for(int i=0;i<8;i++)
 {
  if(a[i]!=b[i])
  {
   break;
  }
 }
 if(i==8)
  return 1;
 else
  return 0;
}
void MAINGAME()
{
 remove("inv.dat");
 ADD("knife");
 int gd=DETECT, gm;
 settextstyle(1,0,1);
 outtextxy(getmaxx()/2-80,20,"BORDERLANDS");
 gotoxy(3,5);
 cout<<"HELLO! WELOME TO BORDERLANDS! I AM BOT. TYPE /bot ANYWHERE IN THE GAME FOR ";
 gotoxy(3,wherey()+1);
 cout<<"COMMANDS AND INSTRUCTIONS. YOU HAVE BEEN GIVEN AN ITEM NOW. TYPE /stats ";
 gotoxy(3,wherey()+1);
 cout<<"TO CHECK YOUR STATS AND ITEMS.";
 input:
 textcolor(WHITE);
 if(wherey()>21)
 {
  gotoxy(3,wherey()+1);
  cout<<"******************************* END OF LINE ********************************";
  getch();
  cleardevice();
  gotoxy(3,1);
  goto input;
 }
 gotoxy(3,wherey()+1);
 cout<<"TYPE <START> OR <BEGIN>";
 char ch[30],c[100];
 INV i;
 fstream x("inv.dat",ios::in|ios::out|ios::binary);
 fstream y("HELP.txt",ios::in);
 rectangle(5,5,getmaxx()-5,getmaxy()-5);//border
 rectangle(10,10,getmaxx()-10,getmaxy()-10);//border
 gotoxy(3,wherey()+2);
 cout<<">";//cursor indicator
 gets(ch);
 if(strcmpi(ch,"/stats")==0)//NOT WORKING
 {
  DISP();
  goto input;
 }
 else if(strcmpi(ch,"/bot")==0)//WORKS!
 {
  delay(500);
  cleardevice();
  rectangle(5,5,getmaxx()-5,getmaxy()-5);
  rectangle(10,10,getmaxx()-10,getmaxy()-10);
  gotoxy(3,3);
  while(!y.eof())
  {
   y.getline(c,100);
   gotoxy(3,wherey());
   puts(c);
  }
  gotoxy(3,wherey()+1);
  cout<<"PRESS ANY KEY TO START	";
  getch();
  cleardevice();
  goto input;
 }
 else if(strcmpi(ch,"quit")==0)//WORKS!
 {
  yn:
  char ch;
  gotoxy(3,wherey()+1);
  cout<<"ARE YOU SURE? y/n";
  gotoxy(3,wherey()+2);
  cout<<">";
  cin>>ch;
  if(ch=='y'|ch=='N')
  {
   delay(500);
   MENU();
  }
  else if(ch=='n'|ch=='N')
   goto input;
  else
   goto yn;
 }
 else if(strcmpi(ch,"begin")==0|strcmpi(ch,"start")==0)
 {
  delay(500);
  cleardevice();
  LOADING();
  LVL1();
 }
 else
 {
  ERROR_MSG(ch);
  goto input;
 }
 getch();
 exit(0);
 y.close();
}
void LOGIN()//USED TO STORE USER NAME AND ACCEPT PASSORD. PASSWORD IS 12345678
{
 login:
 cleardevice();
 int i=0;
 fstream x("PLAYERINFO.dat",ios::in|ios::out|ios::binary);
 int gd=DETECT,gm;
 char un[20],pwd[8];
 setcolor(WHITE);
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 rectangle(getmaxx()/2-200,getmaxy()/2-150,getmaxx()/2+200,getmaxy()/2+150);
 settextstyle(2,0,8);
 outtextxy(getmaxx()/2-160,getmaxy()/2-75,"PLAYER NAME: ");
 rectangle(getmaxx()/2+20,getmaxy()/2-75,getmaxx()/2+170,getmaxy()/2-45);
 outtextxy(getmaxx()/2-160,getmaxy()/2-10,"PASSWORD: ");
 rectangle(getmaxx()/2+20,getmaxy()/2-10,getmaxx()/2+170,getmaxy()/2+20);
 gotoxy(45,12);
 gets(un);
 strcpy(p.pname,un);
 x.write((char*)&p,sizeof(p));
 gotoxy(45,16);
 while(i<8)
 {
  pwd[i]=getch();
  cout<<"*";
  ++i;
 }
 if(check(pwd,"12345678")==1)
 {
  delay(500);
  cleardevice();
  LOADING();
  cleardevice();
  MAINGAME();
 }
 else
 {
  delay(200);
  setfillstyle(SOLID_FILL,BLACK);
  bar(getmaxx()/2-200,getmaxy()/2-150,getmaxx()/2+200,getmaxy()/2+150);
  setcolor(WHITE);
  outtextxy(220,220,"WRONG PASSWORD");
  delay(1000);
  goto login;
 }
 getch();
 x.close();
}
void MENU()//USED TO START OR EXIT
{
 menu:
 cleardevice();
 setcolor(WHITE);
 unsigned char arrow=GETARROW();
 gotoxy(16,4);
 cout<<"PRESS UP TO START";
 gotoxy(16,5);
 cout<<"PRESS DOWN TO EXIT";
 rectangle(5,5,getmaxx()-5,getmaxy()-5);
 rectangle(10,10,getmaxx()-10,getmaxy()-10);
 rectangle(getmaxx()/2-200,getmaxy()/2-150,getmaxx()/2+200,getmaxy()/2+150);
 settextstyle(2,0,8);
 outtextxy(getmaxx()/2-80,getmaxy()/2-70,"START");
 outtextxy(getmaxx()/2-80,getmaxy()/2-5,"EXIT");
 switch(arrow)
 {
  case UP:setcolor(RED);
	  settextstyle(2,0,8);
	  outtextxy(getmaxx()/2-80,getmaxy()/2-70,"START");
	  delay(500);
	  LOGIN();
	  break;
  case DOWN:setcolor(RED);
	    settextstyle(2,0,8);
	    outtextxy(getmaxx()/2-80,getmaxy()/2-5,"EXIT");
	    delay(500);
	    exit(0);
	    break;
 }
 getch();
 goto menu;
}
void main()
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\turboc3\\bgi");
 cleardevice();
 MENU();//while working on the problem change to MAINGAME().
 cleardevice();
 closegraph();
}