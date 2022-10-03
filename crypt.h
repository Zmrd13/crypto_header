
//
// Created by Weder on 02.10.2022.
//

#ifndef INF_CRYPT_H
#define INF_CRYPT_H

#include <vector>
#include <cmath>
/**
 * Библиотека по методичке защиты
 *
 *
 *
 */
using lli = long long int;
using namespace std;

template<typename T>
void nlPrint(T data) {

    cout << endl << data << endl;


};

void nlPrint(const vector<lli> &data) {
    cout << endl;
    for (auto &i: (vector<lli>) data) {
        cout << i << " ";
    }
    cout << endl;
}

/**
 * Названия по методичке
 * perf=2log_2(x)
 * @param iBase - a arg(long long int)
 * @param iPow - x arg(long long int)
 * @param iMod - p arg(long long int)
 * @return pow(a,x)%p =y(long long int)
 *
 */
int modPow(lli iBase, lli iPow, lli iMod) {
    if (iMod == 0) {
        return 0;
    }
    vector<lli> vecMod = {};
    lli logPow = (lli) log2((double) iPow);
    vecMod.push_back(iBase % iMod);
    for (lli i = 1; i <= logPow; i++) {
        vecMod.push_back(((vecMod.at(i - 1) % iMod) * (vecMod.at(i - 1) % iMod)) % iMod);
    }
    vector<lli> vecBinPow = {};
    while (iPow >= 1) {
        vecBinPow.push_back(iPow % 2);
        iPow /= 2;
    }
    lli iResult = 1;
    for (lli i = 0; i < vecBinPow.size(); i++) {
        if (vecBinPow.at(i) == 1) {
            iResult *= (vecMod.at(i) % iMod) % iMod;
            iResult %= iMod;
        }
    }
    return iResult % iMod;
}

/**
 * Названия по методичке
 * @param iA - a arg(long long int)
 * @param iB - b arg(long long int)
 * @return x and y  in ax+by= gcd(a,b)
 *
 */
vector<lli> extGCD(lli iA, lli iB) {
    lli q = 0;
    vector<lli> vecU = {iA, 1, 0};
    vector<lli> vecV = {iB, 0, 1};
    vector<lli> vecT = {};

    if (iA < iB) {
        return {};
    }
    while (vecV[0] != 0) {
        q = vecU[0] / vecV[0];
        vecT = {vecU[0] % vecV[0], vecU[1] - q * vecV[1], vecU[2] - q * vecV[2]};
        vecU = vecV;
        vecV = vecT;
    }
    return vecU;
}

/**
 *
 * Проверка на просту
 *
 * @param  iN - number for check
 * @see crypt.h
 * @return True if number is prime
 *
 * */
bool checkSimple(lli iN) {

    for (int i = 2; i <= sqrt(iN); i++) {
        if (iN % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 *
 * Система Диффи-Хеллмана
 *
 * @param iSeed=NULL - Seed for srand
 * @see crypt.h
 * @return Common random gen key for Bob and Alice
 *
 * */
lli diffHelm(int iSeed = NULL) {
    if (iSeed != 0) {
        srand(iSeed);
    } else {
        srand(time(NULL));
    }
    lli iQ = 0;
    lli iP = 0;
    lli iG = 0;
    do {
        iQ = rand() % ((lli) pow(10, 9) - 1) + 1;
        iP = 2 * iQ + 1;
    } while (!(checkSimple(iQ) && checkSimple(iP)));


    do {
        iG = rand() % (iP - 2) + 2;
    } while (modPow(iG, iQ, iP) == 1);


    nlPrint("G argument");
    nlPrint(iG);
    nlPrint("P argument");
    nlPrint(iP);
    lli iAliceSecKey = rand() % (iP - 2) + 2;
    lli iBobSecKey = rand() % (iP - 2) + 2;
    nlPrint("Alice secret:");
    nlPrint(iAliceSecKey);
    nlPrint("Bob secret:");
    nlPrint(iBobSecKey);
    lli iAlicePubKey = modPow(iG, iAliceSecKey, iP);
    lli iBobPubKey = modPow(iG, iBobSecKey, iP);

    lli iAliceCommKey = modPow(iBobPubKey, iAliceSecKey, iP);
    lli iBobCommKey = modPow(iAlicePubKey, iBobSecKey, iP);

    if (iAliceCommKey == iBobCommKey) {
        nlPrint("Common:");
        nlPrint(iAliceCommKey);
        return iAliceCommKey;
    } else {
        cout << "ERROR:" << endl;
        nlPrint("Alice common:");
        nlPrint(iAliceCommKey);
        nlPrint("Bob common:");
        nlPrint(iBobCommKey);
        return -1;
    }

}

#endif //INF_CRYPT_H
