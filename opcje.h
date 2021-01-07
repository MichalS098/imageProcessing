#ifndef OPCJE_H
#define OPCJE_H

    #define W_OK 0                    /* wartosc oznaczajaca brak bledow */
    #define B_NIEPOPRAWNAOPCJA -1     /* kody bledow rozpoznawania opcji */
    #define B_BRAKNAZWY   -2
    #define B_BRAKWARTOSCI  -3
    #define B_BRAKPLIKU   -4

    /* strukura do zapamietywania opcji podanych przy wywolaniu programu */
    struct opcje{
        FILE *plikWejPtr, *plikWyjPtr;       /* uchwyty do pliku wej. i wyj. */
        char *plikWejNazwa, *plikWyjNazwa;   /* Nazwy plikow wej. i wyj. */
        // Opcje : 
        int negatyw;                       
        int progowanie;
        int konturowanie;
        int lustrzaneOdbicie;
        int obrocenie;
        int rozmycie_x;
        int rozmycie_y;
        int rozciaganieHistogramu;
        int korekcjaGamma;
        int progowanieCzerni;
        int progowanieBieli;
        int zmianaPoziomow;
        int konwersjaDoSzarosci;
        int wyswietlenie;
        // Wartosci parametrow funkcji : 
        int wartoscProguProcent;                   
        int wartoscProguBieliProcent;
        int wartoscProguCzerniProcent;
        double wartoscKorekcjiGamma;    
        int zmianaPoziomowBiel;
        int zmianaPoziomowCzern;
    };

    typedef struct opcje opcje_s; /* alias do "struct opcje" = "t_opcje" */

    void wyzeruj_opcje(opcje_s *);

    int przetwarzaj_opcje(int , char **, opcje_s *);

#endif