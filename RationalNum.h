//
// Created by Oleg Antokhiv on 17.10.2020.
//

#ifndef FALL2020_RATIONALNUM_H
#define FALL2020_RATIONALNUM_H

#include <vector>

    template<class T>
    class RationalNum {
    private:
        int nominator{};
        int denominator{};

        void reduce(std::vector<int> nom, std::vector<int> denom);

    public:
        explicit RationalNum(T x);
    };

std::vector<int> factorization(int a);

#endif //FALL2020_RATIONALNUM_H
