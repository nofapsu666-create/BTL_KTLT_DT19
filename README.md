# ĐỒ ÁN KỸ THUẬT LẬP TRÌNH — ĐỀ TÀI ĐT19
## Hệ thống Quản lý Bãi đỗ xe Ô tô & Xe máy Thông minh

Hệ thống điều hướng quản lý bãi xe thời gian thực bằng ngôn ngữ C tiêu chuẩn. Chương trình ứng dụng mô hình lưu trữ cấu trúc dữ liệu mảng 2 chiều tĩnh (Ma trận vùng đỗ), cơ chế quản lý tệp tin và đồng bộ thời gian thực từ hệ thống giúp tối ưu hóa công tác vận hành ca trực đỗ xe.

---

## 📁 1. Cấu trúc Kiến trúc Hệ thống (4 File)

Dự án được phân rã thành mô hình 4 file độc lập chức năng nhằm tăng tính module hóa, dễ bảo trì và nâng cấp:

1. **`quanlybaixe.h` (File tiêu đề chung)**
   - Khai báo các thư viện chuẩn (`<stdio.h>`, `<stdlib.h>`, `<time.h>`, `<string.h>`).
   - Định nghĩa các hằng số kích thước cấu hình bãi đỗ (`MAX_HANG_OTO`, `MAX_COT_OTO`, v.v.).
   - Định nghĩa cấu trúc dữ liệu thẻ xe `struct TheXe` tích hợp biển số, loại xe, mốc giờ vào và trạng thái ô đỗ.
   - Chứa toàn bộ nguyên mẫu hàm (Function prototypes) của dự án.

2. **`main.c` (Luồng điều khiển chính & Lưu trữ)**
   - Khai báo khởi tạo hai ma trận bãi xe đại diện cho khu vực Ô tô và Xe máy.
   - Xây dựng vòng lặp Menu tương tác bằng cấu trúc kiểm soát chọn lựa `switch-case`.
   - Chịu trách nhiệm đồng bộ dữ liệu: Đọc lịch sử file `lich_su.txt` khi khởi động để khôi phục doanh thu và Ghi lịch sử mỗi khi có lượt xe trả bãi thành công.

3. **`xuly.c` (Khối xử lý logic thuật toán)**
   - **Check-in (Xe vào):** Thuật toán quét ma trận để tìm tọa độ ô trống `[i][j]` gần nhất (ưu tiên hàng thấp trước).
   - **Check-out (Xe ra):** Định vị phương tiện bằng cơ chế so khớp chuỗi `strcmp()`. Tính toán thời gian thực đỗ bằng hàm chuẩn `difftime()`.
   - **Tính phí bậc thang:** Thuật toán lũy tiến tự động phân loại mức giá:
     * *Xe máy:* 2 giờ đầu cố định 5.000 VND, mỗi giờ tiếp theo +2.000 VND/h.
     * *Ô tô:* 2 giờ đầu cố định 20.000 VND, mỗi giờ tiếp theo +10.000 VND/h.
   - **Giải phóng bộ nhớ:** Reset trạng thái ô đỗ về trống (`trangThai = 0`) xóa sạch biển số tránh dữ liệu rác.

4. **`hienthi.c` (Giao diện đồ họa console)**
   - Trực quan hóa sơ đồ bãi đỗ dạng đồ họa ký tự (`[X]` tức ô đã có xe chiếm chỗ, `[ ]` là chỗ trống an toàn).
   - Xuất báo cáo ca trực: Đếm tổng số xe đang gửi, tính toán dung lượng trống còn lại, cập nhật doanh thu.
   - Định dạng chuỗi thời gian: Ép kiểu dữ liệu hệ thống `time_t` sang định dạng chuỗi thân thiện `dd/mm/yyyy hh:mm:ss` thông qua hàm `strftime()`.

---

## 🛠️ 2. Hướng dẫn Biên dịch và Triển khai trên Dev-C++

Do dự án được cấu trúc theo dạng nhiều file liên kết (Multi-file project), việc biên dịch bắt buộc phải gom cụm thông qua tính năng Project của IDE. Bạn làm theo các bước click chuột sau:

1. **Khởi tạo Project:** Mở Dev-C++ -> Chọn `File` -> `New` -> `Project...`
2. **Cấu hình thuộc tính:** Chọn `Console Application`, tick chọn ngôn ngữ `C Project`, đặt tên dự án là `BTL_KTLT`, sau đó bấm `OK` và chọn thư mục lưu trữ.
3. **Tích hợp mã nguồn:** 
   - Click chuột phải vào tên Project ở thanh Sidebar bên trái -> Chọn `Add to Project`.
   - Lần lượt thêm cả 4 file `quanlybaixe.h`, `main.c`, `xuly.c`, `hienthi.c` vào dự án.
4. **Thực thi:** Nhấn phím **`F11`** (hoặc chọn `Execute` -> `Compile & Run`) để trình biên dịch GCC liên kết các file thành tệp thực thi `.exe` duy nhất.

---

## ⚙️ 3. Quy trình Thử nghiệm & Chế độ Giả lập (Test Mode)

Để thuận tiện cho công tác chấm điểm và kiểm thử (Mặc định thời gian đỗ tính theo đơn vị giờ, nếu xe vừa vào rồi ra ngay thì khoảng cách thời gian bằng 0 giây, dẫn đến việc hóa đơn hiển thị 0 VND):

* **Tính năng Giả lập thông minh (Test Mode):** Trong hàm `CheckOut` tại file `xuly.c`, hệ thống đã được cài đặt bộ lọc: Nếu thời gian thực tế từ lúc bấm Check-in đến lúc bấm Check-out **nhỏ hơn 10 giây**, hệ thống tự động kích hoạt chế độ đỗ giả lập **2.5 giờ**.
* **Mục đích:** Giúp giảng viên kiểm thử ngay lập tức độ chính xác của **Thuật toán tính phí bậc thang lũy tiến** (2.5 giờ đỗ sẽ vượt qua ngưỡng 2 giờ đầu, kích hoạt mức giá bậc hai) mà không bắt người kiểm thử phải chờ đợi hàng tiếng đồng hồ ngoài đời thực.

---

## 💾 4. Cơ chế Quản lý Tệp tin (`lich_su.txt`)

Dữ liệu doanh thu và lịch sử ra vào bãi được quản lý bền vững theo cơ chế:
- **Ghi File (`"a"` - Append Mode):** Mỗi lượt xe checkout thành công, dữ liệu thô bao gồm `BienSo TimeVao TimeRa ThanhTien` được ghi nối tiếp vào cuối file `lich_su.txt`.
- **Đọc File (`"r"` - Read Mode):** Khi tắt chương trình đi và khởi động lại, hàm `DocLichSu` sẽ tự động quét toàn bộ file từ dòng đầu đến dòng cuối, cộng dồn toàn bộ số tiền cũ để thiết lập lại tổng doanh thu ca trực, tránh hiện tượng mất mát dữ liệu khi hệ thống gặp sự cố mất điện hoặc reset.
