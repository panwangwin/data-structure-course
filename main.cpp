//
//  main.cpp
//  zip_file
//
//  Created by PAN on 16-5-5.
//  Copyright (c) 2016年 prowind. All rights reserved.
//

#include "zip_function.h"
#include "C:\Users\Administrator\Documents\Visual Studio 2015\Projects\zipfile\zipfile\unzip_function.h"
#include <sstream>

using namespace std;
int main()
{
    zip_file("C://files//aa.txt");
	unzip_file("c://files//test.txt");
	
	return 0;
}