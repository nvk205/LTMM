# Phép Nhân Đa Thức Trong Trường Hữu Hạn GF(2^4)


---

## Cơ sở lý thuyết

### 1. Trường hữu hạn $GF(2^4)$ là gì?
$GF(2^4)$ là một trường hữu hạn chứa $2^4 = 16$ phần tử. Mỗi phần tử trong trường này được biểu diễn dưới dạng một đa thức có hệ số là 0 hoặc 1 (thuộc $GF(2)$) và bậc lớn nhất cho phép là 3.

**Ví dụ về cách biểu diễn:**
*   Đa thức: $A(x) = x^3 + x$
*   Nhị phân 4-bit: `1010`
*   Thập phân: `10`
*   Hexadecimal (Hệ 16): `0xA`

### 2. Các phép toán cơ bản
*   **Phép cộng / trừ:** Trong $GF(2^n)$, phép cộng và phép trừ hoàn toàn giống nhau và tương đương với phép toán **XOR** từng bit (không có nhớ). 
    *   *Ví dụ:* $x^3 + x^3 = 0$ (vì $1 \oplus 1 = 0$).
*   **Đa thức tối giản (Irreducible Polynomial):** Đóng vai trò giống như một "số nguyên tố". Mọi phép nhân nếu sinh ra đa thức có bậc $\ge 4$ đều phải được hạ bậc bằng cách chia lấy dư (modulo) cho đa thức tối giản này.
    *   Trong chương trình, ta sử dụng đa thức chuẩn: $m(x) = x^4 + x + 1$
    *   Mã nhị phân: `10011` (Thập phân: `19`, Hex: `0x13`).

---

## Thuật toán nhân (Shift & XOR)

Để nhân hai phần tử $a$ và $b$, máy tính không nhân chéo như toán học thông thường mà sử dụng thuật toán **Dịch bit (Shift)** và **Cộng (XOR)** cực kỳ tối ưu qua 4 vòng lặp (vì ở đây là $GF(2^4)$):

1.  **Kiểm tra bit cuối của $b$:** Nếu bit ngoài cùng bên phải của $b$ bằng `1`, ta cộng (XOR) giá trị hiện tại của $a$ vào kết quả (`result`).
2.  **Nhân $a$ với $x$ (Dịch trái):** Đẩy tất cả các bit của $a$ sang trái 1 vị trí (`a << 1`).
3.  **Hạ bậc (Modulo):** Nếu $a$ vừa bị dịch trái chạm mốc bậc 4 (tức là bit thứ 4 bị bật thành `1`, giá trị $\ge 16$), ta phải khử nó đi bằng cách cho $a$ XOR với đa thức tối giản $m(x)$.
4.  **Dịch phải $b$:** Đẩy $b$ sang phải 1 bit (`b >> 1`) để loại bỏ bit vừa xét, chuẩn bị vòng lặp tiếp theo.

---

## Cấu trúc Code và Các hàm sử dụng


### 1. Hàm `mul()` 
```c
uint8_t mul(uint8_t a, uint8_t b, uint8_t mod)
```
*   **Đầu vào:**
    *   `a`, `b`: Hai số nguyên 8-bit đại diện cho 2 đa thức cần nhân (giá trị từ `0` đến `15`).
    *   `mod`: Đa thức tối giản dùng để hạ bậc (thường là `19`).
*   **Xử lý:** Chạy 4 vòng lặp thực hiện chính xác Thuật toán Shift & XOR đã mô tả ở trên. Kết thúc vòng lặp sẽ dùng mặt nạ `& 0x0F` để đảm bảo kết quả nằm gọn trong 4 bit.
*   **Đầu ra:** Trả về kết quả của phép nhân.

### 2. Cấu trúc `test_vecto`
```c
typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t mod;
} test_vecto;
```
*   Một cấu trúc dữ liệu (`struct`) dùng để đóng gói một "đề bài" kiểm thử gồm 3 tham số. Giúp cho việc chạy tự động nhiều test case trở nên gọn gàng.

### 3. Hàm `main()`
*   Khởi tạo một mảng (`Array`) chứa 5 bộ `test_vecto` tiêu biểu (nhân bình thường, nhân gây tràn bậc, nhân với phần tử nghịch đảo...).
*   Dùng một vòng lặp `for` để duyệt qua từng bộ test, gọi hàm `mul()` và dùng hàm `printf()` để in kết quả ra màn hình dưới dạng số Thập phân (`%d`) và số Hex (`%X`).

---

**Ví dụ Kết quả (Output):**
```text
--- KET QUA 5 TEST VECTORS ---

Test 1: a = 10 (0xA), b =  5 (0x5), mod = 19 -> KET QUA =  4 (0x4)
Test 2: a =  2 (0x2), b =  3 (0x3), mod = 19 -> KET QUA =  6 (0x6)
Test 3: a =  8 (0x8), b =  2 (0x2), mod = 19 -> KET QUA =  3 (0x3)
Test 4: a =  5 (0x5), b = 11 (0xB), mod = 19 -> KET QUA =  1 (0x1)
Test 5: a = 15 (0xF), b = 15 (0xF), mod = 19 -> KET QUA = 10 (0xA)
```