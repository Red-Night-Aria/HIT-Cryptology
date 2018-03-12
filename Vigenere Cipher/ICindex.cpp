#include <array>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "ICindex.h"
using namespace std;

array<int, 26> countLetterFrequency(const string& text){
    array<int, 26> ca = {};
    for (const auto& ch: text){
        int idx = 0;
        if ('A'<=ch && ch <='Z'){
            idx = ch - 'A';
        }
        else if ('a'<=ch && ch<='z'){
            idx = ch - 'a';
        }
        else continue;
        ca[idx]++;
    }
    return ca;
}

vector<double> calculateICindex(const string& text, int groupNum){
    vector<double> v_ICindex =  {};
    vector<string> sa(groupNum);
    int i = 0;
    for (auto ch: text){
        if (('A'<=ch && ch<='Z')||('a'<=ch && ch<='z')){
            sa[i].push_back(ch);
            if (++i == groupNum){
                i = 0;
            }
        }
    }
    for (const auto& subtext: sa){
        array<int, 26> ca = countLetterFrequency(subtext);
        int len = 0;
        for (auto num: ca) {
            len += num;
        }
        double ICindex = 0;
        for (auto num : ca){
            ICindex += ((double)num/len)*((double)(num-1)/(len-1));
        }
        v_ICindex.push_back(ICindex);
    }

    return v_ICindex;
}

double calculateICindex(const string& text){
    return calculateICindex(text, 1)[0];
}

const array<double, 26> NATURAL_LETTER_FREQUENCY = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 
    0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 
    0.0077, 0.04025, 0.02406, 0.06749, 0.07507,
    0.01929, 0.000095, 0.05987, 0.06327, 0.09056,
};

string attack_vigenere_cipher_by_ICindex_method(const string& cipher){
    /*
        First we infer key's length by calculate ICindex for each group size
    */
    unsigned infer_n = 0;
    const double ENGLISH_TEXT_ICINDEX = 0.067;
    const unsigned MAX_KEY_LENGTH = 512;
    const double TOLERATER = 0.007;

    for (unsigned i=1; i<MAX_KEY_LENGTH; i++){
        vector<double> icv = calculateICindex(cipher, i);
        double ic_avg = 0;
        for (auto& ic : icv){
            ic_avg += abs(ic-ENGLISH_TEXT_ICINDEX);
        }
        //cout << ic_avg/i << " ";
        if (ic_avg < TOLERATER*i){
            infer_n = i;
            break;
        }
    }

    /*
        Then use frequency analysis to deduce cipher's key
    */
    string secretKey = "";
    vector<string> subCipher_vec(infer_n);
    unsigned i = 0;
    for (auto ch: cipher){
        if (('A'<=ch && ch<='Z')||('a'<=ch && ch<='z')){ //it's vital to skip characters are't in alphabet！
            subCipher_vec[i].push_back(ch);
            if (++i == infer_n){
                i = 0;
            }
        }
    }

    for (unsigned i=0; i<infer_n; i++){
        string& subCipher = subCipher_vec[i];
        array<int, 26> LF_arr = countLetterFrequency(subCipher);
        array<double, 26> loss_a = {};

        for (unsigned k=0; k<26; k++){
            for (unsigned l=0; l<26; l++){
                double diff = double(LF_arr[l])/subCipher.size() - NATURAL_LETTER_FREQUENCY[(k+l)%26];
                loss_a[k] += abs(diff);
            }
        }
        auto it = min_element(loss_a.cbegin(), loss_a.cend());
        secretKey.push_back(char('z'+1-(it-loss_a.begin())));
    }

    return secretKey;    
}
