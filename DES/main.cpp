#include <iostream>
#include "DEScryption.h"
#include <fstream>
#include <sstream>

using namespace std;

int encryptBMP(const string& INPUT_PIC, const string& OUTPUT_PIC, DEScryption& fe, Mode mode){
    ifstream pic(INPUT_PIC, ios::binary);
    ofstream enc_pic(OUTPUT_PIC, ios::binary);

    /* read offset field */
    pic.seekg(10, pic.beg);
    unsigned offset = 0;
    pic.read((char *)&offset, 4);
    //cout << offset << endl;
    pic.seekg(0, pic.beg);

    /* copy bmp file head data*/
    const unsigned HEAD_MAX = 3000;
    char bmp_head[HEAD_MAX];
    pic.read(bmp_head, offset);
    enc_pic.write(bmp_head, offset); //enc_pic << bmp_head; WRONG!

    fe.encrypt(pic, enc_pic, mode);
    pic.close();
    enc_pic.close();
}


int main() {
    string srecetKey = "Redim";
    DEScryption fe(srecetKey);
    const string INPUT_PIC = "../test.bmp";
    const string OUTPUT_PIC = "../encrypt_CBC.bmp";

    encryptBMP(INPUT_PIC, OUTPUT_PIC, fe, Mode::CBC);
    return 0;
}