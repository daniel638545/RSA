#include <iostream>
#include "rsa.h"

using namespace std;

int main()
{
    vector<int> primes = all_primes16();

    long long p = random_prime(primes);
    long long q = random_prime(primes);

    while (q == p)
        q = random_prime(primes);

    cout << "Wylosowane liczby pierwsze:\n";
    cout << "p = " << p << "\n";
    cout << "q = " << q << "\n";

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 65537; // standardowa wartość

    long long x, y;
    if (euklides(e, phi, x, y) != 1)
    {
        cout << "e nie jest względnie pierwsze z phi(n)! Wybieram inne e.\n";
        for (e = 3; e < phi; e++)
            if (euklides(e, phi, x, y) == 1)
                break;
    }

    long long d = mod_inverse(e, phi);

    cout << "\nKlucz publiczny:  (e = " << e << ", n = " << n << ")\n";
    cout << "Klucz prywatny:   (d = " << d << ", n = " << n << ")\n";

    return 0;
}
