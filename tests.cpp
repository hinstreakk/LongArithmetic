#include "./header/LongNumbers.hpp"
#include <iostream>

void printTest(std::string test_name, std::vector<std::string> result)
{
    std::cout << test_name << std::endl << std::endl;

    int len = result.size();
    for (int i = 1; i <= len; i++)
    {
        std::cout << "Test " << i << std::endl;
        std::cout << result[i-1] << std::endl;
    }
}

void TestSum()
{
    std::vector<std::string> res;
    LongNumber result;
    // Тест 1: Сложение положительных чисел
    try
    {
        LongNumber num1("157380546.86511627");
        LongNumber num2("15010179.80178");
        result = num1 + num2;
        res.push_back(to_str(result) == "172390726.66689627" ? "OK" : "FAILED");
    }
    catch (const std::exception& e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Сложение отрицательных чисел
    try
    {
        LongNumber num1("-61978035.85645");
        LongNumber num2("-986543209654210.21");
        result = num1 + num2;
        res.push_back(to_str(result) == "-986543271632246.06645" ? "OK" : "FAILED");
    }
    catch (const std::exception& e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Сложение разнозначных чисел
    try
    {
        LongNumber num1("-35.54656645");
        LongNumber num2("6543210.25641");
        result = num1 + num2;
        res.push_back(to_str(result) == "6543174.70984355" ? "OK" : "FAILED");
    }
    catch (const std::exception& e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 4: Сложение с нулем
    try
    {
        LongNumber num1("0");
        LongNumber num2("6543210.25641");
        result = num1 + num2;
        res.push_back(to_str(result) == "6543210.25641" ? "OK" : "FAILED");
    }
    catch (const std::exception& e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestSum()", res);
}

void TestSubtraction()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Вычитание положительных чисел
    try
    {
        LongNumber num1("544456231.516232123");
        LongNumber num2("100000.100000111");
        result = num1 - num2;

        res.push_back(to_str(result) == "544356231.416232012" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Вычитание отрицательных чисел
    try
    {
        LongNumber num1("-5441.12162123");
        LongNumber num2("-111289.16541");
        result = num1 - num2;
        res.push_back(to_str(result) == "-105848.04378877" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Вычитание разнозначных чисел (из отрицательного положительное)
    try
    {
        LongNumber num1("-756236.46565");
        LongNumber num2("119.111123554654");
        result = num1 - num2;
        res.push_back(to_str(result) == "-756355.576773554654" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 4: Вычитание разнозначных чисел (из положительного отрицательное)
    try
    {
        LongNumber num1("36.46511265");
        LongNumber num2("-0.786756297622466523");
        result = num1 - num2;
        res.push_back(to_str(result) == "37.251868947622466523" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 5: Вычитание нуля
    try
    {
        LongNumber num1("7984321.52112");
        LongNumber num2("0");
        result = num1 - num2;
        res.push_back(to_str(result) == "7984321.52112" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestSubtraction()", res);
}

void TestMultiplication()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Умножение положительных чисел
    try
    {
        LongNumber num1("123456789.01234567890");
        LongNumber num2("987.65432109876543210");
        result = num1 * num2;
        res.push_back(to_str(result) == "121932631137.02179522374638011112635269" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Умножение отрицательных чисел
    try
    {
        LongNumber num1("-654523.12123564");
        LongNumber num2("-23.98979875641121100");
        result = num1 * num2;
        res.push_back(to_str(result) == "15701877.95986114076207026876004" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Умножение разнозначных чисел
    try
    {
        LongNumber num1("112435765.532313212");
        LongNumber num2("-2.111222333");
        result = num1 * num2;
        res.push_back(to_str(result) == "-237376899.219771286325363596" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 4: Умножение на ноль
    try
    {
        LongNumber num1("65456123.1031321");
        LongNumber num2("0");
        result = num1 * num2;
        res.push_back(to_str(result) == "0" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }
    printTest("TestMultiplication()", res);
}

void TestDiv()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Деление положительных чисел
    try
    {
        LongNumber num1("820071957.10427341");
        LongNumber num2("1234.567890");
        result = num1 / num2;
        res.push_back(to_str(result) == "664258.291299211912922" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Деление отрицательных чисел
    try
    {
        LongNumber num1("-2255641.156131531");
        LongNumber num2("-1231.65654");
        result = num1 / num2;
        res.push_back(to_str(result) == "1831.388120694370688" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Деление разнозначных чисел
    try
    {
        LongNumber num1("221.1561315431");
        LongNumber num2("-1231.6564154");
        result = num1 / num2;
        res.push_back(to_str(result) == "-0.17955992335027624" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 4: Деление нуля на число
    try
    {
        LongNumber num1("0");
        LongNumber num2("1231.6564154");
        result = num1 / num2;
        res.push_back(to_str(result) == "0" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestDiv()", res);
}

void TestEqual()
{
    std::vector<std::string> res;
    bool result;

    // Тест 1: Равные числа
    try
    {
        LongNumber num1("15351321.546513213");
        LongNumber num2("15351321.546513213");
        result = num1 == num2;
        res.push_back(result == true ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Неравные числа
    try
    {
        LongNumber num1("-15351321.546513213");
        LongNumber num2("15351321.546513213");
        result = num1 == num2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestEqual()", res);
}

void TestNotEqual()
{
    std::vector<std::string> res;
    bool result;

    // Тест 1: Неравные числа
    try
    {
        LongNumber num1("89150112775");
        LongNumber num2("89150112776");
        result = num1 != num2;
        res.push_back(result == true ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Равные числа
    try
    {
        LongNumber num1("15132.123123");
        LongNumber num2("15132.123123");
        result = num1 != num2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestNotEqual()", res);
}

void TestSmaller()
{
    std::vector<std::string> res;
    bool result;

    // Тест 1: Первое больше второго
    try
    {
        LongNumber num1_1("41654131.12132132");
        LongNumber num1_2("1231.1465413241132121");
        result = num1_1 < num1_2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Первое меньше второго
    try
    {
        LongNumber num1_1("56456.213");
        LongNumber num1_2("7456123");
        result = num1_1 < num1_2;
        res.push_back(result == true ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Равные числа
    try
    {
        LongNumber num1_1("0");
        LongNumber num1_2("0");
        result = num1_1 < num1_2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestSmaller()", res);
}

void TestBigger()
{
    std::vector<std::string> res;
    bool result;

    // Тест 1: Первое больше второго
    try
    {
        LongNumber num1_1("774464.2131231231");
        LongNumber num1_2("0.654132");
        result = num1_1 > num1_2;
        res.push_back(result == true ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Первое меньше второго
    try
    {
        LongNumber num1_1("4646.123121231");
        LongNumber num1_2("7456123.1");
        result = num1_1 > num1_2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Равные числа
    try
    {
        LongNumber num1_1("123123.0055");
        LongNumber num1_2("123123.0055");
        result = num1_1 > num1_2;
        res.push_back(result == false ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestBigger()", res);
}

void TestClearZeros()
{
    std::vector<std::string> res;

    // Тест 1: Удаление нулей у положительного числа
    try
    {
        LongNumber num1("00000000000000000001112132.6541650000000000000");
        clear_zeros(num1);
        res.push_back(to_str(num1) == "1112132.654165" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Удаление нулей у отрицательного числа
    try
    {
        LongNumber num1("-0000000000023132465.4123145000000000000");
        clear_zeros(num1);
        res.push_back(to_str(num1) == "-23132465.4123145" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestClearZeros()", res);
}

void TestPower()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Положительное число в степень
    try
    {
        LongNumber num1("52.541123");
        unsigned num2 = 5;
        result = power(num1, num2);
        res.push_back(to_str(result) == "400402476.759925451430069170807446961843" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Отрицательное число в четную степень
    try
    {
        LongNumber num1("-24.5413");
        unsigned num2 = 6;
        result = power(num1, num2);
        res.push_back(to_str(result) == "218466769.373944448150867118040009" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Отрицательное число в нечетную степень
    try
    {
        LongNumber num1("-48.485");
        unsigned num2 = 7;
        result = power(num1, num2);
        res.push_back(to_str(result) == "-629871270110.738017450252102578125" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestPower()", res);
}

void TestSqrt()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Корень из вещественного 1
    try
    {
        LongNumber num1("1123123.45456432123");
        result = LongNumberSqrt(num1);
        res.push_back(to_str(result) == "1059.775190577851388" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Корень из вещественного 2
    try
    {
        LongNumber num1("0.65453213");
        result = LongNumberSqrt(num1);
        res.push_back(to_str(result) == "0.809031600124494" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Корень из нуля
    try
    {
        LongNumber num1("0");
        result = LongNumberSqrt(num1);
        res.push_back(to_str(result) == "0" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestSqrt()", res);
}

void TestAbs()
{
    std::vector<std::string> res;
    LongNumber result;

    // Тест 1: Модуль положительного
    try
    {
        LongNumber num1("54653132.13215431");
        result = abs(num1);
        res.push_back(to_str(result) == "54653132.13215431" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 2: Модуль отрицательного
    try
    {
        LongNumber num1("-12313542163.4132135464");
        result = abs(num1);
        res.push_back(to_str(result) == "12313542163.4132135464" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    // Тест 3: Модуль нуля
    try
    {
        LongNumber num1("0");
        result = abs(num1);
        res.push_back(to_str(result) == "0" ? "OK" : "FAILED");
    }
    catch (const std::exception &e)
    {
        res.push_back("Error\n" + std::string(e.what()));
    }

    printTest("TestAbs()", res);
}

int main()
{
    TestSum();
    TestSubtraction();
    TestMultiplication();
    TestDiv();
    TestEqual();
    TestNotEqual();
    TestSmaller();
    TestBigger();
    TestClearZeros();
    TestPower();
    TestSqrt();
    TestAbs();
}