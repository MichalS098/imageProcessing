//Michał Stanisławski
//
//Przetwarzanie Obrazów II
//03.01.2021r.
//
//Informacje na temat kompilacji i wywolania znajduja sie w pliku z dokumentacja: 'README'
//komenda 'make clean' usuwa pliki z rozszerzeniem .o
//komenda 'make cleanall' usuwa pliki z rozszerzeniem .o i plik wykonywalny
/*-----------------------------------------------------------------------------------------------*
* PRE: Program potrafi wykonywac edycje jedynie na plikach .ppm, .pgm.                           *
*      Program przystosowany do dzialania w systemie linux                                       *
*      Zalecane jest posiadanie programu ImageMagick by program mial mozliwosc wyswietlania zdjec*
* POST: BRAK                                                                                     *
*                                                                                                *
*                                                                                                *
*------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funkcje.h"
#include "opcje.h"

int main(int argc, char **argv) {
    opcje_s Options;         //struktura zawierajaca info. nt. wybranych przez uzytkownika opcji i plikow
    obraz_s *obrazPtr;       //wskaznik na typ "struct obraz" zawierajacy info. nt. naszego obrazu
    obrazPtr = (obraz_s *) malloc(sizeof(obraz_s)); //zaalokowanie pamieci dla struktury z obrazem

    przetwarzaj_opcje(argc, argv, &Options);  //wywoluje funkcje zbierajaca opcje z danych wejsciowych


    Options.plikWejPtr = fopen(Options.plikWejNazwa, "r");    //otwieramy plik
    if (Options.plikWejPtr != NULL) {
        czytaj(obrazPtr, &Options);                         //wczytujemy obraz do struktury
        fclose(Options.plikWejPtr);                        //zamykamy plik
    } else {
        fprintf(stderr, "Blad: Nie otwarto pliku wejsciowego\n");
        return (1);
    }



    /* ----------------------------------------------------------------------------------------------------*
    *  Ponizej znajduje sie seria if'ow sprawdzajacych opcje ze struktury 'Options' i wykonujacych funkcje *
    *  opisane w module funkcje.c, jesli opcje zostaly wybrane(czyli zostala im przypisana wartosc 1).     *
    *  Dopisuje takze komentarz do zdjecia opisujacy jakie zmiany zostaly wykonane na obrazie              *
    * ----------------------------------------------------------------------------------------------------*/

    if (Options.konwersjaDoSzarosci == 1) {
        konwersjaDoSzarosci(obrazPtr);
        strcat(obrazPtr->komentarz, "Konwersji do szarosci, ");
        printf("Konwersja obrazu do szarosci przebiegla pomyslnie\n");
    }
    if (Options.obrocenie == 1) {
        obrocenie(obrazPtr);
        strcat(obrazPtr->komentarz, "Obrocenia obrazu o 90 stopni w prawo, ");
        printf("Wykonano operacje obrocenia obrazu o 90 stopni w prawo\n");
    }
    if (Options.rozciaganieHistogramu == 1) {
        rozciaganieHistogramu(obrazPtr);
        strcat(obrazPtr->komentarz, "Rozciagania histogramu, ");
        printf("Operacja rozciagania histogramu przebiegla pomyslnie\n");
    }
    if (Options.lustrzaneOdbicie == 1) {
        lustrzaneOdbicie(obrazPtr);
        strcat(obrazPtr->komentarz, "Lustrzanego odbicia, ");
        printf("Wykonano lustrzane odbicie\n");
    }
    if (Options.rozmycie_x == 1) {
        rozmycie_x(obrazPtr);
        strcat(obrazPtr->komentarz, "Rozmycia poziomego, ");
        printf("Wykonano operacje rozmycia poziomego\n");
    }
    if (Options.rozmycie_y == 1) {
        rozmycie_y(obrazPtr);
        strcat(obrazPtr->komentarz, "Rozmycia pionowego, ");
        printf("Wykonano operacje rozmycia pionowego\n");
    }
    if (Options.zmianaPoziomow == 1) {
        zmianaPoziomow(obrazPtr, &Options);
        strcat(obrazPtr->komentarz, "Zmiany poziomow bieli i czerni, ");
        printf("Wykonano operacje zmiany poziomow (bieli i czerni)\n");
    }
    if (Options.korekcjaGamma == 1) {
        korekcjaGamma(obrazPtr, &Options);
        strcat(obrazPtr->komentarz, "Korekcji gamma, ");
        printf("Wykonano korekcje gamma\n");
    }
    if (Options.progowanie == 1) {
        progowanie(obrazPtr, &Options);
        strcat(obrazPtr->komentarz, "Progowania, ");
        printf("Wykonano progowanie, z wartoscia progu: %d%%\n", Options.wartoscProguProcent);
    }
    if (Options.progowanieBieli == 1) {
        progowanieBieli(obrazPtr, &Options);
        strcat(obrazPtr->komentarz, "Progowania bieli, ");
        printf("Wykonano progowanie bieli, z wartoscia progu: %d%%\n", Options.wartoscProguBieliProcent);
    }
    if (Options.progowanieCzerni == 1) {
        progowanieCzerni(obrazPtr, &Options);
        strcat(obrazPtr->komentarz, "Progowania czerni, ");
        printf("Wykonano progowanie czerni, z wartoscia progu: %d%%\n", Options.wartoscProguCzerniProcent);
    }
    if (Options.negatyw == 1) {
        negatyw(obrazPtr);
        strcat(obrazPtr->komentarz, "Negatywu, ");
        printf("Wykonano negatyw\n");
    }
    if (Options.konturowanie == 1) {
        konturowanie(obrazPtr);
        strcat(obrazPtr->komentarz, "Konturowania, ");
        printf("Wykonano konturowanie\n");
    }

    Options.plikWyjPtr = fopen(Options.plikWyjNazwa, "w"); //otwieramy plik do zapisu
    if (Options.plikWyjPtr != NULL)     //zapisanie obrazu
    {
        zapisz(obrazPtr, &Options);
        fclose(Options.plikWyjPtr);
    } else {
        fprintf(stderr, "Blad: Nie otwarto pliku wyjsciowego\n");
        return (1);
    }

    if (Options.wyswietlenie == 1)         //wyswietlenie obrazu zapisanego przez uzytkownika
    {                                   //jesli wybral opcje wyswietl
        wyswietl(&Options);
    }
    exit(0);
}
//musze dokonczyc funkcje splotu, w funkcje.c
// i testy zrobic

