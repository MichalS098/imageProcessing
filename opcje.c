//Niektore fragmenty kodu modulu pobrane ze strony https://kcir.pwr.edu.pl/~mucha/PProg/index.html 
//Kod zostal zmieniony i przystosowany do dzialania programu

#include <stdio.h>
#include <string.h>
#include "funkcje.h"
#include "opcje.h"

/*********************************************************/
/* Funkcja inicjuje strukture wskazywana przez Options   */
/* PRE:                                                  */
/*      poprawnie zainicjowany argument Options (!=NULL) */
/* POST:                                                 */
/*      "wyzerowana" struktura Options wybranych opcji   */
/*********************************************************/

void wyzeruj_opcje(opcje_s *Options) {
    Options->plikWejPtr = NULL;
    Options->plikWyjPtr = NULL;
    Options->negatyw = 0;
    Options->konturowanie = 0;
    Options->progowanie = 0;
    Options->wyswietlenie = 0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze Options                                   */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         Options -  struktura z informacjami o wywolanych opcjach     */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola dla opcji, ktore  */
/*	    poprawnie wystapily w linii wywolania programu,                 */
/*	    pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	    zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne            */
/*	    lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, opcje_s *Options) {
    int i;

    wyzeruj_opcje(Options);
    Options->plikWyjPtr = stdout;                                         /* na wypadek gdy nie podano opcji "-o" */

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-')                                      /* blad: to nie jest opcja - brak znaku "-" */
        {
            return B_NIEPOPRAWNAOPCJA;
        }
        switch (argv[i][1]) {
            case 'i':                                                    /* opcja z nazwa pliku wejsciowego */
            {
                if (++i < argc) {                             /* wczytujemy kolejny argument jako nazwe pliku */
                    Options->plikWejNazwa = argv[i];
                    if (strcmp(Options->plikWejNazwa, "-") == 0)        /* gdy nazwa jest "-"        */
                    {
                        Options->plikWejPtr = stdin;                   /* ustwiamy wejscie na stdin */
                        fprintf(stderr, "Blad: nie podano pliku do wczytania, wejscie przekierowane na stdin");
                    }
                } else {
                    fprintf(stderr, "Blad: Brak nazwy pliku\n");
                    return B_BRAKNAZWY;                     /* blad: brak nazwy pliku */
                }
                break;
            }
            case 'o':                                       /* opcja z nazwa pliku wyjsciowego */
            {
                if (++i < argc) {                             /* wczytujemy kolejny argument jako nazwe pliku */
                    Options->plikWyjNazwa = argv[i];
                    if (strcmp(Options->plikWyjNazwa, "-") == 0)      /* gdy nazwa jest "-"         */
                    {
                        Options->plikWyjPtr = stdout;                /* ustwiamy wyjscie na stdout */
                        fprintf(stderr, "Blad: nie podano pliku do zapisu, wyjscie przekierowane na stdout");
                    }
                } else {
                    fprintf(stderr, "Blad: Brak nazwy pliku\n");
                    return B_BRAKNAZWY;                     /* blad: brak nazwy pliku */
                }
                break;
            }
            case 'p':                           /* opcja progowanie sprawdzajaca czy uzytkownik wybral */
            {                                   /* ->progowanie zwykle czy progowanie bieli czy progowanie czerni */

                if (argv[i][2] == 'c')//czy wybral '-pc'
                {
                    if (++i < argc) {                             /* wczytujemy kolejny argument jako wartosc progowania czerni */
                        if (sscanf(argv[i], "%d", &(Options->wartoscProguCzerniProcent)) == 1) {
                            Options->progowanieCzerni = 1;
                        } else {
                            fprintf(stderr, "Blad: Niepoprawna wartosc progu\n");
                            return B_BRAKWARTOSCI;
                        }
                    } else {
                        fprintf(stderr, "Blad: Brak wartosci progu\n");
                        return B_BRAKWARTOSCI;
                    }
                } else if (argv[i][2] == 'b')//czy wybral '-pb'
                {
                    if (++i < argc) {                             /* wczytujemy kolejny argument jako wartosc progowania bieli */
                        if (sscanf(argv[i], "%d", &(Options->wartoscProguBieliProcent)) == 1) {
                            Options->progowanieBieli = 1;
                        } else {
                            fprintf(stderr, "Blad: Niepoprawna wartosc progu\n");
                            return B_BRAKWARTOSCI;
                        }
                    } else {
                        fprintf(stderr, "Blad: Brak wartosci progu\n");
                        return B_BRAKWARTOSCI;
                    }
                } else //czy wybral '-p'
                {
                    if (++i < argc) {                             /* wczytujemy kolejny argument jako wartosc progowania */
                        if (sscanf(argv[i], "%d", &(Options->wartoscProguProcent)) == 1) {
                            Options->progowanie = 1;
                        } else {
                            fprintf(stderr, "Blad: Niepoprawna wartosc progu\n");
                            return B_BRAKWARTOSCI;
                        }
                    } else {
                        fprintf(stderr, "Blad: Brak wartosci progu\n");
                        return B_BRAKWARTOSCI;
                    }
                }
                break; //koniec switch opcja progowanie
            }
            case 'g':                                       /* Opcja z korekcja gamma */
            {
                if (++i < argc) {                             /* wczytujemy kolejny argument jako wartosc wspolczynnika */
                    if (sscanf(argv[i], "%lf", &(Options->wartoscKorekcjiGamma)) == 1) {
                        Options->korekcjaGamma = 1;
                    } else {
                        fprintf(stderr, "Blad: Niepoprawna wartosc korekcji gamma\n");
                        return B_BRAKWARTOSCI;              /* blad: niepoprawna wartosc wspolczynnika */
                    }
                } else {
                    fprintf(stderr, "Blad: Brak wartosci korekcji gamma\n");
                    return B_BRAKWARTOSCI;                  /* blad: brak wartosci wspolczynnika */
                }
                break;
            }
            case 'z':                                       /* Opcja zmiany poziomow bieli i czerni */
            {                                               /* Funkcja pobiera wartosci procentowe od 0 do 100% dla zmiany wartosci bieli i czerni */
                if (++i < argc) {                             // wczytujemy kolejny argument jako wartosc wspolczynnika czerni
                    if (sscanf(argv[i], "%d", &(Options->zmianaPoziomowCzern)) == 1) {
                        Options->zmianaPoziomow = 1;
                    } else {
                        fprintf(stderr, "Blad: Niepoprawna wartosc zmiany czerni\n");
                        return B_BRAKWARTOSCI;
                    }
                } else {
                    fprintf(stderr, "Blad: Brak wartosci zmiany czerni\n");
                    return B_BRAKWARTOSCI;
                }
                if (++i < argc) {                             /* wczytujemy kolejny argument jako wartosc wspolczynnika bieli */
                    if (sscanf(argv[i], "%d", &(Options->zmianaPoziomowBiel)) == 1) {}
                    else {
                        fprintf(stderr, "Blad: Niepoprawna wartosc zmiany bieli\n");
                        return B_BRAKWARTOSCI;
                    }
                } else {
                    fprintf(stderr, "Blad: Brak wartosci zmiany bieli\n");
                    return B_BRAKWARTOSCI;
                }
                break;
            }
            case 'm':                                       /* opcja konwersja do szarosci jesli obraz jest typu ppm */
            {
                Options->konwersjaDoSzarosci = 1;
                break;
            }
            case 'n': {                                     /* Opcja z negatywem */
                Options->negatyw = 1;
                break;
            }
            case 't': {                                     /* Opcja z obroceniem o 90 stopni*/
                Options->obrocenie = 1;
                break;
            }
            case 'l': {                                     /* Opcja z lustrzanym odbiciem */
                Options->lustrzaneOdbicie = 1;
                break;
            }
            case 'k': {                                     /* Opcja z konturowaniem */
                Options->konturowanie = 1;
                break;
            }
            case 'd': {                                     /* Wyswietlenie obrazu po przerobieniu */
                Options->wyswietlenie = 1;
                break;
            }
            case 'r':                             /* Opcja rozmycia pionowego lub poziomego obrazu */
            {
                if (argv[i][2] == 'x')               /* czy uzytkownik wybral '-rx' */
                {
                    Options->rozmycie_x = 1;
                } else if (argv[i][2] == 'y')          /* czy uzytkownik wybral '-ry' */
                {
                    Options->rozmycie_y = 1;
                } else {
                    fprintf(stderr, "Blad: niepoprawna opcja do rozmycia obrazu, prosze wybrac -rx lub -ry\n");
                    return B_NIEPOPRAWNAOPCJA;
                }
                break;
            }
            case 'h': {                                     /* Opcja rozciaganie histogramu */
                Options->rozciaganieHistogramu = 1;
                break;
            }
            default:                              /* nierozpoznana opcja */
            {
                fprintf(stderr, "Blad: Nierozpoznana opcja programu\n");
                return B_NIEPOPRAWNAOPCJA;
            }
        } /*koniec switch */
    } /* koniec for */
    return 0;
}