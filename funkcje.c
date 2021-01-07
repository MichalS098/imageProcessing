#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "funkcje.h"
#include "opcje.h"

/* ----------------------------------------------------------------------------------------------------*
*  W tym module znajduja sie definicje wszystkich funkcji zajmujacych sie edycja obrazu, wczytaniem go *
*  do struktury i zapisywaniem do plikow.                                                              *
*  Deklaracje struktur ktorymi posluguja sie funkcje znajduja sie w plikach naglowkowych.              *
* ----------------------------------------------------------------------------------------------------*/

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(opcje_s *Options) {
    char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
    strcpy(polecenie, "display ");  /* konstrukcja polecenia postaci */
    strcat(polecenie, Options->plikWyjNazwa);     /* display "nazwa_pliku" & */
    strcat(polecenie, " &");
    printf("%s\n", polecenie);      /* wydruk kontrolny polecenia */
    system(polecenie);             /* wykonanie polecenia        */
}

void progowanie(obraz_s *obrazPtr, opcje_s *Options) {
    if(Options->wartoscProguProcent>100||Options->wartoscProguProcent<0)            //sprawdzenie czy uzytkownik wpisal poprawna wartosc progu
    {
        fprintf(stderr,"Blad: niepoprawna wartosc progu, nalezy wybrac wartosc z przedzialu od 0 do 100.\n");
        exit(1);
    }
    float wartoscProgu = (((float) Options->wartoscProguProcent) * ((float) obrazPtr->szarosci)) / 100;  //obliczanie wartosci progu jako iloczyn procent progu i maksymalnej szarosci
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];                   //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if ((piksele[i][j]) <= (int) wartoscProgu) {
                piksele[i][j] = 0;
            } else {
                piksele[i][j] = obrazPtr->szarosci;
            }
        }
    }
}

void konturowanie(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    if ((obrazPtr->typObrazu[1]) == '3') //sprawdza czy to obraz ppm
    {
        for (i = 1; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < ((obrazPtr->ppmMnoznik * obrazPtr->wymx) - 3); j++) {
                piksele[i][j] = (abs((piksele[i][j + 3]) - (piksele[i][j])) + abs((piksele[i + 1][j]) - (piksele[i][j])));
            }
        }
    } else {
        for (i = 1; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < ((obrazPtr->wymx) - 1); j++) {
                piksele[i][j] = (abs((piksele[i][j + 1]) - (piksele[i][j])) + abs((piksele[i + 1][j]) - (piksele[i][j])));
            }
        }
    }
}

void lustrzaneOdbicie(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int temp, tempR, tempG, tempB, i, j;
    const int middleX = ((obrazPtr->wymx) / 2);  //polowa szerokosci obrazu

    if ((obrazPtr->typObrazu[1]) == '3') //sprawdza czy to obraz ppm
    {
        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < (middleX); j++) {
                tempR = piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 3 - 3 * j];
                piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 3 - 3 * j] = piksele[i][3 * j]; //zamiana pixela odpowiadajcego za kolor czerwony
                piksele[i][3 * j] = tempR;

                tempG = piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 2 - 3 * j];
                piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 2 - 3 * j] = piksele[i][3 * j + 1]; //zamiana pikseli zielonych
                piksele[i][3 * j + 1] = tempG;

                tempB = piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 1 - 3 * j];
                piksele[i][(obrazPtr->ppmMnoznik) * (obrazPtr->wymx) - 1 - 3 * j] = piksele[i][3 * j + 2]; //zamiana pikseli niebieskich
                piksele[i][3 * j + 2] = tempB;
            }
        }
    } else {
        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < middleX; j++) {
                temp = piksele[i][(obrazPtr->wymx) - j];
                piksele[i][(obrazPtr->wymx) - j] = piksele[i][j];
                piksele[i][j] = temp;
            }
        }
    }
}

void negatyw(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int temp, i, j;
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            temp = piksele[i][j];
            piksele[i][j] = (obrazPtr->szarosci) - temp;
        }
    }

}

