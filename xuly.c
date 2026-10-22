/* =========================================================
 * Ten File : xuly.c
 * Mo ta    : Check-in, check-out, tim vi tri trong, tinh tien.
 * ========================================================= */
#include "quanlybaixe.h"

/*
 * Ten ham: TinhTien
 * Muc dich: Tinh phi bac thang. Xe may: 5k/4h dau, them 1k/h. O to: 20k/2h dau, them 5k/h.
 * Luu y test: Do chay thuc te, difftime() tra ve giay. 
 * Trong code nay dang tinh gia lap: Cu 1 giay chay thuc = 1 gio de de test nghiem thu.
 */
double TinhTien(int loaiXe, double soGio) {
    double tien = 0;
    int gioLamTron = ceil(soGio); 
    if(gioLamTron == 0) gioLamTron = 1; // Gui chua toi 1h (1s) tinh lam 1h

    if(loaiXe == 1) { // Xe may
        if(gioLamTron <= 4) tien = 5000;
        else tien = 5000 + (gioLamTron - 4) * 1000;
    } else { // O to
        if(gioLamTron <= 2) tien = 20000;
        else tien = 20000 + (gioLamTron - 2) * 5000;
    }
    return tien;
}

/*
 * Ten ham: XeVao
 * Muc dich: Duyet mang 2 chieu theo hang truoc cot sau de tim vi tri trong gan nhat.
 */
void XeVao(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY], int loaiXe, char* bienSo) {
    if(loaiXe == 2) { // Xu ly O to
        for(int i = 0; i < MAX_HANG_OTO; i++) {
            for(int j = 0; j < MAX_COT_OTO; j++) {
                if(baiOto[i][j].trangThai == 0) { // Gap o trong dau tien
                    baiOto[i][j].trangThai = 1;
                    strcpy(baiOto[i][j].bienSo, bienSo);
                    baiOto[i][j].loaiXe = loaiXe;
                    baiOto[i][j].thoiGianVao = time(NULL);
                    
                    char buf[30];
                    FormatThoiGian(baiOto[i][j].thoiGianVao, buf);
                    printf(">> Da dieu huong O TO [%s] vao vi tri [%d][%d] luc %s\n", bienSo, i, j, buf);
                    return;
                }
            }
        }
        printf(">> Bai O TO da day!\n");
    } 
    else if (loaiXe == 1) { // Xu ly Xe may
        for(int i = 0; i < MAX_HANG_XEMAY; i++) {
            for(int j = 0; j < MAX_COT_XEMAY; j++) {
                if(baiXeMay[i][j].trangThai == 0) {
                    baiXeMay[i][j].trangThai = 1;
                    strcpy(baiXeMay[i][j].bienSo, bienSo);
                    baiXeMay[i][j].loaiXe = loaiXe;
                    baiXeMay[i][j].thoiGianVao = time(NULL);
                    
                    char buf[30];
                    FormatThoiGian(baiXeMay[i][j].thoiGianVao, buf);
                    printf(">> Da dieu huong XE MAY [%s] vao vi tri [%d][%d] luc %s\n", bienSo, i, j, buf);
                    return;
                }
            }
        }
        printf(">> Bai XE MAY da day!\n");
    }
}

/*
 * Ten ham: XeRa
 * Muc dich: Tim kiem xe, dung difftime tinh thoi gian do, thanh toan va giai phong bo nho.
 */
void XeRa(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY], char* bienSo) {
    time_t timeRa = time(NULL);
    
    // Tim trong bai O to
    for(int i = 0; i < MAX_HANG_OTO; i++) {
        for(int j = 0; j < MAX_COT_OTO; j++) {
            if(baiOto[i][j].trangThai == 1 && strcmp(baiOto[i][j].bienSo, bienSo) == 0) {
                double soGiay = difftime(timeRa, baiOto[i][j].thoiGianVao);
                double tien = TinhTien(2, soGiay); 
                
                printf("\n--- HOA DON THANH TOAN ---\n");
                printf("Bien so: %s (O to)\n", bienSo);
                printf("Thoi gian gui: %.0f gio (demo so giay)\n", soGiay);
                printf("Tong tien: %.0f VND\n", tien);
                
                GhiLichSu(bienSo, 2, baiOto[i][j].thoiGianVao, timeRa, tien);
                
                // Giai phong o do
                baiOto[i][j].trangThai = 0; 
                return;
            }
        }
    }
    
    // Tim trong bai Xe may
    for(int i = 0; i < MAX_HANG_XEMAY; i++) {
        for(int j = 0; j < MAX_COT_XEMAY; j++) {
            if(baiXeMay[i][j].trangThai == 1 && strcmp(baiXeMay[i][j].bienSo, bienSo) == 0) {
                double soGiay = difftime(timeRa, baiXeMay[i][j].thoiGianVao);
                double tien = TinhTien(1, soGiay);
                
                printf("\n--- HOA DON THANH TOAN ---\n");
                printf("Bien so: %s (Xe may)\n", bienSo);
                printf("Thoi gian gui: %.0f gio (demo so giay)\n", soGiay);
                printf("Tong tien: %.0f VND\n", tien);
                
                GhiLichSu(bienSo, 1, baiXeMay[i][j].thoiGianVao, timeRa, tien);
                
                baiXeMay[i][j].trangThai = 0;
                return;
            }
        }
    }
    
    printf(">> Khong tim thay xe co bien so %s trong bai!\n", bienSo);
}
