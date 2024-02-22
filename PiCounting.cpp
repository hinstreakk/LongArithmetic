#include "./header/LongNumbers.hpp"
#include <tuple>
#include <functional>
#include <iostream>
#include <chrono>

LongNumber PiCounting(unsigned int digits)
{
    unsigned tmp = get_accuracy();
    set_accuracy(0);
    LongNumber C(640320), C3_OVER_24 = C * C * C / LongNumber(24);
    LongNumber one(1), two(2), five(5), six(6), sone(-1);
    LongNumber otf("13591409"), fff("545140134");

    std::function<std::tuple<LongNumber, LongNumber, LongNumber>(const int, const int)> binsplit;
    binsplit = [&](const int a, const int b)
    {
        LongNumber Pab, Qab, Tab;
        int m;
        if (b - a == 1)
        {
            LongNumber aA(a);
            if (a == 0)
            {
                Pab = one, Qab = one;
            }
            else
            {
                Pab = (six * aA - five) * (two * aA - one) * (six * aA - one);
                Qab = aA * aA * aA * C3_OVER_24;
            }
            Tab = Pab * (otf + fff * aA);
            if (a & 1)
            {
                Tab = Tab * sone;
            }
        }
        else
        {
            m = (a + b) / 2;
            LongNumber Pam, Qam, Tam, Pmb, Qmb, Tmb;
            std::tie(Pam, Qam, Tam) = binsplit(a, m);
            std::tie(Pmb, Qmb, Tmb) = binsplit(m, b);

            Pab = Pam * Pmb;
            Qab = Qam * Qmb;
            Tab = Qmb * Tam + Pam * Tmb;
        }
        return std::make_tuple(Pab, Qab, Tab);
    };

    int N = digits / 13 + 1;
    LongNumber P, Q, T;
    std::tie(P, Q, T) = binsplit(0, N);
    LongNumber one_squared = power(LongNumber(10), 2 * digits);
    LongNumber sqrtC = LongNumberSqrt(one_squared * LongNumber(10005));
    LongNumber answer = Q * LongNumber(426880) * sqrtC / T;
    set_accuracy(digits);
    answer = answer / power(LongNumber(10), digits);
    set_accuracy(tmp);
    return answer;
}


int main()
{
    std::cout << "Enter the count of number after comma:" << std::endl;
    unsigned len;
    std::cin >> len;
    auto start = std::chrono::steady_clock::now();
    LongNumber x = PiCounting(len);
    auto end = std::chrono::steady_clock::now();
    long_num_print(x);
    std::cout << "The time of counting the first " << len << " decimal places: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
}