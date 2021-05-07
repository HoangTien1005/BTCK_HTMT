#include "function.h"


string read_excessK(string str, int N, int K)
{
	string tempstr = to_string(baseToDec(str, 16));
	tempstr = decToBase(tempstr, 2, N * 8);
	if (tempstr[0] != '1')
	{
		return to_string(baseToDec(tempstr, 16));
	}
	else
	{
		string substr = tempstr.substr(1);
		int tempint;
		tempint = baseToDec(substr, 2);
		tempint -= K;
		return to_string(tempint);
	}
}

string read_twosComplement(string str, int N)
{
	string tempstr;
	tempstr = to_string(baseToDec(str, 16));
	tempstr = decToBase(tempstr, 2, N * 8);
	if (tempstr[0] != '1')
	{
		return to_string(baseToDec(tempstr, 2));
	}
	else
	{
		string substr = tempstr.substr(1);
		for (int i = substr.length() - 1; i >= 0; i--)
		{
			if (substr[i] == '0')
				substr[i] = '1';
			else
			{
				substr[i] = '0';
				break;
			}
		}
		for (int i = 0; i < substr.length(); i++)
		{
			if (substr[i] == '0')
				substr[i] = '1';
			else
				substr[i] = '0';
		}
		int tempint = baseToDec(substr, 2);
		tempint *= -1;
		return to_string(tempint);

	}
}

string read_precision()
{
	return string();
}

string read_string(string str, bool isUTF16)
{
	if (!isUTF16)
	{
		string temp;
		for (int i = 0; i < str.length(); i = i + 2)
		{
			string temp2;
			temp2 += str[i];
			temp2 += str[i + 1];
			int temp3 = baseToDec(temp2, 16);
			temp += char(temp3);

		}
		return temp;
	}
	else
	{
		string temp;
		for (int i = 0; i < str.length(); i = i + 4)
		{
			string temp2;
			for (int j = i; j < i + 4; j++)
			{
				temp2 += str[j];
			}
			cout << temp2 << endl;
			int temp3 = baseToDec(temp2, 16);
			temp += char(temp3);

		}
		return temp;
	}
}

string read_numberFromFile(string path, int offset, int bytes, bool isLE)
{
	string res;

	char* temp;
	ifstream inFile;
	inFile.open(path, ios::binary);								// mở file

	if (invalidOffset(path, offset, bytes * 2)) return "";		// nếu offset và số byte đọc ko hợp lệ, trả về rỗng

	inFile.seekg(offset);							// nhảy tới vị trí offset

	temp = new char[bytes * 2];
	inFile.read(temp, bytes * 2);						        // đọc vào biến tạm temp

	inFile.close();												// đóng file

	res = temp;
	res.resize(bytes * 2);

	if (isLE) reverse(res.begin(), res.end());					// nếu LE thì đảo chuỗi

	return res;
}

string read_stringFromFile(string path, int offset, int length, bool isLE, bool isUTF16)
{

	int bytes;												// số byte sẽ được đọc 
	if (isUTF16) bytes = length * 2;						// 1 ký tự = 2 byte (UTF16)
	else bytes = length;									// 1 ký tự = 1 byte (ASCII)
	string res;
	char* temp;
	ifstream inFile;

	inFile.open(path, ios::binary);							// mở file

	if (invalidOffset(path, offset, bytes * 2)) return "";	// nếu offset và số byte đọc ko hợp lệ, trả về rỗng

	inFile.seekg(offset, inFile.beg);						// nhảy tới vị trí offset

	temp = new char[bytes * 2];
	inFile.read(temp, bytes * 2);							// đọc vào biến tạm temp

	inFile.close();											// đóng file

	res = temp;
	res.resize(bytes * 2);

	if (isUTF16 && isLE)										// nếu là UTF16 và lưu ở dạng LE
	{
		for (int i = 0; i < res.length() - 3; i += 4)
		{
			swap(res[i], res[i + 2]);
			swap(res[i + 1], res[i + 3]);
		}
	}
	return res;
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
			//case 1: res = read_excessK();
			//	break;
			//case 2: res = read_twosComplement();
			//	break;
			//case 3:  res = read_precision();
			//	break;
			//case 4:  res = read_string();
			//	break;
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
	return choice == 1 ? true : false;
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
	bool ret = false;
	fstream file;
	file.open(path, ios::binary | ios::in);
	file.seekg(0, file.end);
	if (offset + size > file.tellg()) ret = true;
	file.seekg(0);
	file.close();
	return ret;
}

