//
// Created by Oleg Antokhiv on 17.10.2020.
//

#include <cmath>
#include <algorithm>
#include <iostream>
#include "RationalNum.h"

template<class T>
RationalNum<T>::RationalNum(T x) {
    reduce(factorization(int(x * 1e8)), 1e8);
}

template<class T>
void RationalNum<T>::reduce(std::vector<int> nom, std::vector<int> denom) {
    std::vector<int> resNom(std::max(nom.size(), denom.size()), 0);
    std::vector<int> resDenom = resNom;

    for (int i = 2; i < std::min(nom.size(), denom.size()); i++) {
        if (nom[i] > 0 && denom[i]) {
            nom[i] > denom[i] ? resNom[i] = nom[i] - denom[i] : resDenom[i] = denom[i] - nom[i];
        } else if (nom[i] > 0 || denom[i] > 0) {
            denom[i] > 0 ? resDenom[i] = denom[i] : resNom[i] = nom[i];
        }
    }
    // convert to int
    int x = 1;
    for (int i = 0; i < resNom.size(); ++i) {
        x *= resNom[i] > 0 ? resNom[i] : 1;
    }
    nominator = x;
    std::cout << x << std::endl;
    x = 1;
    for (int i = 0; i < resDenom.size(); ++i) {
        x *= resDenom[i] > 0 ? resDenom[i] : 1;
    }
    denominator = x;
    std::cout << x << std::endl;
}


std::vector<int> factorization(int a) {
    std::vector<int> res(a + 1, 0);
    for (int i = 2; i < sqrt(a); i++) {
        while (a % i == 0) {
            res[i]++;
            a /= i;
        }
    }
    res[a]++;
    return res;
}
