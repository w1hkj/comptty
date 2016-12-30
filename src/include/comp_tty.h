//======================================================================
//  comptty; source include
//    Author: Dave Freese, W1HKJ <w1hkj@w1hkj.com>
//
//  based on the program RTTY Compare by
//    Alex Shovkoplyas, VE3NEA ve3nea@dxatlas.com
//  Original written in Pascal and distributed only for Windows OS
//
//  This program is distributed under the GPL license
//======================================================================

#ifndef _COMP_TTY_
#define _COMP_TTY_

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

enum {CER, BER};

void PrepareBaudotTable();
string Encode(string S);

int  Compare(string s1, string s2);
void comp_tty(string ref_file, string comp_file, string &results);

#endif
