#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct phancong
{
    string maphancong; 
	string lop; 
	string mon; 
	string gv; 
    int sotiet; 
	int len; 
    int mucuutien;
	bool ttpc = false; 
};

struct tlop
{
    string mon;
    string gv;
};

struct tklop
{
    string lop;
    tlop tiet[31];
};

struct tgv
{
    string mon;
    string lop;
};

struct tkgv
{
    string gv;
    tgv tiet[31];
};

phancong pc[1000];   // Input phân công
tklop outlop[35];    // Output tkb của lớp
tkgv outgv[1000];    // Output tkb của giáo viên

string DSmon[] = {"SHCN", "Tin", "TD", "Lý", "CN", "Van", "NN", "Hoa", "Sinh", "Dia", "Su", "GDCD", "Toan"};

string DSmonXh[] = {"Van", "Su", "Dia", "GDCD", "NN"};

int gv_tiet[75][31];            // Tiết giáo viên trống (0: trống, 1: ko trống) 
int lop_tiet[35][31];           // Tiết lớp trống (0: trống, 1: ko trống);
int slphancong, sllop, slgv;    // Số lượng của phân công, lớp, giáo viên;
int slphongtin = 3;             // Số lượng phòng tin học của trường

string file_PC = "PC_HK2.txt";

// ===================== Danh Sách Các Hàm ========================
void themPC(int i, string _maPhanCong, string _lop, string _mon, string _gv, int _sotiet, int _len);
void nhap();
void xuat_DSPC();
void xuat_tung_pc(int i);
//void suaCumTiet();
void ghiMucUuTien();
void taoDanhSachLop();
void taoDanhSachGiaoVien();
bool dieuKienSapXep(phancong a, phancong b);
void sapXep();
int tongSoTiet(string mon, string gv);
void outputtheolop(string lop);
int findsttlop(string lop);
int findsttgv(string gv);
bool kiemTraGioLienTiep(int i, int tietbatdau);
bool kiemTraToiDaMon(int tietbatdau, string lop);
bool kiemTraTrungMon(string mon, int tietbatdau, string lop);
bool kiemTraGioKhongXep(string mon, int tietbatdau);
bool kiemTraTrungGioGiaoVien(int k, int tietbatdau);
int findslot(int i, string lop, int sltiet);
void XepPhanCong(int i, string lop, int tietbatdau);
bool check(int i, string lop, int k);
void Xepmotlop(string lop);
void outlop_tunglop(string lop);
void outlop_hetlop();
void outgv_tunggv(string gv);
void outgv_hetgv();
bool checkTatCaPhanCong();
bool checkTietLung();

////////////////////////////////////////

// Thêm 1 phân công
void themPC(int i, string _maPhanCong, string _lop, string _mon, string _gv, int _sotiet, int _len){
    pc[i].maphancong = _maPhanCong;
    pc[i].lop = _lop;
	pc[i].mon = _mon;
	pc[i].gv = _gv;
	pc[i].sotiet = _sotiet;
	pc[i].len = _len;
}

// Nhập dữ liệu vào
void nhap(){
    ifstream fi(file_PC);
    slphancong = 0;
    string _maPhanCong;
    string _lop;
    string _mon;
    string _gv;
    int _sotiet;
    int _len;
    while (!fi.eof()){
        fi >> _maPhanCong >> _lop >> _mon >> _gv >> _sotiet >> _len;
        slphancong++;
        themPC(slphancong, _maPhanCong, _lop, _mon, _gv, _sotiet, _len);
    }
    fi.close();
}

// Xuất danh sách phân công
void xuat_DSPC(){
    for (int i=1; i<=slphancong; i++){
        cout << i << '\t' << pc[i].maphancong << '\t' << pc[i].lop << '\t' << pc[i].mon << '\t' << pc[i].gv << '\t' << pc[i].sotiet << '\t' << pc[i].len << "\t[" << pc[i].mucuutien << "]\t" << tongSoTiet(pc[i].mon, pc[i].gv) << '\n';
    }
}

// Xuất 1 phân công
void xuat_tung_pc(int i){
    cout << pc[i].maphancong << '\t' << pc[i].lop << '\t' << pc[i].mon << '\t' << pc[i].gv << '\t' << pc[i].sotiet << '\t' << pc[i].len << '\n';
}

// Sửa cụm tiết
/*void suaCumTiet(){
    for (int i=1; i<=slphancong; i++){
        if (pc[i].sotiet == 3){
            pc[i].len = pc[i].len;
        }
        else{
            pc[i].len = pc[i].sotiet;
        }
    }
}*/

