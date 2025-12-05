#ifndef RSA_H
#define RSA_H

#include <vector>

std::vector<bool> sieve_eratosthenes();
std::vector<int> all_primes16();

int random_prime(const std::vector<int>& primes);

long long power_mod(long long a, long long d, long long n);
bool miller_rabin_test(long long n, long long a, long long d, int s);
bool is_probable_prime(long long n, int k = 5);

long long euklides(long long a, long long b, long long& x, long long& y);
long long mod_inverse(long long a, long long m);

#endif
