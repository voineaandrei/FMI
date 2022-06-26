#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void XORSHIFT32(unsigned int seed, unsigned int lungime, unsigned int** v)
{
    int i;
    *v=(unsigned *)(malloc(sizeof(int)*lungime));
    (*v)[0]=seed;
    for (i=1; i<lungime; i++)
    {
        seed=seed^seed<<13;
        seed=seed^seed>>17;
        seed=seed^seed<<5;
        (*v)[i]=seed;
    }
}

void liniarizare (char *nume, unsigned char **v)
{
    FILE *f;
    f=fopen(nume,"rb");
    unsigned int W,H;
    fseek(f,18,SEEK_SET);
    fread(&W,4,1,f);
    fread(&H,4,1,f);
    fseek(f,54,SEEK_SET);

    unsigned padding=0;
    if ((3*W)%4!=0)
        padding=4-((3*W)%4);

    *v=(char *)(malloc(3*W*H));
    unsigned i,j;
    unsigned char c[3];
    for (i=H-1; i>=0 && i<=H-1; i--)
    {
        for (j=0; j<3*W; j=j+3)
        {
            fread(&c,3,1,f);
            (*v)[i*3*W+j]=c[2];
            (*v)[i*3*W+j+1]=c[1];
            (*v)[i*3*W+j+2]=c[0];
        }
        fseek(f,padding,SEEK_CUR);
    }
    fclose(f);
}

void MemorieExternaLiniarizare(char *sursa, char *destinatie, unsigned char *v)
{
    FILE *f,*g;
    f=fopen(sursa,"rb");
    g=fopen(destinatie,"wb");
    char s[54];
    fread(&s,54,1,f);
    fwrite(&s,54,1,g);

    unsigned W,H;
    fseek(f,18,SEEK_SET);
    fread(&W,4,1,f);
    fread(&H,4,1,f);
    fclose(f);

    unsigned padding=0;
    if ((3*W)%4!=0)
        padding=4-((3*W)%4);

    unsigned i,j;
    unsigned int m=0;
    for (i=H-1; i>=0 && i<=H-1; i--)
    {
        for (j=0; j<W*3; j+=3)
        {
            fwrite(&v[i*W*3+j+2],1,1,g);
            fwrite(&v[i*W*3+j+1],1,1,g);
            fwrite(&v[i*W*3+j],1,1,g);
        }
        fwrite(&m,padding,1,g);
    }
    fclose(g);
}

void criptare_poza(char *sursa, char *destinatie, char *secretkey)
{
    FILE *f;
    unsigned width,height;
    f=fopen(sursa,"rb");
    if (f==NULL)
    {
        printf("eroare la deschiderea fisierului");
        return;
    }
    fseek(f,18,SEEK_SET);
    fread(&width,4,1,f);
    fread(&height,4,1,f);
    fclose(f);

    // secret_key + nr random
    unsigned int *R;
    f=fopen(secretkey,"r");
    if (f==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        return;
    }
    unsigned R0,SV;
    fscanf(f,"%u %u",&R0,&SV);
    fclose(f);
    XORSHIFT32(R0,2*width*height,&R);
    // <-

    unsigned char *P1,*P2;
    liniarizare(sursa,&P1);

    // permutare
    unsigned i,j;
    unsigned int *permutare=(unsigned *)(malloc(sizeof(unsigned)*(width*height)));
    for (i=0; i<width*height; i++)
        permutare[i]=i;
    unsigned aux;
    for (i=1; i<width*height; i++)
    {
        aux=permutare[width*height-i];
        permutare[width*height-i]=permutare[R[i]%(width*height-i+1)];
        permutare[R[i]%(width*height-i+1)]=aux;
    }
    P2=(char *)(malloc(3*width*height));
    for (i=0; i<width*height; i++)
    {
        P2[3*permutare[i]]=P1[3*i];
        P2[3*permutare[i]+1]=P1[3*i+1];
        P2[3*permutare[i]+2]=P1[3*i+2];
    }
    // <-
// poza permutata
//MemorieExternaLiniarizare(sursa,"pozaPERMUTATA2.bmp",P2);
    // criptare
    unsigned char *C=(char *)(malloc(3*width*height));
    unsigned int m;
    ///   PR;PG;PB;
    ///X3;X2;X1;X0;
    for (i=0; i<3; i++)
    {
        m=255<<(i*8);
        m=SV&m;
        m=m>>(i*8);
        C[2-i]=m^P2[2-i];
        m=255<<(i*8);
        m=R[width*height]&m;
        m=m>>(i*8);
        C[2-i]=C[2-i]^m;
    }
    unsigned int k;
    for (i=width*height+1; i<2*width*height; i++)
    {
        k=3*(i-width*height);
        for (j=0; j<3; j++)
        {
            C[k+(2-j)]=C[k-3+(2-j)]^P2[k+(2-j)];
            m=255<<(j*8);
            m=R[i]&m;
            m=m>>(j*8);
            C[k+(2-j)]=C[k+(2-j)]^m;
        }
    }
    MemorieExternaLiniarizare(sursa,destinatie,C);
    free(R);
    free(P1);
    free(P2);
    free(C);
    free(permutare);
}