// Ghi mức ưu tiên
void ghiMucUuTien(){
    for (int i=1; i<=slphancong; i++){
        if (pc[i].mon == "SHCN"){
            pc[i].mucuutien = 0;
        }
        else if (pc[i].mon == "Van" || pc[i].mon == "TD"){
            pc[i].mucuutien = 1;
        }
        else if (pc[i].mon == "Toan" || pc[i].mon == "NN"){
            pc[i].mucuutien = 2;
        }
        else{
            pc[i].mucuutien = 3;
        }
    }
}

// Tạo danh sách lớp trong outlop
void taoDanhSachLop(){
    outlop[1].lop = "12A";
    outlop[2].lop = "12B";
    outlop[3].lop = "12C";
    outlop[4].lop = "12D";
    outlop[5].lop = "12E";
    outlop[6].lop = "12G";
    outlop[7].lop = "12H";
    outlop[8].lop = "12K";
    outlop[9].lop = "12M";
    outlop[10].lop = "12N";
    
    outlop[11].lop = "11A";
    outlop[12].lop = "11B";
    outlop[13].lop = "11C";
    outlop[14].lop = "11D";
    outlop[15].lop = "11E";
    outlop[16].lop = "11G";
    outlop[17].lop = "11H";
    outlop[18].lop = "11K";
    outlop[19].lop = "11M";
    outlop[20].lop = "11N";
    
    outlop[21].lop = "10A";
    outlop[22].lop = "10B";
    outlop[23].lop = "10C";
    outlop[24].lop = "10D";
    outlop[25].lop = "10E";
    outlop[26].lop = "10G";
    outlop[27].lop = "10H";
    outlop[28].lop = "10K";
    outlop[29].lop = "10M";
    outlop[30].lop = "10N";
    sllop = 30;
}

// Tạo danh sách giáo viên trong outgv
void taoDanhSachGiaoVien(){
    set <string> myset;
    for (int i=1; i<=slphancong; i++){
        myset.insert(pc[i].gv);
    }
    int stt = 1;
    for (set <string>::iterator it=myset.begin(); it!=myset.end(); ++it){
        outgv[stt].gv = *it;
        stt++;
    }
    slgv = myset.size();
}

