//
// Created by Oleg Antokhiv on 17.10.2020.
//

#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include "RationalNum.h"


RationalNum::RationalNum(double x) {
    int64_t a = 1e6;
    int sign = x / std::abs(x);

    reduce(factorization(abs(ceil (x * a))), factorization(a));
    nominator*= sign;
}



void RationalNum::reduce(std::map<int,int> nom, std::map<int,int> denom) {

    for (auto const &[key,val]: nom){
        try {
            int val2 = denom.at(key);
            int x = std::min(val,val2);
            denom[key]-= x;
            nom[key]-= x;
        }
        catch (const std::out_of_range& oor){}

    }

    // convert to int
    int x = 1;
    for (auto & [key, val]: nom) {
        x*= int(pow(key, val));
    }
    nominator = x;

    x = 1;
    for (auto & [key,val] : denom) {
        x*= int(pow(key, val));

    }
    denominator = x;

}

RationalNum RationalNum::operator+(const RationalNum &other) const {
    int nDenom = NOK(denominator, other.denominator);
    return RationalNum(std::make_pair(nominator * (nDenom / denominator > 0 ? nDenom / denominator : 1) +
    other.nominator * (nDenom / other.denominator > 0 ? nDenom / other.denominator : 1),
            nDenom));
}

RationalNum::RationalNum(std::pair<int, int> x) {
    if (x.second == 0)
        throw "Error";
    nominator = x.first;
    denominator = x.second;
    int sign = x.first / abs(x.first) * x.second / abs(x.second);
    reduce(factorization(abs(x.first)), factorization(abs(x.second)));
    nominator*= sign;
    denominator = abs(denominator);
}

RationalNum::RationalNum() {
    nominator = 0;
    denominator = 1;
}

RationalNum RationalNum::operator-(const RationalNum &other) const {
    int nDenom = NOK(denominator, other.denominator);
    return RationalNum(std::make_pair(nominator * (nDenom / denominator) - other.nominator * (nDenom / other.denominator),
            nDenom));
}

RationalNum RationalNum::operator*(const RationalNum &other) const{
    return RationalNum(std::make_pair(nominator * other.nominator,
            denominator * other.denominator));
}

RationalNum RationalNum::operator/(const RationalNum &other) const {
    return RationalNum( std::make_pair(nominator * other.denominator,
            denominator * other.nominator));
}

RationalNum::RationalNum(int a) {
    nominator = a;
    denominator = 1;
}

RationalNum &RationalNum::operator=(const int &other) {
    nominator = other;
    denominator = 1;
    return *this;
}

int64_t RationalNum::getNom() const {
    return nominator;
}

int64_t RationalNum::getDenom() const{
    return denominator;
}

double RationalNum::getDouble() {
    return double(nominator)/double(denominator);
}

bool operator>(const RationalNum& a, int x) {
    if (x == 0){
        return a.nominator > 0;
    }
    return (a.nominator > x * a.denominator);
}

bool operator<(const RationalNum& a, int x) {
    if (x == 0){
        return a.nominator < 0;
    }
    return (a.nominator  < x * a.denominator);
}

bool operator==(const RationalNum& a, int x) {
    if (x == 0){
        return a.nominator == 0;
    }
    return (a.denominator == 1 && a.nominator == x);
}

bool operator>=(const RationalNum &a, int x) {
    if (x == 0){
        return a.nominator >= 0;
    }
    return (a.nominator  >= x * a.denominator);
}

bool operator<=(const RationalNum &a, int x) {
    if (x == 0){
        return a.nominator <= 0;
    }
    return (a.nominator <= x * a.denominator);
}

RationalNum::RationalNum(const RationalNum &other) {
    nominator = other.nominator;
    denominator = other.denominator;
    reduce(factorization(abs(nominator)), factorization(abs(denominator)));
    nominator*= other.nominator / abs(other.nominator);
    denominator = abs(denominator);
}

bool operator!=(const RationalNum &a, int x) {
    if (x == 0){
        return a.nominator != 0;
    }
    return (a.denominator == 1 && a.nominator != x);
}

std::ostream &operator<<(std::ostream &os, const RationalNum &value) {
    os << value.getNom();
    if (value.getDenom() != 1) {
        os << '/' << value.getDenom();
    }
    return os;
}

bool operator==(const RationalNum &a, const RationalNum &x) {
    return (a.getNom() == x.getNom() && a.getDenom() == x.getDenom());
}


std::map<int,int> factorization(LongNum a) {
    std::map<int, int> res;
    for (int i = 2; i <= sqrt(a.toInt()); i++) {
        while (a % i == 0) {
            res[i]++;
            a /= i;
        }
    }
    res[a.toInt()]++;
    return res;
}

std::map<int,int> factorization(unsigned int a){
    std::map<int, int> res;
    for (int i = 2; i <= sqrt(a); i++) {
        while (a % i == 0) {
            res[i]++;
            a /= i;
        }
    }
    res[a]++;
    return res;
}


int NOD(int a, int b){
    if (a < b) {
        std::swap(a, b);
    }
    while (a % b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return b;
}

int NOK(int a, int b){
    return  (a*b) / NOD(a,b);
}

double sqr(const RationalNum& a){
    auto res = a * a;
    return ((double )(res.getNom() / (double)res.getDenom()));
}

RationalNum abs(const RationalNum &a){
    return RationalNum(std::make_pair(std::abs(a.getNom()),std::abs(a.getDenom())));
}