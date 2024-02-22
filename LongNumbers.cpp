#include "../header/LongNumbers.hpp"
#include <algorithm>
#include <tuple>
#include <functional>

namespace
{
    unsigned gAccuracy = 15;
}

LongNumber operator ""_LongNumber (const char *string)
{
    LongNumber a(string);
    return a;
}


LongNumber::LongNumber()
{
    integer_part.resize(1, 0);
    fraction_part.resize(0);
    accuracy = 0;
    sign = true;
}

LongNumber::LongNumber(long long int x)
{
    if (x > 0)
    {
        sign = true;
    }
    else
    {
        sign = false;
        x = x * (-1);
    }
    while(x > 0)
    {
        integer_part.push_back(x % 10);
        x = x / 10;
    }
    fraction_part.resize(0);
    accuracy = 0;
}

LongNumber::LongNumber(const std::string &str)
{
    sign = true;
    int i = 0;
    int len = (int)str.length();
    while(str[i] != '.' && i <= len - 1)
    {
        if (str[i] == '-')
        {
            sign = false;
            i++;
            continue;
        }
        integer_part.push_back(int(str[i] - '0'));
        i++;
    }
    std::reverse(integer_part.begin(), integer_part.end());
    i++;
    accuracy = len - i;
    if (accuracy < 0)
    {
        accuracy = 0;
    }
    while (i <= len - 1)
    {
        fraction_part.push_back(int(str[i] - '0'));
        i++;
    }
    std::reverse(fraction_part.begin(), fraction_part.end());
}

LongNumber::LongNumber(std::vector<int> integer_part, std::vector<int> fraction_part, int accuracy, bool sign)
{
    this->sign = sign;
    this->accuracy = accuracy;
    this->integer_part = std::move(integer_part);
    this->fraction_part = std::move(fraction_part);
}

void set_accuracy(unsigned value)
{
    gAccuracy = value;
}

unsigned get_accuracy()
{
    return gAccuracy;
}

void long_num_print(const LongNumber &x)
{
    if (!x.sign)
    {
        printf("-");
    }
    for (int i = (int)x.integer_part.size() - 1; i >= 0; i--)
    {
        printf("%d", x.integer_part[i]);
    }
    if (x.accuracy != 0)
    {
        printf(".");
    }
    for (int i = (int)x.fraction_part.size() - 1; i >= 0; i--)
    {
        printf("%d", x.fraction_part[i]);
    }
    printf("\n");
    //printf("%d %d", x.accuracy, x.sign);
    printf("\n");
}

void clear_zeros(LongNumber &a)
{
    int i = a.integer_part.size() - 1;
    while (a.integer_part[i] == 0 && a.integer_part.size() > 1)
    {
        a.integer_part.pop_back();
        i--;
    }
    i = a.fraction_part.size() - 1;
    if (i < 0)
    {
        i = 0;
    }
    std::reverse(a.fraction_part.begin(),a.fraction_part.end());
    if (a.fraction_part.size() != 0)
    {
        while (a.fraction_part[i] == 0)
        {
            a.fraction_part.pop_back();
            a.accuracy--;
            i--;
        }
    }
    std::reverse(a.fraction_part.begin(),a.fraction_part.end());
}

std::string to_str(const LongNumber &x)
{
    std::string s;
    if (!x.sign)
    {
        s += '-';
    }
    for (int i = x.integer_part.size() - 1; i >= 0; i--)
    {
        s += x.integer_part[i] + '0';
    }
    if (x.fraction_part.size() != 0)
    {
        s += '.';
        for (int i = x.fraction_part.size() - 1; i >= 0; i--)
        {
            s += x.fraction_part[i] + '0';
        }
    }
    return s;
}

LongNumber abs(const LongNumber &x)
{
    LongNumber a = x;
    a.sign = true;
    return a;
}

LongNumber &LongNumber::operator = (const LongNumber &a)
{
    this->fraction_part = a.fraction_part;
    this->integer_part = a.integer_part;
    this->sign = a.sign;
    this->accuracy = a.accuracy;
    return *this;
}

