/* =========================================================
 * Ten File : main.c
 * Mo ta    : Ham main, menu dieu huong va ghi file lich su.
 * ========================================================= */
#include "quanlybaixe.h"

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
