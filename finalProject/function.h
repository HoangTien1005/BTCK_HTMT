#ifndef FUNCTION_H
#define FUNCTION_H

#define PATH "cau01.bin"

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;


// NHÓM HÀM KIỂM TRA INPUT

bool isNumber(string input);							// kiểm tra chuỗi input có phải số không
bool isInteger(string input);						    // kiểm tra chuỗi input có phải số nguyên không
bool invalidOffset(string path, int offset, int size);  // kiểm tra xem offset có hợp lệ để đọc không



// NHÓM HÀM XỬ LÝ GHI (từ input của user chuyển thành hex rồi ghi ra file)
string write_excessK();				
string write_twosComplement();
string write_precision();
string write_string();

// ghi số ra file theo LE hoặc BE
void write_numberToFile(string path, string number, bool isLE = false);	

// ghi chuỗi ra file theo LE hoặc BE, theo ASCII hoặc UTF16
void write_stringToFile(string path, string str, bool isLE = false, bool isUTF16 = false);	



// NHÓM HÀM XỬ LÝ ĐỌC ( đọc theo yêu cầu của user từ file rồi xuất ra màn hình)

string read_excessK();
string read_twosComplement();
string read_precision();
string read_string();

// đọc một số theo LE hoặc BE ( size là số byte )
string read_numberFromFile(string path, int offset, int bytes, bool isLE = false);

// đọc một chuỗi theo LE hoặc BE, theo ASCII hoặc UTF16 ( size là chiều dài chuỗi )
string read_stringFromFile(string path, int offset, int length, bool isLE = false, bool isUTF16 = false);


// NHÓM HÀM MENU

void writeMenu();										// menu để ghi
void readMenu();										// menu để đọc
bool subMenu();											// menu để thoát khỏi chương trình
bool endiannessMenu();									// menu để chọn LE và BE



// NHÓM HÀM XỬ LÝ PHỤ (còn thiếu)

string decToBase(string s, int base, int N);			// chuyển đổi từ thập phân sang base và phải đủ độ dài N
long long int baseToDec(string s, int base);						// trả về giá trị thập phân của một base 
char getChar(int number);
int getNum(char ch);
void swap(char& a, char& b);

string toBin(string x);
float toDec(string X, int base);
#endif