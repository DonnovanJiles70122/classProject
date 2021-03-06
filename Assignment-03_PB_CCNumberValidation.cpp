#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <iomanip>
using namespace std;
bool isvalidcc(const string&);

int main()
{
    //
    // PLEASE DO NOT CHANGE function main
    //
    vector<string> cardnumbers = {
            "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
            "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
            "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
            "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
            "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
            "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
            "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
            "5556551555555557", "6011316011016011"
    };

    int i;
    vector<string>::iterator itr;

    for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
        cout << setw(2)  << i << " "
             << setw(17) << *itr
             << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
    }

    return 0;
}

bool isvalidcc(const string& str) {
    int SIZE = str.length();
    int cardNum[SIZE];
    int mult, first, second;
    int sum = 0;
    int sum2 = 0;

    for (int i = 0; i < SIZE; i++)
        cardNum[i] = str[i]-48;

    for(int i = SIZE - 1; i >= 0; i--){
        if(i - 1 >= 0) {
            if (cardNum[i - 1] * 2 < 10)
                sum += cardNum[i - 1] * 2;
            else {
                mult = cardNum[i - 1] * 2;
                first = mult / 10;
                second = mult % 10;
                sum += first + second;
            }
        }
        sum2 += cardNum[i];
        i--;
    }

    if((sum + sum2) % 10 == 0)
        return true;
    return false;
}

