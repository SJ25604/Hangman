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

    char ustalZnakZeStanem(){
        if(stan){
            return znak;
        }
        else{
            return symbolZasloniecia;
        }
    }

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
        while (getline(plik, wiersz )){
            slowa.push_back(wiersz);
        }
        plik.close();

        return slowa;
}

//  funkcja losujaca slowo z wczytanej bazy
    std::string wylosujSlowo(/*std::vector<std::string> slowa*/){

        std::vector<std::string> slowa = zaladujSlowaZBazy();

//        rand
/*        srand(time(nullptr));
        int losowa = rand() % slowa.size();*/

/*        nowszy i podobno lepszy system generowania liczb pseudolosowych
        dla c++11*/
        long long int seed =
                std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        std::uniform_int_distribution<int> distribution(0, slowa.size());
        int losowa = distribution(generator);

        std::cout<<losowa<<std::endl<<slowa.size()<<std::endl;
        std::string wylosowane = slowa.at(losowa);
        return wylosowane;
}

    void graj() {
        char jeszczeRaz = '-';
    do{
//    deklaracja zmiennych
        bool odgadniete = false;
        int liczba_dozwolonych_pomylek = 10;
        std::vector<char> literySprawdzone;

/*        losowanie slowa i zamaiana na vector vectorow charow z informacja
        o stanie w drugim wymiarze*/
        std::string slowo = wylosujSlowo();

        std::cout << slowo << std::endl;
// tylko na chwile, aby sprawdzic poprawnosc funkcji losujacej

        std::vector<ZnakZeStanem> slowoZnaki;
        for(auto znak : slowo){
//            ZnakZeStanem doDodania = ZnakZeStanem(znak);
            slowoZnaki.emplace_back(znak);
        }
/*        std::vector<char> slowoZnaki(slowo.begin(), slowo.end());
        std::vector<std::vector<char>> slowoZnakiOdgadniete;
        for (auto litera : slowoZnaki) {
            std::vector<char> doWstawienia = {litera, '0'};
            slowoZnakiOdgadniete.push_back(doWstawienia);
        }*/

//
        //Jakas petla zaporowa do obslugi gry
        while (liczba_dozwolonych_pomylek > 0 && !odgadniete) {

//           deklaracja zmiennych do sprawdzania wystepowania litery w slowie
            char litera;

//            wypisanie slowa
            for (auto literaSlowa : slowoZnaki) {
/*                if (literaSlowa[1] == '1') {
                    std::cout << literaSlowa[0] << ' ';
                } else {
                    std::cout << znakZakrycia << ' ';
                }*/
                std::cout<<literaSlowa.ustalZnakZeStanem()<<' ';
            }

//          prosba o podanie litery i informacja o juz sprawdzonych literach
            std::cout << "\nLitery juz sprawdzone: ";
            for (auto literaSprawdzona : literySprawdzone) {
                std::cout << literaSprawdzona << " ";
            }
            std::cout << "\nMozliwych pomylek: " << liczba_dozwolonych_pomylek
                      << "\nWprowadz litere: " << std::endl;

/*          przyjecie litery i sprawdzenie, czy nie wprowadzono pustego znaku
            lub znaku spoza zakresu liter*/
            do {
                std::cin >> litera;
                _tolower(litera);
            } while (!(litera >= 'a' && litera <= 'z'));


/*            konwersja wprowadzonej litery na mala,
            poniewaz w bazie slowa skladaja sie z malych liter*/

//            sprawdzenie
/*            for(int i = 0; i < slowoZnaki.size(); i++){

            }*/

//            czy litera wystepuje
/*            for(auto literaSlowa : slowoZnakiOdgadniete){
                if(literaSlowa[0] == litera){
                    literaSlowa[1] = 1;
                    trafiona = true;
                }
            }*/
/*            for (int i = 0; i < slowoZnakiOdgadniete.size(); i++) {
                if (slowoZnakiOdgadniete[i][0] == litera) {
                    slowoZnakiOdgadniete[i][1] = '1';
                    trafiona = true;
                }
            }*/
            int liczbaTrafien = 0;
            for (auto & znak : slowoZnaki){
                liczbaTrafien += znak.aktualizujStan(litera);
            }

/*            aktualizacja warunkow petli zaporowej
            w przypadku trafienia literki gra nie zmniejsza dostepnej
            liczby pomylek, ale sprawdza, czy jest jeszcze cos do zgadywania*/
            if (liczbaTrafien) {
                odgadniete = true;
                for (auto literaSlowa : slowoZnaki) {
                    if (!literaSlowa.zwrocStan()) {
                        odgadniete = false;
                    }
                }
            }
//            w przeciwnym razie status odgadniecia slowa sie nie zmienia,
//            zmniejsza sie za to dostepna liczba pomylek
            else {
                liczba_dozwolonych_pomylek--;
            }
            literySprawdzone.push_back(litera);


        }
/*        w petli powinno byc cos, co bedzie kontrolowalo stopien
 *        odgadniecia slowa
        (
        tu potrzeba kontroli wystepowania danej litery
        [petla po tablicy, z porownaniem kazdej litery do podanej przez gracza]
        obsluga podanych juz liter za pomoca vectora charow,
        podstawianie "_" pod nieodgadniete litery,
        byc moze przydatna bedzie tu petla dwuwymiarowa
        w pierwszym wymiarze litery, w drugim informacja o zakryciu/odkryciu
         ),
        pozostala liczbe mozliwych pomylek,

        po petli analiza wyniku -> wygrana/przegrana, odpowiedni komunikat,
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