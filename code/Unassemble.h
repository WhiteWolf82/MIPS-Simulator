#ifndef UNASSEMBLE_H
#define UNASSEMBLE_H

#include<iostream>
using namespace std;

class Unassemble
{
public:
	char* add(int code);
	char* sub(int code);
	char* lw(int code);
	char* sw(int code);
	char* beq(int code);
	char* j(int code);

private:
	char* result = new char;
	int rs, rt, rd;
	int im;
	int tar;
	char reg[40][10] = { "$zero", "$at", "$a0", "$a1", "$a2", "$a3", "$v0", "$v1",
						 "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
						 "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
						 "$t8", "$t9", "$gp", "$sp", "$fp", "$ra" };
};

#endif