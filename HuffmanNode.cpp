// HuffmanNode.cpp: definition of HuffmanNode class.

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <memory>
#include <limits>
#include "HuffmanNode.h"

HuffmanNode::HuffmanNode(void) : frequency(0), left(nullptr), right(nullptr){}

HuffmanNode::HuffmanNode(double freq, const std::shared_ptr<CharFrequency>& cf, const std::shared_ptr<HuffmanNode>& lhs, const std::shared_ptr<HuffmanNode>& rhs){
	this -> frequency = freq;
	this -> charfreq = cf;
	this -> left = lhs;
	this -> right = rhs;
}

HuffmanNode::HuffmanNode(const HuffmanNode &hf2){
	this -> frequency = hf2.frequency;
	this -> charfreq = hf2.charfreq;
	this -> left = hf2.left;
	this -> right = hf2.right;
}

HuffmanNode::HuffmanNode(HuffmanNode &&hf2){
	this -> frequency = hf2.frequency;
	this -> charfreq = hf2.charfreq;
	this -> left = hf2.left;
	this -> right = hf2.right;
	hf2.frequency = std::numeric_limits<double>::quiet_NaN();;
	hf2.charfreq = nullptr;
	hf2.left = nullptr;
	hf2.right = nullptr;
}

HuffmanNode& HuffmanNode::operator=(const HuffmanNode& hf){
	HuffmanNode tmp(hf);
	std::swap(this -> frequency, tmp.frequency);
	std::swap(this -> charfreq, tmp.charfreq);
	std::swap(this -> left, tmp.left);
	std::swap(this -> right, tmp.right);
	return *this;
}

HuffmanNode& HuffmanNode::operator=(HuffmanNode &&hf){
	std::swap(this -> frequency, hf.frequency);
	std::swap(this -> charfreq, hf.charfreq);
	std::swap(this -> left, hf.left);
	std::swap(this -> right, hf.right);
	return *this;
}

HuffmanNode::~HuffmanNode() {}

bool HuffmanNode::operator<(const std::shared_ptr<HuffmanNode>& rhs) const {
  return this->frequency < rhs->frequency;
}
