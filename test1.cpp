#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

string layThoiGianHeThong()
{
    time_t now = time(0);      // Lấy thời gian hiện tại (số giây từ 1/1/1970)
    tm *ltm = localtime(&now); // Chuyển sang múi giờ địa phương

    stringstream ss;                                          // Tạo stringstream để định dạng
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"      // Ngày
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "/" // Tháng (+1 vì tm_mon từ 0-11)
       << 1900 + ltm->tm_year << " "                          // Năm (+1900 vì tm_year tính từ 1900)
       << setfill('0') << setw(2) << ltm->tm_hour << ":"      // Giờ
       << setfill('0') << setw(2) << ltm->tm_min << ":"       // Phút
       << setfill('0') << setw(2) << ltm->tm_sec;             // Giây
    return ss.str();                                          // Trả về chuỗi đã định dạng
}
class GiaoDich
{
protected:
    string loai;
    string maSP;
    int soLuong;
    string thoiGian;

public:
    GiaoDich() {}; // Constructor mặc định
    GiaoDich(const string &loai, const string &maSP, int soLuong) : loai(loai), maSP(maSP), soLuong(soLuong)
    {
        this->thoiGian = layThoiGianHeThong(); // Khởi tạo thời gian khi tạo giao dịch
    }

    virtual void thuchien() = 0; // Phương thức thuần ảo (phải được triển khai bởi lớp con)

    virtual void hienthithongtin() // Hiển thị thông tin giao dịch (có thể ghi đè)
    {
        cout << "Loai giao dich : " << loai << endl;
        cout << "Ma san pham : " << maSP << endl;
        cout << "So luong san pham: " << soLuong << endl;
        cout << "Thoi gian giao dich : " << thoiGian << endl;
    }
    virtual ~GiaoDich() {} // Destructor ảo
};

void nhapsonguyen(string a, int &b) // Hàm nhập số nguyên với kiểm tra
{
    while (true) // Vòng lặp vô hạn đến khi nhập đúng
    {
        string gt;
        cout << "nhap " << a << " : ";
        getline(cin, gt);
        if (gt.empty() || gt == "0") // Cho phép bỏ qua bằng cách nhập trống hoặc 0
        {
            break;
        }
        try // Bắt lỗi chuyển đổi
        {
            int t = stoi(gt); // Chuyển string sang int
            if (t > 0)        // Kiểm tra số dương
            {
                b = t;
                break;
            }
            else
            {
                cout << a << " phai lon hon 0" << endl;
            }
        }
        catch (const invalid_argument &e) // Bắt lỗi chuyển đổi không hợp lệ
        {
            cout << "gia tri khong hop le.Vui long nhap lai ";
            cout << endl;
        }
        catch (const out_of_range &e) // Bắt lỗi số quá lớn
        {
            cout << "So qua lon! Vui long nhap lai mot gia tri hop le." << endl;
        }
    }
}

void ghiLichSuGiaoDich(const string &loai, const string &ma, const int &sl) // Ghi giao dịch vào file
{
    ofstream file("lichsugiaodich.txt", ios::app); // Mở file ở chế độ append
    if (!file)                                     // Kiểm tra mở file thành công
    {
        cout << "khong the mo lich su giao dich" << endl;
        return;
    }
    file << loai << ",ma:" << ma << ",so luong:" << sl << ",thoi gian:" << layThoiGianHeThong() << endl; // Ghi dữ liệu
    file.close();                                                                                        // Đóng file
}

void donFile(const string &filecanxoa) // Xóa nội dung file
{
    ofstream file(filecanxoa, ios::trunc); // Mở file ở chế độ trunc (xóa nội dung cũ)
    if (!file)                             // Kiểm tra mở file thành công
    {
        cout << "Khong the mo tep ";
        return;
    }
    file.close(); // Đóng file
}

