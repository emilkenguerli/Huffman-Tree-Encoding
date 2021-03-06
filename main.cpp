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

    KNGEMI002::HuffmanTree* ht = new KNGEMI002::HuffmanTree(input_file, output_file);

    vector<KNGEMI002::CharFrequency> *s = new vector<KNGEMI002::CharFrequency>;
    ht->encode(*s);
    delete s;
	delete ht;
    return 0;
}
