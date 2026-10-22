#include <stdio.h>
#include <stdlib.h>
#include "parking.h"

int main() {
    int baiDoXe[MAX_ROWS][MAX_COLS];
    // Cấp phát con trỏ động ban đầu là NULL (YC04 - Chống rò rỉ bộ nhớ)
    TheXe *danhSachThe = NULL; 
    int soLuongThe = 0;
    int luaChon;

    khoiTaoBaiXe(baiDoXe);

    do {
        printf("\n===================================\n");
        printf("   HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE ĐT19  \n");
        printf("===================================\n");
        printf("1. Hiển thị sơ đồ ma trận bãi đỗ\n");
        printf("2. Xe vào bãi (Quét thẻ Check-in)\n");
        printf("3. Xe ra bãi (Tính tiền Check-out)\n");
        printf("4. Báo cáo thống kê ca trực từ File\n");
        printf("5. Thoát hệ thống\n");
        printf("Nhập lựa chọn của bạn (1-5): ");
        
        if (scanf("%d", &luaChon) != 1) {
            printf("Lỗi: Vui lòng chỉ nhập số thuộc Menu!\n");
            xoaBoDem();
            continue;
        }

        switch (luaChon) {
            case 1: hienThiSoDo(baiDoXe); break;
            case 2: xeVaoBai(baiDoXe, &danhSachThe, &soLuongThe); break;
            case 3: xeRaBai(baiDoXe, danhSachThe, soLuongThe); break;
            case 4: thongKeCaTruc(); break;
            case 5:
                // Thu hồi vùng nhớ động trước khi đóng ứng dụng để tránh Memory Leak (YC04)
                if (danhSachThe != NULL) {
                    free(danhSachThe);
                    danhSachThe = NULL;
                }
                printf("Đang đóng hệ thống bãi xe an toàn. Tạm biệt!\n");
                break;
            default: printf("Lựa chọn không hợp lệ, vui lòng chọn lại.\n");
        }
    } while (luaChon != 5);

    return 0;
}
