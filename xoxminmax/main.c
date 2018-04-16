#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Hareket{
    int satir,sutun;
}eniyi_hareket_bulma();

char oyuncu='X', karsitaraf='O';

int tahta_kontrol(char tahta[3][3]){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(tahta[i][j]=='-')
                return 1;
        }
    }
    return 0;
}
int degerlendirme (char tahta[3][3],int derinlik){
    int i,j;
    /// satir icin X ve O icin degerlendirme
    for(i=0;i<3;i++){
        if(tahta[i][0]==tahta[i][1] && tahta[i][1]==tahta[i][2]){
            if (tahta[i][i]==oyuncu)
                return +10-derinlik;
            else if (tahta[i][i]==karsitaraf)
                return derinlik-10;
        }
    }
    /// sutun icin X ve O icin degerlendirme
    for(i=0;i<3;i++){
        if(tahta[0][i]==tahta[1][i] && tahta[1][i]==tahta[2][i]){
            if (tahta[i][i] == oyuncu)
                return +10-derinlik;
            else if (tahta[i][i] == karsitaraf)
                return derinlik-10;
        }
    }
    ///diagonal icin (capraz) X ve O icin degerlendirme
    if(tahta[0][0] == tahta[1][1] && tahta[1][1] == tahta[2][2]){
        if(tahta[0][0] == oyuncu)
            return +10-derinlik;
        else if (tahta[0][0] == karsitaraf)
            return derinlik-10;
    }

    if(tahta[0][2] == tahta[1][1] && tahta[1][1] == tahta[2][0]){
        if(tahta[0][2] == oyuncu)
            return +10-derinlik;
        else if(tahta[0][2] == karsitaraf)
            return derinlik-10;
    }
    /// kazanan hic yoksa 0 dondur.
    return 0;
}

int minmax(char tahta[3][3],int derinlik, int max_mi){

    int i,j;


    int temp;
    /// sýfýrdan farklýysa oyun bitmis anlaminda
    int skor = degerlendirme(tahta,derinlik);


    ///maksimize oyuncusu kazanmistir.Yani biz
    if(skor == 10-derinlik)
        return skor;
    /// minimize oyuncusu kazanmistir.Yani PC
    if(skor == derinlik-10)
        return skor;

    /// tahtada bos kare kalmamistir ve berabere sonuclanmistir.
    if(tahta_kontrol(tahta) == 0)
        return 0;

    if(max_mi == 1){

        int en_max = -1000;/// Kullznici icin max hamleyi secer.
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(tahta[i][j] == '-'){
                    tahta[i][j] = oyuncu;
                    temp = minmax(tahta,derinlik+1,0);
                    if(en_max < temp)
                        en_max = temp;
                    tahta[i][j] = '-';
                }
            }

        }
    return en_max;
    }else{
        int en_min= 1000;///Pc icin minimum hamleyi alacak
        ///Pc icin en iyi hamleyi secer
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(tahta[i][j] == '-'){
                    tahta[i][j] = karsitaraf;
                    temp = minmax(tahta,derinlik+1,1);
                    if(en_min > temp)
                        en_min = temp;
                    tahta[i][j] = '-';
                }
            }
        }
        return en_min;
    }
}

struct Hareket eniyi_hareket_bulma(char tahta[3][3]){

    int i,j;
    int en_min = 1000;
    struct Hareket eniyi_hareket;
    eniyi_hareket.satir = -1;
    eniyi_hareket.sutun = -1;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if (tahta[i][j] == '-'){
                tahta[i][j] = karsitaraf;
                int hareket_degeri = minmax(tahta,0,1);
                tahta[i][j] = '-';
                if(hareket_degeri < en_min){
                    eniyi_hareket.satir = i;
                    eniyi_hareket.sutun = j;
                    en_min = hareket_degeri;

                }
            }

        }
    }
    return eniyi_hareket;
}

