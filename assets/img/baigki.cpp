#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class NhanVien {
protected:
    string ten, maNV;
    static int soLuongNV;

public:
    NhanVien() {}
    NhanVien(string ten, string maNV) : ten(ten), maNV(maNV) {
        soLuongNV++;
    }

    void setTenNhanVien(string x) {
        ten = x;
    }

    string getTenNhanVien() const {
        return ten;
    }

    void setMaNV(string x) {
        maNV = x;
    }

    string getMaNV() const {
        return maNV;
    }

    virtual double tinhLuong() const = 0;

    static int getSoLuongNV() {
        return soLuongNV;
    }
};

int NhanVien::soLuongNV = 0;

class NhanVienPart : public NhanVien {
    int soBuoiLam, soGioLam;
    double luongPart;

public:
    NhanVienPart(string ten, string maNV, int soBuoiLam, int soGioLam, double luongPart)
        : NhanVien(ten, maNV), soBuoiLam(soBuoiLam), soGioLam(soGioLam), luongPart(luongPart) {}

    void setSoBuoiLam(int x) {
        soBuoiLam = x;
    }

    int getSoBuoiLam() const {
        return soBuoiLam;
    }

    void setSoGioLam(int x) {
        soGioLam = x;
    }

    int getSoGioLam() const {
        return soGioLam;
    }

    void setLuongPart(double x) {
        luongPart = x;
    }

    double getLuongPart() const {
        return luongPart;
    }

    double tinhLuong() const override {
        return soBuoiLam * soGioLam * luongPart;
    }
};

class NhanVienFullTime : public NhanVien {
    double luongFullTime;

public:
    NhanVienFullTime(string ten, string maNV, double luongFullTime)
        : NhanVien(ten, maNV), luongFullTime(luongFullTime) {}

    void setLuongFullTime(double x) {
        luongFullTime = x;
    }

    double getLuongFullTime() const {
        return luongFullTime;
    }

    double tinhLuong() const override {
        return luongFullTime;
    }
};

class BoPhan {
    string tenBoPhan;
    vector<NhanVien*> danhSachNhanVien;
    static int soLuongNhanVien;

public:
    BoPhan(string tenBoPhan = "") : tenBoPhan(tenBoPhan) {}

    void themNhanVien(NhanVien* nv) {
        danhSachNhanVien.push_back(nv);
        soLuongNhanVien++;
    }

    void hienThiDanhSachNhanVien() const {
        for (size_t i = 0; i < danhSachNhanVien.size(); ++i) {
            NhanVien* nv = danhSachNhanVien[i];
            cout << "Ma NV: " << nv->getMaNV() << " | Ten: " << nv->getTenNhanVien() << " | Luong: " << nv->tinhLuong() << endl;
        }
    }

    void ghiDanhSachNhanVienVaoFile(const string& tenFile) const {
        ofstream outFile(tenFile);
        for (size_t i = 0; i < danhSachNhanVien.size(); ++i) {
            NhanVien* nv = danhSachNhanVien[i];
            outFile << nv->getMaNV() << "  " << nv->getTenNhanVien() << "  " << nv->tinhLuong() << endl;
        }
        outFile.close();
    }

    void docDanhSachNhanVienTuFile(const string& tenFile) {
        ifstream inFile(tenFile);
        string maNV, ten;
        double luong;
        while (inFile >> maNV >> ten >> luong) {
        }
        inFile.close();
    }

    static int getSoLuongNhanVien() {
        return soLuongNhanVien;
    }
};

int BoPhan::soLuongNhanVien = 0;

void hienThiMenu() {
    cout << "Menu:\n";
    cout << "1. Them nhan vien part-time\n";
    cout << "2. Them nhan vien full-time\n";
    cout << "3. Hien thi danh sach nhan vien\n";
    cout << "4. Ghi danh sach nhan vien vao File\n";
    cout << "5. Doc danh sach nhan vien tu file\n";
    cout << "6. Thoat\n";
}

int main() {
    BoPhan bp;
    int choice;
    do {
        hienThiMenu();
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string ten, maNV;
                int soBuoiLam, soGioLam;
                double luongPart;
                cout << "Nhap ma nhan vien: ";
                getline(cin, maNV);
                cout << "Nhap ten nhan vien: ";
                getline(cin, ten);
                cout << "Nhap so buoi: ";
                cin >> soBuoiLam;
                cout << "Nhap so gio: ";
                cin >> soGioLam;
                cout << "Nhap luong theo gio: ";
                cin >> luongPart;
                cin.ignore();
                bp.themNhanVien(new NhanVienPart(ten, maNV, soBuoiLam, soGioLam, luongPart));
                break;
            }
            case 2: {
                string ten, maNV;
                double luongFullTime;
                cout << "Nhap ma nhan vien: ";
                getline(cin, maNV);
                cout << "Nhap ten nhan vien: ";
                getline(cin, ten);
                cout << "Nhap luong full-time: ";
                cin >> luongFullTime;
                cin.ignore(); // To ignore the newline character left in the buffer
                bp.themNhanVien(new NhanVienFullTime(ten, maNV, luongFullTime));
                break;
            }
            case 3: {
                bp.hienThiDanhSachNhanVien();
                break;
            }
            case 4: {
                string tenFile;
                cout << "Nhap ten File de ghi: ";
                getline(cin, tenFile);
                bp.ghiDanhSachNhanVienVaoFile(tenFile);
                break;
            }
            case 5: {
                string tenFile;
                cout << "Nhap ten file de doc: ";
                getline(cin, tenFile);
                bp.docDanhSachNhanVienTuFile(tenFile);
                break;
            }
            case 6: {
                cout << "Thoat chuong trinh.\n";
                break;
            }
            default: {
                cout << "Lua chon khong hop le, vui long chon lai.\n";
                break;
            }
        }
    } while (choice != 6);

    return 0;
}
