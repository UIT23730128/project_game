#include <iostream>  
#include <conio.h>   
#include <windows.h> 
#include <ctime>     // Thư viện để sử dụng các hàm liên quan đến thời gian

using namespace std;

bool gameOver; // Biến để kiểm tra trạng thái của trò chơi
const int width = 25; // Chiều rộng của màn hình trò chơi
const int height = 25; // Chiều cao của màn hình trò chơi
int x, y, chuotX, chuotY, diemSo; // Tọa độ của con rắn và chuột, và điểm số
int duoiX[100], duoiY[100]; // Mảng để lưu trữ tọa độ của đuôi con rắn
int doDaiDuoi; // Độ dài của đuôi con rắn
int sleepTime = 100; // Thời gian ngủ ban đầu (điều chỉnh tốc độ của trò chơi)
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Hướng di chuyển của con rắn
eDirection huong; // Biến để lưu trữ hướng di chuyển hiện tại của con rắn
const int maxIdleTime = 15; // Thời gian tối đa không ăn chuột (giây)
time_t thoiGianCuoiAnChuot; // Thời gian lần cuối cùng ăn chuột

// Khai báo các hàm
void KhoiTao();
void VeManHinh();
void XuLyDauVao();
void XuLyLogic();
void HienThiMenuChinh();
void XuLyLuaChonMenuChinh();
void HienThiHuongDan();
// Hàm khởi tạo trò chơi
void KhoiTao() {

    gameOver = false; // Trò chơi chưa kết thúc

    huong = STOP; // Con rắn chưa di chuyển

    x = width / 2; // Tọa độ ban đầu của con rắn (giữa màn hình)

    y = height / 2; // Tọa độ ban đầu của con rắn (giữa màn hình)

    chuotX = rand() % width; // Tọa độ ngẫu nhiên của chuột

    chuotY = rand() % height; // Tọa độ ngẫu nhiên của chuột

    diemSo = 0; // Điểm số ban đầu

    thoiGianCuoiAnChuot = time(0); // Khởi tạo thời gian lần cuối cùng ăn chuột

}