bool excessKcheck(string str, int N, int K)
{
	int tempint = stoi(str);
	if (tempint >= 0)
		return Ncheck(str, N);
	else if (tempint + K < 0)
		return false;
	else
	{
		return Ncheck(to_string(tempint + K), N);
	}
}

bool twosCompcheck(string str, int N)
{
	int tempint = stoi(str);
	return Ncheck(to_string(abs(tempint)), N);
}

bool Ncheck(string str, int N)
{
	int tempint = stoi(str);
	long long tempint2 = 0;
	for (int i = 0; i < N * 8 - 1; i++)
	{
		tempint2 += pow(2, i);
	}
	if (tempint2 >= tempint)
		return true;
	else
		return false;
}

string write_excessK(string str, int N, int K)
{
	if (str[0] != '-')
	{
		return decToBase(str, 16, N * 2);
	}
	else
	{
		string tempstr;
		int tempint = stoi(str);
		tempint += K;
		tempstr = decToBase(to_string(tempint), 16, N * 2);
		tempstr[0] = 1;
		return tempstr;

	}
}

string write_twosComplement(string str, int N)
{
	if (str[0] != '-')
	{
		return decToBase(str, 16, N * 2);
	}
	else
	{
		string tempstr = decToBase(str, 2, N * 8);
		for (int i = 0; i < tempstr.length(); i++)
		{
			if (tempstr[i] == '0')
			{
				tempstr[i] = '1';
			}
			else
				tempstr[i] = '0';
		}
		for (int i = tempstr.length() - 1; i > 0; i--)
		{
			if (tempstr[i] == '1')
				tempstr[i] = '0';
			else
			{
				tempstr[i] = '1';
				break;
			}
			tempstr[0] = 1;
		}
		return decToBase(to_string(baseToDec(tempstr, 2)), 16, N * 2);

	}
}

string write_precision()
{
	return string();
}

string write_string(string str, bool isUTF16)
{
	if (!isUTF16)
	{
		string temp;
		for (int i = 0; i < str.length(); i++)
		{
			temp += decToBase(to_string(int(str[i])), 16, 2);
		}
		return temp;
	}
	else
	{
		string temp;
		for (int i = 0; i < str.length(); i++)
		{
			temp += decToBase(to_string(int(str[i])), 16, 4);
		}
		return temp;
	}
}

void write_numberToFile(string path, string number, bool isLE)
{
	string res = number;
	if (isLE) reverse(res.begin(), res.end());			// nếu là LE thì đảo chuỗi
	const char* temp = res.c_str();

	fstream outFile;
	outFile.open(path, ios::binary | ios::out | ios::app);
	outFile.write(temp, res.length());
	outFile.close();
}

void write_stringToFile(string path, string str, bool isLE, bool isUTF16)
{
	string res = str;
	if (isUTF16 && isLE)								// nếu là UTF16 và lưu dạng LE
	{
		for (int i = 0; i < res.length() - 3; i += 4)
		{
			swap(res[i], res[i + 2]);
			swap(res[i + 1], res[i + 3]);
		}
	}
	const char* temp = res.c_str();

	fstream outFile;
	outFile.open(path, ios::binary | ios::out | ios::app);
	outFile.write(temp, res.length());
	outFile.close();
}



string decToBase(string s, int base, int N)
{
	int k = atof(s.c_str());
	string res = "";
	if (k < 0) k = -1 * k;
	while (k != 0)
	{
		res = getChar(k % base) + res;
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

void swap(char& a, char& b)
{
	char temp = a;
	a = b;
	b = temp;
}
