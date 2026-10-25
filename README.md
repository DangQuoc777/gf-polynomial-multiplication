# Nhân hai đa thức trong GF(2^4) và GF(2^8)

Bài thực hành lập trình C: nhân hai đa thức trên trường hữu hạn nhị phân bằng phương pháp **Shift-and-XOR**, sau đó rút gọn theo đa thức tối giản (đa thức bất khả quy).

## 1. Đa thức tối giản

| Trường | Đa thức m(x) | Hex | Miền đầu vào |
| --- | --- | --- | --- |
| GF(2^4) | x^4 + x + 1 | `0x13` | `0x0` đến `0xF` |
| GF(2^8) | x^8 + x^4 + x^3 + x + 1 | `0x11B` | `0x00` đến `0xFF` |

Mỗi bit là hệ số của một lũy thừa x. Ví dụ `0xB` = `1011₂` biểu diễn `x^3 + x + 1`.

## 2. Nguyên lý giải thuật

Trong GF(2), phép cộng và trừ đều là XOR (`1 + 1 = 0`). Để tính `a * b mod m(x)`:

1. Khởi tạo kết quả `kq = 0`.
2. Nếu bit thấp nhất của `b` bằng 1, tính `kq ^= a`.
3. Dịch trái `a` một bit (`a <<= 1`) để nhân với x.
4. Nếu `a` xuất hiện bit bậc 4 hoặc 8, XOR với `0x13` hoặc `0x11B` tương ứng để lấy phần dư.
5. Dịch phải `b` (`b >>= 1`). Lặp 4 lần trong GF(2^4), 8 lần trong GF(2^8).

**Lưu ý:** Nhân trong GF(2^n) không phải phép nhân số nguyên thông thường. Kết quả vẫn nằm trong n bit sau phép chia lấy dư.

## 3. Cấu trúc mã nguồn

```text
gf-polynomial-multiplication/
├── main.c            # Giao diện nhập và in kết quả
├── gf.c              # Hai hàm nhân trong GF(2^4), GF(2^8)
├── gf.h              # Khai báo hàm
├── tests/
│   └── test_gf.c     # Kiểm tra tất cả các cặp đầu vào
├── .gitignore
└── README.md
```

## 4. Biên dịch và chạy

Yêu cầu: trình biên dịch C hỗ trợ C11 (ví dụ GCC / MinGW-w64).

**Windows (PowerShell, CMD hoặc terminal của VS Code):**

```bash
gcc -std=c11 -Wall -Wextra main.c gf.c -o gf_mul.exe
.\gf_mul.exe
```

**Linux / macOS:**

```bash
gcc -std=c11 -Wall -Wextra main.c gf.c -o gf_mul
./gf_mul
```

Nhập dữ liệu ở hệ 16, không bắt buộc thêm tiền tố `0x`.

Ví dụ:

```text
=== NHAN HAI DA THUC TRONG GF(2^4) ===
Da thuc toi gian: m(x) = x^4 + x + 1 (0x13)
Nhap A (hex, 0..F; vi du B): B
Nhap B (hex, 0..F; vi du 7): 7
Ket qua: 0xB * 0x7 = 0x4

=== NHAN HAI DA THUC TRONG GF(2^8) ===
Da thuc toi gian: m(x) = x^8 + x^4 + x^3 + x + 1 (0x11B)
Nhap A (hex, 00..FF; vi du 57): 57
Nhap B (hex, 00..FF; vi du 83): 83
Ket qua: 0x57 * 0x83 = 0xC1
```

Chương trình báo lỗi nếu nhập giá trị không hợp lệ hoặc vượt ngoài phạm vi trường.

## 5. Kiểm thử

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic tests/test_gf.c gf.c -o test_gf
./test_gf
```

Trên Windows, có thể đặt tên `test_gf.exe` và chạy `.\test_gf.exe`.

Chương trình kiểm thử so sánh kết quả hàm chính với phép nhân đa thức và chia dư độc lập. Bao gồm tất cả **256 cặp** trong GF(2^4) và **65.536 cặp** trong GF(2^8), tổng **65.792 phép thử**.

## 6. Đưa lên GitHub

1. Đăng nhập GitHub bằng tài khoản cá nhân; cập nhật **Profile → Name** thành họ tên thật theo yêu cầu giảng viên.
2. Tạo repository mới, ví dụ `gf-polynomial-multiplication`, chọn **Public** nếu giảng viên cần mở liên kết để chấm.
3. Không chọn thêm README hoặc .gitignore trong lúc tạo nếu định `push` toàn bộ thư mục này từ máy.
4. Mở terminal ngay trong thư mục dự án và chạy:

```bash
git init
git add .
git commit -m "Implement GF(2^4) and GF(2^8) polynomial multiplication"
git branch -M main
git remote add origin https://github.com/DangQuoc777/gf-polynomial-multiplication.git
git push -u origin main
```

Lệnh trên dùng username GitHub đã kết nối là `DangQuoc777`. Chỉ nộp URL sau khi đã tạo repository và `git push` thành công. Nếu cần hiện đúng họ tên trong lịch sử commit, đặt `git config user.name "HO_TEN_THAT"` và `git config user.email "EMAIL_GITHUB_CUA_BAN"` trước khi commit.
