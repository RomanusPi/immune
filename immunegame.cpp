
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#ifdef __WIN32__
#include <windows.h>
#define CLEARSCR system("cls")
#else
#define CLEARSCR system("clear")
#endif // __WIN32__

using namespace std;

class pole{
public:
bool wasShot=false;
bool IsCell=false;
bool hitted=false;
int distance =0;
};


class Board {

public:
pole board[10+1][10+1];//pierwsze litery drugie cyfry
int howmanyDestroyed;

Board(){howmanyDestroyed=0;}//konstruktor

bool checkifInsideBoard(int &letterdigit,int &digit){
if ((letterdigit>10)||(letterdigit<1)||(digit>10)||(digit<1)) return true;
return false;
}
int checkfordistance(int letterdigit,int digit,bool A1= false){
letterdigit++;
if (!checkifInsideBoard(letterdigit, digit)){
    if (checkhit(letterdigit,digit)) return 1;}
letterdigit=letterdigit-2;
  if (!checkifInsideBoard(letterdigit, digit)){
   if (checkhit(letterdigit,digit)) return 1;}
letterdigit=letterdigit+2;digit++;
if (!checkifInsideBoard(letterdigit, digit)){
   if (checkhit(letterdigit,digit)) return 1;}
 digit=digit-2;
 if (!checkifInsideBoard(letterdigit, digit)){
   if (checkhit(letterdigit,digit)) return 1;}
return 0;
//look in class Gra sprawdzttrafienia 283
//and clas board show "1"
}
bool checkhit(int fletter, int fdigit,bool write=false,int distance =0){

if (board [fletter][fdigit].IsCell==true )
{
    if (distance) {board [fletter][fdigit].distance=distance;return true;}
    if (write) {board [fletter][fdigit].hitted=true;return true;}//uwaga wpisujemy trafienie
    else if (board [fletter][fdigit].hitted==true) return true;
    return false;
}

return false;

}
void show(bool AI=false){
  cout<<endl<<endl;
  for (int c=1;c<=10;c++){
     cout<<c<<" ";if (c!=10 )cout<<" ";//wypisz cyfre przed tabela dla 10 pomin spacje dla rownego
     for (int l=1;l<=10;l++)
     {
       if (board[l][c].distance==1){cout<<"1 ";continue;}
        if (board[l][c].hitted==true){cout<<"T ";continue;}
        if (board[l][c].IsCell==true)
          { if (AI ) {cout <<"O ";continue;}
            else {cout<< "K ";continue;}
            }
        if (board[l][c].wasShot==false)cout<<"O ";
        if (board[l][c].wasShot==true)cout<<"* ";

    }
     cout<<endl;
   }
   cout<<endl<<"   ";
   for (int w=0;w<10;w++){ cout << (char)(65+w)<<" ";}
   cout<<endl;
}
};//kooniec klasy Board   ***


