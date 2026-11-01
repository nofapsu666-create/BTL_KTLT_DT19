/* =========================================================
 * Ten file : quanlybaixe.h
 * Mo ta    : Hang so, kieu du lieu, bien toan cuc (extern)
 *            va nguyen mau ham dung chung cho ca du an.
 * ========================================================= */
#ifndef QUANLYBAIXE_H
#define QUANLYBAIXE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

// Kich thuoc bai do va so luot gui toi da
#define ROW_OTO 4
#define COL_OTO 5
#define ROW_XEMAY 5
#define COL_XEMAY 6
#define MAX_XE 100

typedef enum { XE_MAY = 1, O_TO = 2 } LoaiXe;

// Moi luot gui xe la mot TheXe
typedef struct {
    char maThe[20];
    char bienSo[20];
    LoaiXe loaiXe;
    int rowPos;
    int colPos;
    time_t thoiGianVao;
    time_t thoiGianRa;
    int dangTrongBai;   // 1: dang trong bai, 0: da ra
} TheXe;

// Toa do mot o va hang doi cho thuat toan BFS
typedef struct {
    int r, c;
} Point;

typedef struct {
    Point data[MAX_XE];
    int front;
    int rear;
} Queue;

// Bien toan cuc (dinh nghia trong main.c)
extern int gridOTo[ROW_OTO][COL_OTO];
extern int gridXeMay[ROW_XEMAY][COL_XEMAY];
extern TheXe danhSachThe[MAX_XE];
extern int tongSoXeAcc;
extern long long tongDoanhThu;
extern int tongLuotXeHoanThanh;
extern const int MA_TINH_VALID[];
extern const int SO_LUONG_MA_TINH;

// --- NGUYEN MAU HAM ---

// File main.c: kiem tra bien so
int isKyTuSeriHopLe(char c);
int isMaTinhHopLe(int ma);
int kiemTraBienSoHopLe(const char *bienSo, LoaiXe loai);

// File xuly.c: nghiep vu
void clearInputBuffer();
void initQueue(Queue *q);
int isEmpty(Queue *q);
void pushQueue(Queue *q, Point p);
Point popQueue(Queue *q);
int timViTriTrongGanNhat(LoaiXe loai, int *outR, int *outC);
long long tinhPhi(LoaiXe loai, double soGio);
void ghiLichSuFile(TheXe tx, long long tienPhi);
void docLichSuFile();
void xeVao();
void xeRa();

// File hienthi.c: hien thi
void hienThiSoDo();
void thongKeCaTruc();

#endif