void obrocenie(obraz_s *obrazPtr)                       //funkcja wykonuje obrot obrazu o 90 stopni w prawo,
{                                                       //wykonujac transpozycje na tablicy zawierajaca piksele obrazu    
    int i, j;
    int tablicaPomocnicza[obrazPtr->wymy][(obrazPtr->wymx * obrazPtr->ppmMnoznik)];        //tworze tablice pomocnicza

    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];                             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica;    //zmienna pomocnicza wskazuje na tablice

    int temp = obrazPtr->wymy;
    obrazPtr->wymy = obrazPtr->wymx;                                                       //zamiana szerokosci obrazu z wysokoscia
    obrazPtr->wymx = temp;
    /* Odwrocenie kolumn i transpozycja macierzy */
    for (i = 0; i < (obrazPtr->wymy * obrazPtr->ppmMnoznik); i++) {
        for (j = 0; j < (obrazPtr->wymx); j++) {
            tablicaPomocnicza[(obrazPtr->wymx)-j-1][i] = piksele[j][i];
        }
    }
    free(obrazPtr->obrazTablica);                                                        //zwalniamy pamiec w ktorej byl przechowywany nasz stary obraz ppm
    obrazPtr->obrazTablica = malloc(obrazPtr->ppmMnoznik * obrazPtr->wymx * obrazPtr->wymy * sizeof(int));

    if ((obrazPtr->typObrazu[1]) != '3') //sprawdza czy to obraz ppm, jeśli nie to wykonuje pierwszą pętle
    {
        int(*piksele2)[obrazPtr->wymx];
        piksele2 = (int (*)[obrazPtr->wymx]) obrazPtr->obrazTablica;
        for (i = 0; i < (obrazPtr->wymy * obrazPtr->ppmMnoznik); i++) {
            for (j = 0; j < (obrazPtr->wymx); j++) {
                piksele2[i][j] = tablicaPomocnicza[j][i];
            }
        }
    } else //jeśli jest ppm wykona poniższe opcje
    {
        int(*piksele2)[obrazPtr->wymx * obrazPtr->ppmMnoznik];
        piksele2 = (int (*)[obrazPtr->wymx * obrazPtr->ppmMnoznik]) obrazPtr->obrazTablica;
        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < (obrazPtr->wymx); j++) {
                piksele2[i][3 * j] = tablicaPomocnicza[j][3 * i];
                piksele2[i][3 * j + 1] = tablicaPomocnicza[j][(3 * i) +1];
                piksele2[i][3 * j + 2] = tablicaPomocnicza[j][(3 * i) + 2];
            }
        }
    }
}

void rozmycie_x(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    if ((obrazPtr->typObrazu[1]) == '3') //sprawdza czy to obraz ppm
    {
        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 3; j < ((obrazPtr->ppmMnoznik * obrazPtr->wymx) - 3); j++) {
                piksele[i][j] = (piksele[i][j - 3] + piksele[i][j] + piksele[i][j + 3]) / 3;  // wartosc kazdego koloru w formacie rgb jest srednia aryt.
            }                                                                       // z trzech sasiadujacych, tzn. bierzemy srednia aryt.
        }                                                                            // z koloru czerwonego zielonego i niebieskiego osobno
    } else {
        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 1; j < ((obrazPtr->wymx) - 1); j++) {
                piksele[i][j] = (piksele[i][j - 1] + piksele[i][j] + piksele[i][j + 1]) / 3;  // wartosc piksela jest srednia arytmetyczna z trzech sasiadujacych
            }                                                                       // w jednym wierszu pikseli
        }
    }
}

void rozmycie_y(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 1; i < (obrazPtr->wymy) - 1; i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            piksele[i][j] = (piksele[i - 1][j] + piksele[i][j] + piksele[i + 1][j]) / 3;  // wartosc piksela jest srednia arytmetyczne z sumy
        }                                                                       // piksela srodkowego, piksela nad nim i piksela pod nim
    }
}

void rozciaganieHistogramu(obraz_s *obrazPtr) {
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice

    int wartoscMinJasnosci = obrazPtr->szarosci;      //wartosci skrajne jasnosci obrazu wejsciowego
    int wartoscMaxJasnosci = 0;                       //(narazie zainicjowane wartosciami tymczasowymi)


    //przeszukuje tablice by znalezc rzeczywiste wartosci skrajne jasnosci pixeli
    for (int i = 0; i < (obrazPtr->wymy); i++) {
        for (int j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if (piksele[i][j] > wartoscMaxJasnosci) {
                wartoscMaxJasnosci = piksele[i][j];
            }
            if (piksele[i][j] < wartoscMinJasnosci) {
                wartoscMinJasnosci = piksele[i][j];
            }
        }
    }
    //teraz po znalezieniu wartosci rozpoczynam rozciaganie histogramu
    for (int i = 0; i < (obrazPtr->wymy); i++) {
        for (int j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            piksele[i][j] = (piksele[i][j] - wartoscMinJasnosci) * (obrazPtr->szarosci / (wartoscMaxJasnosci - wartoscMinJasnosci));
        }
    }
}

