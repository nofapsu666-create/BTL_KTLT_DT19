/* =========================================================
 * Ten file : xuly.c
 * Mo ta    : Hang doi, BFS, tinh phi, ghi/doc lich su, xe vao, xe ra.
 * ========================================================= */
#include "quanlybaixe.h"

// Bo phan con lai cua dong nhap (den het '\n' hoac het du lieu)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Queue Operations cho BFS
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void pushQueue(Queue *q, Point p) {
    q->data[q->rear++] = p;
}

Point popQueue(Queue *q) {
    return q->data[q->front++];
}

// 2. Thuat toan BFS tim vi tri do trong gan cong [0][0] nhat
int timViTriTrongGanNhat(LoaiXe loai, int *outR, int *outC) {
    int maxR = (loai == O_TO) ? ROW_OTO : ROW_XEMAY;
    int maxC = (loai == O_TO) ? COL_OTO : COL_XEMAY;
    int visited[10][10] = {0};

    Queue q;
    initQueue(&q);

    Point pStart = {0, 0};
    pushQueue(&q, pStart);
    visited[0][0] = 1;

    int dr[] = {-1, 1, 0, 0};   // len, xuong, trai, phai
    int dc[] = {0, 0, -1, 1};

    while (!isEmpty(&q)) {
        Point curr = popQueue(&q);

        int isOccupied = (loai == O_TO) ? gridOTo[curr.r][curr.c] : gridXeMay[curr.r][curr.c];
        if (isOccupied == 0) {
            *outR = curr.r;
            *outC = curr.c;
            return 1;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < maxR && nc >= 0 && nc < maxC && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                Point nextP = {nr, nc};
                pushQueue(&q, nextP);
            }
        }
    }
    return 0;   // khong con o trong
}

// 3. Tinh phi gui xe theo gio (Free 2h dau, sau do: Xe may 5k/h, O to 10k/h)
long long tinhPhi(LoaiXe loai, double soGio) {
    int gioTron = (int)ceil(soGio);
    if (gioTron <= 0) gioTron = 1;
    if (gioTron <= 2) return 0;

    int gioPhuTroi = gioTron - 2;
    return (loai == XE_MAY) ? ((long long)gioPhuTroi * 5000) : ((long long)gioPhuTroi * 10000);
}

// 4. Ghi va doc file lich su
void ghiLichSuFile(TheXe tx, long long tienPhi) {
    FILE *f = fopen("lich_su_bai_xe.txt", "a");
    if (f != NULL) {
        char tVao[80], tRa[80];
        struct tm *tmVao = localtime(&tx.thoiGianVao);
        strftime(tVao, sizeof(tVao), "%Y-%m-%d %H:%M:%S", tmVao);
        struct tm *tmRa = localtime(&tx.thoiGianRa);
        strftime(tRa, sizeof(tRa), "%Y-%m-%d %H:%M:%S", tmRa);

        fprintf(f, "Ma the: %s | Bien so: %s | Loai: %s | Vao: %s | Ra: %s | Phi: %lld VND\n",
                tx.maThe, tx.bienSo, (tx.loaiXe == O_TO ? "O to" : "Xe may"), tVao, tRa, tienPhi);
        fclose(f);
    }
}

void docLichSuFile() {
    FILE *f = fopen("lich_su_bai_xe.txt", "r");
    if (f == NULL) {
        printf("\nLICH SU TRONG (Chua co du lieu lich su trong file).\n");
        return;
    }

    printf("\n================ LICH SU BAI XE (TU FILE) ================\n");
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line);
    }
    printf("===========================================================\n");
    fclose(f);
}