LongNumber operator + (const LongNumber &a, const LongNumber &b)
{
    std::vector<int> integer_result, fraction_result;
    int next_digit_one = 0;
    int pre_res = 0;

    if (a.sign && !b.sign)
    {
        LongNumber temp = b;
        temp.sign = true;
        return a - temp;
    }
    if (!a.sign && b.sign)
    {
        LongNumber temp = a;
        temp.sign = true;
        return b - temp;
    }

    LongNumber c = LongNumber(a.integer_part, a.fraction_part, a.accuracy, a.sign);
    LongNumber d = LongNumber(b.integer_part, b.fraction_part, b.accuracy, b.sign);
    while (c.fraction_part.size() != d.fraction_part.size())
    {
        if (c.fraction_part.size() > d.fraction_part.size())
        {
            d.fraction_part.insert(d.fraction_part.cbegin(), 0);
        }
        else
        {
            c.fraction_part.insert(c.fraction_part.cbegin(), 0);
        }
    }

    int min_size = std::min(c.fraction_part.size(), d.fraction_part.size());
    int max_size = std::max(c.fraction_part.size(), d.fraction_part.size());
    for (int i = 0; i < min_size; i++)
    {
        pre_res = next_digit_one + c.fraction_part[i] + d.fraction_part[i];
        fraction_result.push_back(pre_res % 10);
        next_digit_one = pre_res / 10;
    }
    for (int i = min_size; i < max_size; i++)
    {
        if (c.fraction_part.size() > d.fraction_part.size())
        {
            pre_res = next_digit_one + c.fraction_part[i];
        }
        else
        {
            pre_res = next_digit_one + d.fraction_part[i];
        }
        fraction_result.push_back(pre_res % 10);
        next_digit_one = pre_res / 10;
    }

    min_size = std::min(a.integer_part.size(), b.integer_part.size());
    max_size = std::max(a.integer_part.size(), b.integer_part.size());
    for (int i = 0; i < min_size; i++)
    {
        pre_res = next_digit_one + a.integer_part[i] + b.integer_part[i];
        integer_result.push_back(pre_res % 10);
        next_digit_one = pre_res / 10;
    }
    for (int i = min_size; i < max_size; i++)
    {
        if (a.integer_part.size() > b.integer_part.size())
        {
            pre_res = next_digit_one + a.integer_part[i];
        }
        else
        {
            pre_res = next_digit_one + b.integer_part[i];
        }
        integer_result.push_back(pre_res % 10);
        next_digit_one = pre_res / 10;
    }

    if (next_digit_one != 0)
    {
        integer_result.push_back(next_digit_one);
    }

    LongNumber sum = LongNumber(integer_result, fraction_result, fraction_result.size(), a.sign);
    clear_zeros(sum);
    return sum;
}

LongNumber operator - (const LongNumber &a, const LongNumber &b)
{
    if (a == b)
    {
        return LongNumber();
    }

    std::vector<int> integer_result, fraction_result;
    int pre_digit_one = 0;
    int pre_res = 0;

    if (a.sign && !b.sign)
    {
        LongNumber temp = b;
        temp.sign = true;
        return a + temp;
    }
    if (!a.sign && b.sign)
    {
        LongNumber x = a;
        x.sign = true;
        LongNumber y = x + b;
        y.sign = false;
        return y;
    }

    if (b > a)
    {
        LongNumber c = b - a;
        c.sign = false;
        return c;
    }

    if (a.fraction_part.size() != 0 || b.fraction_part.size() != 0)
    {
        LongNumber c = LongNumber(a.integer_part, a.fraction_part, a.accuracy, a.sign);
        LongNumber d = LongNumber(b.integer_part, b.fraction_part, b.accuracy, b.sign);
        std::reverse(d.fraction_part.begin(), d.fraction_part.end());
        std::reverse(c.fraction_part.begin(), c.fraction_part.end());
        while (c.fraction_part.size() != d.fraction_part.size())
        {
            if (c.fraction_part.size() > d.fraction_part.size())
            {
                d.fraction_part.push_back(0);
            }
            if (d.fraction_part.size() > c.fraction_part.size())
            {
                c.fraction_part.push_back(0);
            }
        }
        std::reverse(d.fraction_part.begin(), d.fraction_part.end());
        std::reverse(c.fraction_part.begin(), c.fraction_part.end());


        for (int i = 0; i < d.fraction_part.size(); i++)
        {
            pre_res = c.fraction_part[i] - d.fraction_part[i] - pre_digit_one;
            if (pre_res >= 0)
            {
                pre_digit_one = 0;
            }
            else
            {
                pre_res += 10;
                pre_digit_one = 1;
            }
            fraction_result.push_back(pre_res);
        }
        for (int i = d.fraction_part.size(); i < c.fraction_part.size(); i++)
        {
            if (c.fraction_part[i] - pre_digit_one >= 0)
            {
                fraction_result.push_back(c.fraction_part[i] - pre_digit_one);
                pre_digit_one = 0;
            }
            else
            {
                fraction_result.push_back(c.fraction_part[i] + 10 - pre_digit_one);
                pre_digit_one = 1;
            }
        }
    }

    for (int i = 0; i < b.integer_part.size(); i++)
    {
        pre_res = a.integer_part[i] - b.integer_part[i] - pre_digit_one;
        if (pre_res >= 0)
        {
            pre_digit_one = 0;
        }
        else
        {
            pre_res += 10;
            pre_digit_one = 1;
        }
        integer_result.push_back(pre_res);
    }
    for (int i = b.integer_part.size(); i < a.integer_part.size(); i++)
    {
        if (a.integer_part[i] - pre_digit_one >= 0)
        {
            integer_result.push_back(a.integer_part[i] - pre_digit_one);
            pre_digit_one = 0;
        }
        else
        {
            integer_result.push_back(a.integer_part[i] + 10 - pre_digit_one);
            pre_digit_one = 1;
        }
    }

    while (integer_result.size() > 1 && integer_result.back() == 0)
    {
        integer_result.pop_back();
    }

    if (a > b)
    {
        LongNumber diff = LongNumber(integer_result, fraction_result, fraction_result.size(), a.sign);
        clear_zeros(diff);
        return diff;
    }
    else
    {
        LongNumber diff = LongNumber(integer_result, fraction_result, fraction_result.size(), b.sign);
        clear_zeros(diff);
        return diff;
    }
}

