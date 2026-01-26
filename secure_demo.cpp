#include <iostream>
#include <fstream>
#include <string>
#include "rsa.h"

using namespace std;

int main() {
    cout << "Generowanie kluczy...\n";

    BigInt p = get_random_prime_1024();
    BigInt q = get_random_prime_1024();
    while(q == p) q = get_random_prime_1024();

    BigInt n = p * q;
    BigInt phi = (p - 1) * (q - 1);
    BigInt e = 65537;
    BigInt x, y;
    if (euklides(e, phi, x, y) != 1) {
        for(e = 3; e < phi; e += 2)
            if(euklides(e, phi, x, y) == 1) break;
    }
    BigInt d = mod_inverse(e, phi);

    // Zapis kluczy do pliku z opisem
    ofstream keyFile("keys.txt");
    keyFile << "n: " << n << "\n";
    keyFile << "e: " << e << "\n";
    keyFile << "d: " << d << "\n";
    keyFile.close();

    cout << "Klucze zapisane w keys.txt\n";

    // Pobranie wiadomości
    string msg;
    cout << "Podaj wiadomosc do zaszyfrowania: ";
    getline(cin, msg);

    // Zamiana wiadomości na liczby (każdy znak -> jego kod ASCII)
    vector<BigInt> messageNums;
    for(char c : msg) messageNums.push_back((BigInt)c);

    // Szyfrowanie z nagłówkiem
    ofstream cipherFile("cipher.txt");
    cipherFile << "Liczba znakow: " << messageNums.size() << "\n";
    cipherFile << "Szyfrogram:\n";
    for(auto m : messageNums) {
        BigInt c = RSA_encrypt(m, e, n);
        cipherFile << c << "\n";
    }
    cipherFile.close();
    cout << "Wiadomosc zaszyfrowana i zapisana w cipher.txt\n";

    // Deszyfrowanie
    ifstream cipherIn("cipher.txt");
    string line;
    // Pomiń pierwsze dwie linie (nagłówek)
    getline(cipherIn, line);
    getline(cipherIn, line);

    cout << "Odszyfrowana wiadomosc: ";
    while(getline(cipherIn, line)) {
        BigInt c(line);
        BigInt m = RSA_decrypt(c, d, n);
        cout << char(m.convert_to<int>());
    }
    cout << "\n";

    return 0;
}
