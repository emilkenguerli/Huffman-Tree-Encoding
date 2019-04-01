// HuffmanTree.h: declaration of HuffmanTree class.

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <algorithm>
#include "HuffmanNode.h"

using namespace std;
namespace KNGEMI002 {
	class HuffmanTree {
	  std::string extension;
	  std::string input_file;
	  std::string output_file;
	  unsigned int source_bytes;
	  int unique_chars;
	  std::unordered_map<char, string> code_table;

	public:  
	  HuffmanTree(void);
	  HuffmanTree(std::string inputfile,std::string outputfile);
	  HuffmanTree(const HuffmanTree &hf2);
	  HuffmanTree(HuffmanTree &&hf2);
	  HuffmanTree& operator=(const HuffmanTree &hf);
	  HuffmanTree& operator=(HuffmanTree &&hf);
	  ~HuffmanTree();
	  void CompressData(int node, int child);
	  void set_input_filename(std::string filename, std::string extname);
	  void set_output_filename(std::string filename);
	  double encode(vector<CharFrequency> &symbols);
	  void assign_huffman_codes(const shared_ptr<HuffmanNode>& binary_tree,
						   const unique_ptr<string>& code,
						   std::unordered_map<char, string>* huffman_encoding);
	  std::string read_bits(int &count, std::string file_name);
  	  void write_bits(int count, std::string bitstring, std::string file_name);
	};
	
}
#endif