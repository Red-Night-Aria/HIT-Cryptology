#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "vigenere.h"

using namespace std;

Vigenere::Vigenere(unsigned keyLength){
    n = keyLength;
    srand(time(0));
    key.resize(n);
    for (auto& ch: key){
        ch = rand()%26 + 'a';
    }
}

string Vigenere::shiftText(const string& text, bool shiftRight) const{
    string shifted = text;
    unsigned i = 0;
    for (auto& ch: shifted){
        char baseChar;
        if ('a' <= ch && ch <= 'z'){
            baseChar = 'a';
        }
        else if ('A' <= ch && ch <= 'Z'){
            baseChar = 'A';
        } else {
            continue;
            //throw exception();
        }

        int num = ch - baseChar;
        if (shiftRight){
            num += key[i] - 'a';
        } else {
            num -= key[i] - 'a';
        }
        
        if (num >= 26) num -= 26;
        if (num < 0) num += 26;
        ch = baseChar + num;

        if (++i >= n) i -= n;
    }
    return shifted;
}


