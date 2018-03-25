//
// Created by redim on 18-3-17.
//

#ifndef DES_BMPCRYPTION_H
#define DES_BMPCRYPTION_H

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

enum class Mode{ECB, CBC};

class DEScryption {
public:
    DEScryption(const string& strkey);
    void encrypt(istream& input, ostream& output, Mode mode=Mode::ECB);
    void decrypt(istream& input, ostream& output, Mode mode=Mode::ECB);
    uint64_t getKey() { return key;}
private:
    uint64_t key = 0;
    void cipher(istream& input, ostream& output, Mode mode, bool isDecrypt);
    uint64_t BKDRHash(const string &str);
};


#endif //DES_BMPCRYPTION_H
