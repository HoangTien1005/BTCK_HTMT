# BTCK_HTMT

* Một vài lưu ý:

1. Cách chương trình chạy:
- Đầu tiên writeMenu sẽ xuất hiện => cho phép người dùng chọn 1 trong 5 chức năng => người dùng nhập số thập phân => mình sẽ tính toán ra một chuỗi hex,
sau đó cho người dùng chọn kiểu lưu trữ LE hoặc BE => ghi ra file

- Tương tự với readMenu, cho phép người dùng chọn 1 trong 5 chức năng => nhập offset (nhập thêm độ dài chuỗi nếu là đọc chuỗi) => đọc từ file để trả về một 
chuỗi => lấy chuỗi vừa đọc để tính toán ra giá trị thập phân => xuất ra màn hình chuỗi hex của giá trị vừa tìm được

2. Cách sử dụng hàm decToBase(string s, int base, int N): giả sử cần biểu diễn số nguyên dưới dạng 5 BYTE
 decToBase("15", 16, 8) => 000000000F (do biểu diễn số nguyên 5 BYTE dưới dạng THẬP LỤC PHÂN nên cần cho N = 10)
 decToBase("13", 2, 40) => 0000000000000000000000000000000000001101 (do biểu diễn số nguyên 5 BYTE dưới dạng NHỊ PHÂN nên cần cho N = 40)

3. Sử dụng hàm baseToDec(string s, int base) kết hợp với hàm decToBase:
giả sử đọc được chuỗi "1111" trong file, sau đó cần xuất ra màn hình dưới dạng số nguyên 7 BYTE
int dec = baseToDec("1111", 2);
string res = decToBase(to_string(dec), 16, 14) => 0000000000000F
