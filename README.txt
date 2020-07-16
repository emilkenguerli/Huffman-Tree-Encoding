HuffmanNode.h:

This is the header file that declares the HuffmanNode, Compare classes and the CharFrequency struct

HuffmanNode.cpp:

This file defines the 6 special memeber functions and also overloads the operator <

HuffmanTree.h:

This is the header file that declares the HuffmanTree class. It includes the HuffmanNode header as it uses its class to build the tree structure

HuffmanTree.cpp

This file defines the 6 special memeber functions as well as all of HuffmanTree's methods

main.cpp

This is the driver file that includes main(), it includes HuffmanTree.h. It has a help menu pop up if an error occurs in the command line execution. 


MEMORY MANAGEMENT

I ran a program to check for memory leaks. Seeing as I had none due to usage of smart pointers, I left my destructors empty.

aaa.txt

I included this file to use as a default run using the "make run" command. The unit testing also makes use of this text file.


 