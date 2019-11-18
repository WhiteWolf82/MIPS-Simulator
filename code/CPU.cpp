#include "CPU.h"

CPU::CPU()
{
	PC = 2048 * 4;
	instPos = 2048 * 4;
	for (int i = 0; i < 32; i++)
	{
		if (i >= 8 && i <= 15)
			Register[i] = i;
		else if (i >= 16 && i <= 23)
			Register[i] = i * 4;
		else
			Register[i] = 0;
	}
	for (int i = 0; i < 2048 * 4; i++)
	{
		Memory[i].content = 0;
		Memory[i].status = 0;
	}
	for (int i = 2048 * 4; i < 4096 * 4; i++)
	{
		Memory[i].content = 0;
		Memory[i].status = 0;
	}
}

void CPU::checkRegister()
{
	cout << "+---------+----------------------+" << endl;
	cout << "|register |         data         |" << endl;
	cout << "+---------+----------------------+" << endl;
	cout << "|  " << reg[0] << "  |" << "      ";
	printf("0X%08X", Register[0]);
	cout << "      |" << endl;
	for (int i = 1; i < 32; i++)
	{
		cout << "+---------+----------------------+" << endl;
		cout << "|   " << reg[i] << "   |" << "      ";
		printf("0X%08X", Register[i]);
		cout << "      |" << endl;
	}
	cout << "+---------+----------------------+" << endl;
}

void CPU::checkMemoryData()
{
	int beginAddr, endAddr;
	int result;

	cout << "Choose the range of memory address (multiple of 4 from 0-8192) you want to show." << endl;
	cout << "Begin address: ";
	cin >> beginAddr;
	cout << "End address: ";
	cin >> endAddr;

	while (beginAddr % 4 != 0)
	{
		beginAddr++;
	}
	while (endAddr % 4 != 0)
	{
		endAddr--;
	}

	cout << "+--------------+----------------------+---------------+" << endl;
	cout << "|   address    |       content        |     type      |" << endl;

	for (int i = beginAddr; i < endAddr; i += 4)
	{
		cout << "+--------------+----------------------+---------------+" << endl;
		cout << "|  0X";
		if (i == 0)
			cout << "00000000";
		else
			printf("%08X", i);
		cout << "  ";
		if (i < 2048 * 4)	//data field
		{
			result = (Memory[i].content << 24) + (Memory[i + 1].content << 16) +
				(Memory[i + 2].content << 8) + Memory[i + 3].content;
			if (result == 0)
				cout << "|      0X00000000      |     data      |" << endl;
			else
			{
				cout << "|      0X";
				printf("%08X", result);
				cout << "      |" << "     data      |" << endl;
			}

		}
		else if (i < 4096 * 4)	//instruction field
		{
			result = (Memory[i].content << 24) + (Memory[i + 1].content << 16) +
				(Memory[i + 2].content << 8) + Memory[i + 3].content;
			if (result == 0)
				cout << "|      0X00000000      |  instruction  |" << endl;
			else
			{
				cout << "|      0X";
				printf("%08X", result);
				cout << "      |" << "  instruction  |" << endl;
			}
		}
		else
		{
			cout << "Error! Memory exceed!" << endl;
			return;
		}
	}
	cout << "+--------------+----------------------+---------------+" << endl;
}

void CPU::checkMemoryInst()
{
	long beginAddr, endAddr;
	int code;
	char* inst = new char[100];
	//char* tmp = inst;
	Unassemble unassemble;

	cout << "Choose the range of memory address (multiple of 4 from 8192-16384) you want to show." << endl;
	cout << "Begin address: ";
	cin >> beginAddr;
	cout << "End address: ";
	cin >> endAddr;

	while (beginAddr % 4 != 0)
	{
		beginAddr++;
	}
	while (endAddr % 4 != 0)
	{
		endAddr--;
	}

	cout << "+--------------+------------------------+---------------+" << endl;
	cout << "|   address    |        content         |     type      |" << endl;

	for (int i = beginAddr; i < endAddr; i += 4)
	{
		cout << "+--------------+------------------------+---------------+" << endl;
		cout << "|  0X";
		if (i == 0)
			cout << "00000000";
		else
			printf("%08X", i);
		cout << "  ";
		if (i < 2048 * 4)	//data field
		{
			code = (Memory[i].content << 24) + (Memory[i + 1].content << 16) +
				(Memory[i + 2].content << 8) + Memory[i + 3].content;
			if (code == 0)
				cout << "|       0X00000000       |     data      |" << endl;
			else
			{
				cout << "|      0X";
				printf("%08X", code);
				cout << "      |" << "     data      |" << endl;
			}
		}
		else if (i < 4096 * 4)	//instruction field
		{
			int op, func;
			code = (Memory[i].content << 24) + (Memory[i + 1].content << 16) +
				(Memory[i + 2].content << 8) + Memory[i + 3].content;
			if (code == 0)
				cout << "|          null          |  instruction  |" << endl;
			else
			{
				op = (code >> 26) & 63;
				if (op == 0)	//R type
				{
					func = code & 63;
					if (func == 32)	  //add
					{
						inst = unassemble.add(code);
					}
					else if (func == 34)	//sub
					{
						inst = unassemble.sub(code);
					}
				}
				else if (op == 35)	//lw
				{
					inst = unassemble.lw(code);
				}
				else if (op == 43)	//sw
				{
					inst = unassemble.sw(code);
				}
				else if (op == 4)		//beq
				{
					inst = unassemble.beq(code);
				}
				else if (op == 2)		//j
				{
					inst = unassemble.j(code);
				}
				printf("| %-23s", inst);
				cout << "|  instruction  |" << endl;
			}
		}
		else
		{
			cout << "Error! Memory exceed!" << endl;
			return;
		}
	}
	cout << "+--------------+------------------------+---------------+" << endl;
	//delete[] tmp;
}

