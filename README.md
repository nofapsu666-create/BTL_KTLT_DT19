# Hệ thống Quản lý Bãi đỗ Ô tô & Xe máy Thông minh

**Bài tập lớn môn Kỹ thuật lập trình — Đề tài 19 — Nhóm 16**
Phân hiệu Trường Đại học Giao thông vận tải tại TP. Hồ Chí Minh, Khoa Công nghệ thông tin.

Chương trình console viết bằng ngôn ngữ C chuẩn, mô phỏng bãi gửi xe gồm hai khu vực độc lập (ô tô và xe máy). Chương trình quản lý xe vào/ra bằng mã thẻ, kiểm tra biển số, tự động chọn ô đỗ trống gần cổng nhất bằng thuật toán BFS, tính phí theo giờ thực tế, vẽ sơ đồ bãi, thống kê ca trực và ghi lịch sử ra tệp. Chương trình có phân quyền ba vai trò: **Quản trị**, **Nhân viên** và **Khách hàng**; dữ liệu bãi xe, tài khoản và giá gửi được lưu lại giữa các lần chạy.

## Thành viên nhóm

| STT | Họ và tên | MSSV |
|---|---|---|
| 1 | Dương Công Luận | 6751071047 |
| 2 | Trịnh Chí Nhân | 6751071053 |
| 3 | Nguyễn Xuân Quảng Khánh | 6751071034 |
| 4 | Huỳnh Mạnh Khoa | 6751071036 |
| 5 | Nguyễn Trung Hiếu | 6751071021 |

## Cấu trúc mã nguồn

| Tệp | Nội dung |
|---|---|
| `quanlybaixe.h` | Hằng số, `enum LoaiXe`, `struct TheXe`, `Point`, `Queue`, khai báo biến toàn cục (`extern`) và nguyên mẫu hàm |
| `main.c` | Định nghĩa biến toàn cục, bảng mã tỉnh `MA_TINH_VALID`, kiểm tra biển số (`isKyTuSeriHopLe`, `isMaTinhHopLe`, `kiemTraBienSoHopLe`), ba menu theo vai trò (`menuAdmin`, `menuNhanVien`, `menuKhach`) và hàm `main` |
| `xuly.c` | `clearInputBuffer`, `docLuaChon`, `docChuoi`, hàng đợi (`initQueue`, `isEmpty`, `pushQueue`, `popQueue`), BFS `timViTriTrongGanNhat`, `tinhPhi`, `ghiLichSuFile`, `docLichSuFile`, `xeVao`, `xeRa`, `traCuuXe` |
| `hienthi.c` | `hienThiSoDo`, `thongKeCaTruc`, `hienThiBangGia`, `hienThiChoTrong` |
| `taikhoan.c` | Tài khoản và đăng nhập: `khoiTaoTaiKhoan`, `luuTaiKhoan`, `dangNhap`, `doiMatKhau`, `quanLyTaiKhoan` |
| `dulieu.c` | Lưu/đọc dữ liệu giữa các lần chạy: `luuDuLieuBai`, `docDuLieuBai`, `luuCauHinh`, `docCauHinh`, `suaGia` |

## Biên dịch và chạy

Chỉ dùng thư viện chuẩn của C (`stdio`, `stdlib`, `string`, `time`, `math`, `ctype`).

**GCC / Linux / macOS / MinGW:**

```
gcc -Wall main.c xuly.c hienthi.c taikhoan.c dulieu.c -o baixe -lm
./baixe
```

Tùy chọn `-lm` cần thiết để liên kết hàm `ceil` của `math.h`. Chương trình biên dịch không có cảnh báo với `-Wall`.

**Dev-C++:** tạo Console Application (C Project), dùng *Add to Project* thêm cả 6 tệp `quanlybaixe.h`, `main.c`, `xuly.c`, `hienthi.c`, `taikhoan.c`, `dulieu.c`, rồi nhấn F11.

## Thông số bãi đỗ

| Khu vực | Hàng × Cột | Sức chứa |
|---|---|---|
| Ô tô | 4 × 5 | 20 chỗ |
| Xe máy | 5 × 6 | 30 chỗ |