class Cell{
private:
bool busy;
enum WhichPosition {veritical, horizontal};
WhichPosition position;
static int whichCell;
public:
string  name;
int lenght;
int poleletter;
int poledigit;

Cell(){//konstruktor
name="";
lenght=0;
poleletter = 5;
poledigit = 5;
position =horizontal;//jeszcze dorobic
busy=false;
whichCell++;
};
int Randomize(int Range=10)
{
    return( rand() % Range ) + 1;//domyslnie z 10 losuje
}
void PositionfirstCell (Board &boardthatplayer,bool AI =false){
  int all;bool replay;
    if (AI){ poleletter =Randomize();poledigit=Randomize() ;}

    do{
       replay=false;
       for ( all=0;all<lenght;all++)
          {
           if(boardthatplayer.board[poleletter+all][poledigit].IsCell==true||poleletter>10)
           {
            if (poleletter+lenght>10){
               poledigit++;
               if (AI) poleletter= Randomize();//jezeli gra ai i zajete przez inny Cell Randomize inna litere
               else poleletter=5;
               replay=true;break;
            }//powtarzamy gdy zajete pole
            poleletter++;replay=true;break;
           }
          }
    }while(replay);

    for (all=0;all<lenght;all++){//PositionfirstCell i zapamietaj komorki na planszy
          boardthatplayer.board[poleletter+all][poledigit].IsCell=true;
        }
}//koniec PositionfirstCell

bool Move(char move, Board &boardthatplayer){
busy=false;
int all;
if (position==horizontal){
   if((move=='p')&&(poleletter+lenght<=10)){

        if(boardthatplayer.board[poleletter+lenght][poledigit].IsCell==true) {busy=true;return busy;}
        boardthatplayer.board[poleletter][poledigit].IsCell=false;

        boardthatplayer.board[poleletter+lenght][poledigit].IsCell=true;
        poleletter++ ;
   }
   if((move=='l')&&(poleletter>1)){


        if(boardthatplayer.board[poleletter-1][poledigit].IsCell==true) {busy=true; return busy;}
        poleletter-- ;
        boardthatplayer.board[poleletter+lenght][poledigit].IsCell=false;
        boardthatplayer.board[poleletter][poledigit].IsCell=true;

   }
   if((move=='g')&&(poledigit>1)){

         for ( all=0;all<lenght;all++){
            if (boardthatplayer.board[poleletter+all][poledigit-1].IsCell==true){busy=true;return busy;}
         }
         for ( all=0;all<lenght;all++){
            boardthatplayer.board[poleletter+all][poledigit].IsCell=false;
            boardthatplayer.board[poleletter+all][poledigit-1].IsCell=true;
         }
         poledigit-- ;
   }
        if((move=='d')&&(poledigit<10)){//w dol

         for (int all=0;all<lenght;all++){//spr czy nie busy
            if (boardthatplayer.board[poleletter+all][poledigit+1].IsCell==true){busy=true;return busy;}
         }
         for (int all=0;all<lenght;all++){
            boardthatplayer.board[poleletter+all][poledigit].IsCell=false;
            boardthatplayer.board[poleletter+all][poledigit+1].IsCell=true;
        }
        poledigit++ ;
        }

}
if (position==veritical){

        if((move=='p')&&(poleletter+lenght<10)){
          boardthatplayer.board[poleletter][poledigit].IsCell=false;poleletter++ ;
          boardthatplayer.board[poleletter][poledigit].IsCell=true;
          for (int all=0;all<lenght;all++){
            boardthatplayer.board[poleletter][poledigit].IsCell=false;
            boardthatplayer.board[poleletter][poledigit].IsCell=true;
          }
        }
}
//dla veritical mona tez nowe polozenia
return busy;
};
//void obroc();//niewykorzystana
/*
//tworzymy komorki konstruktor
Cell(string jakityp,int jakalenght)
{
lenght=jakalenght;
name =jakityp;
whichCell++;

}
*/

};


class Gra
{
private:
//zmienne globalne (jak je usunac?)
const int TotalNumberCells=4;//ile TotalNumberCells
const int player0=0;
const int player1=1;
const bool AI=true;
const bool write=true;
bool destroyed;
bool replay=false;

public:
 Board plangr[2];//plansze dwa obiekty dla  dwoch playery
 Cell tenCell[2][10];  //dziesiec obiektow Organismow
 bool laststriked=false;

