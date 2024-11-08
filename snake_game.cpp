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


