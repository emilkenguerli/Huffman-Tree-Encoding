// HuffmanNode.h: declaration of HuffmanNode class.
#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

#include <memory>

namespace KNGEMI002 {
	struct CharFrequency {
	  char c;
	  double freq;
	//  std::string code;
	};

	class HuffmanNode {  //BinaryTree
	public: // data structure
	  double frequency;
	  std::shared_ptr<CharFrequency> charfreq;
	  std::shared_ptr<HuffmanNode> left, right;
	  HuffmanNode(void);
	  HuffmanNode(double freq, const std::shared_ptr<CharFrequency>& cf, const std::shared_ptr<HuffmanNode>& lhs, const std::shared_ptr<HuffmanNode>& rhs);
	  HuffmanNode(const HuffmanNode &hf2);
	  HuffmanNode(HuffmanNode &&hf2);
	  HuffmanNode & operator=(const HuffmanNode & hf);
	  HuffmanNode& operator=(HuffmanNode &&hf);
	  ~HuffmanNode();
	public: // methods
	  bool operator<(const std::shared_ptr<HuffmanNode>& rhs) const; //overloading 'less than' operator
	  bool compareNode(const std::shared_ptr<HuffmanNode>& a,
					  const std::shared_ptr<HuffmanNode>& b); //comparing two nodes
	};

	class compare {
	  bool compareNode(const std::shared_ptr<HuffmanNode>& a,
					  const std::shared_ptr<HuffmanNode>& b) {
		if (b<a) return true;
		else return false;
	  };
	public:
	  bool operator()(const std::shared_ptr<HuffmanNode>& lhs,
					  const std::shared_ptr<HuffmanNode>& rhs) {
		return compareNode(lhs, rhs); 
	  }; //comparing two nodes
	};
}
#endif