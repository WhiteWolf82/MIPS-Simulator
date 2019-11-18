#include"Unassemble.h"

char* Unassemble::add(int code)
{
	result[0] = '\0';
	rs = (code >> 21) & 31;
	rt = (code >> 16) & 31;
	rd = (code >> 11) & 31;
	strcat(result, "add    ");
	strcat(result, reg[rd]);
	strcat(result, ", ");
	strcat(result, reg[rs]);
	strcat(result, ", ");
	strcat(result, reg[rt]);
	return result;
}

char* Unassemble::sub(int code)
{
	result[0] = '\0';
	rs = (code >> 21) & 31;
	rt = (code >> 16) & 31;
	rd = (code >> 11) & 31;
	strcat(result, "sub    ");
	strcat(result, reg[rd]);
	strcat(result, ", ");
	strcat(result, reg[rs]);
	strcat(result, ", ");
	strcat(result, reg[rt]);
	return result;
}

char* Unassemble::lw(int code)
{
	char* buffer = new char[100];
	result[0] = '\0';
	rs = (code >> 21) & 31;
	rt = (code >> 16) & 31;
	im = (short)(code & 0xFFFF);
	itoa(im, buffer, 10);
	strcat(result, "lw    ");
	strcat(result, reg[rt]);
	strcat(result, ", ");
	strcat(result, buffer);
	strcat(result, "(");
	strcat(result, reg[rs]);
	strcat(result, ")");
	delete[] buffer;
	return result;
}

char* Unassemble::sw(int code)
{
	char* buffer = new char[100];
	result[0] = '\0';
	rs = (code >> 21) & 31;
	rt = (code >> 16) & 31;
	im = (short)(code & 0xFFFF);
	itoa(im, buffer, 10);
	strcat(result, "sw    ");
	strcat(result, reg[rt]);
	strcat(result, ", ");
	strcat(result, buffer);
	strcat(result, "(");
	strcat(result, reg[rs]);
	strcat(result, ")");
	delete[] buffer;
	return result;
}

char* Unassemble::beq(int code)
{
	char* buffer = new char[100];
	result[0] = '\0';
	rs = (code >> 21) & 31;
	rt = (code >> 16) & 31;
	im = (short)(code & 0xFFFF);
	itoa(im, buffer, 10);
	strcat(result, "beq    ");
	strcat(result, reg[rt]);
	strcat(result, ", ");
	strcat(result, reg[rs]);
	strcat(result, ", ");
	strcat(result, buffer);
	delete[] buffer;
	return result;
}

char* Unassemble::j(int code)
{
	char* buffer = new char[100];
	result[0] = '\0';
	tar = (short)(code & 0x3FFFFFF);
	itoa(tar, buffer, 10);
	strcat(result, "j    ");
	strcat(result, buffer);
	delete[] buffer;
	return result;
}