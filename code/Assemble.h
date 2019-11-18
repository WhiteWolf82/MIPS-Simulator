#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include<iostream>
#include<string>
#include<string.h>

using namespace std;

class Assemble
{
public:
	void rep(char a[]);
	int getRegName(char a[]);
	long add();
	long sub();
	long lw();
	long sw();
	long beq();
	long j();

private:
	int i;
	long result;
	char* tmp = new char[100];
	char* sector[10];
	char inst[100];
	char reg[40][10] = { "$zero", "$at", "$a0", "$a1", "$a2", "$a3", "$v0", "$v1",
						 "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
						 "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
						 "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra" };
};

#endif