void decriptare_poza(char *criptare, char *decriptare, char *secretkey)
{
    FILE *f;
    unsigned width,height;
    f=fopen(criptare,"rb");
    if (f==NULL)
    {
        printf("eroare la deschiderea fisierului");
        return;
    }
    fseek(f,18,SEEK_SET);
    fread(&width,4,1,f);
    fread(&height,4,1,f);
    fclose(f);

    // secret_key + nr random
    unsigned int *R;
    f=fopen(secretkey,"r");
    if (f==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        return;
    }
    unsigned R0,SV;
    fscanf(f,"%u %u",&R0,&SV);
    fclose(f);
    XORSHIFT32(R0,2*width*height,&R);
    // <-

    unsigned i,j;
    unsigned int *permutare=(unsigned *)(malloc(sizeof(unsigned)*(width*height)));
    for (i=0; i<width*height; i++)
        permutare[i]=i;
    unsigned aux;
    for (i=1; i<width*height; i++)
    {
        aux=permutare[width*height-i];
        permutare[width*height-i]=permutare[R[i]%(width*height-i+1)];
        permutare[R[i]%(width*height-i+1)]=aux;
    }
    unsigned int *permutareinv=(unsigned *)(malloc(sizeof(unsigned int)*width*height));
    for (i=0; i<width*height; i++)
        permutareinv[permutare[i]]=i;

    unsigned char *C;
    liniarizare(criptare,&C);
    unsigned char *C2=(unsigned char *)(malloc(3*width*height));
    unsigned m,k;
    for (i=0; i<3; i++)
    {
        m=255<<(i*8);
        m=SV&m;
        m=m>>(i*8);
        C2[2-i]=C[2-i]^m;
        m=255<<(i*8);
        m=R[width*height]&m;
        m=m>>(i*8);
        C2[2-i]=C2[2-i]^m;
    }
    for (i=width*height+1; i<2*width*height; i++)
    {
        k=3*(i-width*height);
        for (j=0; j<3; j++)
        {
            C2[k+(2-j)]=C[k-3+(2-j)]^C[k+(2-j)];
            m=255<<(j*8);
            m=m&R[i];
            m=m>>(j*8);
            C2[k+(2-j)]=C2[k+(2-j)]^m;
        }
    }
    unsigned char *D=(unsigned char *)(malloc(3*width*height));
    for (i=0; i<width*height; i++)
    {
        D[3*permutareinv[i]]=C2[3*i];
        D[3*permutareinv[i]+1]=C2[3*i+1];
        D[3*permutareinv[i]+2]=C2[3*i+2];
    }
    MemorieExternaLiniarizare(criptare,decriptare,D);
    free(R);
    free(C);
    free(C2);
    free(D);
    free(permutare);
    free(permutareinv);
}

void chitest(char *sursa)
{
    FILE *f;
    f=fopen(sursa,"rb");
    if (f==NULL)
    {
        printf("eroare la deschiderea fisierului");
        return;
    }
    unsigned int width,height;
    fseek(f,18,SEEK_SET);
    fread(&width,4,1,f);
    fread(&height,4,1,f);
    unsigned char *IMG;
    liniarizare(sursa,&IMG);
    fseek(f,54,SEEK_SET);
    unsigned int red[256]= {0},green[256]= {0},blue[256]= {0},i;
    for (i=0; i<width*height*3; i+=3)
    {
        red[IMG[i]]++;
        green[IMG[i+1]]++;
        blue[IMG[i+2]]++;
    }
    double fprim=0,ChiR=0,ChiG=0,ChiB=0;
    fprim=(width*height)/256;
    for (i=0; i<=255; i++)
    {
        ChiR=ChiR+((red[i]-fprim)*(red[i]-fprim)/fprim);
        ChiB=ChiB+((blue[i]-fprim)*(blue[i]-fprim)/fprim);
        ChiG=ChiG+((green[i]-fprim)*(green[i]-fprim)/fprim);
    }
    printf("Chi-squared test on RGB channels for: %s\n", sursa);
    printf("R: %.2f\n",ChiR);
    printf("G: %.2f\n",ChiG);
    printf("B: %.2f\n",ChiB);
    free(IMG);
}

