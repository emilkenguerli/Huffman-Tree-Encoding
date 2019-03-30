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
/*using std::priority_queue;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;
*/
// namespace is used in order to escape BinaryTreeNode symbol
using namespace std;

HuffmanTree::HuffmanTree() {
}

HuffmanTree::~HuffmanTree() {
}

double HuffmanTree::encode(vector<CharFrequency> &symbols) {
  char c;
  unsigned char uc;
  std::ifstream in_file;
  std::ifstream temp_file;
//  output_file += ext_name; // add extension to output file name
  in_file.open(input_file, std::ios::binary|std::ios::in);
//  if (out_file.is_open())
//    out_file.close();
//  out_file.open(output_file, std::ios::binary|std::ios::out);
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
    candidates.emplace(new HuffmanNode{(double)s.freq, p, nullptr, nullptr});
  }

  cout << "size=" << candidates.size() << endl;

  // use temporary queue to print out candidates
/*  priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, compare> temp = candidates;
  while (!temp.empty()) {
    std::cout << "candidates=" << temp.top()->charfreq->c << "Then="<< temp.top()->charfreq->freq << std::endl;
    temp.pop();
  }
*/
  // Combining two nodes until there is only one node left.
  while (candidates.size() > 1) {
    shared_ptr<HuffmanNode> left = candidates.top();
    candidates.pop();
    shared_ptr<HuffmanNode> right = candidates.top();
    candidates.pop();
    candidates.emplace(new HuffmanNode{
        left->frequency + right->frequency, nullptr, left, right});
  }
   
 // Traverses the Hoffman tree and assign codes to nodes.

  assign_huffman_codes(candidates.top(), std::make_unique<string>(), &code_table);

  cout << "code_table = " << endl;
  for (auto& it: code_table) {
    cout << it.first << it.second << endl;
  }
  in_file.close();

  std::unordered_map<char, string>::iterator it;

  while (!temp_file.eof())
  {
    temp_file.get(c);
    it = code_table.find(c);
	if (it != code_table.end())
	{
		std::cout << "Element Found - ";
		std::cout << it->first << "::" << it->second << std::endl;
	}
	else
	{
		std::cout << "Element Not Found" << std::endl;
	}

  }
  return 1;
}

void HuffmanTree::assign_huffman_codes(const shared_ptr<HuffmanNode>& binary_tree,
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

void HuffmanTree::CompressData(int node, int child)
{
/*    if (h_tree[node].GetRoot() != -1)
    {
        bit_count++;
        compress_byte(h_tree[node].GetRoot(), node);
    }
    if (child != -1)
    {
        if (child == h_tree[node].GetRight())
                output_bit(0);
            else if(child == h_tree[node].GetLeft())
                output_bit(1);
    }
*/}


void HuffmanTree::set_input_filename(std::string filename, std::string extname)
{
    input_file = filename;
    extension = extname;
}

void HuffmanTree::set_output_filename(std::string filename)
{
    output_file = filename;
}



