#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "HuffmanTree.h"

using std::make_unique;

// namespace is used in order to escape BinaryTreeNode symbol
using namespace std;

KNGEMI002::HuffmanTree::HuffmanTree(void) : extension(".hdr"), output_file("output"){}

KNGEMI002::HuffmanTree::HuffmanTree(std::string inputfile,std::string outputfile){
	this -> extension = ".hdr";
  	this -> input_file = inputfile;
	this -> output_file = outputfile;
}

KNGEMI002::HuffmanTree::HuffmanTree(const HuffmanTree &hf2){
	this -> input_file = hf2.input_file;
	this -> output_file = hf2.output_file;
}

KNGEMI002::HuffmanTree::HuffmanTree(HuffmanTree &&hf2){
	this -> input_file = hf2.input_file;
	this -> output_file = hf2.output_file;
	hf2.input_file = nullptr;
	hf2.output_file = nullptr;
}

KNGEMI002::HuffmanTree& KNGEMI002::HuffmanTree::operator=(const HuffmanTree& hf){
	HuffmanTree tmp(hf);
	std::swap(this -> input_file, tmp.input_file);
	std::swap(this -> output_file, tmp.output_file);
	return *this;
}

KNGEMI002::HuffmanTree& KNGEMI002::HuffmanTree::operator=(HuffmanTree &&hf){
	std::swap(this -> input_file, hf.input_file);
	std::swap(this -> output_file, hf.output_file);
	return *this;
}

KNGEMI002::HuffmanTree::~HuffmanTree() {
}

double KNGEMI002::HuffmanTree::encode(vector<CharFrequency> &symbols) {
  char c;
  unsigned char uc;
  std::ifstream in_file;
  std::ifstream temp_file;
  std::ofstream out_file;
  std::ofstream b_out_file;
  std::string hdr_file;
  
  hdr_file = output_file + extension; // add extension to output file name

  in_file.open(input_file, std::ios::binary|std::ios::in);
  if(!in_file){
		std::cout << "Couldn't open " << input_file << std::endl;
		return 0;
  }

  out_file.open(hdr_file, std::ios::binary|std::ios::out);

  temp_file.open(input_file, std::ios::binary|std::ios::in);

// count number of occurences of each letter and store it in unordered_map
  std::unordered_map<char, int> map;
  while (!in_file.eof())
  {
    in_file.get(c);
    uc = static_cast<unsigned char>(c);
    map[c]++;
  }

for (auto& it: map) {
  CharFrequency a;
  a.c = (char) it.first;
  a.freq = (double) it.second;
  symbols.push_back(a);
}

  // Start with assigning each symbol into candidates.
  priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, compare> candidates;

  for (CharFrequency &s : symbols) {
    shared_ptr<CharFrequency> p(new CharFrequency(s));
    //candidates.emplace(new HuffmanNode{(double)s.freq, p, nullptr, nullptr});
	candidates.emplace(new HuffmanNode((double)s.freq, p, nullptr, nullptr));
  }

  // Combining two nodes until there is only one node left.
  while (candidates.size() > 1) {
    shared_ptr<HuffmanNode> left = candidates.top();
    candidates.pop();
    shared_ptr<HuffmanNode> right = candidates.top();
    candidates.pop();
	candidates.emplace(new HuffmanNode(left->frequency + right->frequency, nullptr, left, right));
  }
   
 // Traverses the Hoffman tree and assign codes to nodes.

  assign_huffman_codes(candidates.top(), std::make_unique<string>(), &code_table);

  std::unordered_map<char, string>::iterator it;
  std::string buffer;
  std::string bits;
  int count = 0;

  while (!temp_file.eof())
  {
    temp_file.get(c);
    it = code_table.find(c);
	if (it != code_table.end())
	{
		buffer += it->first + it->second;
                bits += it->second;
		count ++;
	}
  }
  const char* bytes = buffer.c_str();

  for(int i = 0; i < buffer.length();i++){
	out_file << bytes[i];
  }
  if (out_file.is_open())
    out_file.close();

  std::string binary_file = output_file + ".bin";
  write_bits(count, bits, binary_file); // write into binary file

  int n_symbols; 
  std::string new_bits = read_bits(n_symbols, binary_file); // read number of symbols and string of bits from binary file

  // decode the string
  string temp;
  string decoded;
  for(char& c : new_bits) {
    temp += c;
    for (auto& it: code_table) {
      if (temp == it.second) {
        decoded += it.first;
        temp.clear();
      }
    }
  }
  std::string decoded_string = decoded.substr (0,n_symbols-1); // select correct amount of characters


  std::string original_data(std::istreambuf_iterator<char>(std::ifstream(input_file).rdbuf()), std::istreambuf_iterator<char>());

  // Compare Original and decoded data
  if( decoded_string == original_data )
    cout << "Original and decoded data are identical" << endl;
  else
    cout << "Original and decoded data are not identical" << endl;

  if (in_file.is_open())
    in_file.close();
  if (temp_file.is_open())
    temp_file.close();

  return 1;
}

std::string KNGEMI002::HuffmanTree::read_bits(int &count, string file_name)
{
  using byte = unsigned char;
  using bits_in_byte = std::bitset<8>;
  std::string bitstring ;
  std::ifstream file(file_name, std::ios::binary) ; // open in binary mode
  file.read((char*) (&count), sizeof(count));
  char c ;
  while(file.get(c)) // read byte by byte
    bitstring += bits_in_byte(byte(c)).to_string() ; // append as string of '0' '1'

    return bitstring ;
}

void KNGEMI002::HuffmanTree::write_bits(int count, std::string bitstring, string file_name)
{
  using byte = unsigned char;
  using bits_in_byte = bitset<8>;    // pad with zeroes till integral multiple of bytes
  while( bitstring.size()% 8 ) bitstring += '0';

  ofstream file(file_name, std::ios::binary); 
  file.write(reinterpret_cast<const char *> (&count), sizeof(count));
  for(std::size_t i = 0 ; i < bitstring.size() ; i += 8) {
    // convert '0' or '1' to a byte
    byte b = bits_in_byte( bitstring.substr( i, 8 ) ).to_ulong() ;
    file << b ; // and write into file
  }
}

void KNGEMI002::HuffmanTree::assign_huffman_codes(const shared_ptr<HuffmanNode>& binary_tree,
                       const unique_ptr<string>& code,
                       std::unordered_map<char, string>* huffman_encoding) {
  if (binary_tree) {
    if (binary_tree->charfreq) {
      // leaf node
      (*huffman_encoding)[binary_tree->charfreq->c] = *code;
    } else {  // non-leaf node
      code->push_back('0');
      assign_huffman_codes(binary_tree->left, code, huffman_encoding);
      code->back() = '1';
      assign_huffman_codes(binary_tree->right, code, huffman_encoding);
      code->pop_back();
    }
  }
}


