# ĐT19: Hệ Thống Quản Lý Bãi Đỗ Xe Ô Tô & Xe Máy Thông Minh

Dự án Bài tập lớn môn **Kỹ thuật Lập trình C** ứng dụng cấu trúc ma trận 2 chiều kết hợp kỹ thuật quản lý bộ nhớ động nâng cao.

## 🛠️ Hướng dẫn Biên dịch và Khởi chạy

Giáo viên có thể sử dụng trình biên dịch **GCC** chuẩn để chạy dự án:

### Bước 1: Biên dịch mã nguồn mã sạch lỗi
```bash
gcc -Wall main.c parking.c -o hethong_baixe
```

### Bước 2: Chạy chương trình ứng dụng
```bash
./hethong_baixe
```

---

## 📌 GHI CHÚ QUAN TRỌNG DÀNH CHO GIÁO VIÊN CHẤM BÀI (NOTES)

Kính gửi Thầy/Cô, để đạt điểm tối ưu cho toàn bộ tiêu chuẩn nghiệm thu từ YC01 đến YC04, nhóm đã tối ưu mã nguồn theo các giải pháp:

1. **Mô phỏng thời gian thực:** Để Thầy/Cô tiện test, hệ thống quy ước **1 giây thực tế = 1 giờ gửi xe**. Thầy/Cô chỉ cần đợi 2-3 giây sau khi Check-in là có thể thử nghiệm được ngay biểu phí bậc giờ.
2. **Tính toán tiền gửi theo bậc giờ (ĐT19):** Hệ thống tự động áp dụng bậc giờ giảm dần: Xe máy (2h đầu: 5k/h, giờ sau: 3k/h); Ô tô (2h đầu: 20k/h, giờ sau: 15k/h).
3. **Thống kê dữ liệu ca trực nâng cao (ĐT19):** Chức năng số 4 sẽ tự động mở file, bóc tách chuỗi dữ liệu lịch sử để tính toán tổng doanh thu và đếm số lượng phân loại xe ra vào thực tế.
4. **An toàn bộ nhớ, chống Memory Leak & SegFault (YC04):** Nhóm không dùng mảng cố định mà sử dụng cơ chế cấp phát động linh hoạt bằng con trỏ cấp 2 kết hợp `realloc()`. Toàn bộ bộ nhớ được giải phóng sạch bằng lệnh `free()` ở cuối hàm `main` trước khi thoát chương trình.
