/*
  Autor: Łukasz Pokorzyński, grupa I3
  Program pozwala na tworzenie sekwencji obrazów w formacie PPN i PGN
  Korzysta z pamięci dynamicznej w postaci listy jednokierunkowej.
  Zawiera obsluge plikow formatu PPM i PGM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAZWA 51

typedef struct Obraz {
    char nazwaGlowna[MAX_NAZWA];
    char unikalnaNazwa[MAX_NAZWA];
    int pozycja;
    int wysokosc;
    int szerokosc;
    int kolorDominujacy[3];
    int kanaly;
    int histogram[8];
    struct Obraz* nast;
} Obraz;

typedef struct Sekwencja {
    char nazwaSekwencji[MAX_NAZWA];
    int iloscObrazow;
    struct Obraz* pierwszy;
    struct Sekwencja* nast;
} Sekwencja;

void menu();
void nowaSekwencja( Sekwencja** glowa );
Sekwencja* utworzSekwencje( char* nazwa);
void wyswietlSekwencje( Sekwencja* glowa );
void zmienNazweSek( Sekwencja* el, Sekwencja* glowa );
void usunSekwencje( Sekwencja** glowa );

void otworzSekwencje( Sekwencja* glowa );
/*
void sortujSekwencje( Obraz o[], int numer );
void dodajObraz( Obraz** pierwszy );
void wyswietlObraz( Obraz o[], int licznik );
void usunObraz( Obraz o[], int* licznik );

void stworzHistogram( Obraz* o );
void zamien( Obraz* o1, Obraz* o2 );
*/
void wyczyscBufor( void );
//int sumaPoteg( Obraz o );

int main( void ) {
    menu();
    return 0;
}

void menu( ){
    char znak = ' ';
    Sekwencja* glowa = NULL;
    printf( "Baza obrazow PPM i PGM\n" );
    while ( znak != 'q' && znak != 'Q' ) {
        printf( "\nWybierz jedna z dostepnych opcji:\n" );
        printf( "N - utworz nowa sekwencje\nL - wyswietl dostepne sekwencje\nE - otworz sekwencje\n" );
        printf( "K - usun sekwencje\nQ - wyjdz z programu\nPodaj opcje: " );
        znak = getchar();
        if ( znak == '\n' ) {
            znak = ' ';
            continue;
        }
        wyczyscBufor();
        switch ( znak ) {
            case 'n':
            case 'N':
                nowaSekwencja( &glowa );
                wyczyscBufor();
                break;
            case 'l':
            case 'L':
                wyswietlSekwencje( glowa );
                break;
            case 'e':
            case 'E':
                otworzSekwencje( glowa );
                break;
            case 'k':
            case 'K':
                usunSekwencje( &glowa );
                break;
            case 'q':
            case 'Q':
                puts( "Do widzenia!" );
                break;
            default:
                puts( "Nieznana opcja! Podaj inna." );
        }
    }
}

void nowaSekwencja( Sekwencja** glowa ){
    char nazwa[MAX_NAZWA];
    printf( "Podaj nazwe sekwencji: " );
    scanf( "%50[^\n]", nazwa );
    Sekwencja* temp_nazwa = *glowa;
    while( temp_nazwa != NULL ){
        if( 0 == strcmp( temp_nazwa->nazwaSekwencji, nazwa ) ){
            printf( "Juz istnieje sekwencja o takiej nazwie!\n" );
            return;
        }
        temp_nazwa = temp_nazwa->nast;
    }

    if( *glowa == NULL ){
        *glowa = utworzSekwencje( nazwa );
    } else{
        Sekwencja* temp = *glowa;
        while( temp->nast ){
            temp = temp->nast;
        }
        temp->nast = utworzSekwencje( nazwa );
    }
}

Sekwencja* utworzSekwencje( char* nazwa ){
    Sekwencja* el = malloc(sizeof(Sekwencja));
    if( !el ){
        printf( "Zaalokowanie pamieci nie powiodlo sie!\n" );
        return NULL;
    }
    strcpy( el->nazwaSekwencji, nazwa );
    el->iloscObrazow = 0;
    el->pierwszy = NULL;
    el->nast = NULL;
    printf( "Utworzono sekwencje %s!\n", el->nazwaSekwencji);
    return el;
}

void wyswietlSekwencje( Sekwencja* glowa ){
    if( glowa == NULL ){
        puts( "Brak sekwencji do wyswietlenia! Moze to czas, by jedna stworzyc?" );
    }
    else{
        Sekwencja* temp = glowa;
        puts( "Lista dostepnych sekwencji:" );
        while( temp ){
            printf( "\t%s: %d obrazow\n", temp->nazwaSekwencji, temp->iloscObrazow );
            temp = temp->nast;
        }
    }
}

