#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXT 32
struct kandydat
{
    char imie[MAXT];
    char nazwisko[MAXT];
    char plec;
    char partia[MAXT];
    int klucz;
    struct kandydat *next;
};

struct okreg
{
    char nazwa[MAXT];
    struct kandydat *listakandydatow;
    struct okreg *next;
};


void wypiszlisteokregow(struct okreg *listaokegow);

void wypiszlistekandydatow(struct kandydat*listakandydatow);

void dodajokreg(struct okreg **listaokregow,char nazwa[MAXT]);

void dodajkandydatadookregu(struct okreg *listaokregow, char nazwa[MAXT],char imie[MAXT],char nazwisko[MAXT],char plec,char partia[MAXT],int klucz);

void dodajkandydata(struct kandydat **listakandydatow,char imie[MAXT],char nazwisko[MAXT],char plec,char partia[MAXT],int klucz);

void edytujkandydata(struct okreg *listaokregow,struct kandydat *listakandydatow,char miasto[MAXT],char imie[MAXT],int klucz);

struct okreg * szukajokregu(struct okreg * listaokregow, char nazwa[MAXT]);

struct kandydat * szukajkandydata(struct kandydat * listakandydatow, int klucz);

struct okreg * szukajpopokregu(struct okreg * listaokregow, char nazwa[MAXT]);

struct kandydat * szukajpopkandydata(struct kandydat * listakandydatow, int klucz);

void zwolnijpamiec(struct okreg **listaokregow);

void zwolnijlistekandydatow(struct kandydat ** listakandydatow);

void zwolnijkandydata(struct okreg *listaokregow, struct kandydat ** listakandydatow,char nazwa [MAXT],int klucz);

void zwolnijokreg(struct okreg ** listaokregow, char nazwa[MAXT]);

void sortowanie(struct kandydat ** listakandydatow);

void zamien(struct kandydat **listakandydatow, struct kandydat * wsk);

int dlugosclisty(struct kandydat *listakandydatow);

void przejdzprzezokregi(struct okreg *listaokregow);

void wyswietlmenu();

void wyswitlwtd();

