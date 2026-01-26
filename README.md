# Implementacja Algorytmu RSA w C++
Edukacyjna implementacja RSA w języku C++. Projekt wykorzystuje bibliotekę Boost Multiprecision do obsługi wielkich liczb całkowitych (1024-bitowych i większych).

## Funkcjonalności
Projekt oferuje kompletny zestaw narzędzi do generowania kluczy oraz szyfrowania danych:

- Generowanie kluczy 1024-bitowych: Wykorzystanie generatora liczb losowych oraz testu pierwszości Millera-Rabina do znajdowania dużych liczb pierwszych.
- Implementacja rozszerzonego algorytmu Euklidesa, potęgowania modularnego oraz odwrotności modulo.
- Szyfrowanie i deszyfrowanie: Obsługa zarówno liczb (BigInt), jak i ciągów znaków (tekstu).
- Testy jednostkowe: Wbudowany moduł testujący poprawność algorytmu Euklidesa.
- Obsługa plików: Możliwość zapisu kluczy oraz szyfrogramów do plików tekstowych.

## Wymagania
- Kompilator C++ wspierający standard C++11 lub nowszy.
- Biblioteka Boost (wymagane nagłówki: boost/multiprecision/cpp_int.hpp, boost/random.hpp).

## Struktura
- rsa.h / rsa.cpp: Główna biblioteka zawierająca logikę matematyczną (generowanie liczb pierwszych, operacje modulo, szyfrowanie RSA).
- main.cpp: Główny program demonstracyjny. Testuje algorytm Euklidesa, generuje pary kluczy i szyfruje przykładową liczbę.
- secure_demo.cpp: Rozszerzone demo interaktywne. Pobiera wiadomość od użytkownika, zapisuje klucze do keys.txt, a zaszyfrowaną wiadomość do cipher.txt, po czym ją odszyfrowuje.
- demo.h / demo.cpp: Funkcje pomocnicze do konwersji ciągów tekstowych (std::string) na duże liczby i odwrotnie.
- test.cpp: Zawiera funkcję test_euklides(), która wykonuje 10 000 prób losowych w celu weryfikacji poprawności obliczania NWD i współczynników Bezouta.

## Działanie
### Generowanie liczb pierwszych.
 Program losuje liczby 1024-bitowe, ustawiając najstarszy i najmłodszy bit na 1 (aby zapewnić odpowiednią wielkość i nieparzystość). Następnie liczba jest weryfikowana testem Millera-Rabina (domyślnie 20 iteracji dla wysokiej pewności).

### Szyfrowanie
Klucz publiczny: $(e, n)$ gdzie $e = 65537$ (lub inna liczba pierwsza względem $\phi(n)$).Klucz prywatny: $(d, n)$ obliczany jako odwrotność modulo $e$. Szyfrowanie: $c = m^e \pmod n$.Deszyfrowanie: $m = c^d \pmod n$.

## Autorzy
- Mateusz Hutorowicz
- Daniel Wybranowski
- Michał Zduńczyk


---

