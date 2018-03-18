#include <iostream>
#include "DEScryption.h"
#include <sstream>
#include <fstream>
#include <unistd.h>

int main() {
//    char* buff;
//    getcwd(buff, 0);
//    if (buff==NULL){
//        perror("getcwd error");
//    }
//    else {
//        printf("%s", buff);
//    }

    string srecetKey = "Yezhonghao";
    DEScryption fe(srecetKey);
//    string plain_text = "Hello World";
//    istringstream input(plain_text);
//    ostringstream output;
//    fe.encrypt(input, output);
//    string cipher = output.str();
//    cout << cipher << endl;
//    istringstream another_input(cipher);
//    ostringstream another_output;
//    fe.decrypt(another_input, another_output);
//    cout << another_output.str() << endl;

    ifstream pic("../test.bmp", ios::binary);
    pic.seekg(10, pic.beg);
    ui32 offset = 0;
    pic.read((char *)&offset, 4);
    pic.seekg(0, pic.beg);
    char bmp_head[1000];
    pic.read(bmp_head, offset);
    bmp_head[offset] = '\0';

    ofstream enc_pic("../encrypt.bmp", ios::binary);
    fe.encrypt(pic, enc_pic);
    pic.close();
    enc_pic.close();
    return 0;
}