Cổng ra vào chung nằm tại Hàng 1, Cột 1. Tối đa 100 xe cùng lúc trong bãi (`MAX_XE`).

## Phân quyền và chức năng

Khi mở chương trình, màn hình mặc định là **giao diện khách hàng**, nên người trông xe không phải chọn vai trò mỗi lần bật máy. Nhân viên hoặc quản trị chọn **9. Đăng nhập** rồi nhập tên đăng nhập và mật khẩu; chương trình tự mở đúng menu theo tài khoản. Đăng nhập sai 3 lần thì quay lại màn hình khách hàng.

**Quy trình trong ca trực:** nhân viên đăng nhập **một lần** đầu ca và ở lại menu nhân viên cả ca (đầu menu luôn hiện số chỗ trống). Khi rời máy, chọn **6. Khóa màn hình** để chuyển sang giao diện khách mà không phải đăng xuất; muốn quay lại thì bấm 9 và chỉ cần nhập lại mật khẩu. Khi đang khóa, khách không thoát được chương trình.

**Thiết lập tài khoản:**

1. Lần chạy đầu tiên (chưa có tệp `taikhoan.txt`), chương trình yêu cầu tạo tài khoản **quản trị**: nhập tên đăng nhập, mật khẩu (từ 4 ký tự) và nhập lại mật khẩu.
2. Quản trị đăng nhập, vào **8. Quản lý tài khoản** để thêm tài khoản **nhân viên** (tên đăng nhập và mật khẩu).
3. Từ đó, nhân viên đăng nhập bằng tài khoản được cấp. Mọi người có thể tự đổi mật khẩu.

**Nhân viên** (làm việc tại cổng bãi xe):

| Lựa chọn | Chức năng | Hàm |
|---|---|---|
| 1 | Xe vào bãi: nhập mã thẻ, loại xe, biển số; hệ thống kiểm tra và điều hướng vị trí đỗ | `xeVao()` |
| 2 | Xe ra bãi: quét mã thẻ, tính thời gian, tính phí, giải phóng ô đỗ, ghi lịch sử | `xeRa()` |
| 3 | Xem sơ đồ bãi đỗ (`[ . ]` ô trống, `[ X ]` ô có xe) | `hienThiSoDo()` |
| 4 | Tra cứu xe theo mã thẻ hoặc biển số (vị trí, giờ vào, phí tạm tính) | `traCuuXe()` |
| 5 | Đổi mật khẩu | `doiMatKhau()` |
| 6 | Khóa màn hình (chuyển sang giao diện khách, mở lại bằng mật khẩu) | `menuKhach()`, `xacNhanMatKhau()` |
| 0 | Đăng xuất | |

**Quản trị** có mọi chức năng của nhân viên (mục 1–4) và thêm:

| Lựa chọn | Chức năng | Hàm |
|---|---|---|
| 5 | Thống kê ca trực và doanh thu | `thongKeCaTruc()` |
| 6 | Xem lịch sử ra vào đọc từ tệp `lich_su_bai_xe.txt` | `docLichSuFile()` |
| 7 | Sửa giá gửi xe theo giờ (lưu trong `cauhinh.txt`) | `suaGia()` |
| 8 | Quản lý tài khoản: xem, thêm, xóa nhân viên, đặt lại mật khẩu | `quanLyTaiKhoan()` |
| 9 | Đổi mật khẩu | `doiMatKhau()` |
| 0 | Đăng xuất | |

**Khách hàng** (màn hình mặc định, không cần đăng nhập, chỉ xem):

| Lựa chọn | Chức năng | Hàm |
|---|---|---|
| 1 | Xem bảng giá gửi xe | `hienThiBangGia()` |
| 2 | Xem số chỗ trống hiện tại của từng khu | `hienThiChoTrong()` |
| 3 | Tra cứu xe của mình theo mã thẻ hoặc biển số (dùng khi quên mã thẻ) | `traCuuXe()` |
| 9 | Đăng nhập nhân viên / quản trị | `dangNhap()` |
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
| Xe máy | 5.000 VNĐ (mặc định) |
| Ô tô | 10.000 VNĐ (mặc định) |