typedef struct
{
    double corr;
    unsigned int x,y,height,width;
    char culoare[3];
} Punct;

int comparator(const void *c1, const void *c2)
{
    Punct *a = ((Punct*)c1);
    Punct *b = ((Punct*)c2);
    if (b->corr > a->corr)
        return 1;
    return -1;
}

void liniarizare_Matrice (char *nume, unsigned char ***v)
{
    FILE *f;
    f=fopen(nume,"rb");
    if (f==NULL)
    {
        printf("eroare la deschiderea fisierului");
        return;
    }
    unsigned int W,H;
    fseek(f,18,SEEK_SET);
    fread(&W,4,1,f);
    fread(&H,4,1,f);
    fseek(f,54,SEEK_SET);

    unsigned padding=0;
    if ((3*W)%4!=0)
        padding=4-((3*W)%4);

    *v=(unsigned int **)(malloc(sizeof(unsigned int)*H));
    unsigned i,j;
    unsigned char c[3];
    for (i=H-1; i>=0 && i<=H-1; i--)
    {
        (*v)[i]=(unsigned char *)(malloc(3*W));
        for (j=0; j<3*W; j=j+3)
        {
            fread(&c,3,1,f);
            (*v)[i][j]=c[2];
            (*v)[i][j+1]=c[1];
            (*v)[i][j+2]=c[0];
        }
        fseek(f,padding,SEEK_CUR);
    }
    fclose(f);
}

void MemorieExternaLiniarizare_Matrice(char *sursa, char *destinatie, unsigned char **v)
{
    FILE *f,*g;
    f=fopen(sursa,"rb");
    if (f==NULL)
    {
        printf("eroare la deschiderea fisierului sursa");
        return;
    }
    g=fopen(destinatie,"wb");
    if (g==NULL)
    {
        printf("eroare la deschiderea fisierului destinatie");
        return;
    }
    char s[54];
    fread(&s,54,1,f);
    fwrite(&s,54,1,g);

    unsigned W,H;
    fseek(f,18,SEEK_SET);
    fread(&W,4,1,f);
    fread(&H,4,1,f);
    fclose(f);

    unsigned padding=0;
    if ((3*W)%4!=0)
        padding=4-((3*W)%4);

    unsigned i,j;
    unsigned int m=0;
    for (i=H-1; i>=0 && i<=H-1; i--)
    {
        for (j=0; j<W*3; j+=3)
        {
            fwrite(&v[i][j+2],1,1,g);
            fwrite(&v[i][j+1],1,1,g);
            fwrite(&v[i][j],1,1,g);
        }
        fwrite(&m,padding,1,g);
    }
    fclose(g);
}

void gray_img(char *nume, char ***v)
{
    FILE *f;
    f=fopen(nume,"rb");
    if (f==NULL)
    {
        printf("EROARE LA DESCHIDEREA FISIERULUI\n");
        return;
    }

    unsigned int W,H;
    fseek(f,18,SEEK_SET);
    fread(&W,4,1,f);
    fread(&H,4,1,f);
    fseek(f,54,SEEK_SET);

    unsigned padding=0;
    if ((3*W)%4!=0)
        padding=4-((3*W)%4);

    *v=(unsigned int **)(malloc(sizeof(unsigned int)*H));
    int i,j;
    unsigned char c[3],aux;
    for (i=H-1; i>=0 && i<=H-1; i--)
    {
        (*v)[i]=(unsigned char *)(malloc(sizeof(char)*3*W));
        for (j=0; j<3*W; j+=3)
        {
            fread(&c,3,1,f);
            aux = 0.299*c[2] + 0.587*c[1] + 0.114*c[0];
            (*v)[i][j]=aux;
            (*v)[i][j+1]=aux;
            (*v)[i][j+2]=aux;
        }
        fseek(f,padding,SEEK_CUR);
    }
    fclose(f);
}

