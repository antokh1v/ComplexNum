//
// Created by Oleg Antokhiv on 06.10.2020.
//

#ifndef FALL2020_COMPLEXNUM_H
#define FALL2020_COMPLEXNUM_H


#include <complex>
#include "RationalNum.h"


class ComplexNum {
public:
    ComplexNum(const RationalNum& re, const RationalNum& im = 0);

    ComplexNum operator+(const ComplexNum &x) const ;

    ComplexNum operator-(const ComplexNum &x) const ;

    ComplexNum operator*(const ComplexNum &x) const ;

    ComplexNum operator/(const ComplexNum &x) const ;

    ComplexNum operator+(const RationalNum& x) const ;

    ComplexNum operator-(const RationalNum& x) const ;

    ComplexNum operator*(const RationalNum& x) const ;

    ComplexNum operator/(const RationalNum& x) const ;


    ComplexNum& operator=(const ComplexNum &x);

    ComplexNum &operator+=(const ComplexNum &x);
    ComplexNum &operator-=(const ComplexNum &x);
    ComplexNum &operator*=(const ComplexNum &x);
    ComplexNum &operator/=(const ComplexNum &x);


    ComplexNum operator+(const double &a);

    ComplexNum operator-(const double &a);

    ComplexNum operator*(const double &a);

    ComplexNum operator/(const double &a);

    ComplexNum &operator+=(const double &x);
    ComplexNum &operator-=(const double &x);
    ComplexNum &operator*=(const double &x);
    ComplexNum &operator/=(const double &x);

    friend std::ostream &operator<<(std::ostream &os, const ComplexNum &value);

    RationalNum getRe() const;
    RationalNum getIm() const;

    double abs() const;
    double arg() const;

    friend bool operator==(const ComplexNum &a, const std::complex<double> &b);
    friend bool operator!=(const ComplexNum &a, const std::complex<double> &b);

private:
    RationalNum Im;
    RationalNum Re;
};

ComplexNum pow(const ComplexNum &a, int n);

#endif //FALL2020_COMPLEXNUM_H
