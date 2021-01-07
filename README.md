# Przetwarzanie Obrazow

link do gitHuba:[GitHub](github.com/MichalS098/przetwarzanie2)  

## PL

**KOMPILACJA:** wpisujemy w terminalu "make" ,ktory tworzy nam plik wykonywalny  
                a nastepnie wpisujemy "make clean" by usunac pliki z rozszerzeniem .o  
**URUCHAMIANIE:** program wywolujemy poleceniem "./obr (WYBRANE OPCJE)"  
               przyklad:```./obr -i zdj.pgm -o zdj.pgm -n -k```  
               wykonane zostaja operacje negatywu(-n) i konturowania(-k) na obrazie zdj.pgm(-i)  
               a zmieniony obraz zostaje zapisany do tego samego pliku co definiuje opcja -o  

---

Program zajmuje sie edycja obrazow o rozszerzeniach: .ppm .pgm, zostal przystosowany do  
pracy w systemie linux. Do poprawnego dzialanie programu wymagane jest posiadanie oprogramowania ImageMagick,  
ktorego program uzywa do wyswietlania zdjec.  
Po wybraniu odpowiednich opcji przy wywolaniu
pozwala on na wykonanie wielu funkcji wymienionych ponizej:

* ```-i (nazwaPliku)``` opcja po ktorej podajemy nazwe pliku ze zdjeciem do edycji
* ```-o (nazwaPliku)``` opcja po ktorej podajemy nazwe pliku do zapisania obrazu po edycji
* ```-p (WartoscProgu)``` opcja wykonujaca operacje progowania, podajemy jej wartosc progu z zakresu od 0 do 100
* ```-pc (WartoscProgu)``` opcja wykonujaca operacje progowania czerni, podajemy jej wartosc progu z zakresu od 0 do 100
* ```-pb (WartoscProgu)``` opcja wykonujaca operacje progowania bieli, podajemy jej wartosc progu z zakresu od 0 do 100
* ```-g (WartoscKorekcji)``` opcja wykonujaca operacje korekcji gamma, podajemy jej wartosc korekcji gamma, najczesciej z zakresu (0-1)
* ```-z (WartoscCzerni) (WartoscBieli)``` opcja zmiany poziomow bieli i czerni, podajemy jej wartosc zmiany poziomu czerni i bieli
* ```-m``` opcja wykonujaca operacje konwersji do szarosci obrazu ppm
* ```-n``` opcja wykonujaca negatyw
* ```-t``` opcja wykonujaca obrot o 90 stopni w prawo (transpozycja)
* ```-l``` opcja wykonujaca lustrzane odbicie
* ```-k``` opcja wykonujaca konturowanie
* ```-d``` opcja ta wyswietla obraz po wykonaniu edycji
* ```-rx``` opcja wykonuje rozmycie obrazu w poziomie
* ```-ry``` opcja wykonuje rozmycie obrazu w pionie
* ```-h``` opcja wykonujaca operacje rozciagania histogramu  

---

## EN

**COMPILATION:** type into terminal ```make```, this will use the program make  
to compile program and will make executable file called ```obr```, next you have to  
type ```make clean``` to remove files with .o extension.

**EXECUTION:** to run a program you have to type "./obr (Options)"  
Example:```./obr -i pic.pgm -o pic.pgm -n -k -d```  
this will turn the picture pic.pgm into negative(-n) and  
will make contouring(-k). After that picture will be saved in file  
pic.pgm(-o) and will be displayed(-d)  

---

This program deals with editing images with extensions .ppm .pgm, and was adapted to work  
in the linux system. For proper operation of the program, it is required  
to have ImageMagick software, which is used to display images.  
After selecting options when invoked, it allows you to perform many of functions  
listed below:

* ```-i (fileName)``` it takes name of picture file to edit  
* ```-o (fileName)``` saving option, you choose where you want to save picture after editing
* ```-p (thresholdingValue)``` thresholding function, you have to give it value from range 0-100  
* ```-pc (thresholdingValue)``` thresholding function (black), you have to give it value from range 0-100  
* ```-pb (thresholdingValue)``` thresholding function (white), you have to give it value from range 0-100  
* ```-g (CorrectionValue)``` correctiong gamma function, you have to give it a correction value (typically from range 0-1)
* ```-z (BlackValue) (WhiteValue)``` changing level of black and white colors, it takes two values  
* ```-m``` converting .ppm color image to gray scale  
* ```-n``` negative operation on image
* ```-t``` image rotation 90 degrees right  
* ```-l``` mirror reflection effect  
* ```-k``` contouring effect  
* ```-d``` with this options, picture will be displayed after editing  
* ```-rx``` blur the image horizonatlly
* ```-ry``` blur the image vertically
* ```-h``` histogram equalization function

---
