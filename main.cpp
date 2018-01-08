#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

struct Uzytkownik
{
    int id = 0;
    string login = "", haslo = "";
};

struct Kontakt
{
    int id, idUzytkownika;
    string imie, nazwisko, nr_tel, email, adres;
};

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaZPliku)
{
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaZPliku.length(); pozycjaZnaku++)
    {
        if (daneUzytkownikaZPliku[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownikaZPliku[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.login = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneUzytkownikaZPliku = "";

    fstream plikTekstowy;
    plikTekstowy.open("ListaUzytkownikow.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneUzytkownikaZPliku))
        {
            uzytkownik = pobierzDaneUzytkownika(daneUzytkownikaZPliku);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open("ListaUzytkownikow.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.id << '|';
        plikTekstowy << uzytkownik.login << '|';
        plikTekstowy << uzytkownik.haslo << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Rejestracja przebiegla pomyslnie" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO UZYTKOWNIKA <<<" << endl << endl;

    if (uzytkownicy.empty() == true)
    {
        uzytkownik.id = 1;
    }
    else
    {
        uzytkownik.id = uzytkownicy.back().id + 1;
    }

    cout << "Podaj login: ";
    cin >> uzytkownik.login;

    cout << "Podaj haslo: ";
    cin.sync();
    getline(cin, uzytkownik.haslo);

    uzytkownicy.push_back(uzytkownik);

    dopiszUzytkownikaDoPliku(uzytkownik);
}

int logowanie(vector <Uzytkownik> &uzytkownicy)
{
    string nazwa, haslo;
    cout << "Podaj login uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while(i<uzytkownicy.size())
    {
        if (uzytkownicy[i].login == nazwa)
        {
            for (int proby=0; proby<3; proby++)
            {
                cout << "Masz prob " << 3-proby << " Podaj haslo: ";
                cin >> haslo;

                if (uzytkownicy[i].haslo==haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    system("pause");
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nia ma uzytkownika z takim loginem. Sprobuj ponownie" << endl;
    Sleep(2500);
    return 0;
}

Kontakt pobierzDaneKontaktowe(string daneAdresataZPliku)
{
    Kontakt kontakt;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataZPliku.length(); pozycjaZnaku++)
    {
        if (daneAdresataZPliku[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataZPliku[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                kontakt.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                kontakt.idUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                kontakt.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                kontakt.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                kontakt.nr_tel = pojedynczaDanaAdresata;
                break;
            case 6:
                kontakt.email = pojedynczaDanaAdresata;
                break;
            case 7:
                kontakt.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return kontakt;
}

// funkcja nie jest wykorzystywana
void wczytajKontaktyZPliku(vector <Kontakt> &listaKontaktow)
{
    Kontakt kontakt;
    string daneAdresataZPliku = "";

    fstream plikTekstowy;
    plikTekstowy.open("KsiazkaAdresowa.txt", ios::in);

    if (plikTekstowy.good()==false)
    {
        ofstream plikTekstowy("KsiazkaAdresowa.txt");
        plikTekstowy.close();
    }

    else if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneAdresataZPliku))
        {
            kontakt = pobierzDaneKontaktowe(daneAdresataZPliku);

            listaKontaktow.push_back(kontakt);
        }
        plikTekstowy.close();
    }
}

void wczytajKontaktyZalogowanegoUzytkownika(vector <Kontakt> &kontaktyZalogowanego, int idZalogowanego)
{
    Kontakt kontakt;
    string daneAdresataZPliku = "";

    fstream plikTekstowy;
    plikTekstowy.open("KsiazkaAdresowa.txt", ios::in);

    if (plikTekstowy.good()==false)
    {
        ofstream plikTekstowy("KsiazkaAdresowa.txt");
        plikTekstowy.close();
    }

    else if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneAdresataZPliku))
        {
            kontakt = pobierzDaneKontaktowe(daneAdresataZPliku);
            if(kontakt.idUzytkownika == idZalogowanego)
            {
                kontaktyZalogowanego.push_back(kontakt);
            }
        }
        plikTekstowy.close();
    }
}

void dopiszKontaktDoPliku(Kontakt daneOsoby)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik << daneOsoby.id << '|';
        plik << daneOsoby.idUzytkownika << '|';
        plik << daneOsoby.imie << '|';
        plik << daneOsoby.nazwisko << '|';
        plik << daneOsoby.nr_tel << '|';
        plik << daneOsoby.email << '|';
        plik << daneOsoby.adres << '|' << endl;

        plik.close();
    }
    else cout << "Nie mozna otworzyc pliku" << endl;
}

void dodajAdresata(vector <Kontakt> &adresaci, int idZalogowanegoUzytkownika)
{
    Kontakt kontakt;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    if (adresaci.empty() == true)
    {
        kontakt.id = 1;
    }
    else
    {
        kontakt.id = adresaci.back().id + 1;
    }

    kontakt.idUzytkownika = idZalogowanegoUzytkownika;

    cout << "Podaj imie: ";
    cin >> kontakt.imie;

    cout << "Podaj nazwisko: ";
    cin >> kontakt.nazwisko;

    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, kontakt.nr_tel);

    cout << "Podaj email: ";
    cin >> kontakt.email;

    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, kontakt.adres);

    adresaci.push_back(kontakt);

    dopiszKontaktDoPliku(kontakt);
    cout << endl << kontakt.imie << " " << kontakt.nazwisko << " zostal dodany do KSIAZKI ADRESOWEJ" << endl;
    system("pause");
}

void szukajPoImieniu(vector <Kontakt> &listaKontakow, int zalogowanyID)
{
    string imieDoWyszukania;
    vector <string> znalezioneImiona;
    cout << "Podaj imie: ";
    cin >> imieDoWyszukania;

    int licznikOsob = 0;
    while(licznikOsob < listaKontakow.size())
    {
        if (imieDoWyszukania[0]>95) imieDoWyszukania[0]=imieDoWyszukania[0]-32;
        if ((listaKontakow[licznikOsob].imie==imieDoWyszukania) && (zalogowanyID == listaKontakow[licznikOsob].idUzytkownika))
        {
            znalezioneImiona.push_back (imieDoWyszukania);
            cout << listaKontakow[licznikOsob].imie << " " << listaKontakow[licznikOsob].nazwisko << endl;
            cout << "tel. " << listaKontakow[licznikOsob].nr_tel << ", email: " << listaKontakow[licznikOsob].email << endl;
            cout << "adres: " << listaKontakow[licznikOsob].adres << endl << endl;
            system("pause");
        }
        licznikOsob++;
    }
    if (znalezioneImiona.empty())
    {
        cout << "Nie masz kontaktow o tym imieniu" << endl;
        Sleep(2500);
    }
}

void szukajPoNazwisku(vector <Kontakt> &listaKontakow, int zalogowanyID)
{
    string nazwiskoDoWyszukania;
    vector <string> znalezioneNazwiska;
    cout << "Podaj nazwisko: ";
    cin >> nazwiskoDoWyszukania;

    int licznikOsob = 0;
    while(licznikOsob < listaKontakow.size())
    {
        if (nazwiskoDoWyszukania[0]>95) nazwiskoDoWyszukania[0]=nazwiskoDoWyszukania[0]-32;
        if ((listaKontakow[licznikOsob].nazwisko==nazwiskoDoWyszukania) && (zalogowanyID == listaKontakow[licznikOsob].idUzytkownika))
        {
            znalezioneNazwiska.push_back (nazwiskoDoWyszukania);
            cout << listaKontakow[licznikOsob].imie << " " << listaKontakow[licznikOsob].nazwisko << endl;
            cout << "tel. " << listaKontakow[licznikOsob].nr_tel << ", email: " << listaKontakow[licznikOsob].email << endl;
            cout << "adres: " << listaKontakow[licznikOsob].adres << endl << endl;
            system("pause");
        }
        licznikOsob++;
    }
    if (znalezioneNazwiska.empty())
    {
        cout << "Nie masz kontaktow o tym nazwisku" << endl;
        Sleep(2500);
    }
}

void wyswietlWszystkieKontakty(vector <Kontakt> &wszystkieKontakty, int zalogowanyID)
{
    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        if(zalogowanyID == wszystkieKontakty[licznik].idUzytkownika)
        {
            cout << wszystkieKontakty[licznik].id << " ";
            cout << wszystkieKontakty[licznik].imie << " " << wszystkieKontakty[licznik].nazwisko << endl;
            cout << "tel. " << wszystkieKontakty[licznik].nr_tel << ", email: " << wszystkieKontakty[licznik].email << endl;
            cout << "adres: " << wszystkieKontakty[licznik].adres << endl << endl;
        }
    }
    system("Pause");
}

void wyswietlImionaNazwiska(vector <Kontakt> &wszystkieKontakty, int zalogowanyID)
{
    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        if(zalogowanyID == wszystkieKontakty[licznik].idUzytkownika)
        {
            cout << wszystkieKontakty[licznik].id << " ";
            cout << wszystkieKontakty[licznik].imie << " ";
            cout << wszystkieKontakty[licznik].nazwisko << endl;
        }
    }
}

void aktualizacjaID(vector<Kontakt> &wszystkieKontakty)
{
    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        wszystkieKontakty[i].id = i+1;
    }
}

