#define CATCH_CONFIG_MAIN //So that catch will define a main method
#include <memory>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include "catch.hpp"
#include "HuffmanTree.h"

struct CharFrequency {
	  char c;
	  double freq;
	};

TEST_CASE("FREQUENCY","This tests that the first and last frequency is correct")
{
		
		char c;
		unsigned char uc;
		std::ifstream in_file;
		in_file.open("aaa.txt", std::ios::binary|std::ios::in);
		vector<CharFrequency> *s = new vector<CharFrequency>;
		std::cout << "SIMPLE FREQUENCY TEST" << std::endl;
		std::unordered_map<char, int> map;
		while (!in_file.eof())
		{
			in_file.get(c);
			uc = static_cast<unsigned char>(c);
			map[c]++;
		}
		vector<CharFrequency> symbols;

		for (auto& it: map) {
			CharFrequency a;
			a.c = (char) it.first;
			a.freq = (double) it.second;
			symbols.push_back(a);
		}

		REQUIRE(symbols[0].freq == 3);
		REQUIRE(symbols[4].freq == 8);

		in_file.close();
}