void goruntule(char tahta[3][3]){
    printf("\t\t\tT I C   T A C   T O E\n");
     printf("\n\t\tSutun:   0    |   1   |   2    ");
    printf("\n\t\tSatir:   --------------------\n");
    printf("\n\t\t0\t   %c  |   %c   |   %c   ",tahta[0][0],tahta[0][1],tahta[0][2]);
    printf("\n\t\t\t------|-------|-------");
    printf("\n\t\t1\t   %c  |   %c   |   %c   ",tahta[1][0],tahta[1][1],tahta[1][2]);
    printf("\n\t\t\t------|-------|-------");
    printf("\n\t\t2\t   %c  |   %c   |   %c   ",tahta[2][0],tahta[2][1],tahta[2][2]);
    printf("\n\t\t\t------|-------|-------");
}

int yazma_kontrol(char tahta[3][3], int satir, int sutun){
    if(tahta[satir][sutun]=='-')
        return 1;
    else
        return 0;

}
int ss_kontrol(int satir_or_sutun){
    if(satir_or_sutun < 3 && -1<satir_or_sutun)
        return 1;
    else
        return 0;
}

int rastgele_uretme(){
    int sayi;
    srand(time(NULL));
    sayi=1+rand()%4;
    return sayi;
}

int main()
{
    char tahta[3][3] =
	{
		{ '-', '-', '-' },
		{ '-', '-', '-' },
		{ '-', '-', '-' }
	};
	int derinlik=0;
	int baslama,kazanan,bos_varmi;
	int oyuncu_satir,oyuncu_sutun,kontrol,pc_baslama;
	struct Hareket pc_hamlesi;
	goruntule(tahta);
	printf("\nOyunu ilk siz oynamak istiyorsaniz 1\'e, istemiyorsaniz 0\'a basiniz: ");
	scanf("%d",&baslama);
	if(baslama == 1){

        devam:
        sira_oyuncuda:
        system("cls");
        goruntule(tahta);
        do{
        do{
            printf("\nSatir giriniz : ");
            scanf("%d",&oyuncu_satir);
            kontrol = ss_kontrol(oyuncu_satir);
        }while(kontrol!=1);

        do{
            printf("\nSutun_giriniz : ");
            scanf("%d",&oyuncu_sutun);
            kontrol = ss_kontrol(oyuncu_sutun);
        }while(kontrol!=1);

        kontrol = yazma_kontrol(tahta,oyuncu_satir,oyuncu_sutun);
        }while(kontrol!=1);

        tahta[oyuncu_satir][oyuncu_sutun] = oyuncu;
        goruntule(tahta);
        system("cls");
        kazanan = degerlendirme(tahta,derinlik);
        bos_varmi = tahta_kontrol(tahta);
        if(kazanan == 10-derinlik){
            printf("\n\t\tTebrikler Kazandiniz .");
        }
        else if(kazanan == 0 && bos_varmi == 0){
            printf("\n\t\tBerabere");
        }else {
            derinlik++;
            pc_hamlesi = eniyi_hareket_bulma(tahta);
            tahta[pc_hamlesi.satir][pc_hamlesi.sutun] = karsitaraf;
            goruntule(tahta);
            kazanan = degerlendirme(tahta,derinlik);
            bos_varmi = tahta_kontrol(tahta);
            if(kazanan == derinlik- 10){
                printf("\n\t\tKaybettiniz.");
            }
            else if(kazanan == 0 && bos_varmi == 0){
                printf("\n\t\tBerabere");
            }else{
            goto devam;
            }
        }
	}
	else{
        pc_baslama = rastgele_uretme();
        if(pc_baslama == 1){
            tahta[0][0] = karsitaraf;
            goruntule(tahta);
        }else if(pc_baslama == 2){
            tahta[0][2] = karsitaraf;
            goruntule(tahta);
        }else if(pc_baslama == 3){
            tahta[2][0] = karsitaraf;
            goruntule(tahta);
        }else if(pc_baslama == 4){
            tahta[2][2] = karsitaraf;
            goruntule(tahta);
        }
        goto sira_oyuncuda;
	}

    return 0;
}
