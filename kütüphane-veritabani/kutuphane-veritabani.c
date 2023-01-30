#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ogrenci { 
	char ogrID[9];
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next;
	struct Ogrenci *prev;
}OGRENCI;
	
typedef struct Yazar { 
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}YAZAR;
	
typedef struct KitapOrnek { 
	char EtiketNo[20]; 
	char Durum[9]; 
	struct KitapOrnek *next; 
}KITAPORNEK;
	
typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[14]; 
	int adet;
	struct Kitap *next; 
	struct KitapOrnek *head; 
}KITAP;

typedef struct KitapYazar { 
	char ISBN[14]; 
	int YazarID;
}KITAPYAZAR;

typedef struct Tarih { 
	int gun:5;
	int ay:4; 
	int yil:12;
}TARIH;

typedef struct KitapOdunc { 
	char EtiketNo[20]; 
	char ogrID[9]; 
	int islemTipi:1; 
	struct Tarih islemTarihi;
}KITAPODUNC;

typedef struct kityaz{
	struct KitapYazar* data;
	struct kityaz* next;
}KITYAZ;

typedef struct OduncAlma{
	struct KitapOdunc* p;
	struct OduncAlma* next;
}ODUNCALMA;


//fonksiyonlar

void ogrenciEkle(OGRENCI** head);
void ogrenciListele(OGRENCI** head);
void ogrenciGoruntule(int secim, OGRENCI** head);
void splitDataOgrenci(OGRENCI* head, char buff[255], char delimeter[2]);
OGRENCI* dosyaOkumaOgrenci(char* file_name);
void ogrenciSil(OGRENCI** head);
void dosyaYazdirOgrenci(OGRENCI* head, char* file_name);
void guncellemeIslemi(int secim, OGRENCI* tmp);
void ogrenciGuncelle(OGRENCI**head);
KITAP* dosyaOkumaKitap(char* file_name_kit);
void splitDataKitap(KITAP* head, char buff[255], char delimeter[2]);
int kitapKarsilastirma(char* buff, KITAP* head);
YAZAR* dosyaOkumaYazar(char* file_name);
void splitDataYazar(YAZAR* yaz,char buff[255], char delimeter[2]);
void yazarEkle(YAZAR** head);
void dosyaYazdirYazar(YAZAR* head, char* file_name);
void yazarSil(YAZAR** head);
void yazarGuncelle(YAZAR**head);
void guncellemeIslemiYazar(int secim, YAZAR* tmp);
void raftakiKitaplar(KITAP** head);
void dosyaYazdirKitap(KITAP* head, char* file_name);
KITYAZ* dosyaOkumaKitapYazar(char* file_name_kit);
void kitapAdetleri(KITAP** head);
void splitDataKitapYazar(KITAPYAZAR* head, char buff[255], char delimeter[2]);
void dosyaYazdirKitapYazar(KITYAZ* head, char* file_name);
void kitapYazprint(KITYAZ* head,KITAP* head_kit, YAZAR* head_yaz);
void ISBN_kitap_bulma(KITAP* head, char* ISBN);
void yazar_bulma(YAZAR* head, int num);
ODUNCALMA* dosyaOkumaOdunc();
void splitDataOdunc(ODUNCALMA* head, char buff[255], char delimeter[2]);
void kitapOduncAlma(ODUNCALMA** h, KITAP** head);
void kitapOduncGuncel(KITAP**head, char etiket[20],char* str);
void yazarGoruntule(YAZAR** head);

