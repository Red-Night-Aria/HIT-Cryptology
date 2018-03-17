#include <iostream>
#include "DEScryption.h"
#include <sstream>

int main() {
    string srecetKey = "Yezhonghao";
    DEScryption fe(srecetKey);
    string plain_text = "Hello World";
    istringstream input(plain_text);
    ostringstream output;

    fe.encrypt(input, output);
    string cipher = output.str();
    cout << cipher << endl;

    istringstream another_input(cipher);
    ostringstream another_output;
    //another_input.seekg(0, ios::beg);
    fe.decrypt(another_input, another_output);
    cout << another_output.str() << endl;
    return 0;
}