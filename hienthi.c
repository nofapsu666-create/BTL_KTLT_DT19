/* =========================================================
 * Ten File : hienthi.c
 * Mo ta    : Ve so do bai do, dinh dang thoi gian va bao cao thong ke.
 * ========================================================= */

#include <stdio.h>
#include <time.h>
#include "quanlybaixe.h"

/*
 * Ten ham  : FormatThoiGian
 * Muc dich : Chuyen time_t thanh chuoi string dinh dang "DD/MM/YYYY HH:MM:SS".
 */
void FormatThoiGian(time_t t, char* buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size == 0) return;

    struct tm *tm_info = localtime(&t);
    if (tm_info != NULL) {
        strftime(buffer, buffer_size, "%d/%m/%Y %H:%M:%S", tm_info);
    } else {
        buffer[0] = '\0';
    }
}

/*
 * Ten ham  : InSoDo
 * Muc dich : Duyet va in truc quan so do bai do xe (O to & Xe may).
 */
void InSoDo(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]) {
    printf("\n================ SO DO BAI DO XE ================\n");
    printf("[Loi vao bai o vi tri Hang 1, Cot 1]\n");
    printf("Ky hieu: [ . ] = O trong | [ X ] = Da co xe\n\n");

    /* --- KHU VUC O TO --- */
    printf("--- KHU VUC O TO ---");
    for (int i = 0; i < MAX_HANG_OTO; i++) {
        printf("\nHang %2d: ", i + 1);
        for (int j = 0; j < MAX_COT_OTO; j++) {
            if (baiOto[i][j].trangThai == 1) {
                printf("[ X ] ");
            } else {
                printf("[ . ] ");
            }
        }
    }

    /* --- KHU VUC XE MAY --- */
    printf("\n\n--- KHU VUC XE MAY ---");
    for (int i = 0; i < MAX_HANG_XEMAY; i++) {
        printf("\nHang %2d: ", i + 1);
        for (int j = 0; j < MAX_COT_XEMAY; j++) {
            if (baiXeMay[i][j].trangThai == 1) {
                printf("[ X ] ");
            } else {
                printf("[ . ] ");
            }
        }
    }
    printf("\n=================================================\n");
}

/*
 * Ten ham  : InThongKe
 * Muc dich : In thong ke chi tiet so xe trong bai, luot xe hoan thanh va doanh thu.
 */
void InThongKe(TheXe baiOto[][MAX_COT_OTO], 
                TheXe baiXeMay[][MAX_COT_XEMAY], 
                int tongLuotXeHoanThanh, 
                long long tongDoanhThu) {
    int oToCoXe = 0;
    int xeMayCoXe = 0;

    /* Dem so xe o to hien tai */
    for (int i = 0; i < MAX_HANG_OTO; i++) {
        for (int j = 0; j < MAX_COT_OTO; j++) {
            if (baiOto[i][j].trangThai == 1) {
                oToCoXe++;
            }
        }
    }

    /* Dem so xe may hien tai */
    for (int i = 0; i < MAX_HANG_XEMAY; i++) {
        for (int j = 0; j < MAX_COT_XEMAY; j++) {
            if (baiXeMay[i][j].trangThai == 1) {
                xeMayCoXe++;
            }
        }
    }