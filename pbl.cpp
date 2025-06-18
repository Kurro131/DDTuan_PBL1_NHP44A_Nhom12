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
    time_t now = time(0);      
    tm *ltm = localtime(&now); 
    stringstream ss;                                          
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"      
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "/" 
       << 1900 + ltm->tm_year << " "                          
       << setfill('0') << setw(2) << ltm->tm_hour << ":"      
       << setfill('0') << setw(2) << ltm->tm_min << ":"       
       << setfill('0') << setw(2) << ltm->tm_sec;             
    return ss.str();                                          
}
class GiaoDich
{
protected:
    string loai;
    string maSP;
    int soLuong;
    string thoiGian;
public:
    GiaoDich() {}; 
    GiaoDich(const string &loai, const string &maSP, int soLuong) : loai(loai), maSP(maSP), soLuong(soLuong)
    {
        this->thoiGian = layThoiGianHeThong(); 
    }
    virtual void thuchien() = 0; 
    virtual void hienthithongtin() 
    {
        cout << "Loai giao dich : " << loai << endl;
        cout << "Ma san pham : " << maSP << endl;
        cout << "So luong san pham: " << soLuong << endl;
        cout << "Thoi gian giao dich : " << thoiGian << endl;
    }
    virtual ~GiaoDich() {} 
};
void nhapsonguyen(string a, int &b) 
{
    while (true) 
    {
        string gt;
        cout << "nhap " << a << " : ";
        getline(cin, gt);
        if (gt.empty() || gt == "0") 
        {
            break;
        }
        try 
        {
            int t = stoi(gt); 
            if (t > 0)        
            {
                b = t;
                break;
            }
            else
            {
                cout << a << " phai lon hon 0" << endl;
            }
        }
        catch (const invalid_argument &e) 
        {
            cout << "gia tri khong hop le.Vui long nhap lai ";
            cout << endl;
        }
        catch (const out_of_range &e) 
        {
            cout << "So qua lon! Vui long nhap lai mot gia tri hop le." << endl;
        }
    }
}
void ghiLichSuGiaoDich(const string &loai, const string &ma, const int &sl) 
{
    ofstream file("lichsugiaodich.txt", ios::app); 
    if (!file)                                     
    {
        cout << "khong the mo lich su giao dich" << endl;
        return;
    }
    file << loai << ",ma:" << ma << ",so luong:" << sl << ",thoi gian:" << layThoiGianHeThong() << endl; 
    file.close();                                                                                        
}
void donFile(const string &filecanxoa) 
{
    ofstream file(filecanxoa, ios::trunc); 
    if (!file)                             
    {
        cout << "Khong the mo tep ";
        return;
    }
    file.close(); 
}
void hienthilichsuGiaodich() 
{
    ifstream file("lichsugiaodich.txt"); 
    if (!file)                           
    {
        cout << "Khong the mo tep " << endl;
        return;
    }
    string dl;                
    while (getline(file, dl)) 
    {
        cout << dl << endl; 
    }
    file.close(); 
}
class Laptop
{
private:
    string ma;       
    string hang;     
    string ten;      
    string card;     
    string chatlieu; 
    string cpu;      
    int ram;         
    int khoiluong;   
    int gia;         
public:
    Laptop() : ma(""), hang(""), ten(""), card(""), chatlieu(""), cpu(""), ram(0), khoiluong(0), gia(0) {} 
    Laptop(string ma, string hang, string ten, string card, string chatlieu, string cpu, int ram, int khoiluong, int gia) 
    {
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
    void nhap() 
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
        nhapsonguyen("ram", ram);              
        nhapsonguyen("khoi luong", khoiluong); 
        nhapsonguyen("gia", gia);              
    }
    virtual void hienthithongtin() const 
    {
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
    vector<Laptop> dslaptop;               
    unordered_map<string, Laptop> danhMuc; 
    unordered_map<string, int> TonKho;     
public:
    const vector<Laptop> &getdsLaptop() const 
    {
        return dslaptop; 
    }
    void hienthidanhsachlaptop() 
    {
        for (auto lap : dslaptop) 
        {
            lap.hienthithongtin(); 
            cout << left << setw(15) << "So luong:" << getTonKho(lap.getMa()) << " cai" << endl;
            cout << "-----------------------------\n";
        }
    }
    void hienthiLaptop() 
    {
        const vector<Laptop> &lap = getdsLaptop();
        cout << "Nhap ma laptop muon tim kiem : ";
        string ma;
        getline(cin, ma);
        if (!ktma(ma)) 
        {
            cout << "Khong ton tai ma laptop la " << ma << endl;
            return;
        }
        else
        {
            for (auto &lap : getdsLaptop()) 
            {
                if (lap.getMa() == ma) 
                {
                    lap.hienthithongtin(); 
                    cout << left << setw(15) << "So luong:" << getTonKho(lap.getMa()) << " cai" << endl;
                }
            }
        }
    }
    bool xuatkho(const string &ma, int soluong) 
    {
        if (TonKho[ma] < soluong) 
        {
            return false; 
        }
        TonKho[ma] -= soluong; 
        return true;           
    }
    void nhapKho(const Laptop &lap, int soluong) 
    {
        dslaptop.push_back(lap);        
        TonKho[lap.getMa()] += soluong; 
    }
    void capnhatsoluong(const string &ma, int sl) 
    {
        TonKho[ma] += sl; 
    }
    int getTonKho(const string &ma) 
    {
        auto it = TonKho.find(ma); 
        if (it != TonKho.end())    
        {
            return it->second; 
        }
        return 0; 
    }
    bool ktma(const string &ma) 
    {
        return TonKho.count(ma) == 1; 
    }
    bool themSanPham(const Laptop &lap) 
    {
        if (danhMuc.count(lap.getMa())) 
        {
            return false; 
        }
        danhMuc[lap.getMa()] = lap; 
        TonKho[lap.getMa()] = 0;    
        return true;                
    }
    void xoaSanPham() 
    {
        string ma;
        cout << "Nhap ma San Pham muon xoa : ";
        getline(cin, ma);
        if (ktma(ma)) 
        {
            danhMuc.erase(ma);                                      
            TonKho.erase(ma);                                       
            for (auto it = dslaptop.begin(); it != dslaptop.end();) 
            {
                if (it->getMa() == ma) 
                {
                    it = dslaptop.erase(it); 
                }
                else
                {
                    ++it; 
                }
            }
            cout << "XOA SAN PHAM THANH CONG" << endl;
        }
        else
        {
            cout << "Khong ton tai ma san pham la " << ma << endl;
        }
    }
    void donKho() 
    {
        dslaptop.clear(); 
        TonKho.clear();   
        danhMuc.clear();  
        cout << "DA DON KHO LAPTOP" << endl;
    }
    void capnhatFile() 
    {
        ofstream file("laptop_data.txt", ios::trunc); 
        const vector<Laptop> &laptop = getdsLaptop();
        if (!file) 
        {
            cout << "Khong the mo tep ";
            return;
        }
        for (const auto &lap : laptop) 
        {
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
        file.close(); 
    }
    void suaSanPham() 
    {
        string ma;
        cout << "nhap ma san pham can sua : ";
        getline(cin, ma);
        if (ktma(ma)) 
        {
            for (auto &lap : dslaptop) 
            {
                if (lap.getMa() == ma) 
                {
                    lap.nhap(); 
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
    KhoLaptop &kho;  
    string ngayNhap; 
    int soLuong;     
public:
    NhapKho(KhoLaptop &k) : GiaoDich("nhap", "", 0), kho(k) {} 
    int getSoLuong() { return soLuong; } 
    void thuchien() override 
    {
        cout << "Nhap so luong laptop: ";
        string sl;
        getline(cin, sl);
        soLuong = stoi(sl);               
        for (int i = 0; i < soLuong; i++) 
        {
            Laptop lap;
            cout << "Nhap thong tin laptop thu " << i + 1 << ":" << endl;
            cout << "nhap ma : ";
            string m;
            getline(cin, m);
            if (kho.getTonKho(m) == 0) 
            {
                lap.setma(m); 
                lap.nhap();   
                int sl;
                cout << "nhap so luong laptop cua ma " << lap.getMa() << " : ";
                cin >> sl;
                cin.ignore();
                ghiLichSuGiaoDich("NHAP", m, sl); 
                kho.nhapKho(lap, sl);             
                kho.capnhatFile();                
            }
            else 
            {
                int sl;
                cout << "ma laptop da ton tai, cap nhat so luong : ";
                cin >> sl;
                cin.ignore();
                kho.capnhatsoluong(m, sl);        
                ghiLichSuGiaoDich("NHAP", m, sl); 
            }
        }
    }
    void hienthithongtin() override 
    {
        GiaoDich::hienthithongtin();                         
        cout << "Ngay nhap" << layThoiGianHeThong() << endl; 
    }
};
class XuatKho : public GiaoDich
{
private:
    KhoLaptop &kho;  
    string ngayXuat; 
public:
    XuatKho(KhoLaptop &kho) : GiaoDich("xuat", "", 0), kho(kho) {} 
    void thuchien() override 
    {
        cout << "Nhap ma san pham : ";
        getline(cin, maSP); 
        if (!kho.ktma(maSP)) 
        {
            cout << "Khong ton tai ma sp trong kho" << endl;
        }
        else
        {
            cout << "Nhap so luong: ";
            cin >> soLuong; 
            cin.ignore();
            if (!kho.xuatkho(maSP, soLuong)) 
            {
                cout << "Khong du so luong trong kho!" << endl;
            }
            else
            {
                ghiLichSuGiaoDich("XUAT", maSP, soLuong); 
                kho.capnhatFile();                        
                cout << "Xuat kho thanh cong" << endl;
            }
        }
    }
    void hienthithongtin() override 
    {
        GiaoDich::hienthithongtin();                         
        cout << "Ngay xuat" << layThoiGianHeThong() << endl; 
    }
};
void menu(KhoLaptop &kho) 
{
    int a;
    vector<GiaoDich *> danhsachgiaodich; 
    do
    {
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
        switch (a) 
        {
        case 1: 
        {
            cout << "---NHAP KHO LAPTOP---" << endl;
            auto nhap = new NhapKho(kho);     
            nhap->thuchien();                 
            danhsachgiaodich.push_back(nhap); 
            break;
        }
        case 2: 
        {
            cout << "-----XUAT KHO LAPTOP----" << endl;
            auto xuat = new XuatKho(kho);     
            xuat->thuchien();                 
            danhsachgiaodich.push_back(xuat); 
            break;
        }
        case 3: 
        {
            cout << "TIM KIEM LAPTOP THEO MA" << endl;
            kho.hienthiLaptop(); 
            cout << "-----------------------------\n";
            break;
        }
        case 4: 
        {
            cout << "SAN PHAM CO TRONG KHO" << endl;
            cout << "-----------------------------\n";
            kho.hienthidanhsachlaptop(); 
            break;
        }
        case 5: 
        {
            cout << "-----XOA SAN PHAM-----" << endl;
            kho.xoaSanPham(); 
            cout << "-----------------------------\n";
            break;
        }
        case 6: 
        {
            cout << "-----SUA SAN PHAM-----" << endl;
            kho.suaSanPham(); 
            cout << "-----------------------------\n";
            break;
        }
        case 7: 
        {
            cout << "-----LICH SU GIAO DICH-----" << endl;
            hienthilichsuGiaodich(); 
            cout << "-----------------------------\n";
            break;
        }
        case 10: 
        {
            kho.donKho();                  
            donFile("laptop_data.txt");    
            donFile("lichsugiaodich.txt"); 
            break;
        }
        case 0: 
        {
            cout << "Thoat chuong trinh ";
            for (auto gd : danhsachgiaodich) 
            {
                delete gd;
            }
            danhsachgiaodich.clear(); 
            break;
        }
        default: 
            cout << "Lua chon khong hop ly" << endl;
        }
    } while (a != 0); 
}
int main() 
{
    system("cls"); 
    KhoLaptop kho; 
    menu(kho);     
    return 0;
}