//
// Created by Oleg Antokhiv on 16.10.2020.
//

#ifndef FALL2020_LONGNUM_H
#define FALL2020_LONGNUM_H

#include <vector>
#include <map>
#include <iostream>

class LongNum {
    int sign;
    long exponent;
    std::vector<int> digits;

    void removeZeroes();

public:
    LongNum(std::string Num);

    LongNum();

    LongNum(const LongNum &x);

    LongNum operator*(const LongNum &x);

    friend std::ostream &operator<<(std::ostream &os, const LongNum &value);

    int operator%(int a);

    int digitsAfterPoint();
    LongNum& operator/=(int other);

    int getSign() const ;
    int64_t toInt() const ;


};



#endif //FALL2020_LONGNUM_H