void usuwanieKontaktu(vector<Kontakt> &wszystkieKontakty, int zalogowanyID)
{
    char potwierdzenie;
    int numerKontaktuDoUsuniecia;

    cout << "Wybierz z listy numer kontaktu do usuniecia: " << endl << endl;
    wyswietlImionaNazwiska(wszystkieKontakty, zalogowanyID);

    cout << "Twoj wybor: ";
    cin >> numerKontaktuDoUsuniecia;

    for(int licznik=0; licznik<wszystkieKontakty.size(); licznik++)
    {
        if(numerKontaktuDoUsuniecia == wszystkieKontakty[licznik].id)
        {
            cout << endl << "Czy na pewno chcesz usunac kontakt: " << wszystkieKontakty[licznik].imie << " " <<wszystkieKontakty[licznik].nazwisko << "? [y/n]";
            cin >> potwierdzenie;
            if(potwierdzenie == 'y')
            {
                cout << endl << "Kontakt " << wszystkieKontakty[licznik].imie << " ";
                cout << wszystkieKontakty[licznik].nazwisko << " zostal usuniety z ksiazki adresowej" << endl;
                wszystkieKontakty.erase(wszystkieKontakty.begin()+licznik);
                system("pause");
            }
        }
    }
    aktualizacjaID(wszystkieKontakty);
    ofstream plik("KsiazkaAdresowa.txt");
    plik << "";
    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        dopiszKontaktDoPliku(wszystkieKontakty[i]);
    }
}

