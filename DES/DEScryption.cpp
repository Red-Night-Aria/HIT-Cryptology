//
// Created by redim on 18-3-17.
//

#include "DEScryption.h"

using namespace std; //since des.h has already include std namespace, I have no choice ...

void DEScryption::decrypt(istream &input, ostream &output, Mode mode) {
    cipher(input, output, mode, true);
}

void DEScryption::encrypt(istream &input, ostream &output, Mode mode) {
    /*
    * 加密从流当前位置至流结尾的数据
    * */
    cipher(input, output, mode, false);
}

void DEScryption::cipher(istream &input, ostream &output, Mode mode, bool isDecrypt) {
    ui64 buffer;
    DES des = DES(key);
//    if (mode==Mode::ECB){
//        DES des = DES(key);
//    }
    streamoff begin = input.tellg();
    input.seekg(0, input.end);
    ui64 size = input.tellg() - begin;
    input.seekg(begin);

    ui64 block = size / 8;
    if(isDecrypt) block--;

    for(ui64 i = 0; i < block; i++) {
        input.read((char*) &buffer, 8);

        if(isDecrypt)
            buffer = des.decrypt(buffer);
        else
            buffer = des.encrypt(buffer);

        output.write((char*) &buffer, 8);
    }

    if(!isDecrypt) {
        // Amount of padding needed
        ui8 padding = 8 - (size % 8);

        // Padding cannot be 0 (pad full block)
        if (padding == 0)
            padding  = 8;

        // Read remaining part of file
        buffer = (ui64) 0;
        if(padding != 8)
            input.read((char*) &buffer, 8 - padding);

        // Pad block with a 1 followed by 0s
        ui8 shift = padding * 8;
        buffer <<= shift;
        buffer  |= (ui64) 0x0000000000000001 << (shift - 1);

        buffer = des.encrypt(buffer);
        output.write((char*) &buffer, 8);
    }
    else {
        // Read last line of file
        input.read((char*) &buffer, 8);
        buffer = des.decrypt(buffer);

        // Amount of padding on file
        ui8 padding = 0;

        // Check for and record padding on end
        while(!(buffer & 0x00000000000000ff))
        {
            buffer >>= 8;
            padding++;
        }

        buffer >>= 8;
        padding++;

        if(padding != 8)
            output.write((char*) &buffer, 8 - padding);
    }
}

DEScryption::DEScryption(const string &strkey) {
    key = BKDRHash(strkey);
    //printf("%llx\n", key);
}

ui64 DEScryption::BKDRHash(const string &str) {
    ui64 seed = 131;
    ui64 hash = 0;

    auto it = str.cbegin();
    while (it != str.cend())
    {
        hash = hash * seed + (*it++);
    }

    return hash;
}
