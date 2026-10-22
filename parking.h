#ifndef PARKING_H
#define PARKING_H

#include <time.h>

#define MAX_ROWS 5
#define MAX_COLS 5
#define FILE_DATA "lichsu_baixe.txt"

// Biểu phí theo bậc giờ (ĐT19)
#define PHI_XE_MAY_BAC_1 5000   // 2 giờ đầu
#define PHI_XE_MAY_BAC_2 3000   // Từ giờ thứ 3 trở đi
#define PHI_OTO_BAC_1    20000  // 2 giờ đầu
#define PHI_OTO_BAC_2    15000  // Từ giờ thứ 3 trở đi

typedef enum {
    XE_MAY = 1,
    O_TO = 2
} LoaiXe;

// Struct Quản lý Thẻ Xe (YC03)
typedef struct {
    char maThe[20];
    char bienSo[20];
    LoaiXe loaiPhuongTien;
    time_t thoiGianVao;
    int hangDo;
    int cotDo;
    int trangThai; // 0: Trống, 1: Đang trong bãi
} TheXe;

// Hàm khởi tạo và hỗ trợ bộ đệm (YC04)
void khoiTaoBaiXe(int bai[MAX_ROWS][MAX_COLS]);
void xoaBoDem();

// Nghiệp vụ cốt lõi (ĐT19)
void hienThiSoDo(int bai[MAX_ROWS][MAX_COLS]);
void xeVaoBai(int bai[MAX_ROWS][MAX_COLS], TheXe **danhSachThe, int *soLuongThe);
void xeRaBai(int bai[MAX_ROWS][MAX_COLS], TheXe *danhSachThe, int soLuongThe);
long long tinhTienTheoBac(LoaiXe loai, double soGio);

// Thống kê & Quản lý Tệp tin (ĐT19 & YC04)
void luuLichSuRaBai(const char* bienSo, const char* maThe, int loai, double soGio, long long thanhTien);
void thongKeCaTruc();

#endif
