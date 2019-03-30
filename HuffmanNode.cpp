// HuffmanNode.cpp: definition of HuffmanNode class.

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <memory>
#include "HuffmanNode.h"


bool HuffmanNode::operator<(const std::shared_ptr<HuffmanNode>& rhs) const {
  return frequency < rhs->frequency;
}

bool HuffmanNode::compareNode(const std::shared_ptr<HuffmanNode>& a,
                  const std::shared_ptr<HuffmanNode>& b) {
  if (a < b) return true;
  else return false;
} 