int main()
{
    wyswitlwtd();
    struct okreg * listaokregow=NULL;
    int i=1,klucz;
    char miasto[MAXT],imie[MAXT],nazwisko[MAXT],plec,partia[MAXT];
    for(;;)
    {
        wyswietlmenu();
         while(scanf("%d",&i)!=1)
    {
        puts("zle dane sprobuj jeszcze raz:");
        getchar();
    }
    switch(i)
    {

    case 0:
        puts("dziekuje za zabawe programem:)");
        zwolnijpamiec(&listaokregow);
        exit(0);
        break;
    case 1:
        puts("podaj nazwe okregu");
        scanf("%31s",&miasto);
        dodajokreg(&listaokregow,miasto);
        break;
    case 2:
        puts("podaj nazwe okregu:");
        scanf("%31s",&miasto);
        if(NULL==szukajokregu(listaokregow,&miasto))
        {
            puts("taki okrag nie istnieje");
             break;
        }
        puts("podaj klucz:");
        while(scanf("%d",&klucz)!=1)
        {
        puts("zle dane sprobuj jeszcze raz:");
        getchar();
        }
        puts("podaj imie:");
        scanf("%31s",&imie);
        puts("podaj nazwisko:");
        scanf("%31s",&nazwisko);
        puts("podaj plec(k/m):");
        scanf(" %c",&plec);
        puts("podaj partie:");
        scanf("%31s",&partia);
        dodajkandydatadookregu(listaokregow,miasto,imie,nazwisko,plec,partia,klucz);
        break;
    case 3:
        puts("podaj nazwe okregu:");
        scanf("%31s",&miasto);
        zwolnijokreg(&listaokregow,miasto);
        break;
    case 4:
        puts("podaj nazwe okregu:");
        scanf("%31s",&miasto);
        puts("podaj klucz kandydata:");
        while(scanf("%d",&klucz)!=1)
            {
            puts("zle dane sprobuj jeszcze raz:");
            getchar();
            }
        zwolnijkandydata(listaokregow,&(listaokregow->listakandydatow),miasto,klucz);
        break;
    case 5:
        puts("podaj nazwe okregu:");
        scanf("%31s",&miasto);
        puts("podaj klucz kandydata");
        while(scanf("%d",&klucz)!=1)
            {
            puts("zle dane sprobuj jeszcze raz:");
            getchar();
            }
        puts("podaj imie kandydata:");
        scanf("%31s",&imie);
        edytujkandydata(listaokregow,listaokregow->listakandydatow,miasto,imie,klucz);
        break;
    case 6:
        wypiszlisteokregow(listaokregow);
        break;
    case 7:
        sortowanie(&(listaokregow->listakandydatow));
        wypiszlisteokregow(listaokregow);
        break;

    default:
        puts("zla dana sprobuj wybrac cos z dostepnych opcji");
        break;

    }
    }
   /*
    dodajokreg(&listaokregow, "abc");
    dodajokreg(&listaokregow, "cda");
    dodajkandydatadookregu(listaokregow,"cda","adam",1);
    dodajkandydatadookregu(listaokregow,"cda","ala",2);
    dodajkandydatadookregu(listaokregow,"cda","kasia",3);
    dodajkandydatadookregu(listaokregow,"cda","ela",4);
    dodajkandydatadookregu(listaokregow,"cda","hela",5);
    dodajkandydatadookregu(listaokregow,"abc","aola",1);
    dodajkandydatadookregu(listaokregow,"abc","cela",2);
    dodajkandydatadookregu(listaokregow,"abc","wiola",3);
    edytujkandydata(listaokregow,listaokregow->listakandydatow,"abc","gowno",3);
    wypiszlisteokregow(listaokregow);
    zwolnijkandydata(listaokregow,&(listaokregow->listakandydatow),"cda",5);
    dodajkandydatadookregu(listaokregow,"cda","hela",6);
    zwolnijkandydata(listaokregow,&(listaokregow->listakandydatow),"cda",6);
    wypiszlisteokregow(listaokregow);
    zwolnijpamiec(&listaokregow);*/
}

//funkcje dodajace kandydatow

void dodajkandydata(struct kandydat **listakandydatow,char imie[MAXT],char nazwisko[MAXT],char plec,char partia[MAXT],int klucz)
{
    struct kandydat * znaleziony=szukajkandydata(*listakandydatow,klucz);
    if(znaleziony!=NULL)
    {
        puts("na liscie juz jest ten kandydat");
        return;
    }
    struct kandydat *nowy = (struct kandydat*)malloc(sizeof(struct kandydat));
    strcpy(nowy->imie,imie);
    strcpy(nowy->nazwisko,nazwisko);
    strcpy(nowy->partia,partia);
    nowy->plec=plec;
    nowy->klucz=klucz;
    nowy->next=*listakandydatow;
    *listakandydatow=nowy;
}

void dodajokreg(struct okreg **listaokregow,char nazwa[MAXT])
{
    struct okreg * nowy = (struct okreg *)malloc(sizeof(struct okreg));
    struct okreg *temp=*listaokregow;
    if(nowy==NULL)
    {
        puts("brak pamieci");
        return;
    }
    while(temp!=NULL)
    {
        if(strcmp(temp->nazwa,nazwa)==0)
        {
        puts("taki okrag juz istnieje wymysl inna nazwe");
        return ;
        }
     temp=temp->next;
    }

    strcpy(nowy->nazwa,nazwa);
    nowy->listakandydatow=NULL;
    nowy->next=*listaokregow;
    (*listaokregow)=nowy;
}