bool operator > (const LongNumber &a, const LongNumber &b)
{
    if (a.sign && !b.sign)
    {
        return true;
    }
    else if (!a.sign && b.sign)
    {
        return false;
    }

    if (a.integer_part.size() > b.integer_part.size())
    {
        return true;
    }
    else if (b.integer_part.size() > a.integer_part.size())
    {
        return false;
    }
    else
    {
        for (int i = a.integer_part.size() - 1; i >= 0; i--)
        {
            if (a.integer_part[i] == b.integer_part[i])
            {
                continue;
            }

            if (a.integer_part[i] > b.integer_part[i])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    if (a.fraction_part.size() != 0 && b.fraction_part.size() == 0)
    {
        return true;
    }
    else if (b.fraction_part.size() != 0 && a.fraction_part.size() == 0)
    {
        return false;
    }

    if (a.fraction_part.size() != 0 && b.fraction_part.size() != 0)
    {
        for (int i = std::min(a.fraction_part.size(), b.fraction_part.size()) - 1; i >= 0; i--)
        {
            if (a.fraction_part[i] == b.fraction_part[i])
            {
                continue;
            }

            if (a.fraction_part[i] > b.fraction_part[i])
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (a.fraction_part.size() > b.fraction_part.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool operator < (const LongNumber &a, const LongNumber &b)
{
    return !(a > b || a == b);
}

bool operator == (const LongNumber &a, const LongNumber &b)
{
    if (a.sign != b.sign || a.accuracy != b.accuracy || a.integer_part.size() != b.integer_part.size())
    {
        return false;
    }

    for (int i = 0; i < std::min(a.integer_part.size(), b.integer_part.size()); i++)
    {
        if (a.integer_part[i] != b.integer_part[i])
        {
            return false;
        }
    }
    for (int i = 0; i < std::min(a.fraction_part.size(), b.fraction_part.size()); i++)
    {
        if (a.fraction_part[i] != b.fraction_part[i])
        {
            return false;
        }
    }

    return true;
}

bool operator != (const LongNumber &a, const LongNumber &b)
{
    if (a == b)
    {
        return false;
    }
    return true;
}

LongNumber operator * (const LongNumber &a, const LongNumber &b)
{
    std::vector<int> new_a;
    std::vector<int> new_b;

    if (a.fraction_part.size() != 0)
    {
        for (int i = 0; i < a.fraction_part.size(); i++)
        {
            new_a.push_back(a.fraction_part[i]);
        }
    }
    for (int i = 0; i < a.integer_part.size(); i++)
    {
        new_a.push_back(a.integer_part[i]);
    }

    if (b.fraction_part.size() != 0)
    {
        for (int i = 0; i < b.fraction_part.size(); i++)
        {
            new_b.push_back(b.fraction_part[i]);
        }
    }
    for (int i = 0; i < b.integer_part.size(); i++)
    {
        new_b.push_back(b.integer_part[i]);
    }
    std::reverse(new_a.begin(), new_a.end());
    std::reverse(new_b.begin(), new_b.end());


    int len = new_a.size() + new_b.size();

    std::vector<int> res = std::vector<int>(len, 0);

    for (int i = 0; i < new_a.size(); i++)
    {
        for (int j = 0; j < new_b.size(); j++)
        {
            res[i + j + 1] += new_a[i] * new_b[j];
        }
    }
    for (int i = len - 1; i > 0; i--)
    {
        res[i - 1] = res[i - 1] + res[i] / 10;
        res[i] = res[i] % 10;
    }
    std::reverse(res.begin(), res.end());

    int res_accuracy = a.accuracy + b.accuracy;
    bool res_sign = true;
    if ((!a.sign && b.sign) || (a.sign && !b.sign))
    {
        res_sign = false;
    }
    LongNumber product = LongNumber();
    product.integer_part.pop_back();
    product.sign = res_sign;
    product.accuracy = res_accuracy;
    for (int i = 0; i < res_accuracy; i++)
    {
        product.fraction_part.push_back(res[i]);
    }
    for (int i = res_accuracy; i < len; i++)
    {
        product.integer_part.push_back((res[i]));
    }

    clear_zeros(product);
    return product;
}

LongNumber operator / (const LongNumber &a, const LongNumber &b)
{
    if (b == 0_LongNumber)
    {
        throw "Error: division by zero!\n";
    }
    if (a == 0_LongNumber)
    {
        return 0_LongNumber;
    }
    LongNumber c = abs(a), d = abs(b);
    bool res_sign;
    if (a.sign == b.sign)
    {
        res_sign = true;
    }
    else
    {
        res_sign = false;
    }
    if (c == d)
    {
        return 1_LongNumber;
    }
    if (d == LongNumber(1))
    {
        c.sign = res_sign;
        return c;
    }

    unsigned normalized = std::max(c.accuracy, d.accuracy);
    for (int i = 0; i < normalized; i++)
    {
        if (c.accuracy > 0)
        {
            c.integer_part.insert(c.integer_part.cbegin(), c.fraction_part.back());
            c.fraction_part.pop_back();
            c.accuracy--;
        }
        else
        {
            c.integer_part.insert(c.integer_part.cbegin(), 0);
        }
        if (d.accuracy > 0)
        {
            d.integer_part.insert(d.integer_part.cbegin(), d.fraction_part.back());
            d.fraction_part.pop_back();
            d.accuracy--;
        }
        else
        {
            d.integer_part.insert(d.integer_part.cbegin(), 0);
        }
    }

    while (c.integer_part.size() > 1 && !c.integer_part.back())
    {
        c.integer_part.pop_back();
    }
    while (d.integer_part.size() > 1 && !c.integer_part.back())
    {
        d.integer_part.pop_back();
    }

    int shift = 0;
    for (int i = 0; i < a.accuracy + b.accuracy || i < gAccuracy; i++, shift++)
    {
        c.integer_part.insert(c.integer_part.cbegin(), 0);
    }
    while (c < d)
    {
        c.integer_part.insert(c.integer_part.cbegin(), 0);
        shift++;
    }

    LongNumber low(0), high = c, mid, quotient(0);
    while (low < high || low == high)
    {
        mid = low + (high - low) * 0.5_LongNumber;
        mid.fraction_part.clear();
        mid.accuracy = 0;
        if (mid * d > c)
        {
            high = mid - 1_LongNumber;
        }
        else
        {
            quotient = mid;
            low = mid + 1_LongNumber;
        }
    }

    while (shift > 0 && !quotient.integer_part.empty())
    {
        quotient.fraction_part.push_back(quotient.integer_part.front());
        quotient.integer_part.erase(quotient.integer_part.cbegin());
        quotient.accuracy++;
        shift--;
    }

    while (shift)
    {
        quotient.fraction_part.push_back(0);
        quotient.accuracy++;
        shift--;
    }

    if (quotient.integer_part.empty())
    {
        quotient.integer_part.push_back(0);
    }

    quotient.sign = res_sign;
    clear_zeros(quotient);
    return quotient;
}

LongNumber LongNumberSqrt(const LongNumber &x)
{
    if (x < 0_LongNumber)
    {
        throw "Error: square-rooting a negative number!\n";
    }
    LongNumber b = x, hundred = 100_LongNumber, ten = 10_LongNumber;
    int shift = 0;
    for (int i = 0; i < x.accuracy / 2 + x.accuracy % 2 || i < gAccuracy + 2; i++, shift++)
    {
        b = b * hundred;
    }
    if (b.integer_part.size() % 2 == 0)
    {
        b = b * hundred;
        shift++;
    }

    LongNumber start, end = b, mid, res;
    while (start < end || start == end)
    {
        mid = (start + end) * 0.5_LongNumber;
        mid.fraction_part.clear();
        mid.accuracy = 0;
        if (mid * mid == b)
        {
            res = mid;
            break;
        }
        if (mid * mid < b)
        {
            res = start;
            start = mid + 1_LongNumber;
        }
        else
        {
            end = mid - 1_LongNumber;
        }
    }

    while (shift--)
    {
        res = res / ten;
    }

    return res;
}

LongNumber power(const LongNumber &x, unsigned int degree)
{
    LongNumber res = 1_LongNumber;
    while (degree--)
    {
        res = res * x;
    }
    return res;
}