void hienthilichsuGiaodich() // Hiển thị lịch sử giao dịch
{
    ifstream file("lichsugiaodich.txt"); // Mở file để đọc
    if (!file)                           // Kiểm tra mở file thành công
    {
        cout << "Khong the mo tep " << endl;
        return;
    }
    string dl;                // Biến lưu dòng đọc được
    while (getline(file, dl)) // Đọc từng dòng
    {
        cout << dl << endl; // In ra màn hình
    }
    file.close(); // Đóng file
}
class Laptop
{
private:
    // Các thuộc tính của laptop
    string ma;       // Mã sản phẩm
    string hang;     // Hãng sản xuất
    string ten;      // Tên sản phẩm
    string card;     // Card đồ họa
    string chatlieu; // Chất liệu
    string cpu;      // CPU
    int ram;         // RAM (GB)
    int khoiluong;   // Khối lượng (kg)
    int gia;         // Giá tiền (VND)

public:
    Laptop() : ma(""), hang(""), ten(""), card(""), chatlieu(""), cpu(""), ram(0), khoiluong(0), gia(0) {} // Constructor mặc định

    Laptop(string ma, string hang, string ten, string card, string chatlieu, string cpu, int ram, int khoiluong, int gia) // Constructor với tham số
    {
        // Gán giá trị cho các thuộc tính
        this->hang = hang;
        this->ma = ma;
        this->ten = ten;
        this->card = card;
        this->chatlieu = chatlieu;
        this->gia = gia;
        this->ram = ram;
        this->cpu = cpu;
        this->khoiluong = khoiluong;
    }

    void nhap() // Nhập thông tin laptop từ bàn phím
    {
        cout << "Nhap hang: ";
        getline(cin, hang);
        cout << "Nhap ten: ";
        getline(cin, ten);
        cout << "Nhap card: ";
        getline(cin, card);
        cout << "Nhap chat lieu: ";
        getline(cin, chatlieu);
        cout << "Nhap cpu: ";
        getline(cin, cpu);
        nhapsonguyen("ram", ram);              // Nhập RAM với kiểm tra
        nhapsonguyen("khoi luong", khoiluong); // Nhập khối lượng
        nhapsonguyen("gia", gia);              // Nhập giá
    }

    virtual void hienthithongtin() const // Hiển thị thông tin laptop
    {
        // In thông tin với định dạng cột
        cout << left << setw(15) << "Ma:" << ma << endl;
        cout << left << setw(15) << "Hang:" << hang << endl;
        cout << left << setw(15) << "Ten:" << ten << endl;
        cout << left << setw(15) << "Card:" << card << endl;
        cout << left << setw(15) << "Chat lieu:" << chatlieu << endl;
        cout << left << setw(15) << "CPU:" << cpu << endl;
        cout << left << setw(15) << "Ram:" << ram << " GB" << endl;
        cout << left << setw(15) << "Khoi luong:" << khoiluong << " kg" << endl;
        cout << left << setw(15) << "Gia tien:" << gia << " VND" << endl;
    }

    // Các getter và setter
    string getHang() const { return hang; }
    string getMa() const { return ma; }
    string getTen() const { return ten; }
    string getCard() const { return card; }
    string getChatlieu() const { return chatlieu; }
    int getGia() const { return gia; }
    int getRam() const { return ram; }
    string getCpu() const { return cpu; }
    int getKhoiluong() const { return khoiluong; }
    void setma(const string &m) { ma = m; }
};
class KhoLaptop
{
private:
    vector<Laptop> dslaptop;               // Danh sách laptop
    unordered_map<string, Laptop> danhMuc; // Ánh xạ mã sản phẩm -> thông tin laptop
    unordered_map<string, int> TonKho;     // Ánh xạ mã sản phẩm -> số lượng tồn kho

public:
    const vector<Laptop> &getdsLaptop() const // Lấy danh sách laptop
    {
        return dslaptop; // Trả về vector
    }

    void hienthidanhsachlaptop() // Hiển thị toàn bộ danh sách
    {
        for (auto lap : dslaptop) // Duyệt qua từng laptop
        {
            lap.hienthithongtin(); // Hiển thị thông tin
            cout << left << setw(15) << "So luong:" << getTonKho(lap.getMa()) << " cai" << endl;
            cout << "-----------------------------\n";
        }
    }

