/* =========================================================
 * Ten File : main.c
 * Mo ta    : Ham main, menu dieu huong va ghi file lich su.
 * ========================================================= */
#include "quanlybaixe.h"
#define ROW_OTO 4
#define COL_OTO 5
#define ROW_XEMAY 5
#define COL_XEMAY 6
#define MAX_XE 100
typedef enum { XE_MAY = 1, O_TO = 2 } LoaiXe;
/* 
 * Ten ham: GhiLichSu
 * Muc dich: Ghi thong tin luot xe ra vao file txt de luu tru.
 */
void GhiLichSu(char* bienSo, int loaiXe, time_t vao, time_t ra, double tien) {
    FILE *f = fopen("lich_su.txt", "a");
    if (f == NULL) {
        printf("Loi: Khong the mo file lich_su.txt!\n");
        return;
    }
    char bufVao[30], bufRa[30];
    FormatThoiGian(vao, bufVao);
    FormatThoiGian(ra, bufRa);
    
    fprintf(f, "Bien so: %s | Loai: %d | Vao: %s | Ra: %s | Phi: %.0f VND\n", 
            bienSo, loaiXe, bufVao, bufRa, tien);
    fclose(f);
}
// Bãi đỗ xe và danh sách xe
int gridOTo[ROW_OTO][COL_OTO] = {0};
int gridXeMay[ROW_XEMAY][COL_XEMAY] = {0};
TheXe danhSachThe[MAX_XE];
int tongSoXeAcc = 0;
long long tongDoanhThu = 0;
int tongLuotXeHoanThanh = 0;

// Danh sách các mã tỉnh/thành phố theo quy định cung cấp
const int MA_TINH_VALID[] = {
    11, 12, 14, 99, 98, 22, 23, 24, 21, 25, 27, 26, 20, 97, 19, 28, 88,
    29, 30, 31, 32, 33, 40, 15, 16, 34, 89, 17, 35, 18, 90, 36, 37, 38,
    74, 73, 75, 43, 92, 76, 82, 81, 77, 47, 78, 79, 85, 49, 48, 86, 60,
    39, 93, 41, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61, 72, 70, 62,
    66, 63, 65, 83, 95, 64, 71, 84, 69, 94, 68, 67
};
const int SO_LUONG_MA_TINH = sizeof(MA_TINH_VALID) / sizeof(MA_TINH_VALID[0]);

// Kiểm tra 1 ký tự có nằm trong 20 chữ cái cho phép hay không
int isKyTuSeriHopLe(char c) {
    c = toupper(c);
    // Các chữ cái bị loại trừ: I, O, Q, R, W
    if (c == 'I' || c == 'O' || c == 'Q' || c == 'R' || c == 'W') return 0;
    if (c >= 'A' && c <= 'Z') return 1;
    return 0;
}

// Kiểm tra mã tỉnh có hợp lệ theo danh sách không
int isMaTinhHopLe(int ma) {
    for (int i = 0; i < SO_LUONG_MA_TINH; i++) {
        if (MA_TINH_VALID[i] == ma) return 1;
    }
    return 0;
}

/**
 * Kiểm tra biển số xe theo đúng định dạng:
 * - Mã tỉnh: 2 chữ số hợp lệ ở đầu.
 * - Sê-ri chữ cái:
 *   + Ô tô: Đúng 1 chữ cái hợp lệ
 *   + Xe máy: Đúng 2 chữ cái hợp lệ
 * - Dấu phân cách: Có thể có '-' hoặc không.
 * - Phần số: Chứa từ 4 đến 5 chữ số.
 */
int kiemTraBienSoHopLe(const char *bienSo, LoaiXe loai) {
    int len = strlen(bienSo);
    if (len < 6 || len > 12) return 0;

    // 1. Kiểm tra 2 chữ số mã tỉnh
    if (!isdigit(bienSo[0]) || !isdigit(bienSo[1])) return 0;
    int maTinh = (bienSo[0] - '0') * 10 + (bienSo[1] - '0');
    if (!isMaTinhHopLe(maTinh)) return 0;

    int idx = 2; // Vị trí bắt đầu kiểm tra seri

    // 2. Kiểm tra sê-ri chữ cái theo loại xe
    if (loai == O_TO) {
        if (!isKyTuSeriHopLe(bienSo[idx])) return 0;
        idx += 1;
    } else { // XE_MAY
        if (!isKyTuSeriHopLe(bienSo[idx]) || !isKyTuSeriHopLe(bienSo[idx + 1])) return 0;
        idx += 2;
    }

    // 3. Bỏ qua dấu gạch ngang '-' nếu có
    if (bienSo[idx] == '-') {
        idx++;
    }

    // 4. Kiểm tra phần chữ số còn lại
    int countDigits = 0;
    while (idx < len) {
        if (isdigit(bienSo[idx])) {
            countDigits++;
        } else if (bienSo[idx] != '.') { 
            return 0;
        }
        idx++;
    }

    if (countDigits < 4 || countDigits > 5) return 0;

    return 1;
}
void KhoiTaoBaiXe(TheXe baiOto[][MAX_COT_OTO], TheXe baiXeMay[][MAX_COT_XEMAY]) {
    // Reset toan bo mang 2 chieu ve trang thai 0 (Trong)
    for(int i = 0; i < MAX_HANG_OTO; i++)
        for(int j = 0; j < MAX_COT_OTO; j++)
            baiOto[i][j].trangThai = 0;
            
    for(int i = 0; i < MAX_HANG_XEMAY; i++)
        for(int j = 0; j < MAX_COT_XEMAY; j++)
            baiXeMay[i][j].trangThai = 0;
}

int main() {
    TheXe baiOto[MAX_HANG_OTO][MAX_COT_OTO];
    TheXe baiXeMay[MAX_HANG_XEMAY][MAX_COT_XEMAY];
    KhoiTaoBaiXe(baiOto, baiXeMay);

    int luaChon, loaiXe;
    char bienSo[20];

    do {
        printf("\n=== HE THONG QUAN LY BAI DO XE THONG MINH ===\n");
        printf("1. Xe vao bai\n");
        printf("2. Xe ra bai (Tinh tien)\n");
        printf("3. Xem so do bai do\n");
        printf("4. Xem thong ke ca truc\n");
        printf("0. Thoat chuong trinh\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);
        fflush(stdin);

        switch (luaChon) {
            case 1:
                printf("Chon loai xe (1 - Xe may, 2 - O to): ");
                scanf("%d", &loaiXe);
                fflush(stdin);
                printf("Nhap bien so xe: ");
                gets(bienSo);
                XeVao(baiOto, baiXeMay, loaiXe, bienSo);
                break;
            case 2:
                printf("Nhap bien so xe can lay: ");
                gets(bienSo);
                XeRa(baiOto, baiXeMay, bienSo);
                break;
            case 3:
                InSoDo(baiOto, baiXeMay);
                break;
            case 4:
                InThongKe(baiOto, baiXeMay);
                break;
            case 0:
                printf("Da thoat he thong.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);

    return 0;
}
