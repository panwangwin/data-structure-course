//
//  function.cpp
//  zip_file
//
//  Created by PAN on 16-5-12.
//  Copyright (c) 2016年 prowind. All rights reserved.
//

#include "zip_function.h"
#include "huffman_tree.h"

std::vector<int> counting(128,0);
std::vector<string> code(128,"");
void stat(std::string file, std::vector<int> &count)
{
    for (int i=0; i<file.size(); i++)
    {
        count[(int)file[i]]= count[(int)file[i]]+1;
    }
}

void coding(std::vector<std::string> code, std::string file)
{
	char filename[] = "c://files//test.txt"; // 此处写入文件名;
	std::ofstream yout(filename, ios::out);
	std::string abundant_code,shell_code,final_code;
	int n = 0;
	for (int i = 0; i < 128; i++)
	{
		if (counting[i] != 0)
			n = n + 1;
	}
	yout << n;
	for (int i = 0; i < 128; i++)
	{
		if (counting[i] != 0)
			yout << " " << (char)i << " " << code[i];
	}
	yout << " ";
	yout << file.size();
	yout << " ";
	for (int i=0; i<file.size();i++)
    {
        if (abundant_code.size()!=0)
        {
            shell_code=shell_code+abundant_code;
            abundant_code="";
        }
        shell_code=shell_code+code[(int)file[i]];
        if (shell_code.size()>=8)
        {
            string abuntdant_code(shell_code,8,8);
			abundant_code = abuntdant_code;
			string final_code(shell_code,0,8);
            yout << output(final_code);
			shell_code="";
        }
    }
	int size = shell_code.size();
	if (size != 0)
		for (int i = 0; i < 8 - size; i++)
			shell_code = shell_code + "0";
	yout<<output(shell_code);
}

unsigned char output(std::string code)
{
	unsigned char character = 0x0;
    if (code[0] == '1')
    {
        character=character+0x80;
	};
    if (code[1]== '1')
    {
        character=character+0x40;
	};
    if (code[2]=='1')
    {
        character=character+0x20;
	};
    if (code[3]=='1')
    {
        character=character+0x10;
	};
    if (code[4]=='1')
    {
        character=character+0x8;
	};
    if (code[5]=='1')
    {
        character=character+0x4;
	};
    if (code[6]=='1')
    {
        character=character+0x2;
	};
    if (code[7]=='1')
    {
        character=character+0x1;
	};
	return character;

}

void zip_file(string file_name)
{
    vector<tree_nodes<char>*> the_sons;
    tree_nodes<char>* the_tree;
    std::fstream in(file_name);
    std::istreambuf_iterator<char> beg(in), end;
    std::string the_file(beg, end);
    stat(the_file,counting);
    the_sons=build_sons(counting);
    the_tree=huffman_tree(the_sons);
	for (int i=0; i<128;i++)
    {
        if (counting[i]!=0)
        {
        std::string temp_code="";
        code[i]=get_the_code((char) i , temp_code , the_tree);
		}
    }
	
    coding(code,the_file);
}












