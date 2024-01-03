#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void oku()
{
    FILE * dosya;
    FILE * file;
    int i=0,j=0;
    char ch;
    int sayac=0,sayac2=0,boyut=0;
    char dizi[160054];

    dosya=fopen("okunan.txt","r");//orjinal dosya
    file=fopen("yazilan.txt","w");//sıkıştırılmış dosya

    if(dosya==NULL)
    {
        printf("dosya okunamadi!!!");
    }
    else
    {
        while(!feof(dosya))//dosyanın sonuna kadar okuma islemi
        {
            fseek(dosya,0,SEEK_CUR);//dosyanin imlecini ayarlamak için
            ch=getc(dosya);
            dizi[i]=ch;
            i++;
            boyut++;

            if(boyut==160054)//her bir satýrda 78 karakter olduðu için 78'in katý olan bir deðer aldým
            {
                for(i=12; i<=boyut; i++)//her bir karakteri dolaþmak için
                {

                    if(dizi[i]==dizi[i+79])//datalar karþýlaþtýrýlýyor
                    {
                        sayac++;
                        if(sayac==64)//koþul saðlanýrsa satýrlar eþit demek
                        {
                            i=i+15;//bir sonraki satýra geçmek için
                            sayac=0;
                            sayac2++;//kaç tane eþit olan satýr var onu bulmak için
                        }

                    }
                    else
                    {
                        if(sayac2!=0)//koþul saðlanýrsa demekki eþit olan satýrlar var
                        {
                            for(j=i-(sayac2*79)-sayac-12;j<=i-(sayac2*79)+65-sayac;j++)//eþit olan satýrlarýn sadece ilk olanýný yazdýrmak için
                            {
                                 fseek(file,0,SEEK_CUR);
                                 fprintf(file,"%c",dizi[j]);
                            }
                            sayac2=0;

                            i=i+78-sayac;//bir sonraki satýra geçmek için

                            goto git;//eðer bu if bloðu çalýþýrsa alt taraftaki for çalýþmamalý
                        }
                        for(j=i-12-sayac; j<=i+65-sayac; j++)//satýrlar eþit deðilse satýrlarý yazdýrmak için
                        {
                            fseek(file,0,SEEK_CUR);
                            fprintf(file,"%c",dizi[j]);
                        }
                        i=i+78-sayac;
                        git:
                        fprintf(file,"\n");
                        sayac=0;
                    }


                }
                i=0;
                boyut=0;

            }


        }
        //dosyada kalan en son karakterleri yazdýrmak için bütün iþlemleri tekrarlýyoruz
        for(i=12; i<=boyut; i++)
                {

                    if(dizi[i]==dizi[i+79])
                    {
                        sayac++;
                        if(sayac==64)
                        {
                            i=i+15;
                            sayac=0;
                            sayac2++;

                        }
                    }
                    else
                    {
                        if(sayac2!=0)
                        {
                            for(j=i-(sayac2*79)-sayac-12;j<=i-(sayac2*79)+65-sayac;j++)
                            {
                                 fseek(file,0,SEEK_CUR);
                                 fprintf(file,"%c",dizi[j]);
                            }
                            sayac2=0;

                            i=i+78-sayac;

                            goto git2;
                        }
                        for(j=i-12-sayac; j<=i+65-sayac; j++)
                        {
                            fseek(file,0,SEEK_CUR);
                            fprintf(file,"%c",dizi[j]);
                        }
                        i=i+78-sayac;
                        git2:
                        fprintf(file,"\n");
                        sayac=0;
                    }


                }


    }
    fclose(dosya);
    fclose(file);

}




int main()
{
    oku();

    return 0;
}

