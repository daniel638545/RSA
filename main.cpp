#include <iostream>
#include "rsa.h"

using namespace std;

int main()
{
    gen.seed((unsigned)time(NULL));

    test_euklides();

    cout << "Generowanie liczb pierwszych 1024-bitowych...\n";

    BigInt p = get_random_prime_1024();
    BigInt q = get_random_prime_1024();
    while (q == p)
        q = get_random_prime_1024();

    cout << "Wylosowane liczby pierwsze:\n";
    cout << "p = " << p << "\n\n";
    cout << "q = " << q << "\n\n";

    BigInt n = p * q;
    BigInt phi = (p - 1) * (q - 1);
    BigInt e = 65537;

    BigInt x, y;
    if (euklides(e, phi, x, y) != 1)
    {
        cout << "e nie jest względnie pierwsze z phi(n)! Wybieram inne e.\n";
        for (e = 3; e < phi; e += 2)
            if (euklides(e, phi, x, y) == 1)
                break;
    }

    BigInt d = mod_inverse(e, phi);

    cout << "\nKlucz publiczny:  (e = " << e << ",\n n = " << n << ")\n\n";
    cout << "Klucz prywatny:   (d = " << d << ",\n n = " << n << ")\n";

    // Przykladowa wiadomosc
    BigInt message = 123456789;

    cout << "\nWiadomosc oryginalna m = " << message << "\n";

    BigInt cipher = RSA_encrypt(message, e, n);
    cout << "Szyfrogram c = " << cipher << "\n";

    BigInt decrypted = RSA_decrypt(cipher, d, n);
    cout << "Odszyfrowana wiadomosc m = " << decrypted << "\n";

    return 0;
}