//
// Created by redim on 18-3-17.
//

#ifndef DES_BMPCRYPTION_H
#define DES_BMPCRYPTION_H

#include "des.h"
#include <string>
#include <iostream>

enum class Mode{ECB, CBC};

class DEScryption {
public:
    DEScryption(const string& strkey);
    void encrypt(istream& input, ostream& output, Mode mode=Mode::ECB);
    void decrypt(istream& input, ostream& output, Mode mode=Mode::ECB);
private:
    ui64 key = 0;
    void cipher(istream& input, ostream& output, Mode mode, bool isDecrypt);
    ui64 BKDRHash(const string &str);
};


#endif //DES_BMPCRYPTION_H
