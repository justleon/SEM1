/*  Autor: Lukasz Pokorzynski, PRI2018_Z, g.3
    Program pobiera od uzytkownika po kolei liczby i oblicza z nich
    sume, srednia i mediane wprowadzonego ciagu liczbowego.
    Wyniki te sa pokazywane po kazdorazowym wprowadzeniu liczby. */

#include <stdio.h>

int main( void ){
    int licznik = 0;
    double ciag[100];
    double liczba;
    double sumaCiagu = 0.0;
    double sredniaCiagu;
    double medianaCiagu;
    char czyDalej;

    puts( "Wprowadzaj liczby ciagu, zostanie wyliczona jego suma, srednia i mediana." );
    do{
        printf( "Wpisz liczbe: " );
        scanf("%lf", &liczba);
        getchar(); //wyczysc bufor
        ciag[licznik] = liczba;

        for( int i = licznik; i > 0; --i ){
            if( ciag[i] < ciag[i-1] ){
                double x = ciag[i];
                ciag[i] = ciag[i-1];
                ciag[i-1] = x;
            }
            else{
                break;
            }
        }
        sumaCiagu += liczba;
        sredniaCiagu = sumaCiagu / ( licznik+1 );
        if( licznik % 2 == 0 ){
            medianaCiagu = ciag[licznik/2];
        }
        else{
            medianaCiagu = ( ciag[licznik/2]+ciag[licznik/2 + 1] )/2;
        }
        ++licznik;

        printf( "\nAktualna:\n Suma: %lf\n Srednia: %lf\n Mediana: %lf\n", sumaCiagu, sredniaCiagu, medianaCiagu );
        printf( "\nAby zakonczyc wprowadzanie wpisz q i potwierdz,\nw przeciwnym razie wcisnij Enter: " );
        czyDalej = getchar();
    } while( czyDalej != 'q' && czyDalej != 'Q' );
    return 0;
}