void template_matching (char *nume_imagine, char *nume_sablon, double prag, Punct **FPunct, unsigned *lung, unsigned char COLOR[])
{
    unsigned char **mat_img, **mat_sab;
    gray_img(nume_imagine,&mat_img);
    gray_img(nume_sablon,&mat_sab);
    unsigned int inaltime_imagine,inaltime_sablon,latime_imagine,latime_sablon;
    FILE *f=fopen(nume_imagine,"rb");
    if (f==NULL)
    {
        printf("EROARE LA DESCHIDEREA IMAGINII\n");
        return;
    }
    fseek(f,18,SEEK_SET);
    fread(&latime_imagine,4,1,f);
    fread(&inaltime_imagine,4,1,f);
    fclose(f);

    FILE *g=fopen(nume_sablon,"rb");
    if (g==NULL)
    {
        printf("EROARE LA DESCHIDEREA SABLONULUI\n");
        return;
    }
    fseek(g,18,SEEK_SET);
    fread(&latime_sablon,4,1,g);
    fread(&inaltime_sablon,4,1,g);
    fclose(g);

    unsigned n=inaltime_sablon*latime_sablon;
    double Smedie=0,fimedie=0,corelatie=0,fractie;
    double deviatie_sablon=0,deviatie_fereastra=0;
    unsigned i,j,k,l;

    for (i=0; i<inaltime_sablon; i++)
        for (j=0; j<latime_sablon*3; j+=3)
            Smedie+=mat_sab[i][j];
    Smedie=Smedie/(n*1.00);
    for (i=0; i<inaltime_sablon; i++)
        for (j=0; j<latime_sablon*3; j+=3)
            deviatie_sablon+=((mat_sab[i][j]-Smedie)*(mat_sab[i][j]-Smedie));
    deviatie_sablon=deviatie_sablon/((n-1)*1.00);
    deviatie_sablon=sqrt(deviatie_sablon);
    for (i=0; i<inaltime_imagine-inaltime_sablon; i++)   //400
        for (j=0; j<(latime_imagine-latime_sablon)*3; j+=3) //500*3
        {
            fimedie=0;
            deviatie_fereastra=0;
            corelatie=0;
            for (k=0; k<inaltime_sablon; k++)
                for (l=0; l<latime_sablon*3; l+=3)
                    fimedie+=mat_img[i+k][j+l];
            fimedie=fimedie/(n*1.00);

            for (k=0; k<inaltime_sablon; k++)
                for (l=0; l<latime_sablon*3; l+=3)
                    deviatie_fereastra+=(mat_img[i+k][j+l]-fimedie)*(mat_img[i+k][j+l]-fimedie);
            deviatie_fereastra=deviatie_fereastra/((n-1)*1.00);
            deviatie_fereastra=sqrt(deviatie_fereastra);
            fractie=1/((deviatie_fereastra*deviatie_sablon)*1.00);

            for (k=0; k<inaltime_sablon; k++)
                for (l=0; l<latime_sablon*3; l+=3)
                    corelatie+=fractie*(mat_img[i+k][j+l]-fimedie)*(mat_sab[k][l]-Smedie);
            corelatie=corelatie/(n*1.00);
            if (corelatie>prag)
            {
                *FPunct=(Punct *)realloc(*FPunct,(sizeof(Punct))*(*lung+1));
                (*FPunct)[(*lung)].culoare[0]=COLOR[0];
                (*FPunct)[(*lung)].culoare[1]=COLOR[1];
                (*FPunct)[(*lung)].culoare[2]=COLOR[2];
                (*FPunct)[(*lung)].width=latime_sablon;
                (*FPunct)[(*lung)].height=inaltime_sablon;
                (*FPunct)[(*lung)].x=i;
                (*FPunct)[(*lung)].y=j;
                (*FPunct)[(*lung)].corr=corelatie;
                (*lung)++;
            }
        }
}

void colorare(char *nume_imagine, Punct point,unsigned char ***matrice)
{
    unsigned i,j;
    for (j=0; j<point.width*3; j+=3)   //3*latime_sablon
    {
        (*matrice)[point.x+point.height][point.y+j]=point.culoare[0];
        (*matrice)[point.x+point.height][point.y+j+1]=point.culoare[1];
        (*matrice)[point.x+point.height][point.y+j+2]=point.culoare[2];
        (*matrice)[point.x][point.y+j]=point.culoare[0];
        (*matrice)[point.x][point.y+j+1]=point.culoare[1];
        (*matrice)[point.x][point.y+j+2]=point.culoare[2];
    }
    for (i=0; i<point.height; i++)  //inaltime_sablon
    {
        (*matrice)[point.x+i][point.y+point.width*3]=point.culoare[0];
        (*matrice)[point.x+i][point.y+point.width*3+1]=point.culoare[1];
        (*matrice)[point.x+i][point.y+point.width*3+2]=point.culoare[2];
        (*matrice)[point.x+i][point.y]=point.culoare[0];
        (*matrice)[point.x+i][point.y+1]=point.culoare[1];
        (*matrice)[point.x+i][point.y+2]=point.culoare[2];
    }
}

