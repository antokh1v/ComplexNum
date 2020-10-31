#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>
#include <cmath>
#include "LongNum.h"
#include "RationalNum.h"
#include "ComplexNum.h"
#include <complex>
#include "catch.hpp"

using namespace std;


class PackageStream {
public:
    PackageStream(std::string data, int32_t package_len) : package_len_(package_len), data_(data) {}

    int32_t PackageLen() const {
        return package_len_;
    }

    int32_t ReadPackage(char *buf) {
        int32_t next_pos = std::min<int32_t>(data_.size(), pos_ + PackageLen());
        int32_t len = next_pos - pos_;

        memcpy(buf, data_.c_str() + pos_, len);
        pos_ = next_pos;
        return len;
    }

private:
    const int32_t package_len_;
    int32_t pos_ = 0;

    std::string data_;
};


class BufferedReader {
public:
    explicit BufferedReader(PackageStream *stream) {
        pcg = stream;
        cur_byte = 0;
        buffer_size = 0;
        buffer = new char[pcg->PackageLen()];
    }

    int32_t Read(char *output_buffer, int32_t buffer_len) {
        if (buffer_size - cur_byte >= buffer_len) {
            memcpy(output_buffer, buffer + cur_byte, buffer_len);
            cur_byte += buffer_len;
            if (cur_byte == buffer_size) {
                cur_byte = 0;
                buffer_size = pcg->ReadPackage(buffer);
            }
            return buffer_len;
        } else {
            memcpy(output_buffer, buffer + cur_byte, buffer_size - cur_byte);
            int32_t out_len = buffer_size - cur_byte;
            int32_t last_read_len;
            cur_byte = 0;
            do{
                buffer_size = pcg->ReadPackage(buffer);
                memcpy(output_buffer + out_len, buffer, std::min(buffer_size, buffer_len - out_len));
                last_read_len = buffer_len - out_len;
                out_len += std::min(buffer_size, buffer_len - out_len);
            }while (buffer_size == pcg->PackageLen() && out_len < buffer_len);
            cur_byte = buffer_size == pcg->PackageLen() ? last_read_len : 0;
            return out_len;
        }
    }
    ~BufferedReader(){
        delete[] buffer;
    }

private:
    PackageStream *pcg;
    char *buffer;
    int32_t cur_byte;
    int32_t buffer_size;
};



TEST_CASE("Test Rational Num"){
    RationalNum a = 1.5;
    REQUIRE(a.getNom() == 3);
    REQUIRE(a.getDenom() == 2);
    REQUIRE(a * 2 == 3.0);
    REQUIRE(a / 3 == RationalNum(make_pair(3, 6)));
    REQUIRE(a + RationalNum(make_pair(2.0, 3.0)) == RationalNum(make_pair(13, 6)));

    REQUIRE((RationalNum(std::make_pair(1,3)) * 3).getDouble() == 1.0);
    REQUIRE(RationalNum(4.25) - RationalNum(0.25) == 4.25 - 0.25);


    RationalNum b = make_pair(-2, 3);
    REQUIRE(a / b == make_pair(-9, 4));
    REQUIRE(b * -1 == RationalNum(make_pair(2, 3)));
    REQUIRE((b + abs(b)).getDouble() == 0.0);
    REQUIRE(b / b == 1);

    REQUIRE(!(b > 3));
    REQUIRE(!(b > 0));
    REQUIRE(!(b >= 0 ));
    REQUIRE(b + make_pair(2,3) == 0);
    REQUIRE(!(a < -1));
    REQUIRE(!(a == 4));
    REQUIRE(a.getDouble() < 4.25);
    REQUIRE(a.getDouble() <= 1.5);

    RationalNum c = 5;
    REQUIRE(c <= 5);
    REQUIRE(c >= -1);
    REQUIRE(c != 0);
    REQUIRE(c != 6);
    c = RationalNum();
    REQUIRE(!(c < 0));
    REQUIRE(c <= 0);
    REQUIRE(c >= 0);

    c = a;
    REQUIRE(c.getDenom() == 2);
    REQUIRE(c.getNom() == 3);

    RationalNum d(10.125);
    RationalNum e = d;
    REQUIRE(e.getNom() == 81);
    REQUIRE(e.getDenom() == 8);

    REQUIRE(sqr(e) == RationalNum(make_pair(6561, 64)).getDouble());

    d = RationalNum(10.125125);
    stringstream s1;
    string res1,res2;
    s1 << d;
    s1 >> res1;
    res2 = "81001/8000";
    REQUIRE(res1 == res2);

    d = RationalNum(-10.3222);
    stringstream ds1;
    ds1 << d;
    ds1 >> res1;
    res2 = "-51611/5000";
    REQUIRE(res1 == res2);

    RationalNum w(make_pair(1, 3));
    REQUIRE(w.getNom() == 1);
    REQUIRE(w.getDenom() == 3);

    w = 4;
    REQUIRE(w.getDenom() == 1);
    REQUIRE(w.getNom() == 4);

}