int main (){
	int secim, kontrol=1;
	OGRENCI* head_ogrenci;
	KITAP* head_kitap;
	YAZAR* head_yazar;
	KITYAZ* head_kitapYaz;
	ODUNCALMA* head_odunc;
	int secim_2;//öðrenci bilgisi görüntülemede kullanýlýyor
	
	head_ogrenci=dosyaOkumaOgrenci("Ogrenciler.csv");
	head_kitap=dosyaOkumaKitap("Kitaplar.csv");
	kitapAdetleri(&head_kitap);
	head_yazar=dosyaOkumaYazar("Yazarlar.csv");
	head_kitapYaz=dosyaOkumaKitapYazar("KitapYazar.csv");
	head_odunc=dosyaOkumaOdunc();
	while(kontrol==1){
		printf("\n");
		printf("Ogrenci islemleri:\n");
		printf("\t1-Ogrenci ekle\n");
		printf("\t2-Ogrenci sil\n");
		printf("\t3-Ogrenci guncelle\n");
		printf("\t4-Ogrenci bilgisi goruntule\n");
		printf("\t5-Kitap teslim etmememis ogrencileri listele\n");
		printf("\t6-Cezali ogrencileri listele\n");
		printf("\t7-Tum ogrencileri listele\n");
		printf("\t8-Kitap odunc al\n");
		printf("\t9-Kitap teslim et\n");
		printf("Kitap islemleri:\n");
		printf("\t10-Kitap ekle\n");
		printf("\t11-Kitap sil\n");
		printf("\t12-Kitap guncelle\n");
		printf("\t13-Kitap bilgisi goruntule\n");
		printf("\t14-Raftaki kitaplari listele\n");
		printf("\t15-Zamaninda teslim edilmeyen kitaplari listele\n");
		printf("\t16-Kitap-Yazar eslestir\n");
		printf("\t17-Kitabin yazarini guncelle\n");
		printf("Yazar islemleri:\n");
		printf("\t18-Yazar ekle\n");
		printf("\t19-Yazar sil\n");
		printf("\t20-Yazar guncelle\n");
		printf("\t21-Yazar bilgisi goruntuleme\n");
		printf("\n\t22-programdan cikis\n");
		
		
		printf("\nyapmak istediginiz islemin numarasini giriniz:\n");
	scanf("%d", &secim);
	
	
	
	switch (secim){
		case 1:
			//öðrenci ekle
			ogrenciEkle(&head_ogrenci);
			dosyaYazdirOgrenci(head_ogrenci,"Ogrenciler.csv");
			break;
		case 2:
			//öðrenci sil
			ogrenciSil(&head_ogrenci);
			dosyaYazdirOgrenci(head_ogrenci,"Ogrenciler.csv");
			break;
		case 3:
			//öðrenci güncelle
			ogrenciGuncelle(&head_ogrenci);
			dosyaYazdirOgrenci(head_ogrenci,"Ogrenciler.csv");
			break;
		case 4:
			//bir öðrenci bilgisi görüntüle
			//ad-soyad ya da ID
			printf("Ogrenci bilgisini ad-soyad ile gorunulemek icin: 1\n ");
			printf("Ogrenci bilgisini ID numarasi ile gorunulemek icin: 2\n ");
			scanf("%d",&secim_2);
			ogrenciGoruntule(secim_2,&head_ogrenci);
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			//tüm öðrencileri listele
			ogrenciListele(&head_ogrenci);
			break;
		case 8:
			//kitap ödünç al
			kitapOduncAlma(&head_odunc, &head_kitap);//düzgün çalýþmýyor
			
			break;
		case 9: 
			break;
		case 10:
			//kitap ekle
			break;
		case 11:
			//kitap sil
			break;
		case 12:
			//kitap güncelle
			break;
		case 13:
			//kitap görüntüle
			break;
		case 14:
			//raftaki kitaplarý listele
			raftakiKitaplar(&head_kitap);
			break;
		case 15:
			break;
		case 16:
			//kitap yazar eþleþtir
			kitapYazprint(head_kitapYaz,head_kitap,head_yazar);
			break;
		case 17:
			break;
		case 18:
			//yazar ekle
			yazarEkle(&head_yazar);
			dosyaYazdirYazar(head_yazar,"Yazarlar.csv");
			break;
		case 19:
			//yazar sil
			yazarSil(&head_yazar);
			dosyaYazdirYazar(head_yazar,"Yazarlar.csv");
			break;
		case 20:
			//yazar güncelle
			yazarGuncelle(&head_yazar);
			dosyaYazdirYazar(head_yazar,"Yazarlar.csv");
			break;
		case 21:
			//yazar bilgisi görüntüle
			yazarGoruntule(&head_yazar);
			break;
		case 22:
			//programdan çýkmak için 22
			kontrol=0;
			break;
		default:
			printf("\ngirilen sayi menude bulunmuyor lutfen tekrar giriniz:\n");
	}
	
	}
	
	OGRENCI* tmp1;
	KITAP* tmp2;
	YAZAR* tmp3;
	KITYAZ* tmp4;
	ODUNCALMA* tmp5;

   while (head_ogrenci != NULL)
    {
       tmp1=head_ogrenci;
       head_ogrenci = head_ogrenci->next;
       free(tmp1);
    }
     while (head_kitap != NULL)
    {
    	tmp2=head_kitap;
       head_kitap = head_kitap->next;
       free(tmp2);
    }
     while (head_yazar != NULL)
    {
		tmp3=head_yazar;
       head_yazar = head_yazar->next;
       free(tmp3);
    }
     while (head_kitapYaz != NULL)
    {
		tmp4=head_kitapYaz;
       head_kitapYaz = head_kitapYaz->next;
       free(tmp4);
    }
     while (head_odunc != NULL)
    {
		tmp5=head_odunc;
       head_odunc = head_odunc->next;
       free(tmp5);
    }
    
	
	return 0;
}

