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
	int bytes = 8;	
	bool isLE = false;
	bool isSingle = false;						// nếu là single thì 4 byte, double thì 8 byte
	int choice;
	int offset;
	string res = "";
	int exponent;
	string mantisa = "";

	
	do											// nhập single hoặc double
	{
		cout << "1. 4 byte" << endl;
		cout << "2. 8 byte" << endl;
		cin >> choice;
	} while (choice != 1 && choice != 2);

	isLE = endiannessMenu();					// nhập LE hay BE
	if (choice == 1)
	{
		isSingle = true;
		bytes = 4;
	}

	do											// nhập offset
	{
		cout << "offset: ";
		cin >> offset;
	} while (invalidOffset(PATH, offset, bytes * 2));

	
	string hex_number = read_numberFromFile(PATH, offset, bytes, isLE);
	string number = decToBase(to_string(baseToDec(hex_number, 16)), 2, bytes * 8 );
	if (number[0] == '1') res += '-';
	exponent = baseToDec(number.substr(1, 8), 2) - 127;
	mantisa = number.substr(9);
	if (exponent >= 0)
	{
		if (exponent > 32) return "overflow";
		string head = mantisa.substr(0, exponent);
		head += '.';
		string tail = mantisa.substr(exponent);
		mantisa = head + tail;
		mantisa = '1' + mantisa;
	}
	else 
	{
		mantisa = '1' + mantisa;
		for (int i = exponent + 1; i < 0; i++)
		{
			mantisa = '0' + mantisa;
		}
		mantisa = "0." + mantisa;
	}
	float num = toDec(mantisa, 2);
	res += to_string(num);
	return res;
}

string read_string()
{
	return string();
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

	
	if (isLE)												// nếu LE thì đảo chuỗi
	{
		string after = "";
		for (int i = 0; i < res.length() - 1; i+=2)
		{
			
			after = res[i+1] + after;
			after = res[i] + after;
		}
		return after;
	}
	
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
	res.resize(bytes*2);					

	if(isUTF16 && isLE)										// nếu là UTF16 và lưu ở dạng LE
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
	bool ret = false;
	fstream file;
	file.open(path, ios::binary | ios::in);
	file.seekg(0, file.end);
	if (offset + size > file.tellg()) ret = true;
	file.seekg(0);
	file.close();
	return ret;
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
	int numberLength = 16;						// 8 byte sẽ có 16 kí tự hex
	bool isLE = false;
	bool isSingle = false;						// nếu là single thì 4 byte, double thì 8 byte
	int choice;							
	string input;
	do
	{
		cout << "1. 4 byte" << endl;
		cout << "2. 8 byte" << endl;
		cin >> choice;
	} while (choice != 1 && choice != 2);

	if (choice == 1)
	{
		isSingle = true;
		numberLength = 8;
	}

	cout << "nhap chuoi: ";
	cin.ignore();
	getline(cin, input);


	string kq = "";
	int bitCount = 1;
	int start = 0;
	if (input[0] == '-')
	{
		kq = '1' + kq;
		start = 1;
	}
	else kq = '0' + kq;
	

	int dot_pos = start;
	string x_nguyen = "";

	for (dot_pos; dot_pos < input.length(); dot_pos++)
	{
		if (input[dot_pos] == '.') break;
		x_nguyen = x_nguyen + input[dot_pos];
	}


	string x_nguyen_bin = toBin(x_nguyen);
	bitCount += x_nguyen_bin.length();

	float x_abs = toDec(input, 10);
	int bit_rem, exponent;
	if (isSingle)
	{
		bit_rem = 24 - bitCount + 1;
		exponent = 23 - bit_rem + 127;
	}
	else {
		bit_rem = 53 - bitCount + 1;
		exponent = 52 - bit_rem + 1023;
	}
	long long int temp = round(x_abs * pow(2, bit_rem));

	string temp_str_bin = toBin(to_string(temp));

	string e_str_bin = toBin(to_string(exponent));

	kq += e_str_bin;
	temp_str_bin.erase(temp_str_bin.begin());
	kq += temp_str_bin;
	


	isLE = endiannessMenu();
	
	string number = decToBase(to_string(baseToDec(kq, 2)), 16, numberLength);
	write_numberToFile(PATH, number, isLE);

	return kq;
}

string write_string()
{
	return string();
}

void write_numberToFile(string path, string number, bool isLE)
{
	string res = number;
	
	if (isLE)			// nếu là LE thì đảo chuỗi
	{
		string after = "";
		for (int i = 0; i < res.length() - 1; i += 2)
		{
			after = res[i + 1] + after;
			after = res[i] + after;
		}
		res = after;
	}
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
	long long int k = (long long int)(atof(s.c_str()));
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


long long int baseToDec(string s, int base)
{
	int i = 0;
	long long int sum = 0;
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

string toBin(string x)
//input : 1 so nguyen dang string
//output : day bit tuong ung voi x
{
	long long int x_int = 0;
	for (int i = 0; i < x.length(); i++)
	{
		x_int = x_int * 10 + getNum(x[i]);
	}
	string res = "";
	do {
		res = getChar(x_int % 2) + res;
		x_int /= 2;
	} while (x_int != 0);
	return res;
}

float toDec(string X, int base)
{
	int i = 0;
	if (X[0] == '-') i = 1;
	float sum = 0;
	int length = X.length();
	int dotIndex = length;                                  // index của dấu '.'
	for (int j = 0; j < length; j++)
	{
		if (X[j] == '.') dotIndex = j;
	}

	for (i; i < dotIndex; i++) {
		sum += (X[i] - '0') * pow(base, dotIndex - i - 1);      // xử lý trước dấu .
	}
	for (i = dotIndex + 1; i < length; i++)
	{
		sum += (X[i] - '0') * pow(base, dotIndex - i);          // xử lý sau dấu chấm
	}
	return sum;
}
