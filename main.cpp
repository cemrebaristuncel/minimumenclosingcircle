#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
typedef struct{
		int X;
		int Y;                             // "Noktalar" ad�nda X ve Y de�i�kenleri olan struct tan�mlamas� yapt�k.
	}Noktalar;
	
double uzaklikHesaplayici(double a, double b) {   //�ki nokta aras� uzakl��� hesaplayan fonksiyon. Yar��ap� �izdirirken bize yard�mc� olacak.
	return a*a + b*b;
}

int main(){
	printf("En kucuk yaricapli cevreleyen daire icin 1'e basin, egri icin 2'ye basin\n");	
	int secim;
	scanf("%d",&secim);
    printf("Dosyadan cekilen noktalar: \n");
	Noktalar nokta[100];
	int i=0;                                         //Dosyay� a�ma i�lemleri
	char *satir, *tutucu;
	char dizi[100];           
	FILE *inp;
	inp = fopen("dosya.txt", "r");	
	
	satir = fgets(&dizi[0],100,inp);
	
while(satir != '\0'){
	
	tutucu = strtok(&dizi[0], " ");	
	sscanf(tutucu,"%d", &nokta[i].X);            //Burada yap�lan i�lem, strtok'tan(belirtilen indisten kesme fonksiyonu)�nceki k�sm� nokta dizisinin x ine, strtok'tan sonraki k�sm� ise nokta dizisinin y sine g�nderme i�lemidir.
	tutucu = strtok('\0',"/n");                 //Dolay�s�yla bo�luktan �nceki k�s�m nokta[i].X ' e, bo�luktan sonraki k�s�m ise nokta[i].Y 'ye g�nderilecektir.
	sscanf(tutucu,"%d", &nokta[i].Y);           
	i++;
	satir = fgets(&dizi[0],100,inp);           //Yeni bir sat�ra ge�ti�i i�in "satir" i yeniden tan�ml�yoruz.

}
	
	fclose(inp);
	int noktasayisi = 0;
	noktasayisi = i;
	
if(secim==1)  // secim = 1 ise �ember �izdirece�iz.
{	
	
	
	float  X, Y, yaricap, yeniyaricap;
		for(int k = 0 ; k< noktasayisi; k++)
	{
		printf("%d %d \n",nokta[k].X,nokta[k].Y);
	}
	for(int j = 0; j<noktasayisi;j++)
	{
			if(nokta[j].X > 0 )
		{
			nokta[j].X = 500 + (abs(nokta[j].X * 25));
			
		}
		
		
		if(nokta[j].X < 0)
		{	
			nokta[j].X = 500 - abs(nokta[j].X * 25);
		}
		if(nokta[j].Y>0)                                                  //Tutulan noktalar� koordinat sistemimize g�re uyarlamak i�in bu kodlar� yazd�k.
		{
			nokta[j].Y = 500 - (abs(nokta[j].Y * 25));
		}
		
		if(nokta[j].Y<0)
		{
			nokta[j].Y = 500 + abs(nokta[j].Y * 25);
		}
		if(nokta[j].X == 0)
		{
			nokta[j].X = 500;
		}
		if(nokta[j].Y == 0){
			
			nokta[j].Y = 500;
		}
		 
		             
	}
																   
	
	
	

	for (int i = 0; i < noktasayisi; i++) {
		
		X += nokta[i].X;
		Y += nokta[i].Y;
		
	}
	X /= noktasayisi; Y /= noktasayisi;
	double P = 0.1;
	for (int i = 0; i < 30000; i++) {
		
		int f = 0;
		yaricap = uzaklikHesaplayici(X - nokta[0].X, Y - nokta[0].Y); 
		
		for (int j = 1; j < noktasayisi; j++) {                                                 //Algoritma kodu
			
			yeniyaricap = uzaklikHesaplayici(X - nokta[j].X, Y - nokta[j].Y); 
			if (yaricap < yeniyaricap) 
		{ 
			yaricap = yeniyaricap; 
			f = j;
			
		}
			
		}
		X += (nokta[f].X- X)*P;   
		Y += (nokta[f].Y- Y)*P;
		//printf("%f %f %f\n",(X-500)/25,(500-Y)/25,((sqrt(yaricap)/25)));
		P *= 0.999;
	
		 
     
     
	
	}
	float n =((sqrt(yaricap)/25));
	float merkezx = (X-500)/25;     // Bu �� sat�rda yar��ap�, merkez x'i ve merkez y'yi istenilen �ekilde ��kt� vermesi i�in d�n��t�r�yoruz.
	float merkezy = (500-Y)/25;
	
	
	printf("\nMerkez X: %.4lf Merkez Y: %.4lf\nYaricap Uzunlugu: %.4lf", merkezx,merkezy,n); // Merkez X, Merkez Y ve yar��ap�n yazd�r�lmas� burada ger�ekle�iyor.
		
		
	

	
	int m;
	initwindow(1000,1000);
		
		for(int q = 0; q< noktasayisi; q++)
	{	
		setcolor(4);
		outtextxy(nokta[q].X,nokta[q].Y,"�");
		
	}
	

	setcolor(1);
	line(0,500,1000,500);  // X Eksenini �izen fonksiyon         
	line(500,0,500,1000);  // Y Eksenini �izen fonksiyon
	setcolor(15);
	outtextxy(0,505,"-X");     
	outtextxy(1000,500,"X");                                        
	outtextxy(505,0,"Y");
	outtextxy(500,1000,"-Y");
	for(m=0;m<500;m=m+25){
		line(m,500,m,505);
		line(500,m,505,m);
		                               // Bu iki d�ng� ile koordinat sisteminin eksenlerini  e�it aral�klarla b�lmelendiriyoruz.
	}
	for(m=525;m<1000;m=m+25){         
		line(m,500,m,505);           
		line(500,m,505,m);          
		
		
		}
		circle(X,Y,sqrt(yaricap)); // �stenen �emberi �izdiren circle fonksiyonu
		setcolor(9);
		outtextxy(X-3,Y-3,"�"); //N say�daki noktay� koordinat d�zlemi �zerinde i�aretleyen fonksiyon
		setcolor(10);
		line(X,Y,X+sqrt(yaricap),Y); // Yaricap cizdiren line fonksiyonu
	

	getch();

	closegraph();
}
else if(secim==2) // secim = 2 ise B-Spline e�risini �izdirece�iz.
{
	for(int k = 0 ; k< noktasayisi; k++)
	{
		printf("%d %d \n",nokta[k].X,nokta[k].Y);
	}
	initwindow(1000,1000);
	for(int j = 0; j<noktasayisi;j++)
	{
			if(nokta[j].X > 0 )
		{
			nokta[j].X = 500 + (abs(nokta[j].X * 25));
			
		}
		
		
		if(nokta[j].X < 0)
		{	
			nokta[j].X = 500 - abs(nokta[j].X * 25);
		}
		if(nokta[j].Y>0)                                                          
		{
			nokta[j].Y = 500 - (abs(nokta[j].Y * 25));
		}
		
		if(nokta[j].Y<0)
		{
			nokta[j].Y = 500 + abs(nokta[j].Y * 25);                          // Tekrardan koordinat sistemimizi �izdiriyoruz.
		}
		if(nokta[j].X == 0)
		{
			nokta[j].X = 500;
		}
		if(nokta[j].Y == 0){
			
			nokta[j].Y = 500;
		}
		 
		            
	}
																  
	setcolor(1);
	line(0,500,1000,500);
	line(500,0,500,1000);
	setcolor(15);
	for(int q = 0; q< noktasayisi; q++)
	{	
		setcolor(4);
		outtextxy(nokta[q].X,nokta[q].Y,"�");
		
	}
	
	double t,put_x,put_y;
	
	 int c,gecici,tut,tut2;
	 int dizi_X[noktasayisi][2];
	  
	 for(int i = 0; i<noktasayisi; i++)
	 {
	 	dizi_X[i][0] = nokta[i].X;
	 	dizi_X[i][1] = nokta[i].Y;
	
	 }
    for(gecici=1;gecici<noktasayisi;gecici++)
       {
           for (int i=0;i<noktasayisi-1;i++)
          {
		
	
           if (dizi_X[i][0]>dizi_X[i+1][0])
           {	
           		                               // E�rinin ba�lang�� ve son noktas�n� belirlememiz i�in noktalar�n koordinatlar�n� "x" de�erlerine g�re k���kten b�y��e s�ralad�k.
            tut=dizi_X[i][0];
            dizi_X[i][0]=dizi_X[i+1][0];
            dizi_X[i+1][0]=tut;
			tut2 = dizi_X[i][1];
			dizi_X[i][1] = dizi_X[i+1][1];
			dizi_X[i+1][1] = tut2;
			}		
          }
          
          //NOKTA SAYILARINA G�RE E�R� ��ZME KODUNU DE���T�REREK �STENEN �IKTIYA ULA�MAYA �ALI�TIK.
          
    }
    if(noktasayisi == 3){
    	for(t=0.001;t<=1.0;t+=0.001)
	{
		put_x = pow(1-t,3)*(dizi_X[0][0])+ 3*t*pow(1-t,2)*(((dizi_X[1][0])))-10 + 3*t*t*(1-t)*(((dizi_X[1][0])))+10 + pow(t,3)*(dizi_X[2][0]);  //E�ri �izen fonksiyon
		put_y = pow(1-t,3)*(dizi_X[0][1]) + 3*t*pow(1-t,2)*(((dizi_X[1][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[1][1]))-10) + pow(t,3)*(dizi_X[2][1]); //Noktan�n koordinat�na g�re e�rinin �ekli de�i�mektedir.
		put_y +=10;                                                                                                        //Sat�rlar�n ortas�nda yer alan +10 ve -10 de�erlerini e�ik bir g�r�nt� vermek amac�yla ekledik.
	
		
		putpixel(put_x,put_y,15);
			
	}
    	
    	
    	
    	
	}
	
    
	if(noktasayisi == 4)
	{	
	

int sayac1 = 0, sayac2 = 0;
		int tutx,tuty,tutx1,tuty1;
	
		for(t=0.001;t<=1.0;t+=0.001)
	{	
	
		
	
		while(t<0.5)
		{	
		sayac1++;
		
		put_x = pow(1-t,3)*dizi_X[0][0] + 3*t*pow(1-t,2)*(((dizi_X[1][0]))-10) + 3*t*t*(1-t)*(((dizi_X[1][0]))+10) + pow(t,3)*(dizi_X[2][0]);			
		put_y = pow(1-t,3)*dizi_X[0][1] + 3*t*pow(1-t,2)*(((dizi_X[1][1]))-10)+  3*t*t*(1-t)*(((dizi_X[1][1]))-10) + pow(t,3)*(dizi_X[2][1]);
		put_y +=10;
		if(sayac1 ==499)
		{
			tutx = put_x;
			tuty = put_y-10;
		}
		putpixel(put_x,put_y,15);
		t += 0.001;
		}
		if(t==0.5)
		{ t=0.001;
			break;
		}
	
		
	
			
	}
	
	for(t=0.5;t<=1.0;t+=0.001)
	{	
		while(1.0>t)
		{	
		sayac2++;	
		put_x = pow(1-t,3)*dizi_X[2][0] + 3*t*pow(1-t,2)*(((dizi_X[3][0]))-10) + 3*t*t*(1-t)*(((dizi_X[3][0]))+10) + pow(t,3)*(dizi_X[3][0]);			
		put_y = pow(1-t,3)*dizi_X[2][1] + 3*t*pow(1-t,2)*(((dizi_X[3][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[3][1]))-10) + pow(t,3)*(dizi_X[3][1]);
		put_y +=10;
			if(sayac2 ==1)
		{
			tutx1 = put_x;
			tuty1 = put_y-10;
		}
		putpixel(put_x,put_y,15);
		
		t += 0.001;
		}
		if(t == 1.0)
			{
				break;
			}
		}
	for(t=0.001;t<=1.0;t+=0.001)
	{	
		put_x = pow(1-t,3)*tutx + 3*t*pow(1-t,2)*(((dizi_X[2][0]))-10) + 3*t*t*(1-t)*(((dizi_X[2][0]))+10) + pow(t,3)*tutx1;
		put_y = pow(1-t,3)*tuty + 3*t*pow(1-t,2)*(((dizi_X[2][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[2][1]))-10) + pow(t,3)*tuty1;
		put_y +=10;
		putpixel(put_x,put_y,15);
			
	}
	

	}
	if(noktasayisi == 5)
	{
		int sayac1 = 0, sayac2 = 0;
		int tutx,tuty,tutx1,tuty1;
	
		for(t=0.001;t<=1.0;t+=0.001)
	{	
	
		
	
		while(t<0.5)
		{	
		sayac1++;
		
		put_x = pow(1-t,3)*dizi_X[0][0] + 3*t*pow(1-t,2)*(((dizi_X[1][0]))-10) + 3*t*t*(1-t)*(((dizi_X[1][0]))+10) + pow(t,3)*(dizi_X[2][0]);			
		put_y = pow(1-t,3)*dizi_X[0][1] + 3*t*pow(1-t,2)*(((dizi_X[1][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[1][1]))-10) + pow(t,3)*(dizi_X[2][1]);
		put_y +=10;
		if(sayac1 ==499)
		{
			tutx = put_x;
			tuty = put_y-10;
		}
		putpixel(put_x,put_y,15);
		t += 0.001;
		}
		if(t==0.5)
		{ t=0.001;
			break;
		}

			
	}
		
	for(t=0.5;t<=1.0;t+=0.001)
	{	
		while(1.0>t)
		{	
		sayac2++;	
		put_x = pow(1-t,3)*dizi_X[2][0] + 3*t*pow(1-t,2)*(((dizi_X[3][0]))-10) + 3*t*t*(1-t)*(((dizi_X[3][0]))+10) + pow(t,3)*(dizi_X[4][0]);			
		put_y = pow(1-t,3)*dizi_X[2][1] + 3*t*pow(1-t,2)*(((dizi_X[3][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[3][1]))-10) + pow(t,3)*(dizi_X[4][1]);
		put_y +=10;
			if(sayac2 ==1)
		{
			tutx1 = put_x;
			tuty1 = put_y-10;
		}
		putpixel(put_x,put_y,15);
		
		t += 0.001;
			
	
		}
		if(t == 1.0)
			{
				break;
			}
	
	}
	
for(t=0.001;t<=1.0;t+=0.001)
	{	
		put_x = pow(1-t,3)*tutx + 3*t*pow(1-t,2)*(((dizi_X[2][0]))-10) + 3*t*t*(1-t)*(((dizi_X[2][0]))+10) + pow(t,3)*tutx1;
		put_y = pow(1-t,3)*tuty + 3*t*pow(1-t,2)*(((dizi_X[2][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[2][1]))-10) + pow(t,3)*tuty1;
		put_y +=10;
		putpixel(put_x,put_y,15);
	
			
	}
	}
	if(noktasayisi == 6)
	{
		int sayac1 = 0, sayac2 = 0;
		int tutx,tuty,tutx1,tuty1;
	
		for(t=0.001;t<=1.0;t+=0.001)
	{	
	
		
	
		while(t<0.5)
		{	
		sayac1++;
		
		put_x = pow(1-t,3)*dizi_X[0][0] + 3*t*pow(1-t,2)*(((dizi_X[1][0]))-10) + 3*t*t*(1-t)*(((dizi_X[1][0]))+10) + pow(t,3)*(dizi_X[2][0]);			
		put_y = pow(1-t,3)*dizi_X[0][1] + 3*t*pow(1-t,2)*(((dizi_X[1][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[1][1]))-10) + pow(t,3)*(dizi_X[2][1]);
		put_y +=10;
		if(sayac1 ==499)
		{
			tutx = put_x;
			tuty = put_y-10;
		}
		putpixel(put_x,put_y,15);
		t += 0.001;
		}
		if(t==0.5)
		{ t=0.001;
			break;
		}
	}
	
		for(t=0.001;t<=1.0;t+=0.001)
	{
		put_x = pow(1-t,3)*(dizi_X[3][0])+ 3*t*pow(1-t,2)*(((dizi_X[4][0])-10)) + 3*t*t*(1-t)*(((dizi_X[4][0]))+10) + pow(t,3)*(dizi_X[5][0]);
		put_y = pow(1-t,3)*(dizi_X[3][1]) + 3*t*pow(1-t,2)*(((dizi_X[4][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[4][1]))-10) + pow(t,3)*(dizi_X[5][1]);
		put_y +=10;
		if(sayac2 == 0)
		{ 
			tutx1 = put_x;
			tuty1 = put_y-10;
		}
		sayac2++;
		
		putpixel(put_x,put_y,15);
			
	}
		

	
       for(t=0.001;t<=1.0;t+=0.001)
	{	
		put_x = pow(1-t,3)*tutx + 3*t*pow(1-t,2)*(((dizi_X[2][0]))-10) + 3*t*t*(1-t)*(((dizi_X[2][0]))+10) + pow(t,3)*tutx1;
		put_y = pow(1-t,3)*tuty + 3*t*pow(1-t,2)*(((dizi_X[2][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[2][1]))-10) + pow(t,3)*tuty1;
		put_y +=10;
		putpixel(put_x,put_y,15);
	
			
	}
	}
		if(noktasayisi == 7)
	{ 	
		int sayac1 = 0, sayac2 = 0;
		int tutx,tuty,tutx1,tuty1;
	
		for(t=0.001;t<=1.0;t+=0.001)
	{	
	
		while(t<0.5)
		{	
		sayac1++;
		
		put_x = pow(1-t,3)*dizi_X[0][0] + 3*t*pow(1-t,2)*(((dizi_X[1][0]))-10) + 3*t*t*(1-t)*(((dizi_X[1][0]))+10) + pow(t,3)*(dizi_X[2][0]);			
		put_y = pow(1-t,3)*dizi_X[0][1] + 3*t*pow(1-t,2)*(((dizi_X[1][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[1][1]))-10) + pow(t,3)*(dizi_X[2][1]);
		put_y +=10;
		if(sayac1 ==499)
		{
			tutx = put_x;
			tuty = put_y-10;
		}
		putpixel(put_x,put_y,15);
		t += 0.001;
		}
		if(t==0.5)
		{ t=0.001;
			break;
		}
	}
	
		for(t=0.001;t<=1.0;t+=0.001)
	{
		put_x = pow(1-t,3)*(dizi_X[3][0])+ 3*t*pow(1-t,2)*(((dizi_X[4][0])))-10 + 3*t*t*(1-t)*(((dizi_X[4][0])))+10 + pow(t,3)*(dizi_X[5][0]);
		put_y = pow(1-t,3)*(dizi_X[3][1]) + 3*t*pow(1-t,2)*(((dizi_X[4][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[4][1]))-10) + pow(t,3)*(dizi_X[5][1]);
		put_y +=10;
		if(sayac2 == 0)
		{ 
			tutx1 = put_x;
			tuty1 = put_y-10;
		}
		sayac2++;
		
		putpixel(put_x,put_y,15);
			
	}
			for(t=0.001;t<=1.0;t+=0.001)
	{
		put_x = pow(1-t,3)*(dizi_X[5][0])+ 3*t*pow(1-t,2)*(((((dizi_X[5][0])+(dizi_X[6][0]))/2)-10)) + 3*t*t*(1-t)*(((((dizi_X[5][0])+(dizi_X[6][0]))/2)-10)) + pow(t,3)*(dizi_X[6][0]);
		put_y = pow(1-t,3)*(dizi_X[5][1]) + 3*t*pow(1-t,2)*(((((dizi_X[5][1])+(dizi_X[6][1]))/2)-10))+ 3* t*t*(1-t)*(((((dizi_X[5][1])+(dizi_X[6][1]))/2)-10)) + pow(t,3)*(dizi_X[6][1]);
		put_y +=10;
		putpixel(put_x,put_y,15);
			
	}
	

		
	
for(t=0.001;t<=1.0;t+=0.001)
	{	
		put_x = pow(1-t,3)*tutx + 3*t*pow(1-t,2)*(((dizi_X[2][0]))-10) + 3*t*t*(1-t)*(((dizi_X[2][0]))+10) + pow(t,3)*tutx1;
		put_y = pow(1-t,3)*tuty + 3*t*pow(1-t,2)*(((dizi_X[2][1]))-10)+ 3* t*t*(1-t)*(((dizi_X[2][1]))-10) + pow(t,3)*tuty1;
		put_y +=10;
		putpixel(put_x,put_y,15);
	
			
	}
	
	}		
	
	}
	getch();

	closegraph();
	return 0;
	
}
