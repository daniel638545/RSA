#include "demo.h"
#include <iostream>

using namespace std;

BigInt string_to_number(const string& text) {
    BigInt result = 0;
    for (char c : text) {
        result *= 256;
        result += static_cast<unsigned char>(c);
    }
    return result;
}

string number_to_string(BigInt number) {
    string result;
    while (number > 0) {
        char c = static_cast<char>(number % 256);
        result = c + result;
        number /= 256;
    }
    return result;
}

BigInt encrypt_text(const string& text, const BigInt& e, const BigInt& n) {
    BigInt m = string_to_number(text);
    if (m >= n) {
        cerr << "Wiadomosc za dluga dla tego klucza!\n";
        return -1;
    }
    return RSA_encrypt(m, e, n);
}

string decrypt_text(const BigInt& cipher, const BigInt& d, const BigInt& n) {
    BigInt m = RSA_decrypt(cipher, d, n);
    return number_to_string(m);
}
