#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
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

  output_file += extension; // add extension to output file name
  std::cout << "Output filename: " << output_file << std::endl;
  in_file.open(input_file, std::ios::binary|std::ios::in);

  out_file.open(output_file, std::ios::binary|std::ios::out);

  output_file += ".bin";
  b_out_file.open(output_file, std::ios::binary|std::ios::out);
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

for(auto vite = symbols.begin(); vite != symbols.end(); ++vite) {
    cout << vite->c << vite->freq << endl;
}

  // Start with assigning each symbol into candidates.
  priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, compare> candidates;

  for (CharFrequency &s : symbols) {
    shared_ptr<CharFrequency> p(new CharFrequency(s));
    //candidates.emplace(new HuffmanNode{(double)s.freq, p, nullptr, nullptr});
	candidates.emplace(new HuffmanNode((double)s.freq, p, nullptr, nullptr));
  }

  cout << "size=" << candidates.size() << endl;

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

  cout << "code_table = " << endl;
  for (auto& it: code_table) {
    cout << it.first << it.second << endl;
  }
  in_file.close();

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
//		std::cout << "Element Found - ";
//		std::cout << it->first << "::" << it->second << std::endl;
		buffer += it->first + it->second;
                bits += it->second;
		count ++;
	}
	else
	{
		std::cout << "Element Not Found" << std::endl;
	}

  }
  const char* bytes = buffer.c_str();
  out_file << count;

  for(int i = 0; i < buffer.length();i++){
	out_file << bytes[i];
  }
  if (out_file.is_open())
    out_file.close();
const std::size_t n = bits.length();
std::vector<char> byteArray(n / 8);
b_out_file << count;

for (std::size_t i = 0; i < n / 8; ++i) {
  for (std::size_t j = 0; j < 8; ++j) {
    if (bits[i * 8 + j] == '1') {
      byteArray[i] |= 1 << j;
    }
  }
  b_out_file << byteArray[i];
}
  if (b_out_file.is_open())
    b_out_file.close();

  return 1;
}

void KNGEMI002::HuffmanTree::assign_huffman_codes(const shared_ptr<HuffmanNode>& binary_tree,
                       const unique_ptr<string>& code,
                       std::unordered_map<char, string>* huffman_encoding) {
  if (binary_tree) {
    if (binary_tree->charfreq) {
      // leaf node
      (*huffman_encoding)[binary_tree->charfreq->c] = *code;
      cout << "leaf node = " << *code << endl;
    } else {  // non-leaf node
      code->push_back('0');
      assign_huffman_codes(binary_tree->left, code, huffman_encoding);
      code->back() = '1';
      assign_huffman_codes(binary_tree->right, code, huffman_encoding);
      code->pop_back();
      cout << "non-leaf node = " << *code << endl;
    }
  }
}


