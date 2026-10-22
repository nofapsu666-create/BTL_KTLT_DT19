/* =========================================================
 * Ten File : hienthi.c
 * Mo ta    : In so do bai do, thong ke du lieu, xu ly gio.
 * ========================================================= */
#include "quanlybaixe.h"

/*
 * Ten ham: FormatThoiGian
 * Muc dich: Chuyen time_t thanh chuoi string dinh dang chuan.
 */
void FormatThoiGian(time_t t, char* buffer) {
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 30, "%d/%m/%Y %H:%M:%S", tm_info);
}

/*
 * Ten ham: InSoDo
 * Muc dich: Duyet mang 2 chieu va in truc quan bai do ([X] la co xe, [ ] la trong).
 */
void InSoDo(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]) {
    printf("\n--- SO DO KHU VUC O TO ---\n");
    for(int i = 0; i < MAX_HANG_OTO; i++) {
        for(int j = 0; j < MAX_COT_OTO; j++) {
            if(baiOto[i][j].trangThai == 1) printf("[X] ");
            else printf("[ ] ");
        }
        printf("\n");
    }

    printf("\n--- SO DO KHU VUC XE MAY ---\n");
    for(int i = 0; i < MAX_HANG_XEMAY; i++) {
        for(int j = 0; j < MAX_COT_XEMAY; j++) {
            if(baiXeMay[i][j].trangThai == 1) printf("[X] ");
            else printf("[ ] ");
        }
        printf("\n");
    }
}

void InThongKe(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]) {
    int oToCoXe = 0, xeMayCoXe = 0;
    
    for(int i = 0; i < MAX_HANG_OTO; i++)
        for(int j = 0; j < MAX_COT_OTO; j++)
            if(baiOto[i][j].trangThai == 1) oToCoXe++;

    for(int i = 0; i < MAX_HANG_XEMAY; i++)
        for(int j = 0; j < MAX_COT_XEMAY; j++)
            if(baiXeMay[i][j].trangThai == 1) xeMayCoXe++;

    printf("\n=== BANG THONG KE CA TRUC ===\n");
    printf("- O to dang gui: %d/%d xe\n", oToCoXe, MAX_HANG_OTO * MAX_COT_OTO);
    printf("- Xe may dang gui: %d/%d xe\n", xeMayCoXe, MAX_HANG_XEMAY * MAX_COT_XEMAY);
    printf("=============================\n");
}
