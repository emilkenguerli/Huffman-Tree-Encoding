#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include "HuffmanTree.h"

using namespace std;


static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)>\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t <inputFile>\t\tinput English (ASCII) text file\n"
              << "\t <output file>\t\tthe name of output compressed bitstream file"
              << std::endl;
}

void del(void(*)()) {}
void fun() {}

int main(int argc, char* argv[])
{
    if (argc < 3 || argc > 3)
    {
        show_usage(argv[0]);
        return 1;
    }
    const char * input_file = argv[1];
    const char * output_file = argv[2];
    cout << "Input = " << input_file << endl;
    cout << "Output = " << output_file << endl;

    HuffmanTree ht;

    ht.set_input_filename(input_file, ".hdr");
    ht.set_output_filename(output_file);
    vector<CharFrequency> *s = new vector<CharFrequency>;
    ht.encode(*s);
    return 0;
}

//  std::vector<std::string> args{argv + 1, argv + argc};
//  std::vector<std::string> param_names{"symbols"};

//  HuffmanEncodingWrapper(&param_names);

//GenericTestMain(args, "huffman_coding.cc", "huffman_coding.tsv",
//                         &HuffmanEncodingWrapper, DefaultComparator{},
//                         param_names);