void ogrenciEkle(OGRENCI** head){
	OGRENCI *tmp;
	tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp->next=NULL;
	tmp->prev=NULL;
	OGRENCI *yeni;
	yeni=(OGRENCI*)malloc(sizeof(OGRENCI));
	yeni->next=NULL;
	yeni->prev=NULL;
	
	if(tmp==NULL||yeni==NULL){
		return;
	}
	
	printf("sirasiyla ad, soyad, ID giriniz:\n");
	scanf("%s %s %s", yeni->ad, yeni->soyad, yeni->ogrID);
	yeni->puan=100;

	if(*head==NULL){
		yeni->next=NULL;
		yeni->prev=NULL;
		*head=yeni;
		
	}
	else {
		tmp=*head;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		yeni->next=NULL;
		yeni->prev=tmp;
		tmp->next=yeni;
		
	}
	
}

void ogrenciListele(OGRENCI** head){
	OGRENCI* tmp;
	tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp=*head;
	int count=1;
	if(tmp==NULL){
		printf("ögrenci kaydi yoktur!\n");
		
	}
	else{
		while(tmp!=NULL){
			printf("%d. ogrenci:\n", count);
			printf("\tad: %s\n",tmp->ad);
			printf("\tsoyad: %s\n",tmp->soyad);
			printf("\tnumara: %s\n",tmp->ogrID);
			printf("\tpuan: %d\n",tmp->puan);
			count++;
			tmp=tmp->next;
		}
		
	}
}

void ogrenciGoruntule(int secim, OGRENCI** head){
	OGRENCI *tmp;
	tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp->next=NULL;
	tmp->prev=NULL;
	tmp=*head;
	char isim[30];
	char soyisim[30];
	char ID[9];
	int cikis=1;
	
	if(secim==1){//ad-soyad
		
		printf("ogrencinin adini giriniz: ");
		scanf("%s", isim);
		
		printf("ogrencinin soyadini giriniz: ");
		scanf("%s", soyisim);
		
		
		while(cikis==1){
		 if(strcmp(isim,tmp->ad)||strcmp(soyisim,tmp->soyad)){
			if(tmp->next==NULL){
			cikis=0;
			printf("ogrenci bulunamadi!\n");
			}
			else{
				tmp=tmp->next;
			}
			
		}
		else{
			printf("ogrencinin:\n");
			printf("\tadi: %s\n",tmp->ad);
			printf("\tsoyadi: %s\n",tmp->soyad);
			printf("\tnumarasi: %s\n",tmp->ogrID);
			printf("\tpuani: %d\n",tmp->puan);
			cikis=0;
		}
		
		
		}
	}
	else if(secim==2){
		printf("ogrencinin ID'sini giriniz: ");
		scanf("%s", ID);
		
		while(cikis==1){
		 if(strcmp(ID,tmp->ogrID)){
			if(tmp->next==NULL){
			cikis=0;
			printf("ogrenci bulunamadi!\n");
			}
			else{
				tmp=tmp->next;
			}
			
		}
		else{
			printf("ogrencinin:\n");
			printf("\tadi: %s\n",tmp->ad);
			printf("\tsoyadi: %s\n",tmp->soyad);
			printf("\tnumarasi: %s\n",tmp->ogrID);
			printf("\tpuani: %d\n",tmp->puan);
			
			cikis=0;
		}
		
		
		}
	}
	else{
		printf("yanlis giris!\n");
	}
	
}


