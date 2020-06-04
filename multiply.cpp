#include <iostream>
#include <bitset>

using namespace std;

int main()
{
   int md; int mr;
   long long pro_MR;
   long long crutch;
   cout << "Enter multiplicand and multiplier" << endl;
   do {
      if(cin.fail())
         {
            cin.clear();
            cin.ignore();
            cout << "You have entered wrong input" << endl;
         }
      cin >> md >> mr;
   }
   while(cin.fail());
   crutch=mr;
   pro_MR = crutch;
   /*Here problem is that with variables we can't simulate adding part of register(older 32 bits)
   and also can not shift 32 int so need buffer to add shifted value*/
   crutch = md;
   crutch <<= 32;
   //interface stuff
   cout << "Multiplicand:\n" << bitset<32>(md) << endl;
   cout << "Multiplier:\n" << bitset<32>(mr) << endl;
   cout << "*Assigning multiplier to right 32 bits of product*:\n"
      << "Product:\n" << bitset<64>(pro_MR) << endl;
   for (int i = 0; i < 31; i++) {
      if (pro_MR & 1) {
         cout << "*Last bit in product is 1 - adding*\n";
         pro_MR += crutch;
      }
      cout << "*Shifting product right*\n";
      pro_MR >>= 1;
      cout << bitset<64>(pro_MR)<<endl;
   }
   //for signed multipliyer last bit has negative weight
   if (pro_MR & 1) {
         cout << "*Last (most significant) bit in product is 1 - subtracting*\n";
         //why 1 is here? - cus crutch thug life (and pro_MR filling with 1 if mr < 0)
         pro_MR -= crutch - 1;
   }
   cout << "*Shifting product right*\n";
   pro_MR >>= 1;
   cout << bitset<64>(pro_MR) << endl;

   cout << "Result is: " << pro_MR << endl;
}
