#include "Assemble.h"

void Assemble::rep(char a[])
{
	char *result = new char[100];
	result = a;
	int i;
	for (i = 0; result[i] != '\0'; i++)
	{
		if (result[i] == ' ' || result[i] == '\t' ||
			result[i] == '(' || result[i] == ')')
		{
			result[i] = ',';
		}
	}
	strcpy(a, result);
}

int Assemble::getRegName(char a[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(a, reg[i]) == 0)
			return i;
	}
	return -1;
}

long Assemble::add()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	i = 0;
	while (i < 3)
	{
		tmp = strtok(NULL, ",");
		if (tmp)
			sector[++i] = tmp;
	}
	if (getRegName(sector[1]) == -1 || getRegName(sector[2]) == -1 || getRegName(sector[3]) == -1)
	{
		cout << "Error!" << endl;
	}
	result = (getRegName(sector[2]) << 21) +
		(getRegName(sector[3]) << 16) +
		(getRegName(sector[1]) << 11) + 32;
	return result;
}

long Assemble::sub()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	i = 0;
	while (i < 3)
	{
		tmp = strtok(NULL, ",");
		if (tmp)
			sector[++i] = tmp;
	}
	if (getRegName(sector[1]) == -1 || getRegName(sector[2]) == -1 || getRegName(sector[3]) == -1)
	{
		cout << "Error!" << endl;
	}
	result = (getRegName(sector[2]) << 21) +
		(getRegName(sector[3]) << 16) +
		(getRegName(sector[1]) << 11) + 34;
	return result;
}

long Assemble::lw()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	i = 0;
	while (i < 3)
	{
		tmp = strtok(NULL, ",");
		if (tmp)
			sector[++i] = tmp;
	}
	if (getRegName(sector[1]) == -1 || getRegName(sector[3]) == -1)
	{
		cout << "Error!" << endl;
	}
	result = (35 << 26) +
		(getRegName(sector[3]) << 21) +
		(getRegName(sector[1]) << 16) +
		(atol(sector[2]) & 0xFFFF);
	return result;
}

long Assemble::sw()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	i = 0;
	while (i < 3)
	{
		tmp = strtok(NULL, ",");
		if (tmp)
			sector[++i] = tmp;
	}
	if (getRegName(sector[1]) == -1 || getRegName(sector[3]) == -1)
	{
		cout << "Error!" << endl;
	}
	result = (43 << 26) +
		(getRegName(sector[3]) << 21) +
		(getRegName(sector[1]) << 16) +
		(atol(sector[2]) & 0xFFFF);
	return result;
}

long Assemble::beq()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	i = 0;
	while (i < 3)
	{
		tmp = strtok(NULL, ",");
		if (tmp)
			sector[++i] = tmp;
	}
	if (getRegName(sector[1]) == -1 || getRegName(sector[2]) == -1)
	{
		cout << "Error!" << endl;
	}
	result = (4 << 26) +
		(getRegName(sector[2]) << 21) +
		(getRegName(sector[1]) << 16) +
		(atol(sector[3]) & 0xFFFF);
	return result;
}

long Assemble::j()
{
	getchar();
	gets_s(inst);
	rep(inst);
	sector[0] = strtok(inst, ",");
	tmp = strtok(NULL, ",");
	if (tmp)
		sector[1] = tmp;
	result = (2 << 26) +
		(atol(sector[1]) & 0x3FFFFFF);
	return result;
}