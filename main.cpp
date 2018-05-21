#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <locale>

//Structura

struct ZnakZeStanem{
private:
    char znak;
//    true - odgadniety
    bool stan;
//    symbol zasloniecia
    char symbolZasloniecia = '_';

public:

    ZnakZeStanem(char znak) : znak(znak){
        stan = false;
    }

//    funkcja dajaca dostep tylko gdy znak jest odgadniety
    char ustalZnakZeStanem(){
        if(stan){
            return znak;
        }
        else{
            return symbolZasloniecia;
        }
    }

/*    funkcja altualizuje stan w oparciu o wprowadzona litere i
 * jezeli nie byla odgadnieta, a podana jest taka sama jak przechowywana,
 * to stan jest zmieniany a funkcja zwraca 1.
 * Uzywajaca tej funkcji w petli sprawdzajacej trafienia
 * jako składnika dodawania mozna latwo sprawdzic ile podanych liter bylo
 * w badanym slowie
 * */
    int aktualizujStan(char litera){
        if(!stan && znak == litera){
                stan = true;
                return 1;
        }
        return 0;
    }

    char zwrocStan(){
        return stan;
    }
};

std::vector<std::string> zaladujSlowaZBazy(){
        using namespace std;
//        deklaracje
        vector<string> slowa;
        ifstream plik;
        string wiersz;

//        obsluga pliku i zapisanie w bazie
        plik.open("../slowa/slowaMSDOS.txt");

//        petla wpychajaca kazdy wiersz pliku za poprzednim
        while (getline(plik, wiersz )){
            slowa.emplace_back(wiersz);
        }
        plik.close();

        return slowa;
}

//  funkcja zwracajaca slowo o losowym indeksie z wczytanej bazy
    std::string wylosujSlowo(){

        std::vector<std::string> slowa = zaladujSlowaZBazy();

/*        nowszy i podobno lepszy system generowania liczb pseudolosowych
        dla c++11*/
        long long int seed =
                std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        std::uniform_int_distribution<int> distribution(0, (int) slowa.size());

//        zwraca slowo o wylosowanym indeksie
//        std::cout<<losowa<<std::endl<<slowa.size()<<std::endl;
        return slowa.at(distribution(generator));
}

    void graj() {
        char jeszczeRaz = '-';
    do{
//    deklaracja zmiennych
        bool odgadniete = false;
        int liczba_dozwolonych_pomylek = 12;
        std::vector<char> literySprawdzone;

/*        losowanie slowa konwersja na wektor ZnakowZeStanem*/
        std::string slowo = wylosujSlowo();

/*        std::cout << slowo << std::endl;
// tylko na chwile, aby sprawdzic poprawnosc funkcji losujacej*/

        std::vector<ZnakZeStanem> slowoZnaki;

/* Petla przypisujaca znaki ze slowa do utworzonego wektora ZnakowZeStanem
 * emplace_back() w moim rozumieniu w przeciwieńswtie do push_back()
 * nie kopiuje wpierw utworzonej zmiennej na koniec wektora,
 * ale tam ja tworzy.
 * Przy tworzeniu zmiennej uzywany jest konstruktor,
 * ktory nadaje stanowi wartosc false, wiec ostatecznie otrzymujemy
 * wektor nieodgadnietych liter. */
        for(const auto & znak : slowo) {
            slowoZnaki.emplace_back(znak);
        }

        // Petla zaporowa do obslugi gry
        while (liczba_dozwolonych_pomylek > 0 && !odgadniete) {

//           deklaracja zmiennych do sprawdzania wystepowania litery w slowie
            char litera;

//            wypisanie slowa
            for (auto & literaSlowa : slowoZnaki) {
                std::cout<<literaSlowa.ustalZnakZeStanem()<<' ';
            }

//          prosba o podanie litery i informacja o juz sprawdzonych literach
            std::cout << "\nLitery juz sprawdzone: ";
            for (const auto & literaSprawdzona : literySprawdzone) {
                std::cout << literaSprawdzona << " ";
            }
            std::cout << "\nMozliwych pomylek: " << liczba_dozwolonych_pomylek
                      << "\nWprowadz litere: " << std::endl;

//            chwilowo brak testowania poprawnosci wprowadzonego znaku
/*          przyjecie litery i sprawdzenie, czy nie wprowadzono pustego znaku
            lub znaku spoza zakresu liter*/
//            do {
                std::cin >> litera;
                std::cout<<litera<<std::endl;
                _tolower(litera);
//            } while (!((litera >= 'a' && litera <= 'z') || litera == 'Ax5'));



            int liczbaTrafien = 0;
            for (auto & znak : slowoZnaki){
                liczbaTrafien += znak.aktualizujStan(litera);
            }

/*            aktualizacja warunkow petli zaporowej
            w przypadku trafienia literki gra nie zmniejsza dostepnej
            liczby pomylek, ale sprawdza, czy jest jeszcze cos do zgadywania*/
            if (liczbaTrafien) {
                odgadniete = true;
                for (auto & literaSlowa : slowoZnaki) {
                    if (!literaSlowa.zwrocStan()) {
                        odgadniete = false;
/*                        wyjscie z petli, poniewaz juz wiadomo,
                        ze slowo nie jest odgadniete*/
                        break;
                    }
                }
            }
//            w przeciwnym razie status odgadniecia slowa sie nie zmienia,
//            zmniejsza sie za to dostepna liczba pomylek
            else {
                liczba_dozwolonych_pomylek--;
            }

//            dodajemy sprawdzona literke do listy jej podobnych
            literySprawdzone.push_back(litera);


        }


/*        po petli analiza wyniku -> wygrana/przegrana, odpowiedni komunikat,
        możliwosc ponownej gry*/

        if (odgadniete) {
            std::cout << "Brawo! odgadniete slowo: "
                         << slowo << "." << std::endl;
        } else {
            std::cout << "Niestety, nie udalo Ci sie. "
                         "Slowo, ktore probowales odgadnac to: "
                         << slowo << '.' << std::endl;
        }
        std::cout << "Czy chcesz zagrac jeszcze raz?\nt -> tak\nn -> nie"
                     << std::endl;

//        propozycja ponownej gry
        do {
            std::cin >> jeszczeRaz;
            _tolower(jeszczeRaz);
        } while (!(jeszczeRaz == 't' || jeszczeRaz == 'n'));
    }while(jeszczeRaz == 't');
}


int main() {
    graj();


    return 0;
}