void ogrenciSil(OGRENCI** head){
	char ad[30];
	char soyad[30];
	int cikis=0;
	OGRENCI* tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI* prev=(OGRENCI*)malloc(sizeof(OGRENCI));
	OGRENCI* next=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp=*head;
	prev=NULL;
	next=tmp->next;
	printf("silmek istediginiz ogrencinin adi:\n"); 
	scanf("%s", ad);
	printf("silmek istediginiz ogrencinin soyadi:\n");
	scanf("%s", soyad);
	
	

	while(cikis==0){
		if(strcmp(ad, tmp->ad)||strcmp(soyad, tmp->soyad)){
			if(tmp->next!=NULL){
				prev=tmp;
				next=tmp->next->next;
				tmp=tmp->next;
			}
			else{
				printf("Ogrenci bulunamadi!\n");
				cikis=1;
			}
			
		}else{
			if(tmp->next!=NULL){
				prev->next=next;
				next->prev=prev;
			}else{
				prev->next=NULL;
			}
			printf("Ogrenci silinimstir\n");
			cikis=1;
			
		}
		
	}
	
}

void ogrenciGuncelle(OGRENCI**head){
	char ad[30], soyad[30];
	OGRENCI* tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	tmp=*head;
	int cikis=0,secim;
	printf("bilgilerini guncellemek istediginiz ogrencinin adi:\n");
	scanf("%s",ad);
	printf("bilgilerini guncellemek istediginiz ogrencinin soyadi:\n");
	scanf("%s",soyad);
	
	
		while(cikis==0){
		if(strcmp(ad, tmp->ad)||strcmp(soyad, tmp->soyad)){
			if(tmp->next!=NULL){
				tmp=tmp->next;
			}
			else{
				printf("Ogrenci bulunamadi!\n");
				cikis=1;
			}
			
		}else{
			printf("1-ad guncelleme\n2-soyad guncelleme\n3-ID guncelleme\n4-puan guncelleme\n5-guncelleme yapmak istemiyorum\nyapmak istediginiz islemi seciniz:\n");
			scanf("%d", &secim);
			
			guncellemeIslemi(secim,tmp);
			cikis=1;
		}
	}
	
	
	
}
void guncellemeIslemi(int secim, OGRENCI* tmp){
	
	switch(secim){
		case 1:
			printf("yeni adi giriniz:");
			scanf("%s", tmp->ad);
			break;
		case 2:
			printf("yeni soyadi giriniz:");
			scanf("%s", tmp->soyad);
			break;
		case 3:
			printf("yeni ID giriniz:");
			scanf("%s", tmp->ogrID);
			break;
		case 4:
			printf("yeni puani giriniz:");
			scanf("%d", &tmp->puan);
			break;	
		case 5:
			break;
		default:
			printf("yanlýs girdi!");
	}
	return;
}

