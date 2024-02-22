#ifndef LONGARITHMETIC_LONGNUMBERS_H
#define LONGARITHMETIC_LONGNUMBERS_H

#include <string>
#include <vector>

struct LongNumber
{
public:
    explicit LongNumber();
    explicit LongNumber(long long x);
    explicit LongNumber(const std::string &str);

    friend void long_num_print(const LongNumber &x);
    friend std::string to_str(const LongNumber &x);
    friend LongNumber LongNumberSqrt(const LongNumber &x);
    friend LongNumber power(const LongNumber &x, unsigned degree);

    friend LongNumber operator +  (const LongNumber &a, const LongNumber &b);
    friend LongNumber operator -  (const LongNumber &a, const LongNumber &b);
    friend LongNumber operator *  (const LongNumber &a, const LongNumber &b);
    friend LongNumber operator /  (const LongNumber &a, const LongNumber &b);
    LongNumber& operator =  (const LongNumber &a);
    friend bool operator >  (const LongNumber &a, const LongNumber &b);
    friend bool operator <  (const LongNumber &a, const LongNumber &b);
    friend bool operator ==  (const LongNumber &a, const LongNumber &b);
    friend bool operator != (const LongNumber &a, const LongNumber &b);

private:
    explicit LongNumber(std::vector<int> integer_part, std::vector<int> fraction_part, int accuracy, bool sign);
    friend void clear_zeros(LongNumber &a);
    friend LongNumber abs(const LongNumber &x);
    std::vector<int> integer_part;
    std::vector<int> fraction_part;
    int accuracy;
    bool sign;
};
LongNumber operator ""_LongNumber (const char *string);
void set_accuracy(unsigned value);
unsigned get_accuracy();

#endif //LONGARITHMETIC_LONGNUMBERS_H
