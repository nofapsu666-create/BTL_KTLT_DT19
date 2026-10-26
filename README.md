# Hệ thống Quản lý Bãi đỗ Ô tô & Xe máy Thông minh

**Bài tập lớn môn Kỹ thuật lập trình — Đề tài 19 — Nhóm 16**
Phân hiệu Trường Đại học Giao thông vận tải tại TP. Hồ Chí Minh, Khoa Công nghệ thông tin.

Chương trình console viết bằng ngôn ngữ C chuẩn, mô phỏng bãi gửi xe gồm hai khu vực độc lập (ô tô và xe máy). Chương trình quản lý xe vào/ra bằng mã thẻ, kiểm tra biển số, tự động chọn ô đỗ trống gần cổng nhất bằng thuật toán BFS, tính phí theo giờ thực tế, vẽ sơ đồ bãi, thống kê ca trực và ghi lịch sử ra tệp.

## Thành viên nhóm

| STT | Họ và tên | MSSV |
|---|---|---|
| 1 | Dương Công Luân | 6751071047 |
| 2 | Trịnh Chí Nhân | 6751071053 |
| 3 | Nguyễn Xuân Quảng Khánh | 6751071034 |
| 4 | Huỳnh Mạnh Khoa | 6751071036 |
| 5 | Nguyễn Trung Hiếu | 6751071021 |

## Cấu trúc mã nguồn

| Tệp | Nội dung |
|---|---|
| `quanlybaixe.h` | Hằng số, `enum LoaiXe`, `struct TheXe`, `Point`, `Queue`, khai báo biến toàn cục (`extern`) và nguyên mẫu hàm |
| `main.c` | Định nghĩa biến toàn cục, bảng mã tỉnh `MA_TINH_VALID`, hàm `main` và vòng lặp menu |
| `xuly.c` | Nhập liệu an toàn (`xoaBoDem`, `docChuoiAnToan`), hàng đợi (`initQueue`, `isEmpty`, `pushQueue`, `popQueue`), kiểm tra biển số, BFS `timViTriTrongGanNhat`, `tinhPhi`, `ghiLichSuFile`, `docLichSu`, `xeVao`, `xeRa` |
| `hienthi.c` | `hienThiSoDo`, `thongKeCaTruc` |

## Biên dịch và chạy

Chỉ dùng thư viện chuẩn của C (`stdio`, `stdlib`, `string`, `time`, `math`, `ctype`).

**GCC / Linux / macOS / MinGW:**

```
gcc -Wall main.c xuly.c hienthi.c -o baixe -lm
./baixe
```

Tùy chọn `-lm` cần thiết để liên kết hàm `ceil` của `math.h`. Chương trình biên dịch không có cảnh báo với `-Wall`.

**Dev-C++:** tạo Console Application (C Project), dùng *Add to Project* thêm cả 4 tệp `quanlybaixe.h`, `main.c`, `xuly.c`, `hienthi.c`, rồi nhấn F11.

## Thông số bãi đỗ

| Khu vực | Hàng × Cột | Sức chứa |
|---|---|---|
| Ô tô | 4 × 5 | 20 chỗ |
| Xe máy | 5 × 6 | 30 chỗ |

Cổng ra vào chung nằm tại Hàng 1, Cột 1. Một phiên chạy lưu tối đa 100 lượt gửi (`MAX_XE`).

## Chức năng (menu)

| Lựa chọn | Chức năng | Hàm |
|---|---|---|
| 1 | Xe vào bãi: nhập mã thẻ, loại xe, biển số; hệ thống kiểm tra và điều hướng vị trí đỗ | `xeVao()` |
| 2 | Xe ra bãi: quét mã thẻ, tính thời gian, tính phí, giải phóng ô đỗ, ghi lịch sử | `xeRa()` |
| 3 | Xem sơ đồ bãi đỗ (`[ . ]` ô trống, `[ X ]` ô có xe) | `hienThiSoDo()` |
| 4 | Thống kê ca trực và doanh thu | `thongKeCaTruc()` |
| 0 | Thoát chương trình | |

## Quy định biển số

