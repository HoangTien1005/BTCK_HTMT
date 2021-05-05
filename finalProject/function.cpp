#include "function.h"


string read_excessK()
{
	return string();
}

string read_twosComplement()
{
	return string();
}

string read_precision()
{
	return string();
}

string read_string()
{
	return string();
}

string read_numberFromFile(string path, int offset, int size, bool isLE)
{
	return string();
}

string read_stringFromFile(string path, int offset, int size, bool isLE, bool isUTF16)
{
	return string();
}

void writeMenu()
{
	while (1)
	{
		string res;			// chuỗi lưu trữ kết quả cần ghi
		int choice;

		cout << "WRITE MENU ---- Choose your option " << endl;
		cout << "0. readMenu" << endl;
		cout << "1. excess-K" << endl;
		cout << "2. two's complement" << endl;
		cout << "3. single/double precision" << endl;
		cout << "4. ASCII/UTF16 string" << endl;
		
		cin >> choice;
		switch (choice)
		{
		case 0: readMenu();
			break;
		case 1: // res = write_excess-K function
			break;
		case 2: // res = write_two's-complement function
			break;
		case 3: // res = write_precision function
			break;
		case 4: // res = write_string function
			break;
		default: writeMenu();
		}

		choice = subMenu();						// choice = true if user want to exit
		if (choice) break;						
	}

}

void readMenu()
{
	while (1)
	{
		string res;			// chuỗi lưu trữ kết quả cần xuất ra màn hình
		int choice;

		cout << "READ MENU ---- Choose your option " << endl;
		cout << "0. writeMenu" << endl;
		cout << "1. excess-K" << endl;
		cout << "2. two's complement" << endl;
		cout << "3. single/double precision" << endl;
		cout << "4. ASCII/UTF16 string" << endl;

		cin >> choice;
		switch (choice)
		{	
		case 0: writeMenu();
			break;
		case 1: res = read_excessK();
			break;
		case 2: res = read_twosComplement();
			break;
		case 3:  res = read_precision();
			break;
		case 4:  res = read_string();
			break;
		default: readMenu();
		}

		cout << res << endl;					// xuất kết quả ra màn hình

		choice = subMenu();						// choice = true if user want to exit
		if (choice) break;
	}
}

bool subMenu()
{
	int choice;
	cout << "continue?" << endl;
	cout << "0. yes" << endl;
	cout << "1. no" << endl;
	cin >> choice;
	return choice == 1? true : false;
}

bool endiannessMenu()
{
	int choice;
	cout << "0. big endian" << endl;
	cout << "1. little endian" << endl;
	cin >> choice;
	return choice == 1 ? true : false;
}

bool isNumber(string input)
{
	if (input == "") return false;
	int i = 0;
	if (input[0] == '-') i = 1;
	int dotCount = 0;
	int numberCount = 0;
	int length = input.length();
	if (input[i] == '.' || input[length - 1] == '.') return false;
	for (i; i < length; i++)
	{
		if (input[i] < '0' || input[i] > '9')
		{
			if (input[i] == '.' && dotCount < 1)
			{
				dotCount++;
				continue;
			}
			else return false;
		}
		else
		{
			if (numberCount < 18)
			{
				numberCount++;
				continue;
			}
			else return false;
		}
	}
	return true;
}

bool isInteger(string input)
{
	int i = 0;
	if (input[0] == '-') i = 1;
	int length = input.length();
	bool isInteger = true;
	for (i; i < length; i++)
	{
		if (input[i] == '.') break;
	}
	for (i = i + 1; i < length; i++)
	{
		if (input[i] != '0') isInteger = false;
	}
	return isInteger;
}

bool invalidOffset(string path, int offset, int size)
{
	return false;
}

string write_excessK()
{
	return string();
}

string write_twosComplement()
{
	return string();
}

string write_precision()
{
	return string();
}

string write_string()
{
	return string();
}

void write_numberToFile(string path, string res, bool isLE)
{
}

void write_stringToFile(string path, string res, bool isLE, bool isUTF16)
{
}



string decToBase(string s, int base, int N)
{
	int k = atof(s.c_str());
	string res = "";
	if (k < 0) k = -1 * k;
	while (k != 0)
	{
		res =getChar(k % base) + res;
		k /= base;
	}
	while (res.length() < N)
	{
		res = '0' + res;
	}
	return res;
}


int baseToDec(string s, int base)
{
	int i = 0;
	int sum = 0;
	int length = s.length();                                  // index của dấu '.'
	for (i; i < length; i++)
	{
		sum += getNum(s[i]) * pow(base, length - i - 1);
	}
	return sum;
}

char getChar(int number)
{
	if (number >= 10) return (char)(number + 55);
	else return (char)(number + '0');
}

int getNum(char ch)
{
	if (ch >= 'A') return (int)ch - 55;
	else return (int)ch - '0';
}