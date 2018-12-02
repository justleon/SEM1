#include <stdio.h>

void pobierzDane(int* l1, int* l2, char* z);
void dodajOdejmij(int l1, int l2, char z);
void mnozDziel(int l1, int l2, char z);
void kalkulator();

int main( void ){
    char dalej = ' ';
    do{
        kalkulator();
        printf( "Aby dalej wykonywac obliczenia wcisnij enter, q konczy program: " );
    } while( dalej = getchar() != 'q' );
}

void pobierzDane( int* l1, int* l2, char* z ){
    printf( "Wprowadz dwie liczby (po spacji), na ktorych wykonasz dzialanie: " );
    scanf( "%x %x", l1, l2 );
    getchar();
    printf( "Wybierz dzialanie, wpisz jedno z dostepnych (+, -, *, /): " );
    *z = getchar();
}

void dodajOdejmij( int l1, int l2, char z ){
    (z == '+') ? printf( "Wynik: %X\n", l1+l2 ) : printf( "Wynik: %X\n", l1-l2 );
}

void mnozDziel( int l1, int l2, char z ){
    if((z == '*') || (z == '/')){
        (z == '*') ? printf( "Wynik: %X\n", l1*l2 ) : printf( "Wynik: %X\n", l1/l2 );
    } else{
        printf( "Nie znam takiego dzialania!\n" );
    }
}

void kalkulator(){
    int liczba1, liczba2;
    char znak;
    pobierzDane( &liczba1, &liczba2, &znak);
    getchar();
    ((znak == '+')||(znak == '-')) ? dodajOdejmij( liczba1, liczba2, znak ) : mnozDziel( liczba1, liczba2, znak );
}
