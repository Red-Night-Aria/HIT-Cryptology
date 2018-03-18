#include <iostream>
#include "DEScryption.h"
#include <fstream>

int main() {
    string srecetKey = "Redim";
    DEScryption fe(srecetKey);
    const string INPUT_PIC = "../test.bmp";
    const string OUTPUT_PIC = "../encrypt.bmp";
    ifstream pic(INPUT_PIC, ios::binary);

    /* read offset field */
    pic.seekg(10, pic.beg);
    ui32 offset = 0;
    pic.read((char *)&offset, 4);
    cout << offset << endl;
    pic.seekg(0, pic.beg);

    /* copy bmp file head data*/
    const unsigned HEAD_MAX = 3000;
    char bmp_head[HEAD_MAX];
    pic.read(bmp_head, offset);
    ofstream enc_pic(OUTPUT_PIC, ios::binary);
    enc_pic.write(bmp_head, offset); //enc_pic << bmp_head; WRONG!

    fe.encrypt(pic, enc_pic);
    pic.close();
    enc_pic.close();

//    pic.open("../encrypt.bmp", ios::binary);
//    pic.seekg(10, pic.beg);
//    pic.read((char *)&offset, 4);
//    cout << offset << endl;
    return 0;
}