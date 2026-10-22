#ifndef PARKING_H
#define PARKING_H

// Định nghĩa kích thước ma trận bãi đỗ xe
#define HANG 5
#define COT 5
#define SO_THE_MAX 50

// Định nghĩa cấu trúc thẻ xe đơn giản (YC03)
typedef struct {
    char maThe[20];
    char bienSo[20];
    int loaiXe;      // 1: Xe máy, 2: Ô tô
    long thoiGianVao; // Lưu thời gian dạng số nguyên đơn giản
    int hangDo;      // Vị trí hàng trong bãi
    int cotDo;       // Vị trí cột trong bãi
    int trangThai;   // 0: Thẻ đang trống, 1: Thẻ đang giữ xe
} TheXe;

// Khai báo các hàm xử lý
void khoiTaoBaiXe(int bai[HANG][COT], TheXe dsThe[]);
void hienThiSoDo(int bai[HANG][COT]);
void xeVaoBai(int bai[HANG][COT], TheXe dsThe[]);
void xeRaBai(int bai[HANG][COT], TheXe dsThe[]);
void xemLichSuTuFile();

#endif