void zmienNazweSek( Sekwencja* el, Sekwencja* glowa ){
    char nazwa[MAX_NAZWA];
    printf( "Podaj nowa nazwe sekwencji: " );
    scanf( "%50[^\n]", nazwa );
    Sekwencja* temp_nazwa = glowa;
    while( temp_nazwa != NULL ){
        if( 0 == strcmp( temp_nazwa->nazwaSekwencji, nazwa ) ){
            printf( "Juz istnieje sekwencja o takiej nazwie!\n" );
            wyczyscBufor();
            return;
        }
        temp_nazwa = temp_nazwa->nast;
    }

    strcpy( el->nazwaSekwencji, nazwa );
    Obraz* temp = el->pierwszy;
    while( temp ){
        strcpy( temp->nazwaGlowna, el->nazwaSekwencji );
        temp->nast;
    }
    printf( "Pomyslnie zmieniono nazwe na \"%s\"!\n", el->nazwaSekwencji );
    wyczyscBufor();
}

void usunSekwencje( Sekwencja** glowa ){
    if( *glowa == NULL ){
        puts( "Nie istnieje zadna sekwencja do usuniecia!" );
        return;
    }

    Sekwencja* temp = *glowa;
    char nazwa[MAX_NAZWA];
    printf( "Wpisz nazwe sekwencji do usuniecia: " );
    scanf( "%50[^\n]", nazwa );
    Sekwencja* poprzedni = NULL;
    while( temp != NULL ){
        if( 0 == strcmp( temp->nazwaSekwencji, nazwa ) ){
            printf( "Usuwam sekwencje %s!\n", nazwa );
            Obraz* temp_o;
            while( temp->pierwszy ){
                temp_o = temp->pierwszy;
                temp->pierwszy = temp->pierwszy->nast;
                free( temp_o );
            }
            if( poprzedni == NULL ){
                *glowa = temp->nast;
                free( temp );
            } else{
                poprzedni->nast = temp->nast;
                free( temp );
            }
            printf( "Pomyslnie usunieto %s!\n", nazwa );
            wyczyscBufor();
            return;
        }else{
            poprzedni = temp;
            temp = temp->nast;
        }
    }
    printf( "Nie znaleziono sekwencji o nazwie %s!\n", nazwa );
    wyczyscBufor();
}

void dodajObraz( Obraz** pierwszy ){
    printf( "Podaj sciezke do pliku PPM/PGM: " );
    char sciezka[1000];
    scanf( "%s[^\n]", sciezka );
    wyczyscBufor();
    FILE* plik = fopen( sciezka, "r" );
    if( !plik ){
        printf( "Otwarcie pliku nie powiodlo sie!\n" );
        return;
    }
    Obraz* temp = *pierwszy;


    fclose( plik );
}