    void hienthiLaptop() // Hiển thị laptop theo mã
    {
        const vector<Laptop> &lap = getdsLaptop();
        cout << "Nhap ma laptop muon tim kiem : ";
        string ma;
        getline(cin, ma);
        if (!ktma(ma)) // Kiểm tra mã có tồn tại
        {
            cout << "Khong ton tai ma laptop la " << ma << endl;
            return;
        }
        else
        {
            for (auto &lap : getdsLaptop()) // Duyệt danh sách
            {
                if (lap.getMa() == ma) // Nếu tìm thấy
                {
                    lap.hienthithongtin(); // Hiển thị thông tin
                    cout << left << setw(15) << "So luong:" << getTonKho(lap.getMa()) << " cai" << endl;
                }
            }
        }
    }
    bool xuatkho(const string &ma, int soluong) // Kiểm tra có thể xuất kho
    {
        if (TonKho[ma] < soluong) // Nếu số lượng tồn ít hơn số lượng muốn xuất
        {
            return false; // Không đủ để xuất
        }
        TonKho[ma] -= soluong; // Giảm số lượng tồn kho
        return true;           // Xuất thành công
    }

    void nhapKho(const Laptop &lap, int soluong) // Nhập laptop vào kho
    {
        dslaptop.push_back(lap);        // Thêm vào danh sách
        TonKho[lap.getMa()] += soluong; // Tăng số lượng tồn kho
    }

    void capnhatsoluong(const string &ma, int sl) // Cập nhật số lượng
    {
        TonKho[ma] += sl; // Thêm số lượng mới vào tồn kho
    }

    int getTonKho(const string &ma) // Lấy số lượng tồn kho theo mã
    {
        auto it = TonKho.find(ma); // Tìm kiếm trong map
        if (it != TonKho.end())    // Nếu tìm thấy
        {
            return it->second; // Trả về số lượng
        }
        return 0; // Không tìm thấy trả về 0
    }

    bool ktma(const string &ma) // Kiểm tra mã có tồn tại
    {
        return TonKho.count(ma) == 1; // Đếm số lần xuất hiện (0 hoặc 1)
    }

    bool themSanPham(const Laptop &lap) // Thêm sản phẩm mới
    {
        if (danhMuc.count(lap.getMa())) // Nếu mã đã tồn tại
        {
            return false; // Không thêm được
        }
        danhMuc[lap.getMa()] = lap; // Thêm vào danh mục
        TonKho[lap.getMa()] = 0;    // Khởi tạo số lượng tồn = 0
        return true;                // Thêm thành công
    }

    void xoaSanPham() // Xóa sản phẩm
    {
        string ma;
        cout << "Nhap ma San Pham muon xoa : ";
        getline(cin, ma);
        if (ktma(ma)) // Nếu mã tồn tại
        {
            danhMuc.erase(ma);                                      // Xóa khỏi danh mục
            TonKho.erase(ma);                                       // Xóa khỏi tồn kho
            for (auto it = dslaptop.begin(); it != dslaptop.end();) // Duyệt vector
            {
                if (it->getMa() == ma) // Tìm laptop có mã trùng
                {
                    it = dslaptop.erase(it); // Xóa khỏi vector
                }
                else
                {
                    ++it; // Tiếp tục duyệt
                }
            }
            cout << "XOA SAN PHAM THANH CONG" << endl;
        }
        else
        {
            cout << "Khong ton tai ma san pham la " << ma << endl;
        }
    }

    void donKho() // Dọn kho (xóa toàn bộ)
    {
        dslaptop.clear(); // Xóa danh sách
        TonKho.clear();   // Xóa tồn kho
        danhMuc.clear();  // Xóa danh mục
        cout << "DA DON KHO LAPTOP" << endl;
    }

    void capnhatFile() // Cập nhật dữ liệu vào file
    {
        ofstream file("laptop_data.txt", ios::trunc); // Mở file, xóa nội dung cũ
        const vector<Laptop> &laptop = getdsLaptop();

        if (!file) // Kiểm tra mở file
        {
            cout << "Khong the mo tep ";
            return;
        }
        for (const auto &lap : laptop) // Duyệt danh sách
        {
            // Ghi thông tin từng laptop vào file, cách nhau bởi dấu phẩy
            file << "Ma:" << lap.getMa() << ",Hang:"
                 << lap.getHang() << ",Ten:"
                 << lap.getTen() << ",Card:"
                 << lap.getCard() << ",Chat lieu:"
                 << lap.getChatlieu() << ",CPU:"
                 << lap.getCpu() << ",Ram:"
                 << lap.getRam() << ",Khoi luong:"
                 << lap.getKhoiluong() << ",Gia:"
                 << lap.getGia() << ",So luong"
                 << getTonKho(lap.getMa()) << endl;
        }
        file.close(); // Đóng file
    }