Quản trị có thể sửa đơn giá ở menu quản trị, mục 7. Giá mới được lưu vào `cauhinh.txt`.

Công thức: `g = ceil(t)`, nếu `g <= 2` thì phí = 0, ngược lại phí = `(g - 2) × đơn giá`.

## Thuật toán chính

- **BFS tìm ô trống gần cổng nhất:** duyệt theo hàng đợi từ ô cổng (0,0), thứ tự hướng lên – xuống – trái – phải; độ phức tạp O(R × C).
- **Cấu trúc dữ liệu:** hai ma trận `gridOTo`, `gridXeMay` (0: trống, 1: có xe); mảng `danhSachThe` lưu từng lượt gửi bằng `struct TheXe`.
- **Thời gian thực:** `time`, `difftime`, `localtime`, `strftime`.

## Lưu dữ liệu giữa các lần chạy

| Tệp | Nội dung |
|---|---|
| `bai_xe.dat` | Danh sách xe, số lượt hoàn thành và doanh thu (ghi nhị phân bằng `fwrite`, mỗi lần xe vào/ra). Lần chạy sau đọc lại bằng `fread` và dựng lại sơ đồ bãi |
| `taikhoan.txt` | Tên đăng nhập, mật khẩu, vai trò |
| `cauhinh.txt` | Giá gửi xe máy và ô tô |
| `lich_su_bai_xe.txt` | Lịch sử ra vào (xem bên dưới) |

Các tệp này được tạo khi chạy và nằm trong `.gitignore`. Nếu `bai_xe.dat` bị hỏng, chương trình báo cảnh báo và bắt đầu với bãi trống.

## Tệp lịch sử

Mỗi lượt xe ra được ghi thêm một dòng vào `lich_su_bai_xe.txt` (chế độ `"a"`), gồm mã thẻ, biển số, loại xe, giờ vào, giờ ra và phí. Quản trị chọn mục 6 để đọc lại toàn bộ tệp (chế độ `"r"`). Ví dụ một dòng:

```
Ma the: P1 | Bien so: 29A-111.11 | Loai: O to | Vao: 2026-10-24 11:38:23 | Ra: 2026-10-24 14:48:23 | Phi: 20000 VND
```

## Nhập liệu an toàn

- Đăng nhập: nhập sai quá 3 lần thì quay lại màn hình chính; mật khẩu mới phải từ 4 ký tự; không xóa được tài khoản quản trị hay chính mình.
- Menu: nhập chữ không làm chương trình lặp vô hạn (`clearInputBuffer` bỏ phần thừa của dòng); gặp hết dữ liệu nhập thì chương trình thoát.
- Mã thẻ và biển số đọc bằng `scanf("%19s", ...)` (tối đa 19 ký tự, vừa mảng `char[20]`) nên không ghi tràn bộ nhớ.
- Không cho hai xe đang trong bãi cùng biển số; phần số có dấu chấm chỉ đúng dạng `123.45`.
- Chương trình không dùng cấp phát động (`malloc`/`free`) nên không có rò rỉ bộ nhớ.

## Kết quả thử nghiệm

Đã kiểm thử 18 ca (TC01–TC18) gồm xe vào/ra hợp lệ, thẻ trùng, loại xe sai, biển số sai, bãi đầy, các ca biên về phí (đúng 2 giờ, hơn 2 giờ một giây). Chi tiết trong Chương 4 của báo cáo.

## Hạn chế đã biết

- Tối đa 100 xe cùng lúc trong danh sách (`MAX_XE`); bản ghi xe đã ra được dọn tự động khi nạp dữ liệu hoặc khi danh sách đầy, nên không giới hạn số lượt về lâu dài.
- Mật khẩu lưu dạng văn bản thường trong `taikhoan.txt`, chưa mã hóa (phạm vi môn học).
- Khách hàng tra cứu bằng mã thẻ hoặc biển số, không có tài khoản riêng; xe ra bãi vẫn bắt buộc quét mã thẻ.
- Mã thẻ dài hơn 19 ký tự bị cắt còn 19 ký tự đầu.

Chi tiết trong mục 4.3.2 của báo cáo.
