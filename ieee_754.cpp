#include <iostream>
#include <bitset>
#include <sstream>
#include <cmath>        // std::abs

using namespace std;

int main()
{
   float fa, fb;
    cout << "Enter two floats (aka a & b) to add" << endl;
    do {
        if(cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "You have entered wrong input" << endl;
        }
        cin >> fa >> fb;
    }
    while(cin.fail());
    //fa absolute value should be greater than fb
    if (abs(fa) < abs(fb))
    {
        cout << "*Swapped so abs(a) > abs(b)*\n";
        swap(fa, fb);
    }
    //to get binary representation
    unsigned ia = *(unsigned*)&fa;
    unsigned ib = *(unsigned*)&fb;
    cout << "a:\n" << bitset<32>(ia) << endl;
    cout << "b:\n" << bitset<32>(ib) << endl;

    unsigned expA = (ia >> 23) & UINT8_MAX;
    unsigned manA = (ia & (UINT32_MAX >> 9)) | (1 << 23); //mantissa with leading 1 (like 1.xxxxx...)
    bool signA = ia >> 31;
    unsigned expB = (ib >> 23) & UINT8_MAX;
    unsigned manB = (ib & (UINT32_MAX >> 9)) | (1 << 23);
    unsigned expRes = expA;
    bool signRes = signA;
    unsigned expDiff = expA - expB;
    cout << "Exponents difference is: " << expDiff << endl;
    cout << "B mantissa (right 24 bits) before aligning:\n" << bitset<32>(manB) << endl;
    manB >>= expDiff;
    cout << "B mantissa (right 24 bits) after aligning:\n" << bitset<32>(manB) << endl;
    unsigned manRes;
    cout << "*Adding mantissas*\na mantissa:\n" << bitset<32>(manA) << endl;
    if (signA == (ib >> 31)) {
        manRes = manA + manB;
    }
    else {
        manRes = manA - manB;
    }
    cout << "Resulting mantissa:\n" << bitset<32>(manRes) << endl;
    //handling zero result
    if (manRes == 0) {
        cout << "*Res mantissa is 0 -- result is zero*\n";
        signRes = 0;
        expRes = 0;
    }
    else {
        while (!(manRes >> 23 & 1) && (manRes != 0)) {
            cout << "*Normalizing result*\n";
            if (manRes >> 24 != 0) {
                manRes >>= 1;
                expRes += 1;
                cout << "*Shifted right*\nres mantissa:\n" << bitset<32>(manRes)
                << "\nres exponent:\n" << expRes - 127 << endl;
            }
            else {
                manRes <<= 1;
                expRes -= 1;
                cout << "*Shifted left*\nres mantissa:\n" << bitset<32>(manRes)
                << "\nres exponent:\n" << expRes - 127 << endl;
            }
        }
        manRes &= (UINT32_MAX >> 9);
    }
    unsigned res = (signRes << 31) | (expRes << 23) | manRes;
    cout << "Result in binary form:\n" << bitset<32>(res) << endl;
    float resF = *(float*)&res;
    cout << "Result as float:" << resF;
}
