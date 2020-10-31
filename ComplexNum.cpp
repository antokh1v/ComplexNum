//
// Created by Oleg Antokhiv on 06.10.2020.
//

#include <cmath>
#include "ComplexNum.h"

#define pi M_PI

ComplexNum::ComplexNum(const RationalNum &re, const RationalNum &im) {
    Re = re;
    Im = im;
}

ComplexNum ComplexNum::operator+(const ComplexNum &x) const {
    return ComplexNum(Re + x.Re, Im + x.Im);
}

ComplexNum ComplexNum::operator-(const ComplexNum &x) const {
    return ComplexNum(Re - x.Re, Im - x.Im);
}

double ComplexNum::abs() const {
    return std::sqrt(sqr(Re) + sqr(Im));
}

double ComplexNum::arg() const {
    RationalNum x = Re;
    RationalNum y = Im;
//    if (x > 0 && y >= 0){
//        return atan((y/x).getDouble());
//    }
//    if (x < 0 && y >= 0){
//        return pi - atan(std::abs((y / x).getDouble()));
//    }
//    if (x < 0 && y < 0){
//        return pi + atan(std::abs((y/x).getDouble()));
//    }
//    if (x > 0 && y < 0){
//        return  2*pi - atan(std::abs((y/x).getDouble()));
//    }
//    if (x == 0 && y > 0){
//        return pi/2;
//    }
//    if (x== 0 && y < 0){
//        return  3 * pi / 2;
//    }
    return atan2(y.getDouble(), x.getDouble());
}

ComplexNum ComplexNum::operator*(const ComplexNum &x) const {
    return ComplexNum(RationalNum(abs() * x.abs() * cos(arg() + x.arg())),
                      RationalNum(abs() * x.abs() * sin(arg() + x.arg())));
}

ComplexNum ComplexNum::operator/(const ComplexNum &x) const {
    auto a1 = Re;
    auto a2 = x.getRe();
    auto b1 = Im;
    auto b2 = x.getIm();
    RationalNum real = (a1 * a2 + b1 * b2) / RationalNum(sqr(a2) + sqr(b2));
    RationalNum imag = (a2 * b1 - a1 * b2) / RationalNum(sqr(a2) + sqr(b2));
    return ComplexNum(real, imag);
}

std::ostream &operator<<(std::ostream &os, const ComplexNum &value) {
    if (value.getRe() != 0) os << value.getRe();
    if (value.getIm() != 0) os << (value.Im >= 0 ? '+' : '-') << abs(value.getIm()) << 'i';
    return os;
}

RationalNum ComplexNum::getRe() const {
    return Re;
}

RationalNum ComplexNum::getIm() const {
    return Im;
}

ComplexNum ComplexNum::operator+(const RationalNum &x) const {
    return ComplexNum(RationalNum(Re + x), Im);
}

ComplexNum ComplexNum::operator-(const RationalNum &x) const {
    return ComplexNum(RationalNum(Re - x), Im);
}

ComplexNum ComplexNum::operator*(const RationalNum &x) const {
    return ComplexNum(x * Re, x * Im);
}

ComplexNum ComplexNum::operator/(const RationalNum &x) const {
    return ComplexNum(Re / x, Im / x);
}

ComplexNum &ComplexNum::operator=(const ComplexNum &x) {
    Im = x.Im;
    Re = x.Re;
    return *this;
}

ComplexNum &ComplexNum::operator+=(const ComplexNum &x) {
    Re = Re + x.Re;
    Im = Im + x.Im;
    return *this;
}

ComplexNum &ComplexNum::operator-=(const ComplexNum &x) {
    Re = Re - x.Re;
    Im = Im - x.Im;
    return *this;
}

ComplexNum &ComplexNum::operator*=(const ComplexNum &x) {
    double newArg = arg() + x.arg();
    double newAbs = abs() * x.abs();
    Re = newAbs * cos(newArg);
    Im = newAbs * sin(newArg);
    return *this;
}

ComplexNum &ComplexNum::operator/=(const ComplexNum &x) {
    double newArg = arg() - x.arg();
    double newAbs = abs() / x.abs();
    Re = newAbs * cos(newArg);
    Im = newAbs * sin(newArg);
    return *this;
}

bool operator==(const ComplexNum &a, const std::complex<double> &b) {
    const long double exp = 1e-16;
    return (abs(a.getRe().getDouble() - b.real()) < exp && abs(a.getIm().getDouble() - b.imag()) < exp);
}

bool operator!=(const ComplexNum &a, const std::complex<double> &b) {
    return (!(a == b));
}

ComplexNum ComplexNum::operator+(const double &a) {
    return ComplexNum(Re, Im) + RationalNum(a);
}

ComplexNum ComplexNum::operator-(const double &a) {
    return ComplexNum(Re, Im) - RationalNum(a);
}

ComplexNum ComplexNum::operator*(const double &a) {
    return ComplexNum(Re, Im) * RationalNum(a);
}

ComplexNum ComplexNum::operator/(const double &a) {
    return ComplexNum(Re, Im) / RationalNum(a);
}

ComplexNum &ComplexNum::operator+=(const double &x) {
    Re =  Re + x;
    return *this;
}

ComplexNum &ComplexNum::operator-=(const double &x) {
    Re =  Re - x;
    return *this;
}

ComplexNum &ComplexNum::operator*=(const double &x) {
    Re =  Re * x;
    Im = Im * x;
    return *this;
}

ComplexNum &ComplexNum::operator/=(const double &x) {
    Re =  Re / x;
    Im = Im / x;
    return *this;
}


ComplexNum pow(const ComplexNum &a, int n) {
    return ComplexNum(RationalNum(pow(a.abs(), n) * cos(n * a.arg())),
                      RationalNum(pow(a.abs(), n) * sin(n * a.arg())));
}