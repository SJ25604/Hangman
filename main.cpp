#include <iostream>

    ? zaladujSlowaZBazy(){
    // Funkcja ladujaca zasob slow z bazy
    // jeszcze nie wiem jaki typ danych
}

    ? wylosujSlowo(auto slowa){
    //funkcja losujaca slowo z wczytanej bazy
}

    void graj(? slowo){
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
    ? slowa = zaladujSlowaZBazy();
    ? slowo = wylosujSlowo(slowa);
    graj();


    return 0;
}