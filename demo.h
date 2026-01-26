#ifndef DEMO_H
#define DEMO_H

#include "rsa.h"
#include <string>

BigInt string_to_number(const std::string& text);
std::string number_to_string(BigInt number);

BigInt encrypt_text(const std::string& text, const BigInt& e, const BigInt& n);
std::string decrypt_text(const BigInt& cipher, const BigInt& d, const BigInt& n);

#endif