void konwersjaDoSzarosci(obraz_s *obrazPtr)     //funkcja konwertuje obraz .ppm na format .pgm 
{
    if ((obrazPtr->typObrazu[1]) == '3')  //sprawdzenie czy obraz jest plikiem ppm (kolorowym obrazem)
    {
        int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
        piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
        int i, j;
        int obrazTymczasowy[obrazPtr->wymy][obrazPtr->wymx];  //tworze pomocnicza tablice do przechowywania obrazu

        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < (obrazPtr->wymx); j++) {
                obrazTymczasowy[i][j] = ((piksele[i][(3 * j)] + piksele[i][(3 * j) + 1] + piksele[i][(3 * j) + 2]) / 3);  //wartosc piksela bedzie srednia aryt.
            }                                                                                             //skladowych kolorow obrazu ppm
        }

        sprintf(obrazPtr->typObrazu, "P2\n"); //ustawiamy typ obrazu jako P2
        obrazPtr->ppmMnoznik = 1;              //ustawiamy pomocnicza zmienna na wartosc domyslna
        free(obrazPtr->obrazTablica); //zwalniamy pamiec w ktorej byl przechowywany nasz stary obraz ppm
        obrazPtr->obrazTablica = malloc(obrazPtr->wymx * obrazPtr->wymy * sizeof(int));

        int(*piksele2)[obrazPtr->wymx];
        piksele2 = (int (*)[obrazPtr->wymx]) obrazPtr->obrazTablica;

        for (i = 0; i < (obrazPtr->wymy); i++) {
            for (j = 0; j < (obrazPtr->wymx); j++) {
                piksele2[i][j] = obrazTymczasowy[i][j];    //zapisanie skonwertowanego obrazu do tablicy 'obrazTablica' w strukturze
            }                                            //poprzez uzycie wskaznika piksele2
        }
    } else {
        fprintf(stderr, "Blad: Nie mozna wykonac operacji konwersji do szarosci, nie jest to plik ppm!\n");
    }
}

void progowanieCzerni(obraz_s *obrazPtr, opcje_s *Options) {
    if(Options->wartoscProguCzerniProcent>100||Options->wartoscProguCzerniProcent<0)            //sprawdzenie czy uzytkownik wpisal poprawna wartosc progu
    {
        fprintf(stderr,"Blad: niepoprawna wartosc progu, nalezy wybrac wartosc z przedzialu od 0 do 100.\n");
        exit(1);
    }
    float wartoscProgu = (((float) Options->wartoscProguCzerniProcent) * ((float) obrazPtr->szarosci)) / 100;  //obliczanie wartosci progu jako iloczyn procent progu i maksymalnej szarosci
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if ((piksele[i][j]) <= (int) wartoscProgu) {
                piksele[i][j] = 0;
            }
        }
    }
}

void progowanieBieli(obraz_s *obrazPtr, opcje_s *Options) {
    if(Options->wartoscProguBieliProcent>100||Options->wartoscProguBieliProcent<0)            //sprawdzenie czy uzytkownik wpisal poprawna wartosc progu
    {
        fprintf(stderr,"Blad: niepoprawna wartosc progu, nalezy wybrac wartosc z przedzialu od 0 do 100.\n");
        exit(1);
    }
    float wartoscProgu = (((float) Options->wartoscProguBieliProcent) * ((float) obrazPtr->szarosci)) / 100;  //obliczanie wartosci progu jako iloczyn procent progu i maksymalnej szarosci
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if ((piksele[i][j]) > (int) wartoscProgu) {
                piksele[i][j] = obrazPtr->szarosci;
            }
        }
    }
}

void korekcjaGamma(obraz_s *obrazPtr, opcje_s *Options) {
    double odwrotnoscGamma = 1 / (Options->wartoscKorekcjiGamma); //wartosc 1/gamma potrzebna do wzoru obliczania korekcji gamma
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];                             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica;    //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            piksele[i][j] = (pow(((double) piksele[i][j]) / ((double) obrazPtr->szarosci), odwrotnoscGamma)) * (obrazPtr->szarosci);
        }
    }
}

void zmianaPoziomow(obraz_s *obrazPtr, opcje_s *Options) {
    float nowyPoziomCzerni = (float) obrazPtr->szarosci * ((float) Options->zmianaPoziomowCzern / 100); //nowe poziomy bieli i czerni
    float nowyPoziomBieli = (float) obrazPtr->szarosci * ((float) Options->zmianaPoziomowBiel / 100);   //obliczane jako iloczyn maksymalnej wartosci piksela
    //i podanej procentowej wartosci zmiany poziomu bieli lub czerni
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;
    for (i = 0; i < obrazPtr->wymy; i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if ((piksele[i][j]) <= (int) nowyPoziomCzerni) {
                piksele[i][j] = 0;
            } else if (((piksele[i][j]) > (int) nowyPoziomCzerni) && ((piksele[i][j]) < (int) nowyPoziomBieli)) {
                piksele[i][j] = (piksele[i][j] - (int) nowyPoziomCzerni) * (obrazPtr->szarosci / ((int) nowyPoziomBieli - (int) nowyPoziomCzerni));
            } else if (piksele[i][j] >= (int) nowyPoziomBieli) {
                piksele[i][j] = obrazPtr->szarosci;
            }
        }
    }
}