/*TESTY JEDNOSTKOWE:

wykonalem kompilacje: 'make' nastepnie 'make clean'

(1)TESTY Z OBRAZEM W ODCIENIACH SZAROSCI Z ROZSZERZENIEM .pgm DO TESTOW ZOSTAL UZYTY PLIK testimage.pgm
    1-  CEL TESTU: test ma na celu sprawdzenie funkcji negatyw
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -n -d
        Program poprawnie stworzyl obraz z wprowadzona zmiana negatywu i wyswietlil obraz na ekran.
        PROGRAM DZIALA POPRAWNIE

    2-  CEL TESTU: test ma na celu sprawdzenie funkcji konturowania
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -k -d
        Program stworzyl skonturowany obraz i wyswietlil obraz na ekran
        PROGRAM DZIALA POPRAWNIE

    3-  CEL TESTU: test ma na celu sprawdzenie funkcji progowania
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -p 40 -d
        Program stworzyl obraz z progowaniem o wartosci 40% i wyswietlil na ekran
        poprawnosc progowania sprawdzilem uzywajac programu imagemagick funkcji convert.
        PROGRAM DZIALA POPRAWNIE

    4-  CEL TESTU: test ma na celu sprawdzenie funkcji progowania bieli
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -pb 50 -d
        Program stworzyl obraz z progowaniem bieli o wartosci 50% i wyswietlil na ekran
        poprawnosc zadania sprawdzilem uzywajac funkcji convert programu imagemagick
        PROGRAM DZIALA POPRAWNIE

    5-  CEL TESTU: test ma na celu sprawdzenie obslugi bledow funkcji progowania gdy uzytkownik wpisze niepoprawna wartosc 
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -p 250 -d
        Program wyswietlil blad "niepoprawna wartosc progu, nalezy wybrac wartosc z przedzialu od 0 do 100."
        PROGRAM DZIALA POPRAWNIE

    6-  CEL TESTU: test ma na celu sprawdzenie funkcji korekcji gamma
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -g 0.5 -d
        Program stworzyl obraz z opcja korekcji gamma 0.5 i wyswietlil na ekran
        poprawnosc korekcji sprawdzilem uzywajac programu imagemagick funkcji 'convert -gamma 0.5'
        PROGRAM DZIALA POPRAWNIE
    
    7-  CEL TESTU: test ma na celu sprawdzenie funkcji zmiany poziomu bieli i czerni
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -z 20 30 -d
        Program stworzyl obraz zmieniajac jego poziomy bieli i czerni, i wyswietlil na ekran
        poprawnosc konwersji sprawdzilem uzywajac funkcji 'convert testimage.pgm +level 20,30 test.pgm'
        PROGRAM DZIALA POPRAWNIE

    8-  CEL TESTU: test ma na celu sprawdzenie funkcji obrotu
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -t -d
        Program wyswietlil obraz obrocony o 90 stopni w prawo
        PROGRAM DZIALA POPRAWNIE

    9-  CEL TESTU: test ma na celu sprawdzenie funkcji lustrzanego odbicia   
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -l -d
        Program wyswietlil lustrzane odbicie obrazu wejsciowego 
        PROGRAM DZIALA POPRAWNIE 

    10- CEL TESTU: test ma na celu sprawdzenie funkcji rozmycia poziomego
        WPROWADZONE DANE: ./obr -i testimage.pgm -o test.pgm -rx  i nastepnie 5 razy powtorzone:
                          ./obr -i test.pgm -o test.pgm -rx 
        konczac wyswietleniem ./obr -i testimage.pgm -o test.pgm -rx -d
        Program wyswietlil obraz mocno rozmazany poziomo
        PROGRAM DZIALA POPRAWNIE

(2)DRUGA CZESC, Z UZYCIEM OBRAZU KOLOROWEGO testimage2.ppm :

    11- CEL TESTU: test ma na celu sprawdzenie dzialania konwersji do szarosci obrazu kolorowego
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.pgm -m -d
        Program wyswietlil obraz w odcieniach szarosci , poprawnie wykonal konwersje do szarosci
        PROGRAM DZIALA POPRAWNIE

    12- CEL TESTU: test ma na celu sprawdzenie wykonania jednoczesnie funkcji konwersji do szarosci i lustrzanego odbicia
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.pgm -m -l -d
        Program wyswietlil obraz skonwertowany do szarosci, ktory zostal poddany lustrzanemu odbiciu
        PROGRAM DZIALA POPRAWNIE

    13- CEL TESTU: test ma na celu sprawdzenie funkcji korekcji gamma i funkcji rozciagania histogramu dla obrazow kolorowych
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.ppm -g 0.5 -h -d  
        Program wyswietlil obraz poddany korekcji gamma i rozciagnieciu histogramu
        PROGRAM DZIALA POPRAWNIE

    14- CEL TESTU: test ma na celu sprawdzenie dzialania funkcji rozciagaina histogramu
        Obraz testimage.ppm zostal chwilowo zmieniony, w kodzie obrazu zwiekszylem wartosc maksymalna
        szarosci z wartosci 255 na 350. 
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.ppm -h -d 
        Program wyswietlil obraz z rozciagnietym histogramem, przeskalowal on wartosci pikseli do ustawionej przezemnie
        wartosci maksymalnej szarosci.
        PROGRAM DZIALA POPRAWNIE

    15- CEL TESTU: test ma na celu sprawdzenie dzialania funkcji obrotu polaczonej z funkcja lustrzanego
                   odbicia dla obrazow kolorowych
        WPROWADZONE DANE: ./obr -i testimaqge2.ppm -o test.ppm -t -l -d
        Program wyswietlil kolorowy obraz obrocony o 90 stopni w prawo z efektem lustrzanego odbicia
        PROGRAM DZIALA POPRAWNIE

    16- CEL TESTU: test ma na celu sprawdzenie funkcji negatywu polaczonej z funkcja konturowania dla obrazow kolorowych
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.ppm -n -k -d
        Program stworzyl obraz z efektem negatywu ktory zostal nastepnie skonturowany i poprawnie wyswietlony na ekranie
        PROGRAM DZIALA POPRAWNIE

    17- CEL TESTU: test ma na celu sprawdzenie funkcji rozmycia pionowego i poziomego dla obrazow kolorowych
        WPROWADZONE DANE: ./obr -i testimage.ppm -o test.ppm -rx -ry -d
        Program wyswietlil rozmyty obraz.
        PROGRAM DZIALA POPRAWNIE

    18- CEL TESTU: test ma na celu sprawdzenie dzialania funkcji progowania dla obrazu kolorowego
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.ppm -p 40 -d
        Program wyswietlil obraz po operacji progowania, poprawnosc konwersji sprawdzona z uzyciem programu
        ImageMagick funkcji 'convert testimage2.ppm -threshold 40 test.ppm'
        PROGRAM DZIALA POPRAWNIE

    19- CEL TESTU: test ma na celu sprawdzenie obslugi bledow funkcji konwersji do szarosci jezeli
                   wprowadzimy obraz z rozszerzeniem .pgm
        WPROWADZONE DANE: ./ -i testimage.pgm -o test.pgm -m -d
        Program wypisuje na standardowe wyjscie blad:"nie mona wykonac konwersji do szarosci, nie jest to plik ppm"
        PROGRAM DZIALA POPRAWNIE

    20- CEL TESTU: test ma na celu sprawdzenie dzialania programu dla wykonanej funkcji negatyw 2 razy z rzedu,
                   program powinien koncowo stworzyc obraz identyczny zo brazem wejsciowym
        WPROWADZONE DANE: ./obr -i testimage2.ppm -o test.ppm -n
                          ./obr -i test.ppm -o test.ppm -n -d
        Program wyswietlil niezmieniony obraz wesciowy,
        PROGRAM DZIALA POPRAWNIE

WNIOSKI KONCOWE:

    Program dziala poprawnie dla obrazow .pgm i .ppm, nie ma problemu z otwieraniem plikow i zapisywaniem
    obrazow do plikow. Poprawnie obsluguje wszystkie funkcje i poprawnie wyswietla bledy w przypadku niepoprawnych danych wejsciowych.
    Program nie sprawia problemow takze przy podaniu wielu opcji naraz jak w przypadku sytuacji z testow numer : 17,16 i 15.
    Programowi przydaloby sie wprowadzic zmiany w postaci mozliwosci obslugi formatow .jpg.
*/