void eliminare_non_maximale(Punct **D, unsigned *lungime)
{
    qsort(*D,*lungime,sizeof(Punct),comparator);
    unsigned i,j,k,l,h;
    unsigned st,dr,sus,jos;
    unsigned Intersectie;
    double Suprapunere;
    for (i=0; i<*lungime-1; i++)
        for (j=i+1; j<*lungime; j++)
        {
            st= ((*D)[j].y>=(*D)[i].y)? (*D)[j].y : (*D)[i].y;
            dr= ((*D)[j].y+(*D)[j].width*3<=(*D)[i].y+(*D)[i].width*3)? (*D)[j].y+(*D)[j].width*3 : (*D)[i].y+(*D)[i].width*3;
            sus= ((*D)[j].x>=(*D)[i].x)? (*D)[j].x : (*D)[i].x;
            jos= ((*D)[j].x+(*D)[j].height<=(*D)[i].x+(*D)[i].height)? (*D)[j].x+(*D)[j].height : (*D)[i].x+(*D)[i].height;
            if (st<dr && sus<jos)
            {
                k=(dr-st)/3+1;
                l=jos-sus+1;
                Intersectie=k*l;
                Suprapunere=Intersectie/(((((*D)[i].width)*((*D)[i].height)+(*D)[j].width*(*D)[j].height)-Intersectie)*1.00);
                if (Suprapunere>0.2)
                {
                    for (h=j; h<*lungime-1; h++)
                        (*D)[h]=(*D)[h+1];
                    j--;
                    (*lungime)--;
                }
            }
        }
        (*D)=(Punct *)(realloc(*D,sizeof(Punct)*(*lungime)));
}

