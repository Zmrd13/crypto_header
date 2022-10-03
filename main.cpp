#include <iostream>
#include "crypt.h"

using namespace std;


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