// 5. Xu ly xe vao
void xeVao() {
    if (tongSoXeAcc >= MAX_XE) {
        printf("\nLOI: Bai do xe hoac bo nho luu tru da day!\n");
        return;
    }

    TheXe tx;
    printf("\n--- XE VAO BAI ---\n");
    printf("Nhap ma the xe: ");
    if (scanf("%19s", tx.maThe) != 1) return;

    for (int i = 0; i < tongSoXeAcc; i++) {
        if (strcmp(danhSachThe[i].maThe, tx.maThe) == 0 && danhSachThe[i].dangTrongBai) {
            printf("LOI: Ma the nay dang gui mot xe khac trong bai!\n");
            return;
        }
    }

    int loai;
    printf("Loai xe (1: Xe may, 2: O to): ");
    if (scanf("%d", &loai) != 1 || (loai != 1 && loai != 2)) {
        printf("LOI: Loai xe chon khong hop le!\n");
        clearInputBuffer();
        return;
    }
    tx.loaiXe = (LoaiXe)loai;

    printf("Nhap bien so xe (VD: 29A-567.89 hoac 29AB-123.45): ");
    if (scanf("%19s", tx.bienSo) != 1) return;

    if (!kiemTraBienSoHopLe(tx.bienSo, tx.loaiXe)) {
        printf("LOI: Bien so xe khong dung dinh dang quy dinh!\n");
        printf("Luu y:\n");
        printf(" - Ma tinh phai thuoc danh sach quy dinh.\n");
        printf(" - Se-ri chi gom 20 chu cai: A,B,C,D,E,F,G,H,K,L,M,N,P,S,T,U,V,X,Y,Z.\n");
        printf(" - O to dung 1 chu cai (VD: 29A-123.45).\n");
        printf(" - Xe may dung 2 chu cai ket hop (VD: 29AB-123.45).\n");
        clearInputBuffer();
        return;
    }

    // Doi bien so sang chu hoa, roi kiem tra co xe nao dang trong bai cung bien so khong
    for (int i = 0; tx.bienSo[i] != '\0'; i++)
        tx.bienSo[i] = toupper((unsigned char)tx.bienSo[i]);

    for (int i = 0; i < tongSoXeAcc; i++) {
        if (strcmp(danhSachThe[i].bienSo, tx.bienSo) == 0 && danhSachThe[i].dangTrongBai) {
            printf("LOI: Bien so nay dang co xe trong bai!\n");
            return;
        }
    }

    int r, c;
    if (!timViTriTrongGanNhat(tx.loaiXe, &r, &c)) {
        printf("RAT TIEC: Khu vuc do %s da het cho!\n", (tx.loaiXe == O_TO ? "O to" : "Xe may"));
        return;
    }

    tx.rowPos = r;
    tx.colPos = c;
    if (tx.loaiXe == O_TO) gridOTo[r][c] = 1;
    else gridXeMay[r][c] = 1;

    tx.thoiGianVao = time(NULL);
    tx.thoiGianRa = 0;
    tx.dangTrongBai = 1;
    danhSachThe[tongSoXeAcc++] = tx;

    char timeBuf[80];
    struct tm *tmInfo = localtime(&tx.thoiGianVao);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", tmInfo);

    printf("=> CHAP NHAN XE VAO!\n");
    printf("- Bien so: %s (Hop le)\n", tx.bienSo);
    printf("- Thoi gian vao: %s\n", timeBuf);
    printf("- Dieu huong vi tri do: Khu %s -> Hang %d, Cot %d\n",
           (tx.loaiXe == O_TO ? "O to" : "Xe may"), r + 1, c + 1);
}

// 6. Xu ly xe ra
void xeRa() {
    char maThe[20];
    printf("\n--- XE RA BAI ---\n");
    printf("Quet ma the xe: ");
    if (scanf("%19s", maThe) != 1) return;

    for (int i = 0; i < tongSoXeAcc; i++) {
        if (strcmp(danhSachThe[i].maThe, maThe) == 0 && danhSachThe[i].dangTrongBai) {
            danhSachThe[i].thoiGianRa = time(NULL);
            danhSachThe[i].dangTrongBai = 0;

            if (danhSachThe[i].loaiXe == O_TO)
                gridOTo[danhSachThe[i].rowPos][danhSachThe[i].colPos] = 0;
            else
                gridXeMay[danhSachThe[i].rowPos][danhSachThe[i].colPos] = 0;

            double soGiay = difftime(danhSachThe[i].thoiGianRa, danhSachThe[i].thoiGianVao);
            double soGio = soGiay / 3600.0;

            long long tienPhi = tinhPhi(danhSachThe[i].loaiXe, soGio);
            tongDoanhThu += tienPhi;
            tongLuotXeHoanThanh++;

            printf("=> XAC NHAN XE RA!\n");
            printf("- Bien so: %s\n", danhSachThe[i].bienSo);
            printf("- Thoi gian gui: %.2f gio (%d giay)\n", soGio, (int)soGiay);
            if (tienPhi == 0) {
                printf("- Phi gui xe: 0 VND (Mien phi 2 gio dau)\n");
            } else {
                printf("- Phi gui xe: %lld VND\n", tienPhi);
            }

            ghiLichSuFile(danhSachThe[i], tienPhi);
            return;
        }
    }
    printf("LOI: Khong tim thay xe tuong ung voi ma the nay trong bai!\n");
}