void otworzSekwencje( Sekwencja* glowa ){
    if( glowa == NULL ){
        puts( "Brak sekwencji do otwarcia!" );
        return;
    }

    char znak = ' ';
    char nazwa[MAX_NAZWA];
    wyswietlSekwencje( glowa );
    printf( "Wybierz nazwe sekwencji z dostepnych: " );
    scanf( "%50[^\n]", nazwa );
    Sekwencja* temp = glowa;
    while( temp && temp->nazwaSekwencji != nazwa ){
        if( 0 != strcmp( temp->nazwaSekwencji, nazwa ) ){
            temp = temp->nast;
        } else{
            break;
        }
    }
    if(temp == NULL){
        printf( "Nie istnieje sekwencja o takiej nazwie!\n");
        return;
    }
    wyczyscBufor();

    do{
        printf( "\nObrazy zapisane w sekwencji \"%s\":\n", temp->nazwaSekwencji );
        if(temp->iloscObrazow == 0){
            puts( "Brak obrazow w sekwencji." );
        } else{
            Obraz* temp_obraz = temp->pierwszy;
            for(int i = 0; i < temp->iloscObrazow; ++i){
                printf( "\t%s_%d: %s\n", temp_obraz->nazwaGlowna, i+1, temp_obraz->unikalnaNazwa );
                temp_obraz = temp_obraz->nast;
            }
        }
        printf( "A - dodaj obraz\tD - usun obraz\tS - pokaz dane obrazu\n" );
        printf( "O - sortuj\tC - zmien nazwe sekwencji\nQ - wyjdz do menu\nPodaj opcje: ");
        znak = getchar();
        wyczyscBufor();
        switch( znak ){
            case 'a':
            case 'A':
                dodajObraz( &(temp->pierwszy) );
                break;
            case 'd':
            case 'D':
                //usunObraz( s[numer].obrazy, &(s[numer].iloscObrazow) );
                break;
            case 's':
            case 'S':
                //wyswietlObraz( s[numer].obrazy, s[numer].iloscObrazow );
                break;
            case 'o':
            case 'O':
                //sortujSekwencje( s[numer].obrazy, s[numer].iloscObrazow );
                break;
            case 'c':
            case 'C':
                zmienNazweSek( temp, glowa );
                break;
            case 'q':
            case 'Q':
                puts( "Wracam do menu glownego." );
                break;
            default:
                puts( "Nieznana opcja! Podaj inna." );
        }
    } while( znak != 'q' && znak != 'Q' );
}
/*
void sortujSekwencje( Obraz o[], int numer ){
    int indeks = numer-1;
    if( numer > 1 ){
        char znak = ' ';
        printf( "Wybierz swoja metode sortowania z podanych:\n" );
        printf( "+ (po wysokosci)\n- (po szerokosci)\n/ (po liczbie kanalow)\n* (po kolorze dominujacym)\nWpisz opcje: " );
        znak = getchar();
        wyczyscBufor();
        for(int i = 0; i < indeks; ++i){
            for(int j = i+1; j <= indeks; ++j){
                int oi = sumaPoteg(o[i]);
                int oj = sumaPoteg(o[j]);
                switch(znak){
                    case '+':
                        if(o[i].wysokosc > o[j].wysokosc){
                            zamien( &o[i], &o[j] );
                        } break;
                    case '-':
                        if(o[i].szerokosc > o[j].szerokosc){
                            zamien( &o[i], &o[j] );
                        } break;
                    case '/':
                        if(o[i].kanaly > o[j].kanaly){
                            zamien( &o[i], &o[j] );
                        } break;
                    case '*':
                        if(oi > oj){
                            zamien( &o[i], &o[j] );
                        } break;
                    default:
                        puts( "Nieznana opcja! Wracam do menu." );
                        i = indeks;
                        j = indeks+1;
                }
            }
        }
    } else{
        puts( "Nie ma czego sortowac! :)" );
    }
}

void usunObraz( Obraz o[], int* licznik ){
    if( licznik == 0 ){
        puts( "Sekwencja jest pusta!" );
        return;
    }

    int numer;
    printf( "Wybierz obraz do usuniecia: " );
    scanf( "%d", &numer );
    wyczyscBufor();
    if(numer > *licznik || numer < 1){
        puts( "Nieprawidlowy numer obrazu!" );
        return;
    }
    printf( "Usuwam obraz nr %d!\n", numer);
    numer -= 1;
    for(int i = numer; i < *licznik-1; ++i){
        strcpy(o[numer].unikalnaNazwa, o[numer+1].unikalnaNazwa);
        o[numer] = o[numer+1];
    }
    --( *licznik );
}

void wyswietlObraz( Obraz* pierwszy ){
    if( !pierwszy ){
        printf( "Brak obrazow do pokazania!\n" );
        return;
    }

    int numer;
    Obraz* temp = pierwszy;
    printf( "Wpisz nr obrazu do wyswietlenia sposrod dostepnych: " );
    scanf( "%d", &numer );
    if(numer > licznik || numer < 1){
        puts( "Nieprawidlowy numer obrazu!" );
        wyczyscBufor();
        return;
    }
    printf( "Unikalna nazwa obrazu: %s\n", temp->unikalnaNazwa );
    printf( "Pozycja: %d\n", o[numer].pozycja );
    printf( "Wysokosc: %d\nSzerokosc: %d\n", o[numer].wysokosc, o[numer].szerokosc );
    printf( "Kolor dominujacy[R G B]:\n" );
    for(int i = 0; i < 3; ++i){
        printf( "%d  ", o[numer].kolorDominujacy[i] );
    }
    printf( "\nHistogram:\n");
    for(int i = 0; i < 8; ++i){
        printf( "%d  ", o[numer].histogram[i] );
    }
    printf( "\nLiczba kanalow: %d\n", o[numer].kanaly );
    wyczyscBufor();
}

void stworzHistogram( Obraz* o ){
    srand( time( NULL ) );
    for(int i = 0; i < 8; ++i){
        o->histogram[i] = 0;
    }
    for(int i = 0; i < o->wysokosc; ++i){
        for(int j = 0; j < o->szerokosc; ++j){
            o->histogram[rand() % 8] += 1;
        }
    }
}

void zamien( Obraz* o1, Obraz* o2){
    Obraz temp;
    temp = *o1;
    strcpy(temp.unikalnaNazwa, o1->unikalnaNazwa);
    *o1 = *o2;
    strcpy(o1->unikalnaNazwa, o2->unikalnaNazwa);
    *o2 = temp;
    strcpy(o2->unikalnaNazwa, temp.unikalnaNazwa);

    int tempPoz = o1->pozycja;
    o1->pozycja = o2->pozycja;
    o2->pozycja = tempPoz;
}
*/
void wyczyscBufor(void) {
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
/*
int sumaPoteg(Obraz o) {
    return o.kolorDominujacy[0] * o.kolorDominujacy[0] + o.kolorDominujacy[1] * o.kolorDominujacy[1] +
           o.kolorDominujacy[2] * o.kolorDominujacy[2];
}
*/
