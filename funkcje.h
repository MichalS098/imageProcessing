#ifndef FUNKCJE_H
#define FUNKCJE_H

    #include "opcje.h"        /* Dodajemy plik naglowkowy zawierajacy definicje nazwy opcje_s */
    #define MAX 1024          /* Maksymalny rozmiar wczytywanego obrazu */
    #define DL_LINII 512      /* Dlugosc buforow pomocniczych */
    #define TYP_OBRAZU 64

    struct obraz{
        char komentarz[MAX];            /* Tablica zawierajaca komentarz dopisywany do zdjecia */
        char typObrazu[TYP_OBRAZU];     
        void *obrazTablica;    /* Tablica zawierajaca obraz (info. nt. jego pikseli) */
        int wymx;
        int wymy;
        int szarosci;
        int ppmMnoznik;     // mnoznik do zmiennej wymx,uzywany w petlach przy wyborze obrazu ppm                                     
    };                      // by iteracje w poziomie trwaly 3 razy dluzej 

    typedef struct obraz obraz_s;    /* tworze alias do 'struct obraz' jako obraz_s */

    void wyswietl(opcje_s *);
    void progowanie(obraz_s *, opcje_s *);
    void konturowanie(obraz_s *);
    void lustrzaneOdbicie(obraz_s *);
    void negatyw(obraz_s *);
    void obrocenie(obraz_s *);
    void rozmycie_x(obraz_s *);
    void rozmycie_y(obraz_s *);
    void rozciaganieHistogramu(obraz_s *);
    void progowanieCzerni(obraz_s *, opcje_s *);
    void progowanieBieli(obraz_s *, opcje_s *);
    void korekcjaGamma(obraz_s *, opcje_s *);
    void zmianaPoziomow(obraz_s *, opcje_s *);
    void konwersjaDoSzarosci(obraz_s *);
    int czytaj(obraz_s *, opcje_s *);
    int zapisz(obraz_s *, opcje_s *);
    
#endif