// Điều kiện để sắp xếp ( Mức ưu tiên => Tổng số tiết => Cụm)
bool dieuKienSapXep(phancong a, phancong b){
    if (a.mucuutien < b.mucuutien){
        return true;
    }
    else if (a.mucuutien > b.mucuutien){
        return false;
    }
    else{
        if (tongSoTiet(a.mon, a.gv) > tongSoTiet(b.mon, b.gv)){
            return true;
        }
        else if (tongSoTiet(a.mon, a.gv) < tongSoTiet(b.mon, b.gv)){
            return false;
        }
        else{
            if (a.len > b.len){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

// Sắp xếp phân công
void sapXep(){
    sort(pc + 1, pc + slphancong + 1, dieuKienSapXep);
}

// Tính tổng số tiết
int tongSoTiet(string mon, string gv){ // Co the toi uu dc buoc nay
    int Tong = 0;
    for (int i=1; i<=slphancong; i++){
        if (pc[i].mon == mon && pc[i].gv == gv){
            Tong += pc[i].len;
            //xuat_tung_pc(i);
        }
    }
    return Tong;
}

// Xuất danh sách phân công theo lớp
void outputtheolop(string lop){
    for (int i=1; i<=slphancong; i++){
        if (pc[i].lop == lop){
            cout << i << '\t' << pc[i].maphancong << '\t' << pc[i].lop << '\t' << pc[i].mon << '\t' << pc[i].gv << '\t' << pc[i].sotiet << '\t' << pc[i].len << "\t[" << pc[i].mucuutien << "]\t" << tongSoTiet(pc[i].mon, pc[i].gv) << '\n';
        }
    }
}

// Tìm số thứ tự của lớp
int findsttlop(string lop){
    for (int i=1; i<=sllop; i++){
        if (outlop[i].lop == lop){
            return i;
            break;
        }   
    }
    return 0;
}

// Tìm số thứ tự của giáo viên
int findsttgv(string gv){
    for (int i=1; i<=slgv; i++){
        if (outgv[i].gv == gv){
            return i;
        }
    }
    return 0;
}

// Kiểm tra giờ liên tiếp (H7)
bool kiemTraGioLienTiep(int i, int tietbatdau){ // Van TD
    if (pc[i].mon != "Van" && pc[i].mon != "TD"){
        return true;
    }
    else{
        if (tietbatdau%5 == 2 && pc[i].len > 1){ // Ra choi giua tiet 2 va 3
            return false;
        }
        else{
            return true;
        }
    }
}

// Kiểm tra số môn tối đa của buổi (H13)
bool kiemTraToiDaMon(int tietbatdau, string lop){
    int tietdauthu = ((tietbatdau-1)/5)*5 + 1;
    int sttlop = findsttlop(lop);

    map <string , bool> HashMap;
    int count = 0;
    for (int i=tietdauthu; i<=tietdauthu+4; i++){
        if (lop_tiet[sttlop][i] != 0){ // Tiet da co mon
            if (HashMap[outlop[sttlop].tiet[i].mon] == false){
                count++;
                HashMap[outlop[sttlop].tiet[i].mon] = true;
            }
        }
    }
    if (count >= 4){
        int t = 0;
        for (map<string, bool>::iterator it=HashMap.begin(); it!=HashMap.end(); ++it){
            for (int i=0; i<=4; i++){
                if (it->first == DSmonXh[i]){
                    t++;
                    break;
                }
            }
        }
        if (t == 5){
            return false;
        }
        else{
            return true;
        }

    }
    else{
        return true;    
    }
}

// Kiểm tra trùng môn (H8 + S2)
bool kiemTraTrungMon(string mon, int tietbatdau, string lop){
    int tietdauthu = ((tietbatdau-1)/5)*5 + 1;
    int sttlop = findsttlop(lop);

    for (int i=tietdauthu; i<=tietdauthu+4; i++){
        if (lop_tiet[sttlop][i] != 0){ // Tiet da co mon
            if (outlop[sttlop].tiet[i].mon == mon){ // Trung mon
                return false;
            }
        }
    }
    return true;
}

// Kiểm tra giờ không xếp (H2)
bool kiemTraGioKhongXep(string mon, int tietbatdau){
    if (tietbatdau >= 6 && tietbatdau <= 10 && (mon == "Toan" || mon == "Su" || mon == "Dia" /*|| mon == "Tin" */|| mon == "GDCD")){
        return false;
    }
    if (tietbatdau >= 11 && tietbatdau <= 15 && (mon == "Van" || mon == "Hoa" || mon == "Lý")){
        return false;
    }
    if (tietbatdau >= 16 && tietbatdau <= 20 && mon == "CN"){
        return false;
    }
    if (tietbatdau >= 21 && tietbatdau <= 25 && (mon == "NN" || mon == "Sinh")){
        return false;
    }
    if (tietbatdau >= 26 && tietbatdau <= 30 && (/*mon == "TD" || */mon == "GDQP")){
        return false;
    }
    return true;
}

// Kiểm tra trùng giờ giáo viên (H1)
bool kiemTraTrungGioGiaoVien(int k, int tietbatdau){
    for (int i=1; i<=sllop; i++){
        for (int j=0; j<pc[k].len; j++){
            if (lop_tiet[i][tietbatdau + j] == 1 && outlop[i].tiet[tietbatdau + j].gv == pc[k].gv){ // Co tiet va trung gv
                return false;
            }
        }
    }
    return true;
}

// Kiểm tra đụng độ phòng học - Tiết tin học (H3)
bool kiemTraDungDoPhongHoc(int i, int tietbatdau){
    if (pc[i].mon == "Tin"){
        for (int k=0; k<pc[i].len; k++){   
            int count = 1;
            for (int j=1; j<=sllop; j++){
                if (lop_tiet[j][tietbatdau + k] == 1){
                    if (outlop[i].tiet[tietbatdau].mon == "Tin"){
                        count++;
                        if (count > slphongtin){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
    return true;
}

// Tìm vị trí xếp phân công
int findslot(int i, string lop, int sltiet){ // tra vi tri: 1, 0;
    int sttlop = findsttlop(lop);
    int vitri = 1;
    for (; vitri <= 30; vitri++){
        if (lop_tiet[sttlop][vitri] == 0){ // Tiet trong
            if (check(i, lop, vitri)){
                int j = vitri;
                while (lop_tiet[sttlop][j] == 0){
                    if (j - vitri + 1 == sltiet && j <= (((vitri-1)/5)+1)*5){
                        //cerr << vitri << '-' << j << '-' << (((vitri-1)/5)+1)*5 << ' ';
                        return vitri;
                    }
                    j++;
                }
            }
        }
    }
    return 0;
}

// Xếp Phân Công ( Chính )
void XepPhanCong(int i, string lop, int tietbatdau){ // phan cong i xep vao lop vao tietbatdau  
    int sttlop = findsttlop(lop);
    int sttgv = findsttgv(pc[i].gv);
    for (int j=0; j < pc[i].len; j++){
        lop_tiet[sttlop][tietbatdau+j] = 1;
        outlop[sttlop].tiet[tietbatdau+j].mon = pc[i].mon;
        outlop[sttlop].tiet[tietbatdau+j].gv = pc[i].gv;

        pc[i].ttpc = true;
    
        gv_tiet[sstgv][tietbatdau+j] = 1;
        outgv[sttgv].tiet[tietbatdau+j].mon = pc[i].mon;
        outgv[sttgv].tiet[tietbatdau+j].lop = pc[i].lop; 
    }
}

// tập hợp các điều kiện 
bool check(int i, string lop, int k){
    if (kiemTraGioLienTiep(i, k) && kiemTraTrungMon(pc[i].mon, k, lop) && kiemTraGioKhongXep(pc[i].mon, k) && kiemTraTrungGioGiaoVien(i, k) && kiemTraDungDoPhongHoc(i, k)){
        return true;
    }
    else{
        return false;
    }
}

// Xếp phân công cho 1 lớp
void Xepmotlop(string lop){
    for (int i=1; i<=slphancong; i++){
        if (pc[i].lop == lop){
            int sotiet = pc[i].len;
            int k = findslot(i, lop, sotiet);
            //cout << '[' << k << ']' << ' ';
            if (k != 0){
                XepPhanCong(i, lop, k);
            }
        }
    }
}

// Xuất output 1 lớp
void outlop_tunglop(string lop){
    int sttlop = findsttlop(lop);
    for (int i=1; i<=30; i++){
        cout << ((i-1)/5) + 2 << '\t' << ((i-1)%5)+1 << '\t' << outlop[sttlop].tiet[i].mon << " - " << outlop[sttlop].tiet[i].gv << '\n';
    }
}

// Xuất output tất cả lớp
void outlop_hetlop(){
    ofstream fo("TKB_lop.txt");

    fo << "lop" << "\ttiet";
    for (int i=1; i<=sllop; i++){
        fo << '\t' << outlop[i].lop;
    } 
    fo << '\n';

    for (int j=1; j<=30; j++){   
        fo << ((j-1)/5) + 2 << '\t' << ((j-1)%5)+1 << '\t';
        for (int i=1; i<=sllop; i++){
            fo << outlop[i].tiet[j].mon << " - " << outlop[i].tiet[j].gv << '\t';
        }
        fo << '\n';
    }
    fo.close();
}

// Xuất output 1 giáo viên
void outgv_tunggv(string gv){
    int sttgv = findsttgv(gv);
    for (int i=1; i<=30; i++){
        cout << ((i-1)/5) + 2 << '\t' << ((i-1)%5)+1 << '\t' << outgv[sttgv].tiet[i].mon << "-" << outgv[sttgv].tiet[i].lop << '\n';
    }
}

// Xuất output tất cả giáo viên
void outgv_hetgv(){
    ofstream fo("TKB_gv.txt");

    fo << "lop" << "\ttiet";
    for (int i=1; i<=slgv; i++){
        fo << '\t' << outgv[i].gv;
    } 
    fo << '\n';

    for (int j=1; j<=30; j++){   
        fo << ((j-1)/5) + 2 << '\t' << ((j-1)%5)+1 << '\t';
        for (int i=1; i<=slgv; i++){
            fo << outgv[i].tiet[j].mon << " - " << outgv[i].tiet[j].lop << '\t';
        }
        fo << '\n';
    }
    fo.close();
}

// Kiểm tra tất cả phân công có đc xếp ko (H5)
bool checkTatCaPhanCong(){
    for (int i=1; i<=slphancong; i++){
        if (pc[i].ttpc == false){
            return false;
            //xuat_tung_pc(i);
        }
    }
    return true;
}

// Kiểm tra tiết lủng
bool checkTietLung(){
    for (int i=1; i<=sllop; i++){
        for (int j=1; j<=30; j++){
            if (lop_tiet[i][j] == 0){
                if (j%5 != 0 && j%5 != 1){
                    bool c1 = false;
                    bool c2 = false;
                    for (int jt=j; jt >= ((j-1)/5)*5 + 1; jt--){
                        if (lop_tiet[i][jt] == 1){
                            c1 = true;
                        }
                    }
                    for (int js=j; js <= ((j-1)/5 + 1)*5; js++){
                        if (lop_tiet[i][js] == 1){
                            c2 = true;
                        }
                    }                    
                    if (c1 & c2){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Kiểm tra tiết k của lớp i có là tiết lủng ko
bool TietkLung(int k, int i){
    if (lop_tiet[i][k] == 0){ // Tiết trống
        if (k == ((k-1)/5)*5 + 1){ // Tiet đầu trống
            return true;
        }
        bool c1 = false;
        bool c2 = false;
        int k_truoc = k;
        while (k_truoc >= ((k-1)/5)*5 + 1){
            if (lop_tiet[i][k_truoc] == 1){ // Tiết trước đó có tiết
                c1 = true;
                break;
            }
            k_truoc--;
        }
        int k_sau = k;
        while (k_sau <= ((k-1)/5 + 1)*5){
            if (lop_tiet[i][k_sau] == 1){ // Tiết sau đó có tiết
                c2 = true;
                break;
            }
            k_sau++;
        }
        if (c1 & c2){
            return true;
        }
        else{
            return false;
        }
    }
    return false; 
}

// Kiểm tra tiết thay thế với tiết trống
bool ChecktietThayThe(int lop, int tietbatdau, int tietthaythe){
    // Kiểm tra trùng giáo viên
    for (int i=1; i<=sllop; i++){
        if (i != lop){
            if (lop_tiet[i][tietbatdau] == 1 && outlop[i].tiet[tietbatdau].gv == outlop[lop].tiet[tietthaythe].gv){ // Co tiet va trung gv
                return false;
            }
        }
    }
    
    // Kiểm tra giờ không xếp
    if (!kiemTraGioKhongXep(outlop[lop].tiet[tietthaythe].mon, tietbatdau)){
        return false;
    }

    // Kiểm tra trùng môn
    if (!kiemTraTrungMon(outlop[lop].tiet[tietthaythe].mon, tietbatdau, outlop[lop].lop)){
        return false;
    }

    // Kiểm tra đụng độ phòng học
    if (outlop[lop].tiet[tietthaythe].mon == "Tin"){ 
        int count = 1;
        for (int j=1; j<=sllop; j++){
            if (lop != j && lop_tiet[j][tietbatdau] == 1){
                if (outlop[lop].tiet[tietbatdau].mon == "Tin"){
                    count++;
                    if (count > slphongtin){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// jsadbksa djsabdkjbsa kb
bool ChecktietThayThe2(int lop, int tietbatdau, int tietthaythe){
    // Kiểm tra trùng giáo viên
    for (int i=1; i<=sllop; i++){
        if (i != lop){
            if (lop_tiet[i][tietbatdau] == 1 && outlop[i].tiet[tietbatdau].gv == outlop[lop].tiet[tietthaythe].gv){ // Co tiet va trung gv
                return false;
            }
        }
    }
    
    // Kiểm tra giờ không xếp
    if (!kiemTraGioKhongXep(outlop[lop].tiet[tietthaythe].mon, tietbatdau)){
        return false;
    }

    // Kiểm tra đụng độ phòng học
    if (outlop[lop].tiet[tietthaythe].mon == "Tin"){ 
        int count = 1;
        for (int j=1; j<=sllop; j++){
            if (lop_tiet[j][tietbatdau] == 1){
                if (outlop[lop].tiet[tietbatdau].mon == "Tin"){
                    count++;
                    if (count > slphongtin){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void ThayTheTiet(int i, int tietbatdau, int tietthaythe){
    lop_tiet[i][tietthaythe] = 0;
    lop_tiet[i][tietbatdau] = 1;
    swap(outgv[findsttgv(outlop[i].tiet[tietthaythe].gv)].tiet[tietbatdau], outgv[findsttgv(outlop[i].tiet[tietthaythe].gv)].tiet[tietthaythe]);
    swap(outlop[i].tiet[tietbatdau], outlop[i].tiet[tietthaythe]);
}

void findtietThayThe(int i, int tietbatdau){ // Cum == 1
    for (int tiet = ((tietbatdau-1)/5)*5; tiet >= 5; tiet -= 5){
        if (lop_tiet[i][tiet] == 1 && outlop[i].tiet[tiet].mon != outlop[i].tiet[tiet-1].mon){ // Có tiêt và cum = 1
            if (ChecktietThayThe(i, tietbatdau, tiet)){
                ThayTheTiet(i, tietbatdau, tiet);
                break;
            }
        }
    }
}

bool check1tiet(int lop, int tiet_on_2){
    if (tiet_on_2%5 == 1){
        if (outlop[lop].tiet[tiet_on_2].mon != outlop[lop].tiet[tiet_on_2 + 1].mon){
            return true;
        }
        else{
            return false;
        }
    }
    else if (tiet_on_2%5 == 0){
        if (outlop[lop].tiet[tiet_on_2].mon != outlop[lop].tiet[tiet_on_2 - 1].mon){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (outlop[lop].tiet[tiet_on_2].mon != outlop[lop].tiet[tiet_on_2 + 1].mon && outlop[lop].tiet[tiet_on_2].mon != outlop[lop].tiet[tiet_on_2 - 1].mon){
            return true;
        }
        else{
            return false;
        }
    }
}

bool check1tiet_2(int lop, int tiet_on_2){
    if (outlop[lop].tiet[tiet_on_2].mon != "Van" && outlop[lop].tiet[tiet_on_2].mon != "TD"){
        return true;
    }
    return false;
}

bool Check3_Swap(int lop, int tiet_on_1, int tiet_off, int tiet_on_2){
    if (lop_tiet[lop][tiet_on_1] == 1 && lop_tiet[lop][tiet_off] == 0 && lop_tiet[lop][tiet_on_2] == 1 && check1tiet(lop, tiet_on_2)){
        if (ChecktietThayThe(lop, tiet_off, tiet_on_2) && ChecktietThayThe(lop, tiet_on_2, tiet_on_1)){
            return true;
        }
    }
    return false;
}

bool Check3_Swap_2(int lop, int tiet_on_1, int tiet_off, int tiet_on_2){
    if (lop_tiet[lop][tiet_on_1] == 1 && lop_tiet[lop][tiet_off] == 0 && lop_tiet[lop][tiet_on_2] == 1 && check1tiet_2(lop, tiet_on_2)){
        if (ChecktietThayThe(lop, tiet_off, tiet_on_2) && ChecktietThayThe(lop, tiet_on_2, tiet_on_1)){
            return true;
        }
    }
    return false;
}

void CaiThien1(){
    // Từ thứ 6 => thứ 2
    for (int i=1; i<=sllop; i++){
        for (int tiet=25; tiet>=1; tiet--){
            if (TietkLung(tiet, i)){
                //cout << tiet << ' ' << outlop[i].lop << '\n';
                findtietThayThe(i, tiet);
            }            
        }    
    }

    // Đẩy tiết thứ 7 

    for (int i=1; i<=sllop; i++){
        for (int tiet=30; tiet>=26; tiet--){
            if (lop_tiet[i][tiet] == 1){ // Có tiết

                //  Tìm tiết trống thay thế
                for (int j=26; j>=1; j--){
                    if (lop_tiet[i][j] == 0){ // Tiết trống
                        if (ChecktietThayThe(i, j, tiet)){
                            ThayTheTiet(i, j, tiet);
                            break;
                        }
                    }
                }
            }            
        }    
    }
    // Fill Thứ 6
    
    for (int i=1; i<=sllop; i++){
        for (int tiet=21; tiet<=25; tiet++){
            if (lop_tiet[i][tiet] == 0){ // Trống tiết
                findtietThayThe(i, tiet);
            }            
        }    
    }

    // Đẩy tiết thứ 7 

    for (int i=1; i<=sllop; i++){
        for (int tiet=30; tiet>=26; tiet--){
            if (lop_tiet[i][tiet] == 1){ // Có tiết

                //  Tìm tiết trống thay thế
                for (int j=26; j>=1; j--){
                    if (lop_tiet[i][j] == 0){ // Tiết trống
                        if (ChecktietThayThe(i, j, tiet)){
                            ThayTheTiet(i, j, tiet);
                            break;
                        }
                    }
                }
            }            
        }    
    }

    // Fixxing thứ 7

    for (int i=1; i<=sllop; i++){
        for (int tiet=30; tiet>=26; tiet--){
            if (lop_tiet[i][tiet] == 1){ // Có tiết
                //  Tìm tiết trống thay thế
                for (int j=26; j<=tiet; j++){
                    if (lop_tiet[i][j] == 0){ // Tiết trống
                        if (ChecktietThayThe2(i, j, tiet)){
                            ThayTheTiet(i, j, tiet);
                            break;
                        }
                    }
                }
            }            
        }    
    }

    // 3-Swap
    for (int lop=1; lop<=sllop; lop++){
        for (int tiet_on_1=30; tiet_on_1>=26; tiet_on_1--){
            if (lop_tiet[lop][tiet_on_1] == 1){ // Có tiết 1
                for (int tiet_off=2; tiet_off<=25; tiet_off++){
                    if (lop_tiet[lop][tiet_off] == 0){ // Tiết trống
                        for (int tiet_on_2=2; tiet_on_2 <= 25; tiet_on_2++){
                            if (lop_tiet[lop][tiet_on_2] == 1){ // Có Tiết 2
                                if (Check3_Swap(lop, tiet_on_1, tiet_off, tiet_on_2)){
                                    ThayTheTiet(lop, tiet_off, tiet_on_2);
                                    ThayTheTiet(lop, tiet_on_2, tiet_on_1);
                                    //cout << lop << ' ' << tiet_off << ' ' << tiet_on_2 << '\n';
                                    //cout << lop << ' ' << tiet_on_2 << ' ' << tiet_on_1 << '\n';
                                    //cout << "||||||||||||||||||||||\n";
                                }
                            }
                        }
                    }
                }
            }            
        }    
    }

    for (int lop=1; lop<=sllop; lop++){
        for (int tiet_on_1=30; tiet_on_1>=26; tiet_on_1--){
            if (lop_tiet[lop][tiet_on_1] == 1){ // Có tiết 1
                for (int tiet_off=2; tiet_off<=25; tiet_off++){
                    if (lop_tiet[lop][tiet_off] == 0){ // Tiết trống
                        for (int tiet_on_2=2; tiet_on_2 <= 25; tiet_on_2++){
                            if (lop_tiet[lop][tiet_on_2] == 1){ // Có Tiết 2
                                if (Check3_Swap_2(lop, tiet_on_1, tiet_off, tiet_on_2)){
                                    ThayTheTiet(lop, tiet_off, tiet_on_2);
                                    ThayTheTiet(lop, tiet_on_2, tiet_on_1);
                                    //cout << lop << ' ' << tiet_off << ' ' << tiet_on_2 << '\n';
                                    //cout << lop << ' ' << tiet_on_2 << ' ' << tiet_on_1 << '\n';
                                    //cout << "||||||||||||||||||||||\n";
                                }
                            }
                        }
                    }
                }
            }            
        }    
    }

    // Fixxing thứ 7

    for (int i=1; i<=sllop; i++){
        for (int tiet=30; tiet>=26; tiet--){
            if (lop_tiet[i][tiet] == 1){ // Có tiết
                //  Tìm tiết trống thay thế
                for (int j=26; j<=tiet; j++){
                    if (lop_tiet[i][j] == 0){ // Tiết trống
                        if (ChecktietThayThe2(i, j, tiet)){
                            ThayTheTiet(i, j, tiet);
                            break;
                        }
                    }
                }
            }            
        }    
    }

    /*for (int lop=1; lop<=sllop; lop++){
        for (int i=1; i<=30; i++){
            if (lop_tiet[lop][i] == 0){
                cout << lop << ' ' << i << '\n';
            }
        }
    }*/
}

bool TietkLung2(int k, int i){
    if (lop_tiet[i][k] == 0){ // Tiết trống
        bool c1 = false;
        bool c2 = false;
        int k_truoc = k;
        while (k_truoc >= ((k-1)/5)*5 + 1){
            if (lop_tiet[i][k_truoc] == 1){ // Tiết trước đó có tiết
                c1 = true;
                break;
            }
            k_truoc--;
        }
        int k_sau = k;
        while (k_sau <= ((k-1)/5 + 1)*5){
            if (lop_tiet[i][k_sau] == 1){ // Tiết sau đó có tiết
                c2 = true;
                break;
            }
            k_sau++;
        }
        if (c1 & c2){
            return true;
        }
        else{
            return false;
        }
    }
    return false; 
}

int countTietLung(){
    int ct = 0;
    for (int i=1; i<=sllop; i++){
        for (int tiet=30; tiet>=1; tiet--){
            if (TietkLung2(tiet, i)){
                ct++;
            }            
        }    
    }
    return ct;
}

bool monTrongBuoi(string mon, int lop, int thu){
    for (int tiet = (thu-1)*5 + 1; tiet <= thu*5; tiet++){
        if (outlop[lop].tiet[tiet].mon == mon){
            return true;
        }
    }
    return false;
}

int countHocCachMon(){
    int ct = 0;
    for (int lop=1; lop<=sllop; lop++){
        for (int i=1; i<=25; i++){
            if (i % 5 == 0 || (i % 5 != 0 && outlop[lop].tiet[i].mon != outlop[lop].tiet[i + 1].mon)){
                if (monTrongBuoi(outlop[lop].tiet[i].mon, lop, (i-1)/5 + 2)){
                    ct++;
                }
            }
        }
    }
    return ct;
}

int countBuoiDaygv(){
    int ct = 0;
    int st = 0;
    for (int gv=1; gv<=slgv; gv++){
        st = 0;
        for (int i=1; i<=30; i++){
            if (outgv[gv].tiet[i].lop != ""){
                st++;
            }
        }
        for (int i=1; i<=30; i++){
            if (outgv[gv].tiet[i].lop != ""){
                i = (((i-1)/5)+1)*5 + 1;
                ct++;
            }
        }
        ct -= (st - 1)/5 + 1;
    }
    return ct;
}   

bool TietkLungGv(int k, int i){
    if (outgv[i].tiet[k].lop == ""){ // Tiết trống
        bool c1 = false;
        bool c2 = false;
        int k_truoc = k;
        while (k_truoc >= ((k-1)/5)*5 + 1){
            if (outgv[i].tiet[k_truoc].lop != ""){ // Tiết trước đó có tiết
                c1 = true;
                break;
            }
            k_truoc--;
        }
        int k_sau = k;
        while (k_sau <= ((k-1)/5 + 1)*5){
            if (outgv[i].tiet[k_sau].lop != ""){ // Tiết sau đó có tiết
                c2 = true;
                break;
            }
            k_sau++;
        }
        if (c1 & c2){
            return true;
        }
        else{
            return false;
        }
    }
    return false; 
}

int countTietLungGv(){
    int ct = 0;
    for (int i=1; i<=slgv; i++){
        for (int thu=1; thu <= 6; thu++){
            int t = 0;
            for (int tiet = (thu-1)*5 + 1; tiet <= thu*5; tiet++){
                if (TietkLungGv(tiet, i)){
                    t++;
                }            
            }
            t = max(t-1, 0);
            ct += t;
        }    
    }
    return ct;
}

int countBuoiDay1Tiet(){
    int ct = 0;
    int st = 0;
    for (int gv=1; gv<=slgv; gv++){
        for (int thu=1; thu <= 6; thu++){
            int t = 0;
            for (int tiet = (thu-1)*5 + 1; tiet <= thu*5; tiet++){
                if (outgv[gv].tiet[tiet].lop != ""){
                    t++;
                }            
            }
            if (t == 1)
            ct++;
        }    
    }
    return ct;
}   

int countTietToiThieu(){
    int ct = 0;
    int st = 0;
    for (int lop=1; lop<=sllop; lop++){
        for (int thu=1; thu <= 6; thu++){
            int t = 0;
            for (int tiet = (thu-1)*5 + 1; tiet <= thu*5; tiet++){
                if (lop_tiet[lop][tiet] == 1){
                    t++;
                }            
            }
            if (t == 1)
            ct++;
        }    
    }
    return ct;
}   

int countToiDaMon(){
    int ct = 0;
    int st = 0;
    for (int lop=1; lop<=sllop; lop++){
        for (int thu=1; thu <= 6; thu++){
            int t = 0;
            int tiet = (thu-1)*5 + 1;
            if (!kiemTraToiDaMon(tiet, outlop[lop].lop)){
                ct++;
            }      
        }    
    }
    return ct;
}

void TinhDiemViPham(){
    int h1 = 0;
    int h2 = 0;
    int h3 = 0;
    int h4 = 0;
    int h5 = countTietLung();
    int h6 = 0;
    int h7 = 0;
    int s1 = 0;
    int s2 = countHocCachMon();
    int s3 = countBuoiDaygv();
    int s4 = countTietLungGv();
    int s5 = countBuoiDay1Tiet();
    int s6 = countTietToiThieu();
    int s7 = countToiDaMon();
    cout << "H1: " << h1 << '\n';
    cout << "H2: " << h2 << '\n';
    cout << "H3: " << h3 << '\n';
    cout << "H4: " << h4 << '\n';
    cout << "H5: " << h5 << '\n';
    cout << "H6: " << h6 << '\n';
    cout << "H7: " << h7 << '\n';
    
    cout << "S1: " << s1 << '\n';
    cout << "S2: " << s2 << '\n';
    cout << "S3: " << s3 << '\n';
    cout << "S4: " << s4 << '\n';
    cout << "S5: " << s5 << '\n';
    cout << "S6: " << s6 << '\n';
    cout << "S7: " << s7 << '\n';
    cout << "Điểm Vi Phạm: " << 999 * h1 + 999 * h2 + 999 * h3 + 600 * h4 + 600 * h5 + 600 * h6 + 600 * h7 + 20 * s1 + 20 * s2 + 10 * s3 + 5 * s4 + 10 * s5 + 20 * s6 + 10 * s7 << '\n';
}


int main(){
    // Bắt đầu đếm thời gian
    clock_t start, end;
    double time_use;
    start = clock();


    //freopen("output.txt", "w", stdout);
    memset(lop_tiet, 0, sizeof(lop_tiet));
    memset(gv_tiet, 0, sizeof(gv_tiet));

    nhap();
    //suaCumTiet();
    ghiMucUuTien();
    sapXep();
    taoDanhSachLop();
    taoDanhSachGiaoVien();

    Xepmotlop("10A");
    Xepmotlop("10B");
    Xepmotlop("10C");
    Xepmotlop("10D");
    Xepmotlop("10E");
    Xepmotlop("10G");
    Xepmotlop("10H");
    Xepmotlop("10K");
    Xepmotlop("10M");
    Xepmotlop("10N");
    Xepmotlop("11A");
    Xepmotlop("11B");
    Xepmotlop("11C");
    Xepmotlop("11D");
    Xepmotlop("11E");
    Xepmotlop("11G");
    Xepmotlop("11H");
    Xepmotlop("11K");
    Xepmotlop("11M");
    Xepmotlop("11N");
    Xepmotlop("12A");
    Xepmotlop("12B");
    Xepmotlop("12C");
    Xepmotlop("12D");
    Xepmotlop("12E");
    Xepmotlop("12G");
    Xepmotlop("12H");
    Xepmotlop("12K");
    Xepmotlop("12M");
    Xepmotlop("12N");
    
    CaiThien1();
    outlop_hetlop();
    outgv_hetgv();

    //CaiThien1();
    //cerr << checkTatCaPhanCong();
    //cerr << checkTietLung();

    //cout << slphancong;

    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "[ ] Time: " << time_use << '\n';
    
    TinhDiemViPham();
}
