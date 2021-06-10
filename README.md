# Gtk tutorial by Glade with C language
Các ví dụ cơ bản để làm quen với tạo đồ họa `gtk` bằng công cụ glade với ngôn ngữ `C`
# Biên dịch chương trình
Các ví dụ sử dụng công cụ `Cmake` và `ninja` để biên dịch, bạn cần cài đặt `Cmake` và `ninja` để biên dịch\
khi đã đầy đủ công cụ hãy `clone` về máy bằng lênh:\
(Bạn phải cài đặt `git` trong thiết bị để thực thi lệnh duới đây)
```
git clone https://github.com/LeVDuan/Gtk_tutorial_C.git
```
Đi đến thư mục ví dụ mà bạn muốn biên dịch\
ví dụ muốn biên dịch trong folder `about_dialog`:

```
cd Gtk_tutorial_C/about_dialog/b
```
tại thư mục `b` gõ lệnh sau:
``` 
./ninja
./about_dialog
```
# Nguồn: 
[GTK Glade C Programming Tutorial](https://prognotes.net/gtk-glade-c-programming/)
