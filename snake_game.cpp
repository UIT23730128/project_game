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

// Hàm vẽ màn hình trò chơi

void VeManHinh() {

    system("cls"); // Xóa màn hình

    for (int i = 0; i < width + 2; i++)

        cout << "#"; // Vẽ biên trên của màn hình

    cout << endl;



    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (j == 0)

                cout << "#"; // Vẽ biên trái của màn hình

            if (i == y && j == x)

                cout << "O"; // Vẽ đầu con rắn

            else if (i == chuotY && j == chuotX)

                cout << "C"; // Vẽ chuột

            else {

                bool print = false;

                for (int k = 0; k < doDaiDuoi; k++) {

                    if (duoiX[k] == j && duoiY[k] == i) {

                        cout << "o"; // Vẽ đuôi con rắn

                        print = true;

                    }

                }

                if (!print)

                    cout << " "; // Vẽ khoảng trống

            }



            if (j == width - 1)

                cout << "#"; // Vẽ biên phải của màn hình

        }

        cout << endl;

    }



    for (int i = 0; i < width + 2; i++)

        cout << "#"; // Vẽ biên dưới của màn hình

    cout << endl;

    cout << "Điểm số: " << diemSo << endl; // In điểm số hiện tại



    // Tính toán thời gian còn lại trước khi trò chơi kết thúc nếu không ăn được chuột

    int thoiGianConLai = maxIdleTime - difftime(time(0), thoiGianCuoiAnChuot);

    cout << "Thời gian còn lại để ăn chuột: " << thoiGianConLai << " giây" << endl; // In thời gian còn lại

}
// Hàm xử lý đầu vào từ bàn phím

void XuLyDauVao() {

    if (_kbhit()) { // Kiểm tra xem có phím nào được nhấn không

        switch (_getch()) {

        case 75: // Mũi tên trái

            huong = LEFT;

            break;

        case 77: // Mũi tên phải

            huong = RIGHT;

            break;

        case 72: // Mũi tên lên

            huong = UP;

            break;

        case 80: // Mũi tên xuống

            huong = DOWN;

            break;

        case 'x': // Phím 'x' để thoát trò chơi

            gameOver = true;

            break;

        }

    }

}
// Hàm xử lý logic của trò chơi

void XuLyLogic() {

    int prevX = duoiX[0]; // Lưu tọa độ trước đó của đầu con rắn

    int prevY = duoiY[0]; // Lưu tọa độ trước đó của đầu con rắn

    int prev2X, prev2Y;

    duoiX[0] = x; // Cập nhật tọa độ mới của đầu con rắn

    duoiY[0] = y; // Cập nhật tọa độ mới của đầu con rắn

    for (int i = 1; i < doDaiDuoi; i++) {

        prev2X = duoiX[i];

        prev2Y = duoiY[i];

        duoiX[i] = prevX;

        duoiY[i] = prevY;

        prevX = prev2X;

        prevY = prev2Y;

    }

    switch (huong) {

    case LEFT:

        x--; // Di chuyển sang trái

        break;

    case RIGHT:

        x++; // Di chuyển sang phải

        break;

    case UP:

        y--; // Di chuyển lên trên

        break;

    case DOWN:

        y++; // Di chuyển xuống dưới

        break;

    default:

        break;

    }

// Xử lý khi con rắn đi qua biên của màn hình

    if (x >= width) x = 0; else if (x < 0) x = width - 1;

    if (y >= height) y = 0; else if (y < 0) y = height - 1;



    // Kiểm tra va chạm với đuôi

    for (int i = 0; i < doDaiDuoi; i++)

        if (duoiX[i] == x && duoiY[i] == y)

            gameOver = true;
// Kiểm tra va chạm với chuột

    if (x == chuotX && y == chuotY) {

        diemSo += 1; // Tăng điểm lên 1

        chuotX = rand() % width; // Tạo chuột mới ở vị trí ngẫu nhiên

        chuotY = rand() % height; // Tạo chuột mới ở vị trí ngẫu nhiên

        doDaiDuoi++; // Tăng độ dài đuôi con rắn

        thoiGianCuoiAnChuot = time(0); // Cập nhật thời gian lần cuối cùng ăn chuột

        if (sleepTime > 20) { // Giảm thời gian ngủ nhưng không nhỏ hơn 10ms

            sleepTime -= 40;

        }

    }

}
void HienThiMenuChinh() {

    system("cls");

    cout << "==============================" << endl;

    cout << "       TRÒ CHƠI RẮN SĂN MỒI       " << endl;

    cout << "==============================" << endl;

    cout << "1. Bắt đầu chơi" << endl;

    cout << "2. Hướng dẫn" << endl;

    cout << "3. Thoát" << endl;

    cout << "==============================" << endl;

    cout << "Chọn lựa chọn của bạn: ";

}



void XuLyLuaChonMenuChinh() {

    int luaChon;

    cin >> luaChon;



    switch (luaChon) {

    case 1:

        KhoiTao(); // Khởi tạo trò chơi

        break;

    case 2:

        HienThiHuongDan(); // Hiển thị hướng dẫn

        break;

    case 3:

        gameOver = true; // Thoát trò chơi

        break;

    default:

        cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;

        _getch(); // Đợi người chơi nhấn phím bất kỳ để tiếp tục

        HienThiMenuChinh(); // Hiển thị lại menu chính

        XuLyLuaChonMenuChinh(); // Xử lý lựa chọn từ menu chính

        break;

    }

}



void HienThiHuongDan() {

    system("cls");

    cout << "Chào mừng bạn đến với trò chơi Rắn Săn Mồi!" << endl;

    cout << "Hướng dẫn chơi:" << endl;

    cout << "Sử dụng các phím mũi tên để điều khiển con rắn:" << endl;

    cout << "  - Mũi tên lên: Di chuyển lên trên" << endl;

    cout << "  - Mũi tên xuống: Di chuyển xuống dưới" << endl;

    cout << "  - Mũi tên trái: Di chuyển sang trái" << endl;

    cout << "  - Mũi tên phải: Di chuyển sang phải" << endl;

    cout << "Nhấn phím 'x' để thoát trò chơi." << endl;

    cout << "Nhấn phím bất kỳ để bắt đầu chơi!" << endl;

    _getch(); // Đợi người chơi nhấn phím bất kỳ để bắt đầu

}



int main() {

    // Thiết lập mã hóa ký tự của console sang UTF-8

    SetConsoleOutputCP(CP_UTF8);



    while (!gameOver) {

        HienThiMenuChinh(); // Hiển thị menu chính

        XuLyLuaChonMenuChinh(); // Xử lý lựa chọn từ menu chính



        if (!gameOver) {

            while (!gameOver) { // Vòng lặp chính của trò chơi

                VeManHinh(); // Vẽ màn hình trò chơi

                XuLyDauVao(); // Xử lý đầu vào từ bàn phím

                XuLyLogic(); // Xử lý logic của trò chơi

                Sleep(sleepTime); // Tạm dừng chương trình trong khoảng thời gian sleepTime



                // Kiểm tra thời gian kể từ lần cuối cùng ăn chuột

                if (difftime(time(0), thoiGianCuoiAnChuot) >= maxIdleTime) {

                    gameOver = true;

                }

            }

            cout << "Game Over! Điểm số của bạn là: " << diemSo << endl; // In điểm số khi trò chơi kết thúc

            _getch(); // Đợi người chơi nhấn phím bất kỳ để tiếp tục

            gameOver = false; // Đặt lại trạng thái trò chơi để quay lại menu chính

        }

    }



    return 0;

}