- Hai ký tự đầu là mã tỉnh/thành phố, phải thuộc danh sách 80 mã quy định (`MA_TINH_VALID`).
- Sê-ri chỉ dùng 20 chữ cái: A, B, C, D, E, F, G, H, K, L, M, N, P, S, T, U, V, X, Y, Z (không có I, J, O, Q, R, W). Chữ thường được xem như chữ hoa.
- Ô tô: đúng 1 chữ cái sê-ri (ví dụ `29A-567.89`). Xe máy: đúng 2 chữ cái (ví dụ `29AB-123.45`).
- Dấu gạch ngang `-` sau sê-ri là tùy chọn. Phần số chỉ có một trong ba dạng: `1234`, `12345` hoặc `123.45`.
- Tổng độ dài từ 6 đến 12 ký tự.
- Không cho hai xe đang trong bãi có cùng biển số.

## Biểu phí

Thời gian gửi tính theo đồng hồ hệ thống, làm tròn lên theo giờ (tối thiểu 1 giờ). **2 giờ đầu miễn phí**; từ giờ thứ ba, mỗi giờ phụ trội tính:

| Loại xe | Đơn giá mỗi giờ phụ trội |
|---|---|
| Xe máy | 5.000 VNĐ |
| Ô tô | 10.000 VNĐ |

Công thức: `g = ceil(t)`, nếu `g <= 2` thì phí = 0, ngược lại phí = `(g - 2) × đơn giá`.

## Thuật toán chính

- **BFS tìm ô trống gần cổng nhất:** duyệt theo hàng đợi từ ô cổng (0,0), thứ tự hướng lên – xuống – trái – phải; độ phức tạp O(R × C).
- **Cấu trúc dữ liệu:** hai ma trận `gridOTo`, `gridXeMay` (0: trống, 1: có xe); mảng `danhSachThe` lưu từng lượt gửi bằng `struct TheXe`.
- **Thời gian thực:** `time`, `difftime`, `localtime`, `strftime`.

## Tệp lịch sử

Mỗi lượt xe ra được ghi thêm một dòng vào `lich_su_bai_xe.txt` (chế độ `"a"`), gồm mã thẻ, biển số, loại xe, giờ vào, giờ ra và phí. Khi khởi động, hàm `docLichSu()` đọc lại tệp (chế độ `"r"`) để khôi phục số lượt đã hoàn thành và tổng doanh thu, nên các số liệu này không mất khi tắt chương trình. Ví dụ một dòng:

```
Ma the: P1 | Bien so: 29A-111.11 | Loai: O to | Vao: 2026-10-24 11:38:23 | Ra: 2026-10-24 14:48:23 | Phi: 20000 VND
```

> **Lưu ý khi thử nghiệm/demo:** vì doanh thu được cộng dồn từ tệp lịch sử, muốn bắt đầu một ca thử mới từ 0 thì xóa tệp `lich_su_bai_xe.txt` trước khi chạy.

## Nhập liệu an toàn

- Menu: nhập chữ hoặc dữ liệu sai không làm chương trình lặp vô hạn; gặp hết dữ liệu nhập (EOF) thì chương trình thoát.
- Mã thẻ và biển số đọc bằng `scanf("%19s", ...)` (tối đa 19 ký tự, vừa mảng `char[20]`) rồi bỏ phần thừa của dòng, nên không ghi tràn bộ nhớ.
- Chương trình không dùng cấp phát động (`malloc`/`free`), nên không có rò rỉ bộ nhớ; đã kiểm tra bằng AddressSanitizer và UndefinedBehaviorSanitizer.

## Kết quả thử nghiệm

Đã kiểm thử 18 ca (TC01–TC18) gồm xe vào/ra hợp lệ, thẻ trùng, loại xe sai, biển số sai, bãi đầy, các ca biên về phí (đúng 2 giờ, hơn 2 giờ một giây). Chi tiết trong Chương 4 của báo cáo.

## Hạn chế đã biết

- Mỗi phiên chạy lưu tối đa 100 lượt gửi (`MAX_XE`); bản ghi của lượt đã ra không được tái sử dụng.
- Danh sách xe đang gửi không được lưu khi thoát chương trình (chỉ khôi phục được số lượt và doanh thu từ tệp lịch sử).
- Mã thẻ dài hơn 19 ký tự bị cắt còn 19 ký tự đầu.

Chi tiết trong mục 4.3.2 của báo cáo.
