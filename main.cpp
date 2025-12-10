#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace std::chrono;

struct WordData {
    string word;
    string clue;
    string category; 
};

struct ScoreEntry {
    string nama;
    int skor;
};

struct GameSettings {
    string kategoriDipilih;
    int kesempatanAwal;
    bool valid = false; 
};

const vector<WordData> daftarKataClue = {
    {"komputer", "Alat elektronik yang bekerja secara otomatis untuk mengolah data.", "Teknologi"},
    {"program", "Rangkaian instruksi yang dibuat untuk melakukan tugas tertentu di komputer.", "Teknologi"},
    {"jaringan", "Sekumpulan komputer yang terhubung satu sama lain untuk berbagi data.", "Teknologi"},
    {"internet", "Jaringan komunikasi global yang menghubungkan seluruh dunia.", "Teknologi"},
    {"algoritma", "Serangkaian langkah terstruktur untuk memecahkan masalah.", "Teknologi"},
    
    {"sekolah", "Tempat belajar, mengajar, dan menerima ijazah.", "Akademik"},
    {"matematika", "Ilmu tentang besaran, struktur, ruang, dan perubahan. Sering ada hitungan!", "Akademik"},
    {"kimia", "Ilmu pengetahuan alam yang mempelajari komposisi, struktur, sifat, dan perubahan zat.", "Akademik"},
    {"sejarah", "Ilmu yang mempelajari masa lalu manusia.", "Akademik"},

    {"indonesia", "Negara kepulauan terbesar di dunia.", "Umum"},
    {"samudra", "Hamparan air asin yang sangat luas.", "Umum"},
    {"pegunungan", "Barisan bukit yang tingginya mencapai ribuan meter.", "Umum"}
};

void bersihkanKonsol();
void tampilkanMenu();
int ambilPilihan();
void mulaiGame(); 
void tampilkanBantuan();
void tampilkanTentang();
void gambarHukuman(int kesempatan); 
GameSettings pilihKategoriDanLevel(); 
void simpanSkor(const string& nama, int skor);
void tampilkanPeringkat(); 
bool bandingkanSkor(const ScoreEntry& a, const ScoreEntry& b); 

void bersihkanKonsol(){
  #ifdef_WIN32
        system("cls"); 
    #else
        system("clear");
    #endif
}

int main() {
    srand(time(0)); 
    int pilihan;

    do {
        bersihkanKonsol();
        
        tampilkanMenu();
        pilihan = ambilPilihan();

        if (pilihan !=4) {
        switch (pilihan) {
            case 1:
                mulaiGame();
                break;
            case 2:
                bersihkanKonsol();
                tampilkanBantuan();
                break;
            case 3:
                bersihkanKonsol();
                tampilkanTentang();
                break;
            case 5: 
                bersihkanKonsol();
                tampilkanPeringkat();
                break;
            default:
                cout << "Pilihan tidak valid. Silakan masukkan angka 1-5.\n";
                break;
            }

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else {
            cout << "Terima kasih telah bermain! Sampai jumpa.\n";
        }

    } while (pilihan != 4);

    return 0;
}

void tampilkanMenu() {
    cout << "╔═══════════════════════════════════════╗\n";
    cout << "║       W O R D   G U E S E S   G A M E       ║\n";
    cout << "║             (Game Tebak Kata)             ║\n";
    cout << "╠═══════════════════════════════════════╣\n";
    cout << "║                                       ║\n";
    cout << "║ [1] Mulai Permainan Baru              ║\n";
    cout << "║ [2] Bantuan                           ║\n";
    cout << "║ [3] Tentang                           ║\n";
    cout << "║ [5] Papan Peringkat 🏆                 ║\n";
    cout << "║ [4] Keluar                            ║\n";
    cout << "║                                       ║\n";
    cout << "╚═══════════════════════════════════════╝\n";
    cout << "\n>>> Pilih Opsi Anda (1-5): ";
}

int ambilPilihan() {
    int pilihan;
    cin >> pilihan;

    if (cin >> ws && cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;
    }
    return pilihan;
}
