#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

using BigInt = cpp_int;

typedef independent_bits_engine<mt19937, 1024, BigInt> generator_type;

// Tworzymy globalny generator (zainicjowany czasem)
generator_type gen(clock());

// Potęgowanie modularne: (a^d) % n
BigInt power_mod(BigInt a, BigInt d, BigInt n)
{
    BigInt result = 1;
    a = a % n;
    while (d > 0)
    {
        if ((d & 1))
            result = result * a % n;
        a = a * a % n;
        d >>= 1;
    }
    return result;
}

bool miller_rabin_test(BigInt n, BigInt a, BigInt d, int s)
{
    BigInt x = power_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    for (int r = 1; r < s; r++)
    {
        x = x * x % n;
        if (x == n - 1)
            return true;
    }
    return false;
}

bool is_probable_prime(BigInt n, int k = 5)
{
    if (n < 2)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    BigInt d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    boost::random::uniform_int_distribution<BigInt> dist(2, n - 2);

    for (int i = 0; i < k; i++)
    {
        BigInt a = dist(gen);
        if (!miller_rabin_test(n, a, d, s))
            return false;
    }
    return true;
}

BigInt get_random_prime_1024()
{
    BigInt n;
    while (true)
    {
        n = gen();
        bit_set(n, 1023);
        bit_set(n, 0);

        if (is_probable_prime(n, 20))
        {
            return n;
        }
    }
}

//  Algorytm Euklidesa
BigInt euklides(BigInt a, BigInt b, BigInt &x, BigInt &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    BigInt x1, y1;
    BigInt g = euklides(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a % b);
    return g;
}

BigInt mod_inverse(BigInt a, BigInt m)
{
    BigInt x, y;
    BigInt g = euklides(a, m, x, y);
    if (g != 1)
        return -1;
    return (x % m + m) % m;
}

int main()
{
    gen.seed((unsigned)time(NULL));

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

    return 0;
}