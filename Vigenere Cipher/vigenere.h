#ifndef VIGENERE_H
#define VIGENERE_H
#include <string>
using std::string;

class Vigenere{
public:
    Vigenere(unsigned keyLength);

    const string& getKey() const{
        return key;
    }

    string encrypt(const string& text) const {return shiftText(text, 1);}
    string decrypt(const string& encrypt_text) const {return shiftText(encrypt_text, 0);}
private:
    string key;
    unsigned n;
    string shiftText(const string& text, bool shiftRight) const;
};
#endif