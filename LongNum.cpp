//
// Created by Oleg Antokhiv on 16.10.2020.
//
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "LongNum.h"


LongNum::LongNum(std::string Num) {
    int index;
    if (Num[0] == '-') {
        sign = -1;
        index = 1;
    }
    else {
        sign = 1;
        index = 0;
    }
    exponent = (int) Num.length() - index;

    while (index < Num.length()) {
        if (Num[index] == '.' || Num[index] == ',') {
            exponent = sign == 1 ? index : index - 1;
        } else
            digits.push_back(Num[index] - '0');

        index++;
    }
    removeZeroes();
}

LongNum::LongNum() {
    sign = 1;
    exponent = 1;
    digits = {0};
}

LongNum::LongNum(const LongNum &x) {
    sign = x.sign;
    exponent = x.exponent;
    digits = x.digits;
}

int LongNum::digitsAfterPoint() {
    return 0;
}

LongNum LongNum::operator*(const LongNum &x) {
    LongNum res;

    unsigned int len = digits.size() + x.digits.size();

    res.digits = std::vector<int>(len, 0);
    res.sign = sign * x.sign;
    res.exponent = exponent + x.exponent;

    for (int i = 0; i < digits.size(); i++)
        for (int j = 0; j < x.digits.size(); j++)
            res.digits[i + j + 1] += digits[i] * x.digits[j];

    for (int i = len - 1; i > 0; i--) {
        res.digits[i - 1] += res.digits[i] / 10;
        res.digits[i] %= 10;
    }

    res.removeZeroes();
    return res;
}

void LongNum::removeZeroes() {
    int n = 0;
    if (digitsAfterPoint() != 0) {
        std::find_if(digits.rbegin(), digits.rend(), [&n, this](int x) {
            bool res = x != 0;

            if (!res)
                n++;
            return res;

        });
        if (n != -1 && digits.size() > 1) {
            digits.erase(digits.end() - n, digits.end());
        }
    }
    n = 0;

    std::find_if(digits.begin(), digits.end(), [&n](int x) {
        bool res = x != 0;
        if (!res)
            n++;
        return res;
    });

    if (n != -1 && digits.size() > 1) {
        digits.erase(digits.begin(), digits.begin() + n);
        exponent -= n;
    }
    if (digits.empty()) {
        digits.push_back(0);
        exponent = 1;
    }

}

std::ostream &operator<<(std::ostream &os, const LongNum &value) {
    if (value.sign == -1)
        os << '-'; // если число отрицательное, то сначала выведем знак минус

    // если экспонента положительна, то у числа ненулевая целая часть
    if (value.exponent > 0) {
        size_t i = 0;
        size_t e = value.exponent;

        // выводим первые exponent цифр (или все цифры, если экспонента больше) числа чтобы вывести целую часть
        while (i < value.digits.size() && i < e)
            os << value.digits[i++];

        // если экспонента больше цифр числа, то выводим нули, чтобы дойти до экспоненты
        while (i < e) {
            os << "0";
            i++;
        }

        // если цифры ещё остались
        if (i < value.digits.size()) {
            os << "."; // то выводим точку

            // и выводим оставшиеся цифры как дробную часть
            while (i < value.digits.size())
                os << value.digits[i++];
        }
    } else { // иначе эспонента отрицательна или нулевая
        os << "0."; // выводим нулевую целую часть с точкой

        // выводим |exponent| нулей (если экспонента нулевая, то не будет ни одного нуля)
        for (long i = 0; i < -value.exponent; i++)
            os << "0";

        // выводим все цифры числа
        for (size_t i = 0; i < value.digits.size(); i++)
            os << value.digits[i];
    }

    return os; // возвращаем поток вывода
}

int LongNum::operator%(int a) {
    if (digitsAfterPoint() > 0)
        throw "Invalid operands to binary expression";
    if (a == 0)
        throw "Divide by zero";


    std::vector<int> x = digits;
    for (int i = 0; i < x.size() - 1; i++) {
        x[i + 1] += (x[i] % a) * 10;
    }
    return x.back() % a;
}

LongNum &LongNum::operator/=(int other) {
    int rem;
    for (int i = 0; i < digits.size() - 1; i++) {
        rem = (digits[i] % other) * 10;
        digits[i] /= other;
        digits[i + 1] += rem;
    }
    digits.back() /= other;
    removeZeroes();
    return *this;
}

int64_t LongNum::toInt() const {
    int64_t res = 0;
    for (int i = 0; i < digits.size(); i++) {
        res += digits[i] * (int64_t) pow(10, digits.size() - i - 1);
    }

    return res;

}

int LongNum::getSign() const{
    return sign;
}