 bool destroing=false;
 int rememberedletterdigit, remembereddigit;

bool checkhitsplayera(int nrplayera,int letterdigit,int digit,bool AI1= false){

if(plangr[nrplayera].checkhit(letterdigit,digit,write))//check the cell if it is  was hit
  {
    cout<<endl<<changeforletter(letterdigit)<<digit<<" - hitted!!!!"<<endl;
    if (AI1) {laststriked=true;rememberedletterdigit=letterdigit; remembereddigit=digit;}
    for (int nrCell=0; nrCell <TotalNumberCells ;nrCell++)
    {
       if ((tenCell[nrplayera][nrCell].poledigit==digit)&&(letterdigit>=tenCell[nrplayera][nrCell].poleletter)&&(letterdigit<tenCell[nrplayera][nrCell].poleletter+tenCell[nrplayera][nrCell].lenght))//< =??+lenght
        {//{cout <<"jestem na statku:"<<tenCell[nrplayera][nrCell].name<<endl;
        destroyed=true;
        for (int nastatku =tenCell[nrplayera][nrCell].poleletter;nastatku <(tenCell[nrplayera][nrCell].poleletter+tenCell[nrplayera][nrCell].lenght);nastatku++)
            {
            if (plangr[nrplayera].checkhit(nastatku,digit)) {;continue;}
            destroyed=false;
            }
        if (destroyed){
           if (AI1) destroing=false;
           if (nrplayera==0) {//jezeli teraz sprawdza trafienia wirus
              cout<<"Zniszczono "<<tenCell[nrplayera][nrCell].name<<endl;
              // if (AI1) ostatniodestroyed=true;
              (plangr[nrplayera].howmanyDestroyed)++;
              //czy wygral
              if (plangr[nrplayera].howmanyDestroyed==TotalNumberCells)
              {cout <<"Wszystkie komorki ukladu odpornosciowego zniszone! wirusy "<<" wygraly!!!";return true;}//wykasowac return
              else cout<<"Pozostalo komorek: "<<TotalNumberCells-plangr[nrplayera].howmanyDestroyed<<endl;
           }

           else{ cout<<"Zniszczony wirus  "<<tenCell[nrplayera][nrCell].name<<endl;
              (plangr[nrplayera].howmanyDestroyed)++;
              //czy wygral
              if (plangr[nrplayera].howmanyDestroyed==TotalNumberCells){
              cout <<"Wszystkie wirusy destroyed! Uklad odpornosciowy  "<<" Zwyciezyl !!!";return true;}//<< nrplayera wykasowac return
              else cout<<"Pozostalo wirusow: "<<TotalNumberCells-plangr[nrplayera].howmanyDestroyed<<endl;
           }
         }
       }
     }
   }
   else
   {
     if (plangr[nrplayera].checkfordistance(letterdigit,digit)==1) plangr[nrplayera].checkhit(letterdigit,digit,false,1);
     cout<<changeforletter(letterdigit)<<digit <<" - Nietrafione!"<<endl;
    }

 return false;
}
int Randomize(int Range=10)
{
    return( rand() % Range ) + 1;//z 10 losuje
}

bool DidwasShot(int player,int letterdigit,int digit, bool write=false){
   if (write) {plangr[player].board[letterdigit][digit].wasShot=true; return true;}
   if (plangr[player].board[letterdigit][digit].wasShot==true) {return true;}
   return false;
}


void PlaceOrganism(int player){//dla playera 0
 bool Isbusy=false;//przechowuje czy pole zajete po Moveieciu
 char letter;bool automatycznie=false;
    {
    for (int nrCell=0; nrCell<TotalNumberCells ;nrCell++){//spr czy wszyskie juz rozmieszczone
    if (nrCell==0) { tenCell[player][nrCell].name =  "Biale Krwinki"; tenCell[player][nrCell].lenght=4; tenCell[player][nrCell].PositionfirstCell(plangr[player],automatycznie);} //rozmiesc poczatkowo Cell
    if (nrCell==1) { tenCell[player][nrCell].name =  "Limfocyty "; tenCell[player][nrCell].lenght=3;tenCell[player][nrCell].PositionfirstCell(plangr[player],automatycznie); };
    if (nrCell==2) { tenCell[player][nrCell].name =  "Przeciwciala"; tenCell[player][nrCell].lenght=2;tenCell[player][nrCell].PositionfirstCell(plangr[player],automatycznie); };
    if (nrCell==3) { tenCell[player][nrCell].name =  "Limfocyt T "; tenCell[player][nrCell].lenght=1;tenCell[player][nrCell].PositionfirstCell(plangr[player],automatycznie); };
    //case

     while (letter!='n'|| Isbusy)
        {
        plangr[player].show(); // wyswietl plansze
        if (Isbusy) {cout <<"Pole zajete  przez inna komorke "<<endl;Isbusy=false;}
        if (letter=='k') cout <<"Nastepna ";
        cout<<"Rozmiesc komorki ukladu odpornosciowego: "<< tenCell[player][nrCell].name <<"  "<<tenCell[player][nrCell].lenght<<" pol dlugosci."<<endl;
        cout<<"wcisnij p-prawo; l-lewo; g-gora; d-dol; a-automatycznie; n-nastepny (zatwierdz enter)";
        if (!automatycznie)
        {cin>>letter; if (letter=='a') automatycznie=true;;}//usun przyspiesz nrCell=0;
       else  letter ='n';
        if ( Isbusy) { continue;};
        Isbusy=tenCell[player][nrCell].Move(letter,plangr[player]);
        }
     cout <<endl;//"nrCell"<<nrCell;
     letter='k';
    // if (nrCell==2) break;//na razie ograniczamy do trzech Organismow
     }
   }

}
void PlaceOrganism(int player,bool AI){//dla komputera automatycznie
 bool Isbusy=false;//przechowuje czy pole zajete po Moveieciu
 char letter;
 for (int nrCell=0; nrCell<TotalNumberCells ;nrCell++){//spr czy wszyskie juz rozmieszczone
    if (nrCell==0) { tenCell[player][nrCell].name =  "Borelioza"; tenCell[player][nrCell].lenght=4; tenCell[player][nrCell].PositionfirstCell(plangr[player],AI);} //rozmiesc poczatkowo Cell
    if (nrCell==1) { tenCell[player][nrCell].name =  "Grypa "; tenCell[player][nrCell].lenght=3;tenCell[player][nrCell].PositionfirstCell(plangr[player],AI); };
    if (nrCell==2) { tenCell[player][nrCell].name =  "Koronowirus "; tenCell[player][nrCell].lenght=2;tenCell[player][nrCell].PositionfirstCell(plangr[player],AI); };
    if (nrCell==3) { tenCell[player][nrCell].name =  "Gruzlica "; tenCell[player][nrCell].lenght=1;tenCell[player][nrCell].PositionfirstCell(plangr[player],AI); };
     while (letter!='n'|| Isbusy)
        {
        plangr[player].show(); // wyswietl plansze
        if (Isbusy) {cout <<"Pole zajete  przez innego wirusa "<<endl;Isbusy=false;}
        if (letter=='k') cout <<"Nastepny wirus";
        cout<<"PositionfirstCell wirusa "<< tenCell[player][nrCell].name <<"  "<<tenCell[player][nrCell].lenght<<" pol  lenghti."<<endl;
        cout<<"wcisnij p-prawo; l-lewo; g-gora; d-dol ; n-nastepny ";
        letter ='n';
        if ( Isbusy) { continue;};
        Isbusy=tenCell[player][nrCell].Move(letter,plangr[player]);
        }
     cout <<endl;//"nrCell"<<nrCell;
     letter='k';
    // if (nrCell==2) break;//na razie ograniczamy do trzech Organismow
     }
}
bool wasitRandomed( int iLiczba, int tab[], int ile )//notU
{
    if( ile <= 0 )
         return false;

    int i = 0;
    do
    {
        if( tab[ i ] == iLiczba )
             return true;

        i++;
    } while( i < ile );

    return false;
}
//void aito(bool AI=true){cout <<AI;}

void AIattack(int &letterdigit, int &digit) {
   //static bool overfire=false;
   if ((laststriked&&!destroyed)||destroing)
   {

      letterdigit=rememberedletterdigit+1;
      digit=remembereddigit;

     if ((letterdigit>10)||(DidwasShot(player0,letterdigit,digit)))//check if was fire on next letter
      {//go opposide
        do//sprawdza czy jest Cell i czy byl juz hitted
        {

            letterdigit--;
            if (letterdigit<1){letterdigit=1; cout<<"blad trafienia" ;}
        }while (DidwasShot(player0,letterdigit,digit));

      }
      else destroing=true;

     }
     else {
      letterdigit=Randomize();
      digit=Randomize();
      replay=false;
      do {
       if (DidwasShot(player0,letterdigit,digit)){letterdigit++ ;replay=true;}
       else replay=false;

        if (letterdigit>10){letterdigit=1;digit++;}
        if (digit >10) {digit=1;letterdigit=1 ;replay=true; }

    }while(replay);
     // overfire=false;
     }


  }//dorobic jesli trafi na inny Cell niz aktualny lub puste pole

