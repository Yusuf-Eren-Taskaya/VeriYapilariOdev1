#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Dugum{
	int derece;
	int katSayi;
	struct Dugum *sonraki;
};

struct Dugum *top; 




void Ekleme(int der,int kat){

	struct Dugum *ekleme = top;

    while(ekleme!=NULL){
    	// mevcut litede yeni eklenmek istenen derecenin olup olmadýðý araþtýrýlýyor
 		if(ekleme->derece == der){
 				printf(" Bu derece onceden eklenmis... ");
				return;
		 }
        ekleme=ekleme->sonraki;
    }
	
	ekleme=top;
	
	if(ekleme==NULL){
		// daha önceden hiç eleman eklenmemiþ
		struct Dugum * ekleme=(struct Dugum*) malloc(sizeof(struct Dugum*));
 		ekleme->sonraki = NULL;
 		ekleme->derece = der;
 		ekleme->katSayi = kat;
		top = ekleme;
	
  	}
  	else
 	{
		if (ekleme->derece < der)
			{
			// yeni girilen deðer büyük
			// baþa eklenecek
		   		struct Dugum * gecici=(struct Dugum*) malloc(sizeof(struct Dugum*));
		    	gecici->derece = der;
		    	gecici->katSayi = kat;
		    	gecici->sonraki = ekleme;
				top = gecici;
				return;
			}
			else
			{
				ekleme=top;
				struct Dugum * iter=ekleme;
			  
				while(iter->sonraki!=NULL && iter->sonraki->derece > der )
				{
					iter=iter->sonraki;
			  	}
			  	
			  	struct Dugum * gecici=(struct Dugum*) malloc(sizeof(struct Dugum*));
				gecici->sonraki = iter->sonraki;
				iter->sonraki = gecici;
				gecici->derece = der;
				gecici->katSayi = kat;
				top = ekleme;
				
			}
		
		
	}
}


void Silme(int data){
	
	struct Dugum *onceki,*gecici = top;
	
	if(top == NULL)
	{
		printf("stack bos\n");
	}
	else
	{
		while(gecici->derece != data){
			onceki = gecici;
			gecici = gecici->sonraki;
		}
		
		if(gecici==top){
			top = gecici->sonraki;
			free(gecici);
		}
		else
		{
			onceki->sonraki = gecici->sonraki;
			free(gecici);
		}
		
	}
}


void Yazdirma(){

	
	if(top == NULL)
	{
		printf("Stack bos\n");
	}
	else
	{
	//Elemanlar yukardan asagi listelendikten sonra polinom seklinde yazdiriliyor
		struct Dugum *listele = top;
	
		while(listele->sonraki != NULL)
		{
			printf("%d ",listele->derece);
			printf(" %d\n",listele->katSayi);
			listele = listele->sonraki;
		}
		
		printf("%d ",listele->derece);
		printf(" %d\n\n",listele->katSayi);
	}



	if(top == NULL){
		printf("Stack bos\n");
	}
	else
	{
		struct Dugum *gecici = top;
		
		while(gecici != NULL){
			
			
			if(gecici->katSayi == 0){
				printf("0");
			}
			else if(gecici->katSayi == 1){
				printf("x");
				
			}
			else
			{
				printf("%dx",gecici->katSayi);
			}
			
			printf("^%d",gecici->derece);
			
			if(gecici->sonraki != NULL)
			{
				printf(" + ");
			}
				
			gecici = gecici->sonraki;
		}
		

	}
	
}


void Hesapla(int data){
	
	int hesaplama=0,drc,kts;
		
	if(top == NULL)
	{
		printf("Stack bos\n");
	}
	else
	{
		struct Dugum *gecici = top;
		while(gecici->sonraki != NULL){
			
				kts=gecici->katSayi;
				drc=gecici->derece;
				
				hesaplama +=  kts * pow(data,drc);
				
				gecici = gecici->sonraki;		
		}
		
			kts=gecici->katSayi;
			drc=gecici->derece;
			
			hesaplama +=  kts * pow(data,drc);	
		
			printf("\nson:%d\n",hesaplama);
		
	}

}


void TextYazma(){
	
	FILE *fp;
	
	fp = fopen ("liste.txt", "w");  
	
	if (fp == NULL) 
    { 
        fprintf(stderr, "\nYazma hatasi\n");  
    }
	
	if(top == NULL){
		printf("Stack bos\n");
	}
	else
	{
		struct Dugum *gecici = top;
	
		while(gecici->sonraki != NULL)
		{
						
			fprintf(fp," %d ",gecici->derece);
    		fprintf(fp," %d ",gecici->katSayi);
			
			gecici = gecici->sonraki;
		}
	
		fprintf(fp," %d ",gecici->derece);
    	fprintf(fp," %d ",gecici->katSayi);
    	printf("Elemanlar texte yazildi");
	}

	fclose (fp); 
}


int main(){

	int secim,deger,katsayi;

	while(1){
	
	printf("\n");
	printf("1-Ekleme\n");
	printf("2-Silme islemi\n");
	printf("3-Yazdirma\n");
	printf("4-Hesaplama\n");
	printf("5-Cikis islemi\n");

	
	printf("\nSecim yapiniz: ");
	scanf("%d",&secim);
	printf("\n");
	
		switch(secim)
		{

		case 1:
			printf("Eklemek istediginiz dereceyi giriniz  :");
			scanf("%d",&deger);
			printf("Eklemek istediginiz katsayiyi giriniz :");
			scanf("%d",&katsayi);
			Ekleme(deger,katsayi);
			break;
		case 2:
			printf("Bulup silinecek sayiyi giriniz");
			scanf("%d",&deger);
			Silme(deger);
			break;
		case 3:
			Yazdirma();
			break;
		case 4:
			printf("Hesaplanacak sayiyi giriniz");
			scanf("%d",&deger);
			Hesapla(deger);
			break;
		case 5:
			TextYazma();
			exit(0);
			break;

		}
	}
	
}