void dodajkandydatadookregu(struct okreg *listaokregow, char nazwa[MAXT],char imie[MAXT],char nazwisko[MAXT],char plec,char partia[MAXT],int klucz)
{

    struct okreg * znaleziony = szukajokregu(listaokregow,nazwa);
    if(znaleziony==NULL)
    {
        puts("brak szukanego okregu");
        return ;
    }
    dodajkandydata(&(znaleziony->listakandydatow),imie,nazwisko,plec,partia,klucz);

}

void edytujkandydata(struct okreg *listaokregow,struct kandydat * listakandydatow,char miasto[MAXT], char nazwa[MAXT],int klucz)
{
        struct okreg *pom=szukajokregu(listaokregow,miasto);
        struct kandydat *temp;
        temp=szukajkandydata(pom->listakandydatow,klucz);
        if(temp==NULL)
        {
            puts("nie ma takiego kandydata");
            return;
        }
        strcpy(temp->imie,nazwa);
}

//funkcje szukajace danych
struct okreg * szukajokregu(struct okreg * listaokregow, char nazwa[MAXT])
{
    struct okreg * temp=listaokregow;
 while(temp!=NULL)
 {
     if(strcmp(nazwa,temp->nazwa)==0)
        return temp;
     temp=temp->next;
 }
 return NULL;
}

struct okreg * szukajpopokregu(struct okreg * listaokregow, char nazwa[MAXT])
{
    struct okreg * temp=listaokregow;
    if(strcmp(temp->nazwa,nazwa)==0)
        return temp;
    else
    {
    while(temp->next!=NULL)
    {
        if(strcmp(nazwa,temp->next->nazwa)==0)
            return temp;
        temp=temp->next;
    }
    return NULL;
    }
}

struct kandydat * szukajkandydata(struct kandydat * listakandydatow, int klucz)
{
    struct kandydat * temp=listakandydatow;
 while(temp!=NULL)
 {
     if(temp->klucz==klucz)
        return temp;
     temp=temp->next;
 }
 return NULL;
}

struct kandydat * szukajpopkandydata(struct kandydat * listakandydatow , int klucz)
{
        struct kandydat * temp=listakandydatow;
        if(temp->klucz==klucz)
            return temp;
            else
            {
                  while (temp->next!=NULL)
        {
            if(temp->next->klucz==klucz)
                return temp;
            temp=temp->next;
        }
          return NULL;
            }


}

//funkcje wypisujace
void wypiszlisteokregow(struct okreg *listaokregow)
{
    struct okreg *temp=listaokregow;
    if(temp==NULL)
    {
        puts("lista okregow jest pusta");
    }
    else
    {
        puts("lista okregow:");
        while(temp!=NULL)
        {
            printf("%s\n",temp->nazwa);
            wypiszlistekandydatow(temp->listakandydatow);
            temp=temp->next;
        }

    }
}
void wypiszlistekandydatow(struct kandydat*listakandydatow)
{
    struct kandydat *temp=listakandydatow;
    if(temp==NULL)
    {
        puts("lista kandydatow jest pusta");
    }
    else
    {
        puts("lista kandydatow:");
        while(temp!=NULL)
        {
            printf("%s %d\n",temp->imie,temp->klucz);
            temp=temp->next;
        }

    }
}

//funkcje usuwajace
void zwolnijpamiec(struct okreg ** listaokregow)
{
    while(*listaokregow!=NULL)
    {
        struct okreg *u=*listaokregow;
        *listaokregow=(*listaokregow)->next;
        zwolnijlistekandydatow(&(u->listakandydatow));
        printf("usuniecie okregu o nazwa %s\n",u->nazwa);
        free(u);
    }
}

