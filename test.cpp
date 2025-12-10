#include "rsa.h"

using namespace std;

void test_euklides() {
    cout << "--- Rozpoczynam test poprawnosci zaimplementowanego algorytmu Euklidesa ---\n";
    
    int test_cycles = 10000;
    int err = 0;

    for (int i = 0; i < test_cycles; i++) {
        BigInt a = gen();
        BigInt b = gen();

        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (a == 0) a = 1;
        if (b == 0) b = 1;

        BigInt x, y;
        BigInt nwd = euklides(a, b, x, y);
        BigInt check_ = a * x + b * y;
        bool div_a = (a % nwd == 0);
        bool div_b = (b % nwd == 0);

        if (check_ != nwd || !div_a || !div_b) {
            cout << "[BLAD] Test nr " << i << " nieudany!\n";
            cout << "Dla a=" << a << ", b=" << b << "\n";
            cout << "Otrzymano x=" << x << ", y=" << y << ", NWD=" << nwd << "\n";
            cout << "Wynik równania a*x + b*y = " << check_ << "\n";
            err++;
            break;
        }
    }

    if (err == 0) {
        cout << "[SUKCES] Przetestowano " << test_cycles << " losowych par. Wszystkie wyniki poprawne.\n";
    } else {
        cout << "[PORAZKA] Znaleziono błędy w implementacji!\n";
    }
    cout << "----------------------------------------------\n\n";
}