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
            ("help,H", "produce help message")
            ("bmp,B", "whether input file is bmp syntax")
            ("mode,M", po::value<string>()->default_value("ECB"), "encrypt mode, either ECB or CBC")
            ("input,I", po::value<string>(&input), "input file")
            ("output,O", po::value<string>(&output)->default_value("decrypt_result"));

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")){
        cout << desc << "\n";
        return 1;
    }

    Mode mode=Mode::ECB;
    if (vm["mode"].as<string>() == "CBC"){
        mode = Mode::CBC;
    }

    if (vm.count("bmp")){
        encryptBMP(input, output, fe, mode);
    }
    else {
        ifstream input_strm(input, ios::binary);
        ofstream output_strm(output, ios::binary);
        fe.encrypt(input_strm, output_strm, mode);
        input_strm.close();
        output_strm.close();
    }

    return 0;
}

