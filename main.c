/* =========================================================
 * Ten file : main.c
 * Mo ta    : Bien toan cuc, kiem tra bien so xe va ham main (menu).
 * Bien dich: gcc -Wall main.c xuly.c hienthi.c -o baixe -lm
 * ========================================================= */
#include "quanlybaixe.h"

// Bai do xe va danh sach xe
int gridOTo[ROW_OTO][COL_OTO] = {0};
int gridXeMay[ROW_XEMAY][COL_XEMAY] = {0};
TheXe danhSachThe[MAX_XE];
int tongSoXeAcc = 0;
long long tongDoanhThu = 0;
int tongLuotXeHoanThanh = 0;

// Danh sach cac ma tinh/thanh pho theo quy dinh cung cap
const int MA_TINH_VALID[] = {
    11, 12, 14, 99, 98, 22, 23, 24, 21, 25, 27, 26, 20, 97, 19, 28, 88,
    29, 30, 31, 32, 33, 40, 15, 16, 34, 89, 17, 35, 18, 90, 36, 37, 38,
    74, 73, 75, 43, 92, 76, 82, 81, 77, 47, 78, 79, 85, 49, 48, 86, 60,
    39, 93, 41, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61, 72, 70, 62,
    66, 63, 65, 83, 95, 64, 71, 84, 69, 94, 68, 67
};
const int SO_LUONG_MA_TINH = sizeof(MA_TINH_VALID) / sizeof(MA_TINH_VALID[0]);

// Kiem tra 1 ky tu co nam trong 20 chu cai cho phep hay khong
int isKyTuSeriHopLe(char c) {
    c = toupper((unsigned char)c);
    // Cac chu cai bi loai tru: I, J, O, Q, R, W
    if (c == 'I' || c == 'J' || c == 'O' || c == 'Q' || c == 'R' || c == 'W') return 0;
    if (c >= 'A' && c <= 'Z') return 1;
    return 0;
}

// Kiem tra ma tinh co hop le theo danh sach khong
int isMaTinhHopLe(int ma) {
    for (int i = 0; i < SO_LUONG_MA_TINH; i++) {
        if (MA_TINH_VALID[i] == ma) return 1;
    }
    return 0;
}

/**
 * 1. Kiem tra bien so xe theo dung dinh dang:
 * - Ma tinh: 2 chu so hop le o dau.
 * - Se-ri chu cai:
 *   + O to: dung 1 chu cai hop le
 *   + Xe may: dung 2 chu cai hop le
 * - Dau gach ngang '-' sau se-ri: co the co hoac khong.
 * - Phan so: 4 hoac 5 chu so; neu co dau cham thi dung dang 123.45
 */
int kiemTraBienSoHopLe(const char *bienSo, LoaiXe loai) {
    int len = strlen(bienSo);
    if (len < 6 || len > 12) return 0;

    // Kiem tra 2 chu so ma tinh
    if (!isdigit((unsigned char)bienSo[0]) || !isdigit((unsigned char)bienSo[1])) return 0;
    int maTinh = (bienSo[0] - '0') * 10 + (bienSo[1] - '0');
    if (!isMaTinhHopLe(maTinh)) return 0;

    int idx = 2; // Vi tri bat dau kiem tra se-ri

    // Kiem tra se-ri chu cai theo loai xe
    if (loai == O_TO) {
        if (!isKyTuSeriHopLe(bienSo[idx])) return 0;
        idx += 1;
    } else { // XE_MAY
        if (!isKyTuSeriHopLe(bienSo[idx]) || !isKyTuSeriHopLe(bienSo[idx + 1])) return 0;
        idx += 2;
    }

    // Bo qua dau gach ngang '-' neu co
    if (bienSo[idx] == '-') {
        idx++;
    }

    // Kiem tra phan chu so con lai
    int countDigits = 0;
    int coDauCham = 0;
    while (idx < len) {
        if (isdigit((unsigned char)bienSo[idx])) {
            countDigits++;
        } else if (bienSo[idx] == '.' && countDigits == 3 && !coDauCham) {
            coDauCham = 1;   // dau cham chi duoc dung sau 3 chu so dau
        } else {
            return 0;
        }
        idx++;
    }

    if (countDigits < 4 || countDigits > 5) return 0;
    if (coDauCham && countDigits != 5) return 0;   // dang 123.45

    return 1;
}

int main() {
    int luaChon;

    do {
        printf("\n========= HE THONG QUAN LY BAI DO XE THONG MINH =========\n");
        printf("1. Xe vao bai (Quet the & Dieu huong)\n");
        printf("2. Xe ra bai (Tinh phi & Giai phong o do)\n");
        printf("3. Xem so do bai do xe (Truc quan)\n");
        printf("4. Thong ke ca truc & Doanh thu\n");
        printf("5. Xem lich su ra vao (tu file)\n");
        printf("0. Thoat chuong trinh\n");
        printf("Lua chon cua ban: ");

        int kq = scanf("%d", &luaChon);
        if (kq == EOF) {            // het du lieu nhap: thoat de khong lap vo han
            luaChon = 0;
        } else if (kq != 1) {       // nhap chu: bo dong loi, roi vao nhanh default
            clearInputBuffer();
            luaChon = -1;
        } else {
            clearInputBuffer();     // bo phan thua cua dong
        }

        switch (luaChon) {
            case 1: xeVao(); break;
            case 2: xeRa(); break;
            case 3: hienThiSoDo(); break;
            case 4: thongKeCaTruc(); break;
            case 5: docLichSuFile(); break;
            case 0: printf("Dang thoat he thong...\n"); break;
            default: printf("Lua chon khong hop le, vui long thu lai!\n");
        }
    } while (luaChon != 0);

    return 0;
}
