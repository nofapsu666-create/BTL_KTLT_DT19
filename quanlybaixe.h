/* =========================================================
 * Ten File : quanlybaixe.h
 * Mo ta    : File header dinh nghia cau truc du lieu va thu vien.
 * ========================================================= */
#ifndef QUANLYBAIXE_H
#define QUANLYBAIXE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Kich thuoc bai do
#define MAX_HANG_OTO 2
#define MAX_COT_OTO 5
#define MAX_HANG_XEMAY 3
#define MAX_COT_XEMAY 10

// Cau truc TheXe
typedef struct {
    int trangThai; // 0: Trong, 1: Co xe
    char bienSo[20];
    int loaiXe;    // 1: Xe may, 2: O to
    time_t thoiGianVao;
} TheXe;

// --- NGUYEN MAU HAM ) ---

// File main.c
void GhiLichSu(char* bienSo, int loaiXe, time_t vao, time_t ra, double tien);

// File hienthi.c
void InSoDo(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]);
void InThongKe(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]);
void FormatThoiGian(time_t t, char* buffer);

// File xuly.c
void XeVao(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY], int loaiXe, char* bienSo);
void XeRa(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY], char* bienSo);
double TinhTien(int loaiXe, double soGiay);

#endif