    void suaSanPham() // Sửa thông tin sản phẩm
    {
        string ma;
        cout << "nhap ma san pham can sua : ";
        getline(cin, ma);
        if (ktma(ma)) // Kiểm tra mã tồn tại
        {
            for (auto &lap : dslaptop) // Duyệt danh sách
            {
                if (lap.getMa() == ma) // Tìm laptop cần sửa
                {
                    lap.nhap(); // Gọi phương thức nhập để sửa
                }
            }
        }
        else
        {
            cout << "Khong ton tai ma san pham la " << ma << endl;
        }
    }
};
class NhapKho : public GiaoDich
{
private:
    KhoLaptop &kho;  // Tham chiếu đến kho laptop
    string ngayNhap; // Ngày nhập
    int soLuong;     // Số lượng nhập

public:
    NhapKho(KhoLaptop &k) : GiaoDich("nhap", "", 0), kho(k) {} // Constructor

    int getSoLuong() { return soLuong; } // Getter số lượng

    void thuchien() override // Triển khai phương thức ảo
    {

        cout << "Nhap so luong laptop: ";
        string sl;
        getline(cin, sl);
        soLuong = stoi(sl);               // Chuyển string sang int
        for (int i = 0; i < soLuong; i++) // Nhập từng laptop
        {
            Laptop lap;
            cout << "Nhap thong tin laptop thu " << i + 1 << ":" << endl;
            cout << "nhap ma : ";
            string m;
            getline(cin, m);
            if (kho.getTonKho(m) == 0) // Nếu mã chưa tồn tại
            {
                lap.setma(m); // Gán mã
                lap.nhap();   // Nhập thông tin
                int sl;
                cout << "nhap so luong laptop cua ma " << lap.getMa() << " : ";
                cin >> sl;
                cin.ignore();
                ghiLichSuGiaoDich("NHAP", m, sl); // Ghi vào lịch sử
                kho.nhapKho(lap, sl);             // Nhập vào kho
                kho.capnhatFile();                // Cập nhật file
            }
            else // Nếu mã đã tồn tại
            {
                int sl;
                cout << "ma laptop da ton tai, cap nhat so luong : ";
                cin >> sl;
                cin.ignore();
                kho.capnhatsoluong(m, sl);        // Chỉ cập nhật số lượng
                ghiLichSuGiaoDich("NHAP", m, sl); // Ghi lịch sử
            }
        }
    }

    void hienthithongtin() override // Hiển thị thông tin nhập kho
    {
        GiaoDich::hienthithongtin();                         // Gọi phương thức của lớp cha
        cout << "Ngay nhap" << layThoiGianHeThong() << endl; // Thêm ngày nhập
    }
};
class XuatKho : public GiaoDich
{
private:
    KhoLaptop &kho;  // Tham chiếu đến kho laptop
    string ngayXuat; // Ngày xuất

public:
    XuatKho(KhoLaptop &kho) : GiaoDich("xuat", "", 0), kho(kho) {} // Constructor

    void thuchien() override // Triển khai phương thức ảo
    {

        cout << "Nhap ma san pham : ";
        getline(cin, maSP); // Nhập mã sản phẩm

        if (!kho.ktma(maSP)) // Kiểm tra mã có tồn tại
        {
            cout << "Khong ton tai ma sp trong kho" << endl;
        }
        else
        {
            cout << "Nhap so luong: ";
            cin >> soLuong; // Nhập số lượng
            cin.ignore();

            if (!kho.xuatkho(maSP, soLuong)) // Kiểm tra có đủ số lượng để xuất
            {
                cout << "Khong du so luong trong kho!" << endl;
            }
            else
            {
                ghiLichSuGiaoDich("XUAT", maSP, soLuong); // Ghi lịch sử
                kho.capnhatFile();                        // Cập nhật file
                cout << "Xuat kho thanh cong" << endl;
            }
        }
    }