TEST_CASE("Test complex"){
    complex<double> b(1, 2);
    ComplexNum a(1,2);
    REQUIRE(a == b);
    REQUIRE(a - 1 == b - 1.0);
    REQUIRE(a * -2.0 == b * -2.0);
    REQUIRE(a / 0.5 == b / 0.5);
    REQUIRE(a + a * 2 == b + b * 2.0);

    ComplexNum a1(3);
    complex<double> b1(3.0, 0);
    REQUIRE(a + a1 == b + b1);
    REQUIRE(a + a1 != b - b1);
    REQUIRE(a * a1 == b * b1);
    REQUIRE(a / a1 == b / b1);

    a1 = ComplexNum(3, 2);
    b1 = complex<double> (3, 2);
    REQUIRE(a / a1 == b / b1);
    REQUIRE(a * a1 == b * b1);
    REQUIRE(a + a1 == b + b1);
    REQUIRE(a - a1 == b - b1);

    REQUIRE(a.arg() == arg(b));
    REQUIRE(a.abs() == abs(b));

    REQUIRE(pow(a, 5) == pow(b, 5));

    a = ComplexNum(make_pair(4,5), make_pair(7, 9));
    b = complex<double >(4.0 / 5.0, 7.0 / 9.0);

    REQUIRE(a == b);
    REQUIRE(a + a1 == b + b1);
    REQUIRE(a / a1 == b / b1);
    REQUIRE(a * a1 == b * b1);
    REQUIRE(a - a1 == b - b1);

    a *= RationalNum(-1);
    b *= -1;
    REQUIRE(a == b);

    a += ComplexNum(10.45, -89.21);
    b += complex<double>(10.45, -89.21);
    REQUIRE(a == b);

    a /= ComplexNum(3,9);
    b /= complex<double >(3, 9);
    REQUIRE(a == b);

    a -= ComplexNum(10.45, -89.21);
    b -= complex<double>(10.45, -89.21);
    REQUIRE(a == b);

    a = a + RationalNum(10000);
    b+= 10000;
    REQUIRE(a == b);

    a+= 1;
    b+= 1;
    REQUIRE(a == b);

    a = ComplexNum(4,5);
    b = complex<double >(4, 5);
    a -= 100;
    b -= 100;
    REQUIRE(a == b);

    a*= 999;
    b*= 999;
    REQUIRE(a == b);

    a/= 5;
    b/= 5;
    REQUIRE(a == b);

    stringstream s;

    s << "5/6-3/2i";
    stringstream s1;
    s1 << ComplexNum(make_pair(5,6), make_pair(-3,2));
    string res1;
    string res2;
    s >> res1;
    s1 >> res2;
    REQUIRE(res1 == res2);

    stringstream ds;
    ds << "3-99/10000i";
    stringstream ds1;
    ds1 << ComplexNum(3, make_pair(-99,10000));
    ds >> res1;
    ds1 >> res2;
    REQUIRE(res1 == res2);

    a = ComplexNum(4332.0/32.0, 398.0/ 321.0) +  0.999999;
    b = complex<double>(4332.0/32.0,398.0 / 321.0) +  0.999999;
    REQUIRE(a == b);

    a.setRe(3.2121);
    a.setIm(4);
    REQUIRE(a.getRe().getDouble() == 3.2121);
    REQUIRE(a.getIm() == 4);
}