int main()
{
    //CRIPTARE, DECRIPTARE
    FILE *test;
     char nume_img_sursa[101],nume_img_criptata[101],nume_img_decriptata[101],nume_secretkey[101];
     printf("Numele imaginii sursa care va fi criptat: ");
     fgets(nume_img_sursa,101,stdin);
     nume_img_sursa[strlen(nume_img_sursa)-1]='\0';
     test=fopen(nume_img_sursa,"rb");
     while (test==NULL)
     {
         printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
         fgets(nume_img_sursa,101,stdin);
         nume_img_sursa[strlen(nume_img_sursa)-1]='\0';
         test=fopen(nume_img_sursa,"rb");
     }
     fclose(test);

     printf("Imaginea criptata va fi salvata cu numele: ");
     fgets(nume_img_criptata,101,stdin);
     nume_img_criptata[strlen(nume_img_criptata)-1]='\0';
     printf("Cheia secreta se afla in fisierul: ");
     fgets(nume_secretkey,101,stdin);
     nume_secretkey[strlen(nume_secretkey)-1]='\0';

     test=fopen(nume_secretkey,"r");
     while (test==NULL)
     {
         printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
         fgets(nume_secretkey,101,stdin);
         nume_secretkey[strlen(nume_secretkey)-1]='\0';
         test=fopen(nume_secretkey,"r");
     }
     fclose(test);

     criptare_poza(nume_img_sursa,nume_img_criptata,nume_secretkey);
     printf("Imaginea criptata care trebuie decriptata are numele: ");
     fgets(nume_img_criptata,101,stdin);
     nume_img_criptata[strlen(nume_img_criptata)-1]='\0';

     test=fopen(nume_img_criptata,"rb");
     while(test==NULL)
     {
         printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
         fgets(nume_img_criptata,101,stdin);
         nume_img_criptata[strlen(nume_img_criptata)-1]='\0';
         test=fopen(nume_img_criptata,"rb");
     }
     fclose(test);

     printf("Imaginea decriptata va fi salvata cu numele: ");
     fgets(nume_img_decriptata,101,stdin);
     nume_img_decriptata[strlen(nume_img_decriptata)-1]='\0';
     printf("Cheia secreta se afla in fisierul: ");
     fgets(nume_secretkey,101,stdin);
     nume_secretkey[strlen(nume_secretkey)-1]='\0';

     test=fopen(nume_secretkey,"r");
     while (test==NULL)
     {
         printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
         fgets(nume_secretkey,101,stdin);
         nume_secretkey[strlen(nume_secretkey)-1]='\0';
         test=fopen(nume_secretkey,"r");
     }
     fclose(test);

     decriptare_poza(nume_img_criptata,nume_img_decriptata,nume_secretkey);
     chitest(nume_img_sursa);
     chitest(nume_img_criptata);
     printf("\n\n");
     //TEMPLATE MATCHING
     Punct *D=NULL;
     unsigned lungime=0,i;
     int nr;
     unsigned char **matricea_img;
     char nume_imagine[51],nume_sablon[32][51]; // va rog sa nu fie mai mult de 32 de sabloane, multumesc :)
     unsigned char COLOR[32][3]= {255,0,0,255,255,0,0,255,0,0,255,255,255,0,255,0,0,255,192,192,192,255,140,0,128,0,128,128,0,0};
     printf("Numele imaginii pe care se va efectua template matching: ");
     fgets(nume_imagine,51,stdin);
     nume_imagine[strlen(nume_imagine)-1]='\0';

     test=fopen(nume_imagine,"rb");
     while (test==NULL)
     {
         printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
         fgets(nume_imagine,51,stdin);
         nume_imagine[strlen(nume_imagine)-1]='\0';
         test=fopen(nume_imagine,"rb");
     }
     fclose(test);

     printf("Numarul de sabloane folosite este: ");
     scanf("%d",&nr);
     fgetc(stdin);

     char character;
     printf("Se folosesc culorile din PDF-ul proiectului pentru cifre de la 0 la 9? (Daca raspunsul e nu, culorile sunt bagate manual de la tastatura.)\nY/N:");
     scanf("%c",&character);
     while(character!='Y' && character!='y' && character!='N' && character!='n') //edgy + template_matching pt litere maybe?
             scanf("%c",&character);

     fgetc(stdin);
     if (character=='N' || character=='n')
     {
         for (i=0; i<nr; i++)
         {
             printf("Numele sablonului cu numarul %u este: ",i);
             fgets(nume_sablon[i],51,stdin);
             nume_sablon[i][strlen(nume_sablon[i])-1]='\0';
             test=fopen(nume_sablon[i],"rb");
             while(test==NULL)
             {
                 printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
                 fgets(nume_sablon[i],51,stdin);
                 nume_sablon[i][strlen(nume_sablon[i])-1]='\0';
                 test=fopen(nume_sablon[i],"rb");
             }
             fclose(test);
             printf("Valorea octetului R cu care se va colora sablonul %u este:",i);
             scanf("%u",&COLOR[i][0]);
             printf("Valorea octetului G cu care se va colora sablonul %u este:",i);
             scanf("%u",&COLOR[i][1]);
             printf("Valorea octetului B cu care se va colora sablonul %u este:",i);
             scanf("%u",&COLOR[i][2]);
             fgetc(stdin);
             template_matching(nume_imagine,nume_sablon[i],0.50,&D,&lungime,COLOR[i]);
         }
     }
     else
         for (i=0; i<nr; i++)
         {
             printf("Numele sablonului cu numarul %u este: ",i);
             fgets(nume_sablon[i],51,stdin);
             nume_sablon[i][strlen(nume_sablon[i])-1]='\0';

             test=fopen(nume_sablon[i],"rb");
             while(test==NULL)
             {

                 printf("NUMELE INTRODUS ESTE GRESIT. FISIERUL NU EXISTA. INCEARCA ALT NUME:");
                 fgets(nume_sablon[i],51,stdin);
                 nume_sablon[i][strlen(nume_sablon[i])-1]='\0';
                 test=fopen(nume_sablon[i],"rb");
             }
             fclose(test);
             template_matching(nume_imagine,nume_sablon[i],0.50,&D,&lungime,COLOR[i]);
         }
     liniarizare_Matrice(nume_imagine,&matricea_img);
     eliminare_non_maximale(&D,&lungime);
     for (i=0; i<lungime; i++)
         colorare(nume_imagine,D[i],&matricea_img);
     char nume_imagine_finala[51];
     printf("Imaginea finala dupa colorare va fi salvata in: ");
     fgets(nume_imagine_finala,51,stdin);
     nume_imagine_finala[strlen(nume_imagine_finala)-1]='\0';
     MemorieExternaLiniarizare_Matrice(nume_imagine,nume_imagine_finala,matricea_img);
     free(D);
     free(matricea_img);
     return 0;
}
