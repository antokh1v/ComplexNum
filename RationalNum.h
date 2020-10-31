//
// Created by Oleg Antokhiv on 17.10.2020.
//

#ifndef FALL2020_RATIONALNUM_H
#define FALL2020_RATIONALNUM_H

#include <vector>
#include <map>
#include "LongNum.h"

class RationalNum {
    private:
        int nominator{};
        int denominator{};

        void reduce(std::map<int,int> nom, std::map<int,int> denom);

    public:
        RationalNum(double x);
        RationalNum(std::pair<int, int> x);
        RationalNum(int a);
        RationalNum();

        RationalNum operator+(const RationalNum& other) const ;
        RationalNum operator-(const RationalNum& other) const ;
        RationalNum operator*(const RationalNum& other) const ;
        RationalNum operator/(const RationalNum& other) const ;



        RationalNum(const RationalNum& other);
        RationalNum& operator=(const int& other);
        friend bool operator>(const RationalNum& a, int x);
        friend bool operator<(const RationalNum& a, int x);
        friend bool operator==(const RationalNum& a, int x);
        friend bool operator!=(const RationalNum& a, int x);
        friend bool operator>=(const RationalNum& a, int x);
        friend bool operator<=(const RationalNum& a, int x);
        friend bool operator==(const RationalNum& a, const RationalNum& x);

        int64_t getNom() const;
        int64_t getDenom() const;

        friend std::ostream &operator<<(std::ostream &os, const RationalNum & value);
        double getDouble();
    };

std::map<int,int> factorization(LongNum a);
std::map<int,int> factorization(unsigned int a);
int NOD(int a, int b);
int NOK(int a, int b);

double sqr(const RationalNum& a);

RationalNum abs(const RationalNum &a);

#endif //FALL2020_RATIONALNUM_H
