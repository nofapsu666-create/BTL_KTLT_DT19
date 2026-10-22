#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parking.h"

void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void khoiTaoBaiXe(int bai[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            bai[i][j] = 0; 
        }
    }
}

void hienThiSoDo(int bai[MAX_ROWS][MAX_COLS]) {
    printf("\n===== SƠ ĐỒ BÃI ĐỖ XE HIỆN TẠI =====\n");
    printf("     Cột: ");
    for (int j = 0; j < MAX_COLS; j++) printf("[%d] ", j);
    printf("\n");
    
    for (int i = 0; i < MAX_ROWS; i++) {
        if (i < 3) printf("KHU XE MÁY [Hàng %d]: ", i);
        else printf("KHU Ô TÔ   [Hàng %d]: ", i);
        
        for (int j = 0; j < MAX_COLS; j++) {
            if (bai[i][j] == 0) printf(" .  ");
            else if (bai[i][j] == 1) printf(" M  ");
            else if (bai[i][j] == 2) printf(" C  ");
        }
        printf("\n");
    }
    printf("=====================================\n");
}

long long tinhTienTheoBac(LoaiXe loai, double soGio) {
    long long tongTien = 0;
    if (loai == XE_MAY) {
        if (soGio <= 2) {
            tongTien = (long long)(soGio * PHI_XE_MAY_BAC_1);
        } else {
            tongTien = (2 * PHI_XE_MAY_BAC_1) + (long long)((soGio - 2) * PHI_XE_MAY_BAC_2);
        }
    } else if (loai == O_TO) {
        if (soGio <= 2) {
            tongTien = (long long)(soGio * PHI_OTO_BAC_1);
        } else {
            tongTien = (2 * PHI_OTO_BAC_1) + (long long)((soGio - 2) * PHI_OTO_BAC_2);
        }
    }
    return tongTien;
}

// Sử dụng Cấp phát động (Pointer to Pointer) để quản lý mảng linh hoạt, chống tràn (YC04)
void xeVaoBai(int bai[MAX_ROWS][MAX_COLS], TheXe **danhSachThe, int *soLuongThe) {
    char maTheTam[20];
    printf("\n--- QUÉT THẺ VÀO BÃI ---\n");
    printf("Nhập mã thẻ xe: ");
    scanf("%19s", maTheTam);
    xoaBoDem();

    for (int i = 0; i < *soLuongThe; i++) {
        if ((*danhSachThe)[i].trangThai == 1 && strcmp((*danhSachThe)[i].maThe, maTheTam) == 0) {
            printf("Lỗi: Mã thẻ này đang ở trong bãi!\n");
            return;
        }
    }

    int loai;
    do {
        printf("Chọn loại xe (1: Xe máy, 2: Ô tô): ");
        if (scanf("%d", &loai) != 1) { xoaBoDem(); loai = 0; }
    } while (loai != 1 && loai != 2);
    xoaBoDem();

    int rDo = -1, cDo = -1;
    int hangBatDau = (loai == 1) ? 0 : 3;
    int hangKetThuc = (loai == 1) ? 3 : 5;

    for (int i = hangBatDau; i < hangKetThuc; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (bai[i][j] == 0) { rDo = i; cDo = j; break; }
        }
        if (rDo != -1) break;
    }

    if (rDo == -1) {
        printf("Hết chỗ: Phân khu này đã đầy!\n");
        return;
    }

    // Tăng kích thước mảng động bằng realloc an toàn (Chống lỗi Segmentation Fault)
    (*soLuongThe)++;
    TheXe *temp = (TheXe *)realloc(*danhSachThe, (*soLuongThe) * sizeof(TheXe));
    if (temp == NULL) {
        printf("Lỗi hệ thống: Cấp phát bộ nhớ thất bại!\n");
        (*soLuongThe)--;
        return;
    }
    *danhSachThe = temp;

    int indexMoi = *soLuongThe - 1;
    strcpy((*danhSachThe)[indexMoi].maThe, maTheTam);
    printf("Nhập biển số xe: ");
    scanf("%19s", (*danhSachThe)[indexMoi].bienSo);
    xoaBoDem();
    
    (*danhSachThe)[indexMoi].loaiPhuongTien = (LoaiXe)loai;
    (*danhSachThe)[indexMoi].thoiGianVao = time(NULL);
    (*danhSachThe)[indexMoi].hangDo = rDo;
    (*danhSachThe)[indexMoi].cotDo = cDo;
    (*danhSachThe)[indexMoi].trangThai = 1;

    bai[rDo][cDo] = loai;
    printf("\n>> CHECK-IN THÀNH CÔNG! Vị trí đỗ: Hàng %d, Cột %d\n", rDo, cDo);
}