void zwolnijokreg(struct okreg ** listaokregow,char nazwa[MAXT])
{
    struct okreg * temp=szukajpopokregu(*listaokregow,nazwa);
    struct okreg *u;
    if(temp==NULL)
    {
        puts("brak takiego okregu ");
        return ;
    }
    if(temp->nazwa==(*listaokregow)->nazwa)
    {
        u=*listaokregow;
        *listaokregow=(*listaokregow)->next;
        zwolnijlistekandydatow(&(u->listakandydatow));
        printf("usuniecie okregu o nazwa %s\n",u->nazwa);
        free(u);
    }
    else
    {
        u=temp->next;
        temp->next=u->next;
        zwolnijlistekandydatow(&(u->listakandydatow));
        printf("usuniecie okregu o nazwie %s\n",u->nazwa);
        free(u);

    }

}
void zwolnijlistekandydatow(struct kandydat ** listakandydatow)
{
    while(*listakandydatow!=NULL)
    {
        struct kandydat *u=*listakandydatow;
        *listakandydatow=(*listakandydatow)->next;
        printf("usuniecie kandydata o kluczu %d\n",u->klucz);
        free(u);
    }
}

void zwolnijkandydata(struct okreg *listaokregow ,struct kandydat ** listakandydatow,char nazwa[MAXT], int klucz)
{
    struct okreg * temp=szukajokregu(listaokregow,nazwa);
    struct kandydat *pom;

    pom=szukajpopkandydata(temp->listakandydatow,klucz);
    if(pom==NULL)
    {
        puts("brak takiego kandydata");
        return;
    }
    struct kandydat *u;
    if(klucz==temp->listakandydatow->klucz)
    {
        u=temp->listakandydatow;
        *listakandydatow=temp->listakandydatow->next;
        printf("usuniecie kandydata o kluczu %d\n", u->klucz);
        free(u);

    }
    else
    {
        u=pom->next;
        pom->next=u->next;
        printf("usuniecie kandydata o kluczu %d\n",klucz);
        free(u);
    }

}

//sortowanie
void sortowanie(struct kandydat ** listakandydatow)
{
    struct kandydat *tmp;

            int i=0,dl=dlugosclisty(*listakandydatow);

        for(i;i<dl;i++)
    {
        tmp=*listakandydatow;
        while(tmp->next!=NULL)
    {
        if(strcmp(tmp->nazwisko,tmp->next->nazwisko)>0)
        {
            zamien(listakandydatow,tmp);
        }
        else
        {
            tmp=tmp->next;
        }
    }
    }

}
//funkcje pomocnicze
void zamien(struct kandydat **listakandydatow, struct kandydat * wsk)
{
    struct kandydat *pop,*nast;
    if(*listakandydatow==NULL || wsk==NULL || wsk->next==NULL)
    {
        return;
    }

    if(wsk==(*listakandydatow))
    {
        (*listakandydatow)=(*listakandydatow)->next;
        wsk->next=(*listakandydatow)->next;
        (*listakandydatow)->next=wsk;
    }
    else
    {
        pop=*listakandydatow;
        nast=wsk->next;
        while(pop->next!=wsk)
            pop=pop->next;
        wsk->next=nast->next;
        nast->next=wsk;
        pop->next=nast;

    }
}

int dlugosclisty(struct kandydat *listakandydatow)
{
    struct kandydat * temp=listakandydatow;
    int i=0;
    while(temp!=NULL)
    {
        ++i;
        temp=temp->next;
    }
    return i;
}
void przejdzprzezokregi(struct okreg * listaokregow)
{
    struct okreg *pom=listaokregow;
    while(pom!=NULL)
    {
        sortowanie(&(pom->listakandydatow));
        pom=pom->next;
    }
}
void wyswietlmenu()
{
    puts("1.dodaj okrag\n2.dodaj kandydata\n3.zwolnij okreg\n4.zwolnij kandydata\n5.edytuj kandydata\n6.wypisz wszystko\n7.posortuj\n0.koniec");
}
void wyswitlwtd()
{
    puts("program do zarzadzania baza danych politykow. wybierz opcje z dostepnych w menu wpisanie 0 konczy dzialanie programu. baw sie dobrze");
}
