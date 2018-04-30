#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <experimental/random>
#include <vector>
    std::vector<std::string> zaladujSlowaZBazy(){
    using namespace std;
        // Funkcja ladujaca zasob slow z bazy
        //
        // chwilowo na sztywno, wciaz potrzebna obsluga pliku i funkcja losujaca
    vector<string> slowa = {"samochod","telefon", "grzegrzolka"};
    return slowa;
}

    std::string wylosujSlowo(/*std::vector<std::string> slowa*/){
        //funkcja losujaca slowo z wczytanej bazy
//    srand(time(0));
        std::vector<std::string> slowa = zaladujSlowaZBazy();
        return slowa[std::experimental::randint(0, sizeof(slowa)-1)];   //experymentalna funkcja randint zwraca pseudolosowa wartosc z przedzialu domknietego
}

    void graj(){
    std::string slowo = wylosujSlowo();
    //Jakas petla zaporowa do obslugi gry
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
}


int main() {
    graj();


    return 0;
}