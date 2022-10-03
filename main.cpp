#include <iostream>
#include "crypt.h"

using namespace std;

lli random(lli min, lli max) {
    return rand() % (max - min) + min;
}

lli BCStep(lli iA, lli iP, lli iY) {
    lli iM = sqrt(iP) + 1, iK = iM;
    vector<lli> vecCalc = {};
    vector<lli> vecAns;

    lli iNumber = 0;
    lli iIndex = 0;

    for (lli i = 0; i <= iM - 1; i++) {
        vecCalc.push_back((modPow(iA, i, iP) * (iY % iP)) % iP);
    }
    cout << endl;

    for (lli i = 1; i <= iK; i++) {
        iNumber = modPow(iA, i * iM, iP);
        for (lli j = 0; j < vecCalc.size(); j++) {
            if (iNumber == vecCalc[j]) {
                iIndex++;
                vecAns.push_back(i * iM - j);
            }
        }
    }
    cout << endl << "vecAns:" << endl;


    for (int i = 0; i < vecAns.size(); i++) {
        if (modPow(iA, vecAns[i], iP) == iY) {
            cout << "(+)";
        }
        cout << vecAns[i] << " ";
    }
    cout << endl;

    return 0;
}


int main() {
    nlPrint("modPow");
    nlPrint(modPow(5, 2206, 22));
    nlPrint("extGCD");
    int iA = 240, iB = 49;
    nlPrint(to_string(iA) + "  " + to_string(iB));
    nlPrint(extGCD(iA, iB));
    nlPrint("checkSimple(23)=true");
    nlPrint(checkSimple(23));
    nlPrint("checkSimple(18)=false");
    nlPrint(checkSimple(18));
    nlPrint("diffHelm()");
    nlPrint(diffHelm(1));
    lli iRandA = random(1, (lli) pow(10, 2));
    lli iRandX = random(1, (lli) pow(10, 2));
    lli iRandP = random(1, (lli) pow(10, 2));
    nlPrint("BD STEP");
    cout << iRandA << " " << iRandX << " " << iRandP << endl;
    nlPrint(modPow(iRandA, iRandX, iRandP));
    nlPrint(BCStep(iRandA, iRandP, modPow(iRandA, iRandX, iRandP)));
    return 0;
}