    void hienthithongtin() override // Hiển thị thông tin xuất kho
    {
        GiaoDich::hienthithongtin();                         // Gọi phương thức của lớp cha
        cout << "Ngay xuat" << layThoiGianHeThong() << endl; // Thêm ngày xuất
    }
};
void menu(KhoLaptop &kho) // Hiển thị menu chương trình
{
    int a;
    vector<GiaoDich *> danhsachgiaodich; // Danh sách các giao dịch
    do
    {
        // Hiển thị menu
        cout << "--------Menu-------" << endl;
        cout << "1. Nhap kho Laptop" << endl;
        cout << "2. Xuat kho Laptop" << endl;
        cout << "3. Tim kiem Laptop trong kho theo ma" << endl;
        cout << "4. Kiem tra san pham co trong kho" << endl;
        cout << "5. Xoa san pham trong kho" << endl;
        cout << "6. Chinh sua san pham theo ma" << endl;
        cout << "7. Hien thi lich su giao dich " << endl;
        cout << "10. Don kho Laptop" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban la : ";
        cin >> a;
        cin.ignore();
        switch (a) // Xử lý lựa chọn
        {
        case 1: // Nhập kho
        {
            cout << "---NHAP KHO LAPTOP---" << endl;
            auto nhap = new NhapKho(kho);     // Tạo giao dịch nhập
            nhap->thuchien();                 // Thực hiện nhập
            danhsachgiaodich.push_back(nhap); // Thêm vào danh sách
            break;
        }
        case 2: // Xuất kho
        {
            cout << "-----XUAT KHO LAPTOP----" << endl;
            auto xuat = new XuatKho(kho);     // Tạo giao dịch xuất
            xuat->thuchien();                 // Thực hiện xuất
            danhsachgiaodich.push_back(xuat); // Thêm vào danh sách
            break;
        }
        case 3: // Tìm kiếm
        {
            cout << "TIM KIEM LAPTOP THEO MA" << endl;

            kho.hienthiLaptop(); // Hiển thị laptop theo mã
            cout << "-----------------------------\n";
            break;
        }
        case 4: // Hiển thị toàn bộ
        {
            cout << "SAN PHAM CO TRONG KHO" << endl;
            cout << "-----------------------------\n";
            kho.hienthidanhsachlaptop(); // Hiển thị tất cả
            break;
        }
        case 5: // Xóa sản phẩm
        {
            cout << "-----XOA SAN PHAM-----" << endl;
            kho.xoaSanPham(); // Gọi phương thức xóa
            cout << "-----------------------------\n";
            break;
        }
        case 6: // Sửa sản phẩm
        {
            cout << "-----SUA SAN PHAM-----" << endl;
            kho.suaSanPham(); // Gọi phương thức sửa
            cout << "-----------------------------\n";
            break;
        }
        case 7: // Lịch sử giao dịch
        {
            cout << "-----LICH SU GIAO DICH-----" << endl;
            hienthilichsuGiaodich(); // Hiển thị lịch sử
            cout << "-----------------------------\n";
            break;
        }
        case 10: // Dọn kho
        {
            kho.donKho();                  // Dọn kho
            donFile("laptop_data.txt");    // Xóa file dữ liệu
            donFile("lichsugiaodich.txt"); // Xóa file lịch sử
            break;
        }
        case 0: // Thoát
        {
            cout << "Thoat chuong trinh ";
            for (auto gd : danhsachgiaodich) // Giải phóng bộ nhớ
            {
                delete gd;
            }
            danhsachgiaodich.clear(); // Xóa danh sách
            break;
        }
        default: // Lựa chọn không hợp lệ
            cout << "Lua chon khong hop ly" << endl;
        }
    } while (a != 0); // Lặp đến khi chọn 0
}

int main() // Hàm chính
{
    system("cls"); // Xóa màn hình console
    KhoLaptop kho; // Tạo đối tượng kho
    menu(kho);     // Gọi menu
    return 0;
}