void CPU::insertInst()
{
	Assemble assemble;
	int op;
	long result;
	cout << "Choose the type of instruction your want to insert." << endl;
	cout << "1. add" << endl;
	cout << "2. sub" << endl;
	cout << "3. lw" << endl;
	cout << "4. sw" << endl;
	cout << "5. beq" << endl;
	cout << "6. j" << endl;
	cin >> op;
	cout << "Input the instruction." << endl;

	switch (op)
	{
	case 1: result = assemble.add();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	case 2: result = assemble.sub();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	case 3: result = assemble.lw();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	case 4: result = assemble.sw();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	case 5: result = assemble.beq();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	case 6: result = assemble.j();
		for (int i = 0; i < 4; i++)		//Big Endian
		{
			Memory[instPos + i].status = 1;
			Memory[instPos + i].content = (result >> (8 * (3 - i))) & 0XFF;
		}
		instPos += 4;
		break;
	default: cout << "Invalid input!" << endl;
		break;
	}

	cout << "Inserting successful!" << endl;
}

void CPU::execute()
{
	if (Memory[PC].status == 0)
	{
		cout << "There is no instruction at PC = " << PC << "." << endl;
		return;
	}

	cout << "Execute: ";

	code = (Memory[PC].content << 24) + (Memory[PC + 1].content << 16) +
		(Memory[PC + 2].content << 8) + Memory[PC + 3].content;
	op = (code >> 26) & 63;

	if (op == 0)	//R type
	{
		rs = (code >> 21) & 31;
		rt = (code >> 16) & 31;
		rd = (code >> 11) & 31;
		func = code & 63;
		if (func == 32)		//add
		{
			Register[rd] = Register[rs] + Register[rt];
			printf("add\t%s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
		}
		else if (func == 34)	//sub
		{
			Register[rd] = Register[rs] - Register[rt];
			printf("sub\t%s, %s, %s\n", reg[rd], reg[rs], reg[rt]);
		}
		PC += 4;
	}
	else if (op == 35)	//lw
	{
		int result = 0;

		rs = (code >> 21) & 31;
		rt = (code >> 16) & 31;
		im = (short)(code & 0xFFFF);

		for (int i = 0; i < 4; i++)
		{
			result += Memory[Register[rs] + im * 4 + i].content << (8 * (3 - i));
		}

		Register[rt] = result;
		printf("lw\t%s, %d(%s)\n", reg[rt], im, reg[rs]);
		PC += 4;
	}
	else if (op == 43)	//sw
	{
		rs = (code >> 21) & 31;
		rt = (code >> 16) & 31;
		im = (short)(code & 0xFFFF);

		for (int i = 0; i < 4; i++)
		{
			Memory[Register[rs] + im * 4 + i].content = (Register[rt] >> (8 * (3 - i))) & 0XFF;
		}

		printf("sw\t%s, %d(%s)\n", reg[rt], im, reg[rs]);
		PC += 4;
	}
	else if (op == 4)		//beq
	{
		rs = (code >> 21) & 31;
		rt = (code >> 16) & 31;
		im = (short)(code & 0xFFFF);
		printf("beq\t%s, %s, %d\n", reg[rt], reg[rs], im);
		if (Register[rt] == Register[rs])
			PC = PC + 4 + im * 4;
	}
	else if (op == 2)		//j
	{
		tar = (short)(code & 0x3FFFFFF);
		printf("j\t%d\n", tar);
		PC = tar * 4;
	}
}