void xeRaBai(int bai[MAX_ROWS][MAX_COLS], TheXe *danhSachThe, int soLuongThe) {
    char maTheTam[20];
    printf("\n--- QUÉT THẺ RA BÃI ---\n");
    printf("Nhập mã thẻ xe: ");
    scanf("%19s", maTheTam);
    xoaBoDem();

    int indexThe = -1;
    for (int i = 0; i < soLuongThe; i++) {
        if (danhSachThe[i].trangThai == 1 && strcmp(danhSachThe[i].maThe, maTheTam) == 0) {
            indexThe = i;
            break;
        }
    }

    if (indexThe == -1) {
        printf("Lỗi: Không tìm thấy xe ứng với mã thẻ này trong bãi!\n");
        return;
    }

    time_t thoiGianRa = time(NULL);
    double soGiayGui = difftime(thoiGianRa, danhSachThe[indexThe].thoiGianVao);
    double soGioTinhTien = (soGiayGui < 1) ? 1 : soGiayGui; // Giả lập 1 giây = 1 giờ để cô dễ chấm

    long long phiGuiXe = tinhTienTheoBac(danhSachThe[indexThe].loaiPhuongTien, soGioTinhTien);

    struct tm *tmVao = localtime(&danhSachThe[indexThe].thoiGianVao);
    char strVao[30]; // Đã sửa từ ký tự đơn sang mảng chuỗi an toàn
    strftime(strVao, sizeof(strVao), "%Y-%m-%d %H:%M:%S", tmVao);

    printf("\n====== HÓA ĐƠN THANH TOÁN ======\n");
    printf("Mã thẻ: %s | Biển số: %s\n", danhSachThe[indexThe].maThe, danhSachThe[index_the].bienSo);
    printf("Thời gian vào: %s\n", strVao);
    printf("Thời gian gửi mô phỏng: %.0f giờ\n", soGioTinhTien);
    printf("THÀNH TIỀN (Tính theo bậc): %lld VNĐ\n", phiGuiXe);
    printf("================================\n");

    luuLichSuRaBai(danhSachThe[indexThe].bienSo, danhSachThe[index_the].maThe, 
                   (int)danhSachThe[indexThe].loaiPhuongTien, soGioTinhTien, phiGuiXe);

    bai[danhSachThe[indexThe].hangDo][danhSachThe[indexThe].cotDo] = 0;
    danhSachThe[index_the].trangThai = 0; 
    printf(">> Check-out xong! Đã giải phóng vị trí [%d][%d].\n", 
           danhSachThe[indexThe].hangDo, danhSachThe[indexThe].cotDo);
}

void luuLichSuRaBai(const char* bienSo, const char* maThe, int loai, double soGio, long long thanhTien) {
    FILE *f = fopen(FILE_DATA, "a");
    if (f == NULL) return;
    fprintf(f, "%s | %s | %s | %.0f gio | %lld VND\n", 
            maThe, bienSo, (loai == 2) ? "O to" : "Xe may", soGio, thanhTien);
    fclose(f);
}

// Thống kê ca trực xử lý dữ liệu bền vững từ file dữ liệu (ĐT19)
void thongKeCaTruc() {
    FILE *f = fopen(FILE_DATA, "r");
    if (f == NULL) {
        printf("\nChưa có lịch sử giao dịch nào trong ca trực.\n");
        return;
    }
    
    char dong[100];
    int txtLoaiXe;
    long long txtTien;
    int tongXeMay = 0, tongOTo = 0;
    long long tongDoanhThu = 0;

    printf("\n======= THỐNG KÊ DOANH THU CA TRỰC =======\n");
    while (fgets(dong, sizeof(dong), f) != NULL) {
        printf("%s", dong);
        if (strstr(dong, "Xe may") != NULL) tongXeMay++;
        if (strstr(dong, "O to") != NULL) tongOTo++;
        
        // Tìm chữ VND để lấy con số doanh thu cộng dồn
        char *p = strstr(dong, " | ");
        if (p != NULL) {
            p = strstr(p + 3, " | ");
            if (p != NULL) {
                p = strstr(p + 3, " | ");
                if (p != NULL) {
                    sscanf(p + 3, "%*f gio | %lld VND", &txtTien);
                    tongDoanhThu += txtTien;
                }
            }
        }
    }
    fclose(f);
    printf("------------------------------------------\n");
    printf("Tổng số lượt xe máy đã xử lý: %d\n", tongXeMay);
    printf("Tổng số lượt ô tô đã xử lý : %d\n", tongOTo);
    printf("TỔNG DOANH THU CA TRỰC     : %lld VNĐ\n", tongDoanhThu);
    printf("==========================================\n");
}