  char changeforletter(int letterdigit)
{
    return (char)(letterdigit+64);
}

};


int Cell::whichCell=0;//definicja skladnika statycznego


int main()//zaczynamy
{
Gra Organism;

const int player0=0;
const int player1=1;
const bool write=true;
bool AI=true;//wybieramy kto gra
char letter;
int digit=-1;
int letterdigit;///usunac
bool levelAI=false;//poziom AI false slaby true sredniozawansowany
bool replay;
bool gameover=false;
srand( time( 0 ) );//loswy generator
CLEARSCR;

//rozmieszczenie Organismow
cout << " Rozmiesc komorki ukladu odpornosciowego "<<endl;
Organism.PlaceOrganism(player0);//
//rozmiesc wirusy
Organism.PlaceOrganism(player1,AI);
//gra zaczynamy
system("cls");
cout <<"Zaczynamy";

do{

   bool replaystrzal=false;
   //wyswietl plansze
   Organism.plangr[player0].show();
   Organism.plangr[player1].show(AI); //podasz AI nie wyswietli statku

   do{
      do{replaystrzal=false;
        cout<<endl<<"sprawdz pole - podaj litere pozniej cyfre: ";cin>>letter;

        if (!((((int)letter>=65)&&(letter<75 ))||(((int)letter>=97)&&(letter<107 )))){replaystrzal=true;}
        }while (replaystrzal);
     do{
        replaystrzal=false;
        if (!((digit>=1)&&(digit<=10)))cout<<"podaj cyfre: ";
        cin>>(digit); if (!((digit>=1)&&(digit<=10)))cout<<digit<<endl;//jak ominac gdy obie podane
        if (!((digit>=1)&&(digit<=10))){;replaystrzal=true;;fflush(stdin);cin.clear();}//cin.ignore(numeric_limits<streamsize>::max(), '\n');}
       }while (replaystrzal);
     if (((int)letter)>96) {letterdigit=(int)letter-96;}//zamiana duzych na male
     else letterdigit=(int)letter-64;
     if (Organism.DidwasShot(player1,letterdigit,digit))cout <<endl<< "Pole juz sprawdzone";
     }while(Organism.DidwasShot(player1,letterdigit,digit));//gdy trafiamy juz uzyte pole
CLEARSCR; //system("cls");
// tu przesylam ostrzal od jednego playera do drugiego w sieci
{

}

gameover=Organism.checkhitsplayera(player1,letterdigit,digit);
Organism.DidwasShot(player1,letterdigit,digit,write);//jesli write to go writee

//teraz drugi player/komputer
if (!gameover){//omijamy gdy koniec gry player0 win
  levelAI=true;
  if (levelAI){Organism.AIattack(letterdigit, digit );}
  else
  {//weak level
    letterdigit=Organism.Randomize();
    digit=Organism.Randomize();
    replay=false;
    do{
      if (Organism.DidwasShot(player0,letterdigit,digit)){letterdigit++ ;cout<<"uwagapowtarzam";replay=true;}
      else replay=false;
      if (letterdigit>10){letterdigit=10;digit++;}
      if (digit >10) {digit=1; letterdigit=1;}
    }while(replay);
  }
  cout<<endl<<"Wirus atakuje " <<Organism.changeforletter (letterdigit)<<" " <<digit<<endl;

//tu przesyla trzeba  do pierwszego playera w sieci
{

}
   Organism.DidwasShot(player0,letterdigit,digit,write);
   Organism.laststriked=false; //Organism.ostatniodestroyed=false;
   gameover= Organism.checkhitsplayera(player0,letterdigit,digit,AI);


}

}while(!gameover);

return 0;
}


// rozmieszczenie ai
//inteligentne strzelanie ai


