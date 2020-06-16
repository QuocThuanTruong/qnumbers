# QNumbers
Implements QInt and QFloat 128 bits

![Bintray](https://img.shields.io/badge/1-Số%20nguyên%20lớn-blue)

* Thiết kế kiểu dữ liệu QInt có độ lớn 16 byte với các hàm sau:

  ![alt text](https://github.com/QuocThuanTruong/QNumbers/blob/master/Img/qint.png)
  
  - Hàm Nhập: void ScanQInt(QInt &x)
  - Hàm xuất: void PrintQInt( QInt x)
  - Hàm chuyển đổi số QInt thập phân sang nhị phân: bool * DecToBin (QInt x)
  - Hàm chuyển đổi số QInt nhị phân sang thập phân: QInt BinToDec(bool *bit)
  - Hàm chuyển đổi số QInt nhị phân sang thập lục phân: char *BinToHex(bool *bit)
  - Hàm chuyển đổi số QInt thập phân sang thập lục phân: char *DecToHex(QInt x)
  - Các operator toán tử : “+”, “-” , “*”, “/” (tính theo thuật toán trên số nhị phân)
  - Các toán tử so sánh và gán: “<”, “>”, “==”, “<=”, “>=”, “=”
  - Các toán tử: AND “&”, OR “|”, XOR “^”, NOT “~”
  - Các toán tử: dịch trái “<<”, dịch phải “>>”, xoay trái: “rol”, xoay phải: “ror”
  
![Bintray](https://img.shields.io/badge/2-Số%20chấm%20động%20chính%20xác%20cao-blue)

* Thiết kế kiểu dữ liệu biểu diễn số chấm động có độ chính xác Quadruple-precision (độ chính xác
gấp 4 lần) độ lớn 128 bit có cấu trúc biểu diễn như sau:

  ![alt text](https://github.com/QuocThuanTruong/QNumbers/blob/master/Img/qfloat.png)

* Hãy định nghĩa các hàm sau:
  - Hàm Nhập: void ScanQfloat (Qfloat &x)
  - Hàm xuất: void PrintQfloat( Qfloat x)
  - Hàm chuyển đổi số Qfloat nhị phân sang thập phân: Qfloat BinToDec(bool *bit)
  - Hàm chuyển đổi số Qfloat thập phân sang nhị phân bool *DecToBin(Qfloat x)

![Bintray](https://img.shields.io/badge/3-Chương%20trình%20minh%20họa-blue)

* Chương trình thực thi đọc tham số dòng lệnh ở dạng command line: 
<MSSV1_MSSV2_MSSV3_MSSV4_MSSV5.exe> <input.txt> <output.txt> <type>.

![Bintray](https://img.shields.io/badge/4-Quy%20định%20cấu%20trúc%20tập%20tin-blue)

![alt text](https://github.com/QuocThuanTruong/QNumbers/blob/master/Img/file.png)

