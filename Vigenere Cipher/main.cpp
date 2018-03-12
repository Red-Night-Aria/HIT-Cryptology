#include <iostream>
#include <fstream>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include "vigenere.h"
#include "ICindex.h"

using namespace std;

int main(){
    string text, line;
    ifstream txtin("Alice's Adventures in Wonderland.txt");
    while (getline(txtin, line)){
        text = text + line + "\n";
    }

    // part1: 根据用户输入n，生成相应长度的密钥并加密文件"input"
    unsigned n;
    cout << "The length of key ? "; cin >> n;
    Vigenere v = Vigenere(n);
    cout << "\nThe generated key: " << v.getKey() << endl;

    string encrypt_text = v.encrypt(text);
    cout << "\nThe encrypted text is stored in output.txt\n" << endl;
    ofstream txtout("output.txt");
    txtout << encrypt_text << endl;

    // part2: 解密Vigenere密文
    cout << "Decrypting encrypted text......" << endl;
    string infer_key = attack_vigenere_cipher_by_ICindex_method(encrypt_text);
    cout << "infer key: " << infer_key << endl;
    
    // part3: 统计明文和 n=4,16 两种情况下密文中各字符出现的频率
    // array<array<int, 26>, 3> caa = {};
    // caa[0] = countLetterFrequency(text);
    // caa[1] = countLetterFrequency(Vigenere(4).encrypt(text));
    // caa[2] = countLetterFrequency(Vigenere(16).encrypt(text));
    // ofstream txtout("frequency.dat");
    // for (auto& ca: caa){
    //     for (auto num : ca){
    //         txtout << num << ' ';
    //     }
    //     txtout << endl;
    // }

    // part4: 计算明文和密文的重合指数。要求给出 n =1,2,4,8,16,32,64, 128,256 几种情况下的计算结果。
    // ofstream txtout("ICindex.dat");
    // array<int, 9> na = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    // txtout << calculateICindex(text) << " ";
    // for (auto n : na){
    //     txtout << calculateICindex(Vigenere(n).encrypt(text)) << " ";
    // }

    return 0;
}