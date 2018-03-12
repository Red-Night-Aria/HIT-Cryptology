#ifndef ICindex_H
#define ICindex_H

#include <array>
#include <string>
#include <vector>
using std::array;
using std::string;
using std::vector;

array<int, 26> countLetterFrequency(const string& text);
double calculateICindex(const string& text);
vector<double> calculateICindex(const string& text, int groupNum);
string attack_vigenere_cipher_by_ICindex_method(const string& cipher);

#endif