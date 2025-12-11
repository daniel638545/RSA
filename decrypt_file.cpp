#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rsa.h"

using namespace std;

bool load_private_key(const string &filename, BigInt &d, BigInt &n)
{
    ifstream keyFile(filename);
    if (!keyFile.is_open())
    {
        cerr << "BLAD: Nie mozna otworzyc pliku klucza: " << filename << endl;
        return false;
    }

    string label;
    BigInt e_dummy; // e nie jest potrzebne do deszyfrowania, ale jest w pliku

    if (keyFile >> label >> n >> label >> e_dummy >> label >> d)
    {
        keyFile.close();
        return true;
    }
    else
    {
        cerr << "BLAD: Niepoprawny format pliku klucza." << endl;
        return false;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Uzycie: " << argv[0] << " <plik_klucza> <plik_szyfrogramu>" << endl;
        cout << "Przyklad: " << argv[0] << " keys.txt cipher.txt" << endl;
        return 1;
    }

    string keyFilename = argv[1];
    string cipherFilename = argv[2];

    cout << "--- Narzedzie do deszyfrowania RSA ---\n";

    BigInt d, n;
    cout << "Wczytywanie klucza z: " << keyFilename << "..." << endl;
    if (!load_private_key(keyFilename, d, n))
    {
        return 1;
    }
    cout << "Klucz wczytany pomyslnie.\n";

    ifstream cipherFile(cipherFilename);
    if (!cipherFile.is_open())
    {
        cerr << "BLAD: Nie mozna otworzyc pliku z szyfrogramem: " << cipherFilename << endl;
        return 1;
    }

    string line;
    getline(cipherFile, line);
    getline(cipherFile, line);

    cout << "Deszyfrowanie wiadomosci...\n\n";
    cout << ">>> TRESC WIADOMOSCI: ";

    string cipherLine;
    bool anythingDecrypted = false;
    while (cipherFile >> cipherLine)
    {
        try
        {
            BigInt c(cipherLine);
            BigInt m = RSA_decrypt(c, d, n);

            char decodedChar = static_cast<char>(m.convert_to<int>());
            cout << decodedChar;
            anythingDecrypted = true;
        }
        catch (...)
        {
            cerr << "\n[BLAD podczas przetwarzania fragmentu szyfrogramu]\n";
        }
    }

    if (!anythingDecrypted)
    {
        cout << "(Pusty lub niepoprawny format pliku)";
    }

    cout << "\n\n--- Koniec wiadomosci ---\n";
    cipherFile.close();

    return 0;
}