#include <iostream>
#include <stdlib.h>
#define MAKS_KENAR 800
#define MAKS_DUGUM 400
#include <graphics.h>
#include <conio.h>

// 140202004 Cengiz Eren
// 130202052 Canberk Bozaci
// 140202006 Tarik Tekin
using namespace std;

void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int dugum_adet;
int kume[MAKS_DUGUM];

/** Eger dugumler daha once birlesmemislerse birlestirilirler.Bu islem kume numaralari ile yapilir.*/
void birlestir(int p, int q)
{
    int i;
    for(i=65;i<dugum_adet+65;i++)
    {
        if(kume[i]==q)
            kume[i]=p;
    }
}

/** Kenarlar icin struct yapisi oluþturuldu.*/
typedef struct _kenar{
    int ilk;
    int son;
    int maliyet;
}KENAR;
KENAR kenar[800],EKYA[200];
int main(){
    bool matris[20][20];
    int indis_x, indis_y;
    int sayac=0;

      int gd = DETECT, gm;

   initgraph(&gd, &gm, "C:\\TC\\BGI");


    /** Matris elemanlari baslangicta 0 tanimlaniyor. */
    for(int satir=0; satir<20; satir++){
        for(int sutun=0; sutun<20; sutun++)
            matris[satir][sutun] =  0;
        }


   /** Kullanicinin kac tane dugum girecegi bilgisi aliniyor,Kontrol ediliyor,Uygun degilse islemi tekrar yapmasi isteniyor */
    b:
    cout << "Kac Adet Dugum Girilecek: ";
    cin  >> dugum_adet;
    if (dugum_adet <0 ){
        cout<<"\nLutfen gecerli dugum adedi giriniz\n";
        goto b;
    }
    if (dugum_adet >400 ){
        cout<<"\nLutfen gecerli dugum adedi giriniz\n";
        goto b;
    }
    //Kontrol...
    if(dugum_adet == 0){
        cout << "!!!Kapatiliyor!!!";
        exit(0);
    }

    int komsuluk_matrisi[dugum_adet][3];    //{X, Y, Dugum}
    char c='A';


    /** Kullanicidan dugumlerin indis degerleri isteniyor.Sartlar uygunsa devem ediliyor.*/
    do{ a:
        cout << endl << "Dugumun Indislerini Giriniz(20'den Kucuk Olmali): ";
        cin  >> indis_x;
        cin >> indis_y;
        if (indis_x >20 || (indis_y>20) ){
        cout << "\nLutfen gecerli deger giriniz:\n";
        goto a;
        }
        if (indis_x<0 || indis_y<0 ){
            cout << "\nLutfen gecerli deger giriniz:\n";
        goto a;
        }
        matris[indis_x][indis_y] = 1;
        komsuluk_matrisi[sayac][0] = indis_x;
        komsuluk_matrisi[sayac][1] = indis_y;
        komsuluk_matrisi[sayac][2] = c;
        c++;
        sayac++;
    }while(dugum_adet>sayac);
    cout << endl;

   /** Matrisin gorsel sekli ciziliyor */
    for(int satir=0; satir<20; satir++)
        for(int sutun=0; sutun<20; sutun++){
            if(satir==0){
                if(sutun==0)
                    cout << "    " << sutun << "  ";
                else{
                    if(sutun/10==0)
                        cout << sutun << "  ";
                    else
                        cout << sutun << " ";
                }
            }
        }
    for(int satir=0; satir<20; satir++)
        for(int sutun=0; sutun<=20; sutun++){
                if(satir/10 == 0)
                    cout << endl << satir << "   ";
                else
                    cout << endl << satir << "  ";
                    for(int dugum=0; dugum<20; dugum++){
                        if(matris[satir][dugum] == 1){
                            cout << "0";

                        }
                        else
                            cout << "-";
                        if( dugum == 9 )
                            cout << "   ";
                        else
                            cout << "  ";
                    }
            break;
        }
    cout << endl << endl;


     /** Dugumleri degerleri ile birlikte yazdirma */
    for(int k=0; k<dugum_adet; k++)
        cout << (char)komsuluk_matrisi[k][2] << ": " << komsuluk_matrisi[k][0] << "-" << komsuluk_matrisi[k][1] << endl;
    cout << endl;


    /** Dugumler arasindaki mesafeler bulunuyor */
    int mesafe_matrisi[(dugum_adet)*(dugum_adet-1)/2 ][3];  //{Dugum, Dugum, Mesafe}
    int k=0;
    for(int l=0; l<dugum_adet; l++){
            for(int m=l+1; m<dugum_adet; m++){
                if(k<(dugum_adet)*(dugum_adet-1)/2){
                    mesafe_matrisi[k][0] = komsuluk_matrisi[l][2];
                    mesafe_matrisi[k][1] = komsuluk_matrisi[m][2];
                    mesafe_matrisi[k][2] = abs(komsuluk_matrisi[l][0] - komsuluk_matrisi[m][0])
                        + abs(komsuluk_matrisi[l][1] - komsuluk_matrisi[m][1]);
                }
                else
                    break;
                k++;
            }
    }

     /** Bulunan mesafe degerleri yazdirilir ve kenar matrisi ile mesafe matrisinin uygun degerleri birbiriyle eslestirilir*/
    for(int i=0; i<((dugum_adet)*(dugum_adet-1)/2); i++){
        cout << (char)mesafe_matrisi[i][0] << "-" << (char)mesafe_matrisi[i][1] << ":" << mesafe_matrisi[i][2];
        kenar[i].ilk = (char) mesafe_matrisi[i][0];
        kenar[i].son = (char) mesafe_matrisi[i][1];
        kenar[i].maliyet = mesafe_matrisi[i][2];
        cout << endl;
    }

    /** dugumleri mesafelerine gore siralama */
    int gecici,gecici_dugum1,gecici_dugum2;
    for (int i=0;i<((dugum_adet)*(dugum_adet-1)/2);++i)
        for (int j=0;j<((dugum_adet)*(dugum_adet-1)/2)-1;++j){
            if (mesafe_matrisi[j][2] >mesafe_matrisi[j+1][2]){
                gecici = mesafe_matrisi[j][2];
                mesafe_matrisi[j][2]=mesafe_matrisi[j+1][2];
               mesafe_matrisi[j+1][2]=gecici;
               gecici_dugum1=mesafe_matrisi[j][0];
               mesafe_matrisi[j][0]=mesafe_matrisi[j+1][0];
               mesafe_matrisi[j+1][0]=gecici_dugum1;
               gecici_dugum2=mesafe_matrisi[j][1];
               mesafe_matrisi[j][1]=mesafe_matrisi[j+1][1];
               mesafe_matrisi[j+1][1]=gecici_dugum2;
            }
    }

    /** Eslesme sonrasi degerler atanir */
for(int i=0; i<((dugum_adet)*(dugum_adet-1)/2); i++){
        //cout << (char)mesafe_matrisi[i][0] << "-" << (char)mesafe_matrisi[i][1] << ":" << mesafe_matrisi[i][2];
        kenar[i].ilk = (char) mesafe_matrisi[i][0];
        kenar[i].son =  (char)mesafe_matrisi[i][1];
        kenar[i].maliyet = mesafe_matrisi[i][2];
    }


    cout <<"\n Kenar mesafelerine gore siralanmis hal\n";
    for(int i=0; i<((dugum_adet)*(dugum_adet-1)/2); i++){
        cout << (char)mesafe_matrisi[i][0] << "-" << (char)mesafe_matrisi[i][1] << ":" << mesafe_matrisi[i][2];
        cout << endl;
    }
int z=0;
int t=0;
int x,y;

    /**Dugumlere Kume Numarasi Veriliyor*/
    for(int i=0;i<dugum_adet;i++){
        kume[kenar[i].ilk]=i;
    }


    while((t<=dugum_adet-1) && z<=((dugum_adet)*(dugum_adet-1)/2)){
            x = kume[kenar[z].ilk];
            y = kume[kenar[z].son];
if( x !=y )
        {
            birlestir(x,y);
            EKYA[t].ilk=kenar[z].ilk;
            EKYA[t].son=kenar[z].son;
            EKYA[t].maliyet=kenar[z].maliyet;
            t++;
        }
    z++;
    }



    cout<<("Basla\tGit\tMaliyet\n");
    int toplam=0;
     for(int i=0;i<t;i++){
        cout<<(char)EKYA[i].ilk<<"\t"<<(char)EKYA[i].son<<"\t"<<EKYA[i].maliyet<<"\n";
         toplam+=EKYA[i].maliyet;
     }





      int m = 50, n = 50;

   for (int c = 0 ; c < 20 ; c++ )
   {
       setlinestyle(c, -1, 2);

       line(m, n, m+570, n);
       n = n + 30;
   }

         n = 50;
    for (int c = 0 ; c < 20 ; c++ )
   {
       setlinestyle(c, -1, 2);

       line(m, n, m, n+570);
       m = m+ 30;
   }
   outtextxy(10,10,"Ornek bir matris tablosu");
   outtextxy(145,145,"D0");
   outtextxy(265,205,"D1");
   outtextxy(175,265,"D2");
   outtextxy(325,115,"D3");
   outtextxy(385,385,"D4");
   outtextxy(415,265,"D5");

   outtextxy(35,30,"0");
   outtextxy(35,52,"1");
   outtextxy(35,82,"2");
   outtextxy(35,112,"3");
   outtextxy(35,142,"4");
   outtextxy(35,172,"5");
   outtextxy(35,202,"6");
   outtextxy(35,232,"7");
   outtextxy(35,262,"8");
   outtextxy(35,292,"9");
   outtextxy(25,322,"10");
   outtextxy(25,352,"11");
   outtextxy(25,382,"12");
   outtextxy(25,412,"13");
   outtextxy(25,442,"14");
   outtextxy(25,472,"15");
   outtextxy(25,502,"16");
   outtextxy(25,532,"17");
   outtextxy(25,562,"18");
   outtextxy(25,592,"19");


    outtextxy(52,30,"1");
    outtextxy(82,30,"2");
    outtextxy(112,30,"3");
    outtextxy(142,30,"4");
    outtextxy(172,30,"5");
    outtextxy(202,30,"6");
    outtextxy(232,30,"7");
    outtextxy(262,30,"8");
    outtextxy(292,30,"9");
    outtextxy(322,30,"10");
    outtextxy(352,30,"11");
    outtextxy(382,30,"12");
    outtextxy(412,30,"13");
    outtextxy(442,30,"14");
    outtextxy(472,30,"15");
    outtextxy(502,30,"16");
    outtextxy(532,30,"17");
    outtextxy(562,30,"18");
    outtextxy(592,30,"19");
cout<<endl<<"Toplam maliyet: "<<toplam<<endl;
    getch();
     closegraph();
    return 0;
}