int czytaj(obraz_s *obrazPtr, opcje_s *Options) /* funkcja odczytujaca obraz i zapisujaca wszystkie dane o nim do struktury obrazPtr */
{
    char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
    int znak;                /* zmienna pomocnicza do czytania komentarzy */
    int koniec = 0;            /* czy napotkano koniec danych w pliku */
    int i, j;

    /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
    if (Options->plikWejPtr == NULL) {
        fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
        return (0);
    }

    /* Sprawdzenie "numeru magicznego" - powinien być P2 lub P3 */
    if (fgets(buf, DL_LINII, Options->plikWejPtr) == NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    {
        koniec = 1;
    }                              /* Nie udalo sie? Koniec danych! */

    if ((buf[0] != 'P') || ((buf[1] != '2') && (buf[1] != '3')) || koniec) {  /* Czy to jest 'P2' lub 'P3' */
        fprintf(stderr, "Blad: To nie jest plik PGM ani PPM\n");
        return (0);
    } else {
        sprintf(obrazPtr->typObrazu, "%s", buf);   //zapisanie typu obrazu do tablicy w strukturze
    }

    /* Pominiecie komentarzy */
    do {
        if ((znak = fgetc(Options->plikWejPtr)) == '#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
            if (fgets(buf, DL_LINII, Options->plikWejPtr) == NULL)  /* Przeczytaj ja do bufora                */
                koniec = 1;                   /* Zapamietaj ewentualny koniec danych */
        } else {
            ungetc(znak, Options->plikWejPtr);                   /* Gdy przeczytany znak z poczatku linii */
        }                                         /* nie jest '#' zwroc go                 */
    } while (znak == '#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
    /* i nie nastapil koniec danych         */

    /* Pobranie wymiarow obrazu, liczby odcieni szarosci i alokacja pamieci dla tablicy */
    if (fscanf(Options->plikWejPtr, "%d %d %d", &(obrazPtr->wymx), &(obrazPtr->wymy), &(obrazPtr->szarosci)) != 3)//pobranie wymiarow obrazu
    {
        fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
        return (0);
    } else  //jesli dobrze wczytano dane, zostanie zaalokowana pamiec dla obrazu w zaleznosci czy to obraz ppm czy pgm
    {
        if ((obrazPtr->typObrazu[1]) == '2') //sprawdza czy to P2 (obraz pgm)
        {
            obrazPtr->obrazTablica = malloc(obrazPtr->wymx * obrazPtr->wymy * sizeof(int));  //rezerwujemy odpowiednio duza tablice
            obrazPtr->ppmMnoznik = 1; //mnozenie nie bedzie wykonywane
        } else //Jesli nie P2, to P3 (czyli obraz ppm)
        {
            obrazPtr->obrazTablica = malloc(3 * obrazPtr->wymx * obrazPtr->wymy * sizeof(int));  //jesli to obraz ppm wymiar x bedzie 3 razy wiekszy
            obrazPtr->ppmMnoznik = 3;
        }
    }

    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];                             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica;    //zmienna pomocnicza wskazuje na tablice

    /* Pobranie obrazu i zapisanie w tablicy obrazTablica za pomoca zmiennej wskaznikowej piksele */
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            if (fscanf(Options->plikWejPtr, "%d", &(piksele[i][j])) != 1) {
                fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
                return (0);
            }
        }
    }
    return ((obrazPtr->wymx) * (obrazPtr->wymy));   /* Czytanie zakonczone sukcesem    */
}      /* Zwroc liczbe wczytanych pikseli */

int zapisz(obraz_s *obrazPtr, opcje_s *Options)        //funkcja zapisujaca przetworzony obraz do wskazanego pliku, zapisujaca komentarz o historii edycji
{
    int (*piksele)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)];             //tworzymy zmienna pomocnicza jako wskaznik na tablice
    piksele = (int (*)[(obrazPtr->wymx) * (obrazPtr->ppmMnoznik)]) obrazPtr->obrazTablica; //zmienna pomocnicza wskazuje na tablice
    int i, j;

    fprintf(Options->plikWyjPtr, "%s", obrazPtr->typObrazu);
    fprintf(Options->plikWyjPtr, "#Na obrazie zostaly wykonane funkcje: %s\n", obrazPtr->komentarz);
    fprintf(Options->plikWyjPtr, "%d %d\n", obrazPtr->wymx, obrazPtr->wymy);
    fprintf(Options->plikWyjPtr, "%d\n", obrazPtr->szarosci);
    for (i = 0; i < (obrazPtr->wymy); i++) {
        for (j = 0; j < (obrazPtr->ppmMnoznik * obrazPtr->wymx); j++) {
            fprintf(Options->plikWyjPtr, "%d ", piksele[i][j]);
        }
        fprintf(Options->plikWyjPtr, "\n");
    }
    return 0;
}
