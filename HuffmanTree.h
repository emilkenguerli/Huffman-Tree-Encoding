// HuffmanTree.h: declaration of HuffmanTree class.

#include <string>
#include <vector>
#include <unordered_map>
#include "HuffmanNode.h"

using namespace std;

class HuffmanTree {
  std::string extension;
  std::string input_file;
  std::string output_file;
  unsigned int source_bytes;
  int unique_chars;
  std::unordered_map<char, string> code_table;

public:  
  HuffmanTree();
  ~HuffmanTree();
  void CompressData(int node, int child);
  void set_input_filename(std::string filename, std::string extname);
  void set_output_filename(std::string filename);
  double encode(vector<CharFrequency> &symbols);
  void assign_huffman_codes(const shared_ptr<HuffmanNode>& binary_tree,
                       const unique_ptr<string>& code,
                       std::unordered_map<char, string>* huffman_encoding);
};	