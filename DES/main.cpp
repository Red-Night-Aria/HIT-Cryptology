#include <iostream>
#include "DEScryption.h"
#include <fstream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <random>
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

uint64_t random_transform(uint64_t bytes, default_random_engine& e1) {
    uniform_int_distribution<int> uniform_dist(0, 63);
    int keep = uniform_dist(e1);
    uniform_int_distribution<int> uniform_dist1(0, UINT64_MAX);
    uint64_t randNum = uniform_dist1(e1) | (1<<keep);
    return bytes xor randNum;
}

int main(int argc, char** argv) {
    string srecetKey = "Redim";
    DEScryption fe(srecetKey);

    string input, output;
    po::options_description desc("usage: ");
    desc.add_options()
            ("help", "produce help message")
            ("input", po::value<string>(&input), "input file")
            ("output", po::value<string>(&output)->default_value("decrypt_result"));

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")){
        cout << desc << "\n";
        return 1;
    }

    cout << input << " "+output << endl;
//    const string INPUT_PIC = "../test.bmp";
//    const string OUTPUT_PIC = "../encrypt_CBC.bmp";
//
//    encryptBMP(INPUT_PIC, OUTPUT_PIC, fe, Mode::CBC);

//    uint64_t origin_bytes = 0;
//    array<int, 64> frequency = {};
//
//    random_device r;
//    default_random_engine e1(r());
//
//    for (int i=0; i<256; i++){
//        uint64_t transform_bytes = random_transform(origin_bytes, e1);
//        uint64_t encrypyed_bytes = DES::encrypt(transform_bytes, fe.getKey());
//        uint64_t mask = 1;
//        for (int i=0; i<64; i++){
//            if ((encrypyed_bytes & mask) != 0){
//                ++frequency[i];
//            }
//            mask = mask << 1;
//        }
//    }
//
//    for (int i=0; i<64; i++){
//        cout << "pos " << i << ": " << frequency[i] << endl;
//    }


    return 0;
}

