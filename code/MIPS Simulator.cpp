/*Only supports Add, Sub, Lw, Sw, Beq and J for now.*/
#include<iostream>
#include<string>
#include<string.h>
#include"Assemble.h"
#include"Unassemble.h"
#include"CPU.h"

using namespace std;

int main()
{
	string operation;
	CPU cpu;
	Assemble assemble;
	Unassemble unassemble;

	cout << "+-------------+-------------------------------+" << endl;
	cout << "|  operation  |           function            |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      R      |        check registers        |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      D      |      check memory (data)      |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      U      |   check memory (instruction)  |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      A      |       insert instruction      |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      T      |         run by step           |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      C      |           assemble            |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      I      |         un-assemble           |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "|      Q      |            quit               |" << endl;
	cout << "+-------------+-------------------------------+" << endl;
	cout << "Please input the command." << endl;
	cin >> operation;

	while (1)
	{
		if (operation == "R")
		{
			cpu.checkRegister();
			cout << endl;
		}
		else if (operation == "D")
		{
			cpu.checkMemoryData();
			cout << endl;
		}
		else if (operation == "U")
		{
			cpu.checkMemoryInst();
			cout << endl;
		}
		else if (operation == "A")
		{
			cpu.insertInst();
			cout << endl;
		}
		else if (operation == "T")
		{
			cpu.execute();
			cout << endl;
		}
		else if (operation == "C")
		{
			long result;
			int op;
			cout << "1. add" << endl;
			cout << "2. sub" << endl;
			cout << "3. lw" << endl;
			cout << "4. sw" << endl;
			cout << "5. beq" << endl;
			cout << "6. j" << endl;
			cin >> op;
			cout << "Input the instruction." << endl;
			if (op == 1)
			{
				result = assemble.add();
			}
			else if (op == 2)
			{
				result = assemble.sub();
			}
			else if (op == 3)
			{
				result = assemble.lw();
			}
			else if (op == 4)
			{
				result = assemble.sw();
			}
			else if (op == 5)
			{
				result = assemble.beq();
			}
			else if (op == 6)
			{
				result = assemble.j();
			}
			else
			{
				cout << "Invalid input!" << endl;
				continue;
			}
			cout << "The machine code is: ";
			printf("0X%08X\n", result);
			cout << endl;
		}
		else if (operation == "I")
		{
			int code;
			char* result = new char[100];
			//char* tmp = result;
			int op;
			cout << "1. add" << endl;
			cout << "2. sub" << endl;
			cout << "3. lw" << endl;
			cout << "4. sw" << endl;
			cout << "5. beq" << endl;
			cout << "6. j" << endl;
			cin >> op;
			cout << "Input the machine code." << endl;
			scanf("%X", &code);
			cout << "The instruction is: ";
			if (op == 1)
			{
				result = unassemble.add(code);
				cout << result << endl;
			}
			else if (op == 2)
			{
				result = unassemble.sub(code);
				cout << result << endl;
			}
			else if (op == 3)
			{
				result = unassemble.lw(code);
				cout << result << endl;
			}
			else if (op == 4)
			{
				result = unassemble.sw(code);
				cout << result << endl;
			}
			else if (op == 5)
			{
				result = unassemble.beq(code);
				cout << result << endl;
			}
			else if (op == 6)
			{
				result = unassemble.j(code);
				cout << result << endl;
			}
			else
				cout << "Invalid input!" << endl;
			cout << endl;
			//delete[] tmp;
		}
		else if (operation == "Q")
		{
			break;
		}
		else
		{
			cout << "Invalid input!" << endl;
		}

		cout << "Please input the command." << endl;
		cin >> operation;
	}
}