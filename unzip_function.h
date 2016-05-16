#pragma once
#ifndef vector_staff
#define vector_staff


#include <iostream>
#include <vector>
#include <string>

#endif
#include <fstream>
#include "C:\Users\Administrator\Desktop\zip_file\zip_file\huffman_tree.h"

struct dictionary
{
	char character;
	std::string code;
};


tree_nodes<char> * read_dictionary(std::string the_file);
void unzip_file(std::string file_name);