OGRENCI* dosyaOkumaOgrenci(char* file_name){
	FILE* fp;
	fp=fopen(file_name, "r");
	char buff[255];
	
	OGRENCI* head =(OGRENCI*)malloc(sizeof(OGRENCI));
	
	if(head==NULL){
		return;
	}
	head->prev=NULL;
	OGRENCI* prev;
	OGRENCI* curr;
	if(fgets(buff, 255, fp)!=NULL){
		splitDataOgrenci(head, buff, ",");
	}else{
		return;
	}
	
	prev=head;
	while(fgets(buff, 255, fp)!=NULL){
		curr=(OGRENCI*)malloc(sizeof(OGRENCI));
		prev->next=curr;
		curr->prev=prev;
		
		splitDataOgrenci(curr,buff,",");
		prev=curr;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
	
}




void splitDataOgrenci(OGRENCI* head, char buff[255], char delimeter[2]){
	char* token;
	
	token=strtok(buff, delimeter);
	strcpy(head->ogrID, token);
	
	token=strtok(NULL, delimeter);
	strcpy(head->ad,token);
	
	token=strtok(NULL, delimeter);
	strcpy(head->soyad,token);
	
	token=strtok(NULL, delimeter);
	head->puan=atoi(token);
	
	
}
void dosyaYazdirOgrenci(OGRENCI* head, char* file_name){
	FILE* fp=fopen(file_name,"w");
	OGRENCI* tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	char buf[10];
	
	tmp=head;
	while(tmp!=NULL){
		fputs(tmp->ogrID,fp);
		fputc(',',fp);
		fputs(tmp->ad,fp);
		fputc(',',fp);
		fputs(tmp->soyad,fp);
		fputc(',',fp);
		itoa(tmp->puan,buf,10);
		fputs(buf,fp);
		fputc('\n',fp);
		tmp=tmp->next;
	}
	fclose(fp);
	return;
	
}

void kitapOduncAlma(ODUNCALMA** h, KITAP** head){
	char ID[10]; 
	char etiket[20];
	ODUNCALMA* yeni =(ODUNCALMA*)malloc(sizeof(ODUNCALMA));
	KITAPODUNC* k =(KITAPODUNC*)malloc(sizeof(KITAPODUNC));
	if(head==NULL||k==NULL){
		return;
	}
	printf("kitabi alacak ogrencinin numarasini giriniz:\n");
	scanf("%s",ID);
	raftakiKitaplar(head);
	printf("almak istediginiz kitabin etiket no'sunu giriniz:\n'");
	scanf("%s", etiket);
	printf("odunc alinan gunun tarihini gg.aa.yyyy olacak sekilde giriniz:\n");
	scanf("%d.%d.%d", k->islemTarihi.gun,k->islemTarihi.ay,k->islemTarihi.yil);
	
	strcpy(k->EtiketNo,etiket);
	strcpy(k->ogrID,ID);
	
	k->islemTipi=0;
	yeni->p=k;
	
	kitapOduncGuncel(head, etiket, ID);
	
}
void kitapOduncGuncel(KITAP**head, char etiket[20],char* str){
	KITAP* tmp=(KITAP*)malloc(sizeof(KITAP));
	KITAPORNEK* p=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
	tmp=*head;
	
	while(tmp!=NULL){
		p=tmp->head;
		while( p!=NULL){
			if(strcmp(etiket,p->EtiketNo)){
				p->next;
			}else{
				strcpy(p->Durum,str);
			}
		}
		
		tmp=tmp->next;
	}
	
}

ODUNCALMA* dosyaOkumaOdunc(){
	FILE* fp=fopen("KitapOdunc.csv","r");
	char buff[255];
	int kont;
	
	ODUNCALMA* head =(ODUNCALMA*)malloc(sizeof(ODUNCALMA));
	KITAPODUNC* k =(KITAPODUNC*)malloc(sizeof(KITAPODUNC));
	head->next=NULL;
	head->p=k;
	if(head==NULL||k==NULL){
		return;
	}

	if(fgets(buff, 255, fp)!=NULL){
		splitDataOdunc(head, buff, ",");
	}else{
		return;
	}
	ODUNCALMA* prev;
	prev=head;
	while(fgets(buff, 255, fp)!=NULL){
		ODUNCALMA* tmp =(ODUNCALMA*)malloc(sizeof(ODUNCALMA));
		KITAPODUNC* tmpk =(KITAPODUNC*)malloc(sizeof(KITAPODUNC));
		if(tmp==NULL||k==NULL){
		return;
		}
		
		tmp->p=tmpk;
		prev->next=tmp;
		splitDataOdunc(tmp,buff,",");		
		prev=tmp;
		
	}
	prev->next=NULL;
	fclose(fp);
	return head;
	
}
void splitDataOdunc(ODUNCALMA* head, char buff[255], char delimeter[2]){
	char* token;
	
	token=strtok(buff, delimeter);
	strcpy(head->p->EtiketNo, token);
	
	token=strtok(NULL, delimeter);
	strcpy(head->p->ogrID,token);
	
	token=strtok(NULL, delimeter);
	head->p->islemTipi=atoi(token);	
	
	token=strtok(NULL, ".");
	head->p->islemTarihi.gun=atoi(token);	
	
	token=strtok(NULL, ".");
	head->p->islemTarihi.ay=atoi(token);
	token=strtok(NULL, "\n");
	head->p->islemTarihi.yil=atoi(token);	
	
}


void kitapEkle(KITAP** head){
	KITAP *tmp;
	tmp=(KITAP*)malloc(sizeof(KITAP));
	tmp->next=NULL;
	KITAP *yeni;
	yeni=(KITAP*)malloc(sizeof(KITAP));
	yeni->next=NULL;
	
	if(tmp==NULL||yeni==NULL){
		return;
	}
	
	
	printf("sirasiyla kitap adi, ISBN no ve adet sayisi giriniz:\n");
	scanf("%s %s %s %d", yeni->kitapAdi, yeni->ISBN,&yeni->adet); 
	

	
	if(*head==NULL){
		yeni->next=NULL;
		*head=yeni;
		
	}
	else {
		tmp=*head;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		yeni->next=NULL;
		tmp->next=yeni;
		
	}
	
}

KITAP* dosyaOkumaKitap(char* file_name_kit){
	FILE* fp1;
	fp1=fopen(file_name_kit, "r");
	char buff[255];
	int kont;
	
	KITAP* head =(KITAP*)malloc(sizeof(KITAP));
	head->next=NULL;
	head->head=NULL;	
	if(head==NULL){
		return;
	}

	if(fgets(buff, 255, fp1)!=NULL){
		splitDataKitap(head, buff, ",");
	}else{
		return;
	}
	KITAP* prev;
	prev=head;
	while(fgets(buff, 255, fp1)!=NULL){
		KITAP* tmp =(KITAP*)malloc(sizeof(KITAP));
		if(tmp==NULL){
		return;
		}
		
		tmp->head=NULL; 
		prev->next=tmp;
		splitDataKitap(tmp,buff,",");		
		prev=tmp;
		
	}
	prev->next=NULL;
	fclose(fp1);
	return head;
	
}

void splitDataKitap(KITAP* head, char buff[255], char delimeter[2]){
	char* token;
	
	token=strtok(buff, delimeter);
	strcpy(head->kitapAdi, token);
	
	token=strtok(NULL, delimeter);
	strcpy(head->ISBN,token);
	
	token=strtok(NULL, delimeter);
	head->adet=atoi(token);
	
}




void kitapAdetleri(KITAP** head){
	KITAP* tmp=(KITAP*)malloc(sizeof(KITAP));
	tmp=*head;
	int i;
	char new_ISBN[20], say[4];
	
	while(tmp!=NULL){
		KITAPORNEK* prev=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
			tmp->head=prev;
				strcpy(new_ISBN,tmp->ISBN);
			strcat(new_ISBN,"_");
			itoa(1, say, 10);
			strcat(new_ISBN, say);
			strcpy(prev->EtiketNo,new_ISBN);
			strcpy(prev->Durum,"rafta");
			
			
		for(i=2;i<=tmp->adet;i++){
			KITAPORNEK* yeni=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
			strcpy(new_ISBN,tmp->ISBN);
			strcat(new_ISBN,"_");
			itoa(i, say, 10);
			strcat(new_ISBN, say);
			strcpy(yeni->EtiketNo,new_ISBN);
			strcpy(yeni->Durum,"rafta");
			prev->next=yeni;
			prev=yeni;
			
		}
		prev->next=NULL;
		tmp=tmp->next;
	}
		
	}
	
void raftakiKitaplar(KITAP** head){
	KITAP* tmp=(KITAP*)malloc(sizeof(KITAP));
	tmp=*head;
	KITAPORNEK* p=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
	printf("rafta olan kitaplar:\n");
	int k;
	while(tmp!=NULL){
		k=0;
		p=tmp->head;
		while(p!=NULL){
			if(strcmp(p->Durum,"rafta")==0){
				if(k==0){
					printf("\tkitap adi: %s\n", tmp->kitapAdi);
					printf("\t\trafta olan orenkleri:\n");
				}
				k++;
				printf("%s\n",p->EtiketNo);
			}
			p=p->next;
		}
		tmp=tmp->next;
	}
	
}


KITYAZ* dosyaOkumaKitapYazar(char* file_name_kit){
	FILE* fp1;
	fp1=fopen(file_name_kit, "r");
	char buff[255], buff2[255];
	int kont;
	
	KITYAZ* head =(KITYAZ*)malloc(sizeof(KITYAZ));
	KITAPYAZAR* p =(KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
	head->data=	p;
	if(head==NULL||p==NULL){
		return;
	}

	if(fgets(buff, 255, fp1)!=NULL){
		splitDataKitapYazar(p, buff, ",");
	}else{
		return;
	}
	KITYAZ* prev;
	head->data=p;
	prev=head;
	
	while(fgets(buff, 255, fp1)!=NULL){
		KITYAZ* tmpb =(KITYAZ*)malloc(sizeof(KITYAZ));
		KITAPYAZAR* tmp =(KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
		if(tmp==NULL||tmpb==NULL){
		return;
		}
		 
		prev->next=tmpb;
		splitDataKitapYazar(tmp,buff,",");	
		tmpb->data=tmp;
		prev=tmpb;
		
	}
	prev->next=NULL;
	fclose(fp1);
	return head;
	
}

void splitDataKitapYazar(KITAPYAZAR* head, char buff[255], char delimeter[2]){
	char* token;
	
	token=strtok(buff, delimeter);
	strcpy(head->ISBN, token);
	
	token=strtok(NULL, delimeter);
	head->YazarID=atoi(token);
	
}

	
void dosyaYazdirKitapYazar(KITYAZ* head, char* file_name){ 
	FILE* fp=fopen(file_name,"w");
	KITYAZ* tmp=(KITYAZ*)malloc(sizeof(KITYAZ));
	char buf[10];
	
	tmp=head;
	while(tmp!=NULL){
		fputs(tmp->data->ISBN,fp);
		fputc(',',fp);
		itoa(tmp->data->YazarID,buf,10);
		fputs(buf,fp);
		fputc('\n',fp);
		tmp=tmp->next;
	}
	fclose(fp);
	return;
	
}

void kitapYazprint(KITYAZ* head,KITAP* head_kit, YAZAR* head_yaz){
	KITYAZ* tmp=(KITYAZ*)malloc(sizeof(KITYAZ));
	KITAPYAZAR* p =(KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
	char str[20];
	if(tmp==NULL||p==NULL){
		return;
	}
	tmp->data=p;
	tmp=head;
	while(tmp!=NULL){
		ISBN_kitap_bulma(head_kit,tmp->data->ISBN);
		yazar_bulma(head_yaz,tmp->data->YazarID);
		tmp=tmp->next;
	}
	
	
}
void ISBN_kitap_bulma(KITAP* head, char* ISBN){
	KITAP*tmp= (KITAP*)malloc(sizeof(KITAP));
	tmp=head;
	int cikis=0;
	char str[20];
	if(tmp==NULL){
		return;
	}
	
	while(tmp!=NULL&&cikis==0){
		if(strcmp(tmp->ISBN, ISBN)){
			tmp=tmp->next;
		}else{
			cikis=1;
			printf("%s,", tmp->kitapAdi);
		}
		
	}
	return;
}

void yazar_bulma(YAZAR* head, int num){
	YAZAR* tmp=(YAZAR*)malloc(sizeof(YAZAR));
	tmp=head;
	int cikis=0;
	if(tmp==NULL){
		return;
	}
		while(tmp!=NULL&&cikis==0){
		if(tmp->yazarID!=num){
			tmp=tmp->next;
		}else{
			cikis=1;
			printf("%s %s\n", tmp->yazarAd, tmp->yazarSoyad);
		}
		
	}
	
}

YAZAR* dosyaOkumaYazar(char* file_name){
	FILE* fp;
	fp=fopen(file_name, "r");
	char buff[255];
	
	YAZAR* head =(YAZAR*)malloc(sizeof(YAZAR));
	
	if(head==NULL){
		return;
	}
	YAZAR* prev;
	YAZAR* curr;
	if(fgets(buff, 255, fp)!=NULL){
		splitDataYazar(head, buff, ",");
	}else{
		return;
	}
	
	prev=head;
	while(fgets(buff, 255, fp)!=NULL){
		curr=(YAZAR*)malloc(sizeof(YAZAR));
		prev->next=curr;
		
		splitDataYazar(curr,buff,",");
		prev=curr;
	}
	prev->next=NULL;
	fclose(fp);
	return head;
	
}

void splitDataYazar(YAZAR* yaz,char buff[255], char delimeter[2]){
	char* token;
	
	token=strtok(buff, delimeter);
	yaz->yazarID=atoi(token);
	
	token=strtok(NULL, delimeter);
	strcpy(yaz->yazarAd,token);
	
	token=strtok(NULL, "\n");
	strcpy(yaz->yazarSoyad,token);
}

void yazarEkle(YAZAR** head){
	YAZAR *tmp;
	tmp=(YAZAR*)malloc(sizeof(YAZAR));
	tmp->next=NULL;
	YAZAR *yeni;
	yeni=(YAZAR*)malloc(sizeof(YAZAR));
	yeni->next=NULL;
	int sayi=0;
	if(tmp==NULL||yeni==NULL){
		return;
	}
	
	printf("sirasiyla ad, soyad giriniz:\n");
	scanf("%s %s", yeni->yazarAd, yeni->yazarSoyad);
	
	
	if(*head==NULL){
		yeni->next=NULL;
		yeni->yazarID=1;
		*head=yeni;
		
	}
	else {
		tmp=*head;
		while(tmp->next!=NULL){
			tmp=tmp->next;
			sayi++;
		}
		sayi++;
		yeni->yazarID=sayi+1;
		yeni->next=NULL;
		tmp->next=yeni;
		
	}
	
}

void dosyaYazdirYazar(YAZAR* head, char* file_name){
	FILE* fp=fopen(file_name,"w");
	YAZAR* tmp=(YAZAR*)malloc(sizeof(YAZAR));
	char buf[10];
	
	tmp=head;
	while(tmp!=NULL){
		itoa(tmp->yazarID,buf,10);
		fputs(buf,fp);
		fputc(',',fp);
		fputs(tmp->yazarAd,fp);
		fputc(',',fp);
		fputs(tmp->yazarSoyad,fp);
		fputc('\n',fp);
		tmp=tmp->next;
	}
	fclose(fp);
	return;
	
}

void yazarSil(YAZAR** head){
	char ad[30];
	char soyad[30];
	int cikis=0;
	YAZAR* tmp=(YAZAR*)malloc(sizeof(YAZAR));
	YAZAR* prev=(YAZAR*)malloc(sizeof(YAZAR));
	YAZAR* next=(YAZAR*)malloc(sizeof(YAZAR));
	tmp=*head;
	prev=NULL;
	next=tmp->next;
	printf("silmek istediginiz yazarin adi:\n");
	scanf("%s", ad);
	printf("silmek istediginiz yazarin soyadi:\n");
	scanf("%s", soyad);
	
	

	while(cikis==0){
		if(strcmp(ad, tmp->yazarAd)||strcmp(soyad, tmp->yazarSoyad)){
			if(tmp->next!=NULL){
				prev=tmp;
				next=tmp->next->next;
				tmp=tmp->next;
			}
			else{
				printf("Yazar bulunamadi!\n");
				cikis=1;
			}
			
		}else{
			if(tmp->next!=NULL){
				prev->next=next;
				while(tmp->next!=NULL){
					tmp->next->yazarID--;
					tmp=tmp->next;
				}
			}else{
				prev->next=NULL;
			}
			printf("Yazar silinimstir\n");
			cikis=1;
			
		}
		
	}
	
}

void yazarGuncelle(YAZAR**head){
	char ad[30], soyad[30];
	YAZAR* tmp=(YAZAR*)malloc(sizeof(YAZAR));
	tmp=*head;
	int cikis=0,secim;
	printf("bilgilerini guncellemek istediginiz yazarin adi:\n");
	scanf("%s",ad);
	printf("bilgilerini guncellemek istediginiz yazarin soyadi:\n");
	scanf("%s",soyad);
	
	
		while(cikis==0){
		if(strcmp(ad, tmp->yazarAd)||strcmp(soyad, tmp->yazarSoyad)){
			if(tmp->next!=NULL){
				tmp=tmp->next;
			}
			else{
				printf("Yazar bulunamadi!\n");
				cikis=1;
			}
			
		}else{
			printf("1-ad guncelleme\n2-soyad guncelleme\n3-guncelleme yapmak istemiyorum\nyapmak istediginiz islemi seciniz:\n");
			scanf("%d", &secim);
			
			guncellemeIslemiYazar(secim,tmp);
			cikis=1;
		}
	}
	
	
	
}
void guncellemeIslemiYazar(int secim, YAZAR* tmp){
	
	switch(secim){
		case 1:
			printf("yeni adi giriniz:");
			scanf("%s", tmp->yazarAd);
			break;
		case 2:
			printf("yeni soyadi giriniz:");
			scanf("%s", tmp->yazarSoyad);
			break;
		case 3:
			
			break;	
		default:
			printf("yanlýs girdi!");
	}
	return;
}
void yazarGoruntule(YAZAR** head){
	YAZAR *tmp;
	tmp=(YAZAR*)malloc(sizeof(YAZAR));
	tmp=*head;
	char isim[30];
	char soyisim[30];
	char ID[9];
	int cikis=0;
	
		printf("yazarin adini giriniz: ");
		scanf("%s", isim);
		
		printf("yazarin soyadini giriniz: ");
		scanf("%s", soyisim);
		
		
		while(cikis==0){
		 	if(strcmp(isim,tmp->yazarAd)||strcmp(soyisim,tmp->yazarSoyad)){
				if(tmp->next==NULL){
				cikis=0;
				printf("yazar bulunamadi!\n");
				}
				else{
					tmp=tmp->next;
				}
			
			}
			else{
				printf("yazarin:\n");
				printf("\tadi: %s\n",tmp->yazarAd);
				printf("\tsoyadi: %s\n",tmp->yazarSoyad);
				printf("\tID: %d\n",tmp->yazarID);

				cikis=1;
			}
			
		
		
		}
	
	}
	

