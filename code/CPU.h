#ifndef CPU_H
#define CPU_H

#include<iostream>
#include<string>
#include<string.h>
#include"Assemble.h"
#include"Unassemble.h"

using namespace std;

class CPU
{
public:
	CPU();
	void checkRegister();
	void checkMemoryData();
	void checkMemoryInst();
	void insertInst();
	void execute();

private:
	int PC;
	int instPos;
	int op;
	int func;
	int rs, rt, rd;
	int im;
	int tar;
	long code;
	char inst[100];
	const char* reg[40] = { "$zero", "$at", "$a0", "$a1", "$a2", "$a3", "$v0", "$v1",
						 "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
						 "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
						 "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };
	long Register[32];
	struct
	{
		long content;
		int status;
	}Memory[4096 * 4];
};

#endif