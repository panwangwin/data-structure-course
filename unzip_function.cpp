#include "unzip_function.h"
tree_nodes<char> * read_dictionary(std::string file_name)
{
	std::fstream in(file_name);
	int n;
	in >> n;
	dictionary *dict;
	dict = new dictionary[n];
	for (int i = 0; i < n; i++)
	{
		in >> dict[i].character;
		in >> dict[i].code;
	}
	tree_nodes<char> * root, *step;
	root = new tree_nodes<char>;
	for (int i = 0; i < n; i++)
	{
		step = root;
		for (int j = 0; j < dict[i].code.size(); j++)
		{
			if (dict[i].code[j] == '1')
			{
				if (step->left_son == NULL)
				{
					step->left_son = new tree_nodes<char>;;
					step = step->left_son;
				}
				else
					step = step->left_son;
			}
			else if (dict[i].code[j] == '0')
			{
				if (step->right_son == NULL)
				{
					step->right_son = new tree_nodes<char>;;
					step = step->right_son;
				}
				else
					step = step->right_son;
			}
		}
		step->data = dict[i].character;
	}
	return root;
}

void unzip_file(std::string file_name)
{
	tree_nodes<char>* root,*step;
	root=read_dictionary(file_name);
	std::fstream in(file_name);
	int n,char_nos;
	in >> n;
	dictionary *dict;
	dict = new dictionary[n];
	for (int i = 0; i < n; i++)
	{
		in >> dict[i].character;
		in >> dict[i].code;
	}
	in >> char_nos;
	std::string shell_code="", abundant_code="";
	char filename[] = "c://files//test_unzip.txt"; // 此处写入文件名;
	std::ofstream yout(filename, ios::out);
	step = root;
	
	in.get();
	while (char_nos>0)
	{
		char the_char;
		the_char=in.get();
		
		unsigned char yoyo;
		yoyo = (unsigned char)the_char;
		if (yoyo - 0x80 >= 0)
		{
			yoyo=yoyo - 0x80;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x40 >= 0)
		{
			yoyo = yoyo - 0x40;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x20 >= 0)
		{
			yoyo = yoyo - 0x20;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if ((step->right_son) != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x10 >= 0)
		{
			yoyo = yoyo - 0x10;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x8 >= 0)
		{
			yoyo = yoyo - 0x8;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x4 >= 0)
		{
			yoyo = yoyo - 0x4;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x2 >= 0)
		{
			yoyo = yoyo - 0x2;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		if (yoyo - 0x1 >= 0)
		{
			yoyo = yoyo - 0x1;
			if (step->left_son != NULL)
				step=step->left_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->left_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		else
		{
			if (step->right_son != NULL)
				step=step->right_son;
			else
			{
				yout << step->data;
				step = root;
				step = step->right_son;
				char_nos = char_nos - 1;
				if (char_nos == 0)
					break;
			}
		}
		the_char = in.peek();
		if (the_char == EOF)
			in.setstate(in.goodbit);
		
	}
}