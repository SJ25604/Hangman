#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>

std::vector<std::string> zaladujSlowaZBazy(){
        using namespace std;
//        deklaracje
        vector<string> slowa;
        ifstream plik;
        string wiersz;

//        obsluga pliku i zapisanie w bazie
        plik.open("../slowa/slowa.txt");
        while (getline(plik, wiersz )){
            slowa.push_back(wiersz);
        }
        plik.close();

        return slowa;
}

    std::string wylosujSlowo(/*std::vector<std::string> slowa*/){
        //funkcja losujaca slowo z wczytanej bazy
        std::vector<std::string> slowa = zaladujSlowaZBazy();

//        rand
/*        srand(time(nullptr));
        int losowa = rand() % slowa.size();*/

//        nowszt i podobno lepszy system generowania liczb pseudolosowych dla c++11
        long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        std::uniform_int_distribution<int> distribution(0, slowa.size());
        int losowa = distribution(generator);

        std::cout<<losowa<<std::endl<<slowa.size()<<std::endl;
        std::string wylosowane = slowa.at(losowa);
        return wylosowane;   //randint jest wspierany od c++14 :(, więc jednak standardowe rozwiązanie
}

    void graj() {
        char jeszczeRaz = '-';
    do{
//    deklaracja zmiennych
        bool odgadniete = false;
        int liczba_dozwolonych_pomylek = 5;
        char znakZakrycia = '_';
        std::vector<char> literySprawdzone;

//    losowanie slowa i zamaiana na vector vectorow charow z informacja o stanie w drugim wymiarze
        std::string slowo = wylosujSlowo();
//        std::cout << slowo << std::endl;       //tylko na chwile, aby sprawdzic poprawnosc funkcji losujacej
        std::vector<char> slowoZnaki(slowo.begin(), slowo.end());
        std::vector<std::vector<char>> slowoZnakiOdgadniete;
        for (auto litera : slowoZnaki) {
            std::vector<char> doWstawienia = {litera, '0'};
            slowoZnakiOdgadniete.push_back(doWstawienia);
        }

//
        //Jakas petla zaporowa do obslugi gry
        while (liczba_dozwolonych_pomylek > 0 && !odgadniete) {

//           deklaracja zmiennych do sprawdzania wystepowania litery w slowie
            char litera;
            bool trafiona = false;

//            wypisanie slowa
            for (auto literaSlowa : slowoZnakiOdgadniete) {
                if (literaSlowa[1] == '1') {
                    std::cout << literaSlowa[0] << ' ';
                } else {
                    std::cout << znakZakrycia << ' ';
                }
            }

//          prosba o podanie litery i informacja o juz sprawdzonych literach
            std::cout << "\nLitery juz sprawdzone: ";
            for (auto literaSprawdzona : literySprawdzone) {
                std::cout << literaSprawdzona << " ";
            }
            std::cout << "\nMozliwych pomylek: " << liczba_dozwolonych_pomylek << "\nWprowadz litere: " << std::endl;

//            przyjecie litery i sprawdzenie, czy nie wprowadzono pustego znaku lub znaku spoza zakresu liter
            do {
                std::cin >> litera;
            } while (!((litera >= 'a' && litera <= 'z') || (litera >= 'A' && litera <= 'Z')));


//            konwersja wprowadzonej litery na mala, poniewaz w bazie slowa skladaja sie z malych liter
            _tolower(litera);

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
            for (int i = 0; i < slowoZnakiOdgadniete.size(); i++) {
                if (slowoZnakiOdgadniete[i][0] == litera) {
                    slowoZnakiOdgadniete[i][1] = '1';
                    trafiona = true;
                }
            }

//            aktualizacja warunkow petli zaporowej
//            w przypadku trafienia literki gra nie zmniejsza dostepnej liczby pomylek,
//            ale sprawdza, czy jest jeszcze cos do zgadywania
            if (trafiona) {
                odgadniete = true;
                for (auto literaSlowa : slowoZnakiOdgadniete) {
                    if (literaSlowa[1] != '1') {
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
        //w petli powinno byc cos, co bedzie kontrolowalo stopien odgadniecia slowa
        //(
        //tu potrzeba kontroli wystepowania danej litery
        //[petla po tablicy, z porownaniem kazdej litery do podanej przez gracza]
        //obsluga podanych juz liter za pomoca vectora charow,
        //podstawianie "_" pod nieodgadniete litery,
        //byc moze przydatna bedzie tu petla dwuwymiarowa
        //w pierwszym wymiarze litery, w drugim informacja o zakryciu/odkryciu
        // ),
        //pozostala liczbe mozliwych pomylek,
        //
        //po petli analiza wyniku -> wygrana/przegrana, odpowiedni komunikat, możliwosc ponownej gry

        if (odgadniete) {
            std::cout << "Brawo! odgadniete slowo: " << slowo << "." << std::endl;
        } else {
            std::cout << "Niestety, nie udalo Ci sie. Slowo, ktore probowales odgadnac to: " << slowo << '.'
                      << std::endl;
        }
        std::cout << "Czy chcesz zagrac jeszcze raz?\nt -> tak\nn -> nie" << std::endl;
        do {
            std::cin >> jeszczeRaz;
        } while (!(jeszczeRaz == 't' || jeszczeRaz == 'T' || jeszczeRaz == 'n' || jeszczeRaz == 'N'));
    }while(jeszczeRaz == 't');
}


int main() {
    graj();


    return 0;
}