void edycjaDanychOsobowych(vector<Kontakt> &wszystkieKontakty, int zalogowanyID)
{
    int numerKontaktuDoEdycji;
    int numerAtrybutu = 0;

    cout << "Wybierz z listy numer osoby, ktorej dane chcesz edystowac" << '\n' << '\n';
    wyswietlImionaNazwiska(wszystkieKontakty, zalogowanyID);
    //system("pause");

    cout << endl << "podaj numer: ";
    cin >> numerKontaktuDoEdycji;

    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        if(numerKontaktuDoEdycji == wszystkieKontakty[i].id)
        {
            system("cls");

            cout << "Wybierz ktory z atrybutow wybranej osoby chcesz edytowac" << endl << endl;
            cout << "1. imie: " << wszystkieKontakty[i].imie << endl;
            cout << "2. nazwisko: " << wszystkieKontakty[i].nazwisko << endl;
            cout << "3. nr tel: " << wszystkieKontakty[i].nr_tel << endl;
            cout << "4. email: " << wszystkieKontakty[i].email << endl;
            cout << "5. adres: " << wszystkieKontakty[i].adres << endl << endl;
            cout << "6. POWROT DO MENU GLOWNEGO:" << endl;

            cout << "podaj numer atrybutu: ";
            cin >> numerAtrybutu;

            if(numerAtrybutu == 1)
            {
                string noweImie = "";
                cout << "Podaj nowe imie: ";
                cin.sync();
                getline(cin, noweImie);
                wszystkieKontakty[i].imie = noweImie;
            }
            else if(numerAtrybutu == 2)
            {
                string noweNazwisko = "";
                cout << "Podaj nowe nazwisko: ";
                cin.sync();
                getline(cin, noweNazwisko);
                wszystkieKontakty[i].nazwisko = noweNazwisko;
            }
            else if(numerAtrybutu == 3)
            {
                string nowyTel = "";
                cout << "Podaj nowy numer tel: ";
                cin.sync();
                getline(cin, nowyTel);
                wszystkieKontakty[i].nr_tel = nowyTel;
            }
            else if(numerAtrybutu == 4)
            {
                string nowyEmail = "";
                cout << "Podaj nowy email: ";
                cin.sync();
                getline(cin, nowyEmail);
                wszystkieKontakty[i].email = nowyEmail;
            }
            else if(numerAtrybutu == 5)
            {
                string nowyAdres = "";
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, nowyAdres);
                wszystkieKontakty[i].adres = nowyAdres;
            }
            else if(numerAtrybutu == 6)
            {
                break;
            }
            cout << endl << "Dane zostaly poprawnie zmienione";
            system("pause");
        }
    }
    ofstream plik("KsiazkaAdresowa.txt");
    plik << "";
    for(int i=0; i<wszystkieKontakty.size(); i++)
    {
        dopiszKontaktDoPliku(wszystkieKontakty[i]);
    }
}

void aktualizacjaUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open("ListaUzytkownikow.txt", ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.id << '|';
        plikTekstowy << uzytkownik.login << '|';
        plikTekstowy << uzytkownik.haslo << '|' << endl;
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}


void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "haslo zostalo zmienione" << endl;
            system("pause");
        }
    }
    ofstream plik("ListaUzytkownikow.txt");
    plik << "";
    for(int i=0; i<uzytkownicy.size(); i++)
    {
        aktualizacjaUzytkownikaDoPliku(uzytkownicy[i]);
    }
}

void zakonczProgram()
{
    system("cls");
    cout << endl << "Koniec pracy programu..." << endl;
    Sleep(1500);
    exit(0);
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Kontakt> listaKontaktow;
    Kontakt osoba;
    char wybor;
    int idZalogowanegoUzytkownika=0;
    int iloscKontaktow = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);
    //wczytajKontaktyZPliku(listaKontaktow);

    while (1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << ">>> KSIAZKA ADRESOWA - LOGOWANIE <<<" << endl << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = getch();

            switch(wybor)
            {
            case '1':
                system("cls");
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case '2':
                system("cls");
                rejestracja(uzytkownicy);
                break;
            case '9':
                zakonczProgram();
                break;
            }
        }
        else
        {
            if(listaKontaktow.empty() == true)
            {
                wczytajKontaktyZalogowanegoUzytkownika(listaKontaktow, idZalogowanegoUzytkownika);
            }
            system("cls");
            cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukaj kontakt po imieniu" << endl;
            cout << "3. Wyszukaj kontakt po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie kontakty" << endl;
            cout << "5. Edytuj kontakt" << endl;
            cout << "6. Usun kontakt" << endl;
            cout << "7. Zmiana hasla do logowania" << endl;
            cout << "8. Wylogowanie" << endl;
            cout << "9. Zakoncz dzialanie programu" << endl << endl;
            cout << "Wybieram opcje: ";
            wybor=getch();
            cout << endl;

            switch(wybor)
            {
            case '1':
                system("cls");
                dodajAdresata(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '2':
                system("cls");
                szukajPoImieniu(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '3':
                system("cls");
                szukajPoNazwisku(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '4':
                system("cls");
                wyswietlWszystkieKontakty(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '5':
                system("cls");
                edycjaDanychOsobowych(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '6':
                system("cls");
                usuwanieKontaktu(listaKontaktow, idZalogowanegoUzytkownika);
                break;
            case '7':
                system("cls");
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8':
                idZalogowanegoUzytkownika=0;
                break;
            case '9':
                zakonczProgram();
                break;
            }
        }
    }

    return 0;
}
