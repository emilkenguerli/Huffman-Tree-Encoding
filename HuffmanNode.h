// HuffmanNode.h: declaration of HuffmanNode class.

#include <memory>

struct CharFrequency {
public:
  char c;
  double freq;
//  std::string code;
};

class HuffmanNode {  //BinaryTree
public: // data structure
  double frequency;
  std::shared_ptr<CharFrequency> charfreq;
  std::shared_ptr<HuffmanNode> left, right;
public: // methods
  bool operator<(const std::shared_ptr<HuffmanNode>& rhs) const; //overloading 'less than' operator
  bool compareNode(const std::shared_ptr<HuffmanNode>& a,
                  const std::shared_ptr<HuffmanNode>& b); //comparing two nodes
};

struct compare {
  bool operator()(const std::shared_ptr<HuffmanNode>& lhs,
                  const std::shared_ptr<HuffmanNode>& rhs) const {
    return lhs->compareNode(lhs, rhs); //lhs->frequency > rhs->frequency;
  }

};