#include <stdio.h>      //menunjuk kepada library standard input/output
#include <stdlib.h>     //menunjuk kepada library standard library
#include <string.h>     //menunjuk kepada library string
#include <time.h>       //menunjuk kepada library time

#define biayaAdmin          3000.00         //Biaya administrasi Rp3000
#define dendaRT             8000.00         //Denda pemakaian melebihi tempo untuk kategori RT Rp8000
#define dendaUsaha          10000.00        //Denda pemakaian melebihi tempo untuk kategori Usaha Rp10000
#define BPMRT               5000.00         //Biaya pemeliharaan meter rumah tangga Rp.5000
#define BPMU                5000.00         //Biaya pemeliharaan meter usaha Rp.5000
#define tempo               21           //Tempo / batas waktu pembayaran tanggal 21
#define maxArray            20           //Memberikan elemen maksimal yang dapat disimpan di array
                                         //untuk melakukan pengulangan

// fungsi dan prosedur untuk validasi input
float validasiFloat(float *var); void validasiInput(float *var); void validasiNegatif(float *var);
    void validasiMenu(float *var, int batas1, int batas2);

// prosedur serta fungsi yang digunakan
void menuAwal(); void registrasi(); void menuAdmin(); void administrator();
    void kelompok(); void regisRTSubsidi(); void regisRTNonSubsidi();void regisUsaha();
    void inputPemakaian(); void strukPembayaran(); void hapusStrukPembayaran(); void riwayatStrukPembayaran();
    void keluar();

// array data pembayaran
char nama[maxArray][50]; char alamat[maxArray][50]; char kategori[maxArray][4];
float biaya1[maxArray]; float biaya2[maxArray]; float biaya3[maxArray]; float denda[maxArray]; float BPM[maxArray];

//struct data admin
typedef struct {
    char username[20];
    char password[10];
    char nama[50];
} adm;
adm Admin;

//variabel penyimpan data admin selama log in
char username[20]; char password[10]; char namaAdmin[50];

// variabel perhitungan biaya
float  pBulanLalu[maxArray], pBulanIni[maxArray], totalPemakaian[maxArray],
     tarifPemakaian[maxArray], totalBiaya[maxArray], Denda;



int i;
int main()
{
    system("COLOR F5");
    while(i<maxArray) {
        system("cls");
        menuAwal();
        float ulang;
        printf("\t\t ________________________________________________________________________\n");
        printf("\t\t|+______________________________________________________________________+|\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t||                Pembayaran Air Minum Anda Telah Selesai.              ||\n");
        printf("\t\t||             Apakah Anda ingin melakukan pembayaran lainnya?          ||\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t|| [1] Ya       || Kembali ke menu registrasi                           ||\n");
        printf("\t\t|| [2] Tidak    || Tampilkan struk dan keluar                           ||\n");
        printf("\t\t|+______________________________________________________________________+|\n");
        printf("\t\t ________________________________________________________________________ \n");
        printf("\n\t\t Masukkan pilihan Anda : ");
        validasiMenu(&ulang, 1, 2);
        if(ulang==1) i++;
        else if(ulang==2) {
            break;
        }
    }
    system("cls");
    strukPembayaran();
    keluar();
    return 0;
}


void menuAwal()
{
    float pilMenu = 0;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                  PROGRAM PENGHITUNG PEMBAYARAN AIR                   ||\n");
    printf("\t\t||                 PERUMDA AIR MINUM DENPASAR NUSANTARA                 ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t||           [ I Gusti Ayu Krisna Kusuma Dewi || 2205551072 ]           ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| [1] Registrasi Pelanggan                                             ||\n");
    printf("\t\t|| [2] Masuk sebagai administrator                                      ||\n");
    printf("\t\t|| [3] Keluar                                                           ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Pilih menu yang diinginkan: ");
    validasiMenu(&pilMenu, 1, 3);
    if(pilMenu==1){
        system("cls");
        registrasi();
    } else if(pilMenu==2){
        system("cls");
        administrator();
    } else if(pilMenu==3){
        system("cls");
        keluar();
    }
}


void administrator()
{
    float pilMenu;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                 L O G  I N  A D M I N I S T R A T O R                ||\n");
    printf("\t\t||              Silahkan masukkan username dan password Anda            ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n");
    printf("\t\t Username        : ");
    fgets(username, sizeof(username), stdin);
    printf("\t\t Password        : ");
    fgets(password, sizeof(password), stdin);
    fflush(stdin);

    FILE *loginAdmin;

    loginAdmin = fopen("dataAdmin.txt","r");
    if (loginAdmin==NULL) return 1;

    fread(&Admin, sizeof(Admin), 1, loginAdmin);
        if(strcmp(username, Admin.username)==0 && strcmp(password, Admin.password)==0) {
            strcpy(namaAdmin, Admin.nama);
            fclose(loginAdmin);
            printf("\t\t ________________________________________________________________________\n");
            printf("\t\t|+______________________________________________________________________+|\n");
            printf("\t\t||                                                                      ||\n");
            printf("\t\t||                              LOG IN BERHASIL                         ||\n");
            printf("\t\t                          Selamat datang, %s", namaAdmin);
            printf("\t\t||                                                                      ||\n");
            printf("\t\t|+______________________________________________________________________+|\n");
            printf("\t\t ________________________________________________________________________ \n");
            printf("\t\t  Tekan ENTER untuk melanjutkan.\n");
            getchar();
            system("cls");
            menuAdmin();
        } else {
            printf("\t\t ________________________________________________________________________\n");
            printf("\t\t|+______________________________________________________________________+|\n");
            printf("\t\t||                                                                      ||\n");
            printf("\t\t||                    USERNAME ATAU PASSWORD SALAH                      ||\n");
            printf("\t\t||        Mohon untuk memasukkan username dan password yang benar       ||\n");
            printf("\t\t||                                                                      ||\n");
            printf("\t\t|+______________________________________________________________________+|\n");
            printf("\t\t ________________________________________________________________________ \n");
            printf("\t\t  Tekan ENTER untuk melanjutkan.\n");
            getchar();
            system("cls");
            fflush(stdin);
            menuAwal();
            }
}

void menuAdmin()
{
    float pilMenu = 0;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                  M E N U  A D M I N I S T R A T O R                  ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| [1] Lihat riwayat pembayaran                                         ||\n");
    printf("\t\t|| [2] Hapus riwayat pembayaran                                         ||\n");
    printf("\t\t|| [3] Kembali ke menu awal                                             ||\n");
    printf("\t\t|| [4] Keluar                                                           ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Pilih menu yang diinginkan: ");
    validasiMenu(&pilMenu, 1, 3);
    if(pilMenu==1){
        system("cls");
        riwayatStrukPembayaran();
    } else if(pilMenu==2){
        system("cls");
        hapusStrukPembayaran();
    } else if(pilMenu==3){
        system("cls");
        menuAwal();
    } else if(pilMenu==4){
        system("cls");
        keluar();
    }
}


void registrasi()
{
    float pilMenu;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                      M E N U  R E G I S T R A S I                    ||\n");
    printf("\t\t||             Silahkan lakukan registrasi sesuai dengan arahan         ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Nama      : ");
    fgets(nama[i], sizeof(nama[i]), stdin);
    printf("\t\t Alamat    : ");
    fgets(alamat[i], sizeof(alamat[i]), stdin);
    fflush(stdin);
    printf("\n\t\t ________________________________________________________________________ \n");
    printf("\n\t\t                      Selamat datang, %s\n\n", nama[i]);
    printf("\t\t|| Klik [1] untuk melanjutkan ke registrasi berikutnya.                 ||\n");
    printf("\t\t|| Klik [2] untuk kembali ke menu awal.                                 ||\n");
    printf("\n\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Pilih menu yang diinginkan: ");
    validasiMenu(&pilMenu, 1, 2);
    if(pilMenu==1){
        system("cls");
        kelompok();
    } else if(pilMenu==2){
        system("cls");
        menuAwal();
    }
}

void kelompok()
{
    float pilMenu;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                       M E N U  R E G I S T R A SI                    ||\n");
    printf("\t\t||       Mohon Pilih Sesuai dengan Tipe Kelompok Fasilitas Air Anda     ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| [1] Rumah Tangga / Non Niaga Bersubsidi                              ||\n");
    printf("\t\t|| [2] Rumah Tangga / Non Niaga Tanpa Subsidi                           ||\n");
    printf("\t\t|| [3] Usaha / Niaga                                                    ||\n");
    printf("\t\t|| [4] Kembali ke menu utama                                            ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Pilih tipe kelompok fasilitas : ");
    validasiMenu(&pilMenu, 1, 4);
    if(pilMenu==1){
        system("cls");
        regisRTSubsidi();
    }else if(pilMenu==2){
        system("cls");
        regisRTNonSubsidi();
    }else if(pilMenu==3){
        system("cls");
        regisUsaha();
    }else if(pilMenu==4){
        system("cls");
        menuAwal();
    }
}


void regisRTSubsidi()
{
    float pilMenu = 0;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                 RUMAH TANGGA / NON NIAGA BERSUBSIDI                  ||\n");
    printf("\t\t||           Mohon untuk memilih tipe rumah Anda pada daftar ini        ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t|| > Rumah Tangga A1 [Lebar Jalan : 0-3,99 meter]                       ||\n");
    printf("\t\t||   [1] Daya Listrik 450 VA || D1-1                                    ||\n");
    printf("\t\t||   [2] Daya Listrik 900 VA || D1-2                                    ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A2 [Lebar Jalan : 4-6,99 meter]                       ||\n");
    printf("\t\t||   [3] Daya Listrik 450 VA || D2-1                                    ||\n");
    printf("\t\t||   [4] Daya Listrik 900 VA || D2-2                                    ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A3 [Lebar Jalan : 7-10 meter]                         ||\n");
    printf("\t\t||   [5] Daya Listrik 450 VA || D3-1                                    ||\n");
    printf("\t\t||   [6] Daya Listrik 900 VA || D3-2                                    ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A4 [Lebar Jalan : >10 meter]                          ||\n");
    printf("\t\t||   [7] Daya Listrik 450 VA || D4-1                                    ||\n");
    printf("\t\t||   [8] Daya Listrik 900 VA || D4-2                                    ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t||   [9] Kembali ke menu sebelumnya                                     ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Mohon masukkan pilihan sesuai dengan tipe rumah Anda. ");
    printf("\n\t\t  Contoh: 1 ");
    printf("\n\t\t  Pilihan : ");
    validasiMenu(&pilMenu, 1, 9);
    if(1<= pilMenu && pilMenu <= 12) {
    if(pilMenu==1){
        strcpy(kategori[i], "D1-1"); biaya1[i] = 1780; biaya2[i] = 2060; biaya3[i] = 5880;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==2){
        strcpy(kategori[i], "D1-2"); biaya1[i] = 2060; biaya2[i] = 2340; biaya3[i] = 5940;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==3){
        strcpy(kategori[i], "D2-1"); biaya1[i] = 2340; biaya2[i] = 2620; biaya3[i] = 6000;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==4){
        strcpy(kategori[i], "D2-2"); biaya1[i] = 2620; biaya2[i] = 2900; biaya3[i] = 6060;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==5){
        strcpy(kategori[i], "D3-1"); biaya1[i] = 2900; biaya2[i] = 3180; biaya3[i] = 6120;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==6){
        strcpy(kategori[i], "D3-2"); biaya1[i] = 3180; biaya2[i] = 3460; biaya3[i] = 6180;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==7){
        strcpy(kategori[i], "D4-1"); biaya1[i] = 3460; biaya2[i] = 3740; biaya3[i] = 6240;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==8){
        strcpy(kategori[i], "D4-2"); biaya1[i] = 3740; biaya2[i] = 4020; biaya3[i] = 6300;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }
        system("cls");
        inputPemakaian();
    }else if(pilMenu==9){
        system("cls");
        registrasi();
    }
}


void regisRTNonSubsidi()
{
    float pilMenu;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||               RUMAH TANGGA / NON NIAGA TANPA BERSUBSIDI              ||\n");
    printf("\t\t||           Mohon untuk memilih tipe rumah Anda pada daftar ini        ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t|| > Rumah Tangga A1 [Lebar Jalan : 0-3,99 meter]                       ||\n");
    printf("\t\t||   [1]  Daya Listrik  1.300 VA || D1-3                                ||\n");
    printf("\t\t||   [2]  Daya Listrik >1.300 VA || D1-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A2 [Lebar Jalan : 4-6,99 meter]                       ||\n");
    printf("\t\t||   [3]  Daya Listrik  1.300 VA || D2-3                                ||\n");
    printf("\t\t||   [4]  Daya Listrik >1.300 VA || D2-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A3 [Lebar Jalan : 7-10 meter]                         ||\n");
    printf("\t\t||   [5]  Daya Listrik  1.300 VA || D3-3                                ||\n");
    printf("\t\t||   [6]  Daya Listrik >1.300 VA || D3-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A4 [Lebar Jalan : >10 meter]                          ||\n");
    printf("\t\t||   [7]  Daya Listrik  1.300 VA || D4-3                                ||\n");
    printf("\t\t||   [8]  Daya Listrik >1.300 VA || D4-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Rumah Tangga A5 [Persil Rumah terdapat Jenis Usaha]                ||\n");
    printf("\t\t||   [9]  Daya Listrik    450 VA || D5-1                                ||\n");
    printf("\t\t||   [10] Daya Listrik    900 VA || D5-2                                ||\n");
    printf("\t\t||   [11] Daya Listrik  1.300 VA || D5-3                                ||\n");
    printf("\t\t||   [12] Daya Listrik >1.300 VA || D5-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t||   [13] Kembali ke menu sebelumnya                                     ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Mohon masukkan pilihan sesuai dengan tipe rumah Anda. ");
    printf("\n\t\t Mohon masukkan pilihan sesuai dengan tipe rumah Anda. ");
    printf("\n\t\t  Contoh: 1 ");
    printf("\n\t\t  Pilihan : ");
    validasiMenu(&pilMenu, 1, 13);
    if(1<= pilMenu && pilMenu <= 12) {
     if(pilMenu==1){
        strcpy(kategori[i], "D1-3"); biaya1[i] = 6340; biaya2[i] = 9200; biaya3[i] = 9600;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==2){
        strcpy(kategori[i], "D1-4"); biaya1[i] = 6420; biaya2[i] = 9350; biaya3[i] = 9650;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }else if(pilMenu==3){
        strcpy(kategori[i], "D2-3"); biaya1[i] = 6490; biaya2[i] = 9500; biaya3[i] = 9800;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==4) {
        strcpy(kategori[i], "D2-4"); biaya1[i] = 6570; biaya2[i] = 9650; biaya3[i] = 9950;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==5) {
        strcpy(kategori[i], "D3-3"); biaya1[i] = 6640; biaya2[i] = 9800; biaya3[i] = 10100;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==6) {
        strcpy(kategori[i], "D3-4"); biaya1[i] = 6720; biaya2[i] = 9950; biaya3[i] = 10250;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==7){
        strcpy(kategori[i], "D4-3"); biaya1[i] = 6790; biaya2[i] = 10100; biaya3[i] = 10400;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==8) {
        strcpy(kategori[i], "D4-4"); biaya1[i] = 6870; biaya2[i] = 10250; biaya3[i] = 10550;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==9) {
        strcpy(kategori[i], "D5-1"); biaya1[i] = 6940; biaya2[i] = 10400; biaya3[i] = 10700;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==10) {
        strcpy(kategori[i], "D5-2"); biaya1[i] = 7020; biaya2[i] = 10550; biaya3[i] = 10850;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==11) {
        strcpy(kategori[i], "D5-3"); biaya1[i] = 7090; biaya2[i] = 10700; biaya3[i] = 11000;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    } else if(pilMenu==12) {
        strcpy(kategori[i], "D5-4"); biaya1[i] = 7170; biaya2[i] = 10850; biaya3[i] = 11150;
        denda[i] = dendaRT; BPM[i] = BPMRT;
    }
        system("cls");
        inputPemakaian();
    } else if(pilMenu==13) {
        system("cls");
        registrasi();
    }
}


void regisUsaha()
{
    float pilMenu = 0;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                             USAHA / NIAGA                            ||\n");
    printf("\t\t||       Mohon untuk memilih tipe usaha/niaga Anda pada daftar ini      ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t|| > Niaga Kecil [Lebar Jalan : 0-6,99 meter]                           ||\n");
    printf("\t\t||   [1]  Daya Listrik    450 VA || E1-1                                ||\n");
    printf("\t\t||   [2]  Daya Listrik    900 VA || E1-2                                ||\n");
    printf("\t\t||   [3]  Daya Listrik  1.300 VA || E1-3                                ||\n");
    printf("\t\t||   [4]  Daya Listrik >1.300 VA || E1-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Niaga Sedang [Lebar Jalan : 7-10 meter]                            ||\n");
    printf("\t\t||   [5]  Daya Listrik    450 VA || E2-1                                ||\n");
    printf("\t\t||   [6]  Daya Listrik    900 VA || E2-2                                ||\n");
    printf("\t\t||   [7]  Daya Listrik  1.300 VA || E2-3                                ||\n");
    printf("\t\t||   [8]  Daya Listrik >1.300 VA || E2-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t|| > Niaga Besar [Lebar Jalan : >10 meter]                              ||\n");
    printf("\t\t||   [9]  Daya Listrik    450 VA || E3-1                                ||\n");
    printf("\t\t||   [10] Daya Listrik    900 VA || E3-2                                ||\n");
    printf("\t\t||   [11] Daya Listrik  1.300 VA || E3-3                                ||\n");
    printf("\t\t||   [12] Daya Listrik >1.300 VA || E3-4                                ||\n");
    printf("\t\t|| -------------------------------------------------------------------- ||\n");
    printf("\t\t||   [13] Kembali ke menu sebelumnya                                     ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\n\t\t Mohon masukkan pilihan sesuai dengan tipe rumah Anda. ");
    printf("\n\t\t Mohon masukkan pilihan sesuai dengan tipe rumah Anda. ");
    printf("\n\t\t  Contoh: 1 ");
    printf("\n\t\t  Pilihan : ");
    validasiMenu(&pilMenu, 1, 13);
    if(1<= pilMenu && pilMenu <= 12) {
     if(pilMenu==1) {
        strcpy(kategori[i], "E1-1"); biaya1[i] = 9200; biaya2[i] = 9850; biaya3[i] = 10950;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==2) {
        strcpy(kategori[i], "E1-2"); biaya1[i] = 9500; biaya2[i] = 10150; biaya3[i] = 11250;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==3) {
        strcpy(kategori[i], "E1-3"); biaya1[i] = 9800; biaya2[i] = 10450; biaya3[i] = 11550;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==4) {
        strcpy(kategori[i], "E1-4"); biaya1[i] = 10100; biaya2[i] = 10750; biaya3[i] = 11850;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==5) {
        strcpy(kategori[i], "E2-1"); biaya1[i] = 10400; biaya2[i] = 11050; biaya3[i] = 12150;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==6) {
        strcpy(kategori[i], "E2-2"); biaya1[i] = 10700; biaya2[i] = 11350; biaya3[i] = 12550;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==7) {
        strcpy(kategori[i], "E2-3"); biaya1[i] = 11000; biaya2[i] = 11650; biaya3[i] = 13150;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==8) {
        strcpy(kategori[i], "E2-4"); biaya1[i] = 11300; biaya2[i] = 11950; biaya3[i] = 13950;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==9) {
        strcpy(kategori[i], "E3-1"); biaya1[i] = 11600; biaya2[i] = 12250; biaya3[i] = 14750;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==10) {
        strcpy(kategori[i], "E3-2"); biaya1[i] = 11900; biaya2[i] = 12550; biaya3[i] = 15050;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==11){
        strcpy(kategori[i], "E3-3"); biaya1[i] = 12200; biaya2[i] = 12850; biaya3[i] = 15850;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } else if(pilMenu==12){
        strcpy(kategori[i], "E3-4"); biaya1[i] = 12500; biaya2[i] = 13150; biaya3[i] = 16650;
        denda[i] = dendaUsaha; BPM[i] = BPMU;
    } system("cls");
      inputPemakaian();
    } else if(pilMenu==13){
        system("cls");
        registrasi();
    }
}


void inputPemakaian()
{
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                      INPUT PEMAKAIAN AIR MINUM                       ||\n");
    printf("\t\t||            Mohon Masukkan Pemakaian Air Minum Anda (dalam m3)        ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\t\t  Mohon untuk memasukkan angka seperti contoh di bawah. \n");
    printf("\t\t  Contoh: 150 atau 192.5 \n");
    printf("\t\t  Pemakaian air minum sebelum tanggal 21 (bulan lalu)                       : ");
    validasiNegatif(&pBulanLalu[i]);
    printf("\t\t  Total pemakaian air minum sebelum tanggal 21 hingga sekarang (bulan ini)  : ");
    validasiNegatif(&pBulanIni[i]);

    while (pBulanLalu[i] > pBulanIni[i]){
        printf("\n\t\t  Pemakaian bulan ini harus lebih besar dari bulan lalu.\n");
        printf("\t\t  Pemakaian air minum sebelum tanggal 21 (bulan lalu)                       : ");
        validasiNegatif(&pBulanLalu[i]);
        printf("\t\t  Total pemakaian air minum sebelum tanggal 21 hingga sekarang (bulan ini)  : ");
        validasiNegatif(&pBulanIni[i]);
    }

    totalPemakaian[i] = pBulanIni[i] - pBulanLalu[i];
    if (totalPemakaian[i] <= 10) {
        tarifPemakaian[i] = totalPemakaian[i]*biaya1[i];
    } else if (11 <= totalPemakaian[i] && totalPemakaian[i] <= 20) {
        tarifPemakaian[i] = totalPemakaian[i]*biaya2[i];
    } else if ( totalPemakaian[i] > 20) {
        tarifPemakaian[i] = totalPemakaian[i]*biaya3[i];}

    time_t waktuPembayaran;
    waktuPembayaran = time(NULL);
    struct tm tm = *localtime(&waktuPembayaran);


    if ((tm.tm_mday - tempo) <= 0) {
         Denda = 0;
    } else {
         Denda = denda[i];}

    totalBiaya[i] = tarifPemakaian[i] + BPM[i] + biayaAdmin + Denda;
    system("cls");
}


void strukPembayaran()
{
    time_t waktuPembayaran;
    waktuPembayaran = time(NULL);
    struct tm tm = *localtime(&waktuPembayaran);
    float biayaKeseluruhan;
        printf("\t\t ________________________________________________________________________\n");
        printf("\t\t|+______________________________________________________________________+|\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t||                 PERUMDA AIR MINUM DENPASAR NUSANTARA                 ||\n");
        printf("\t\t||           S T R U K  P E M B A Y A R A N  A I R  M I N U M           ||\n");
        printf("\t\t||                                                                      ||\n");
    for(int j = 0 ; j <= i ; j++){
        printf("\t\t|| ==================================================================== ||\n");
        printf("\t\t||                        [Identitas Pelanggan]                         ||\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t||   Nama     : %s ", nama[j]);
        printf("\t\t||   Alamat   : %s ", alamat[j]);
        printf("\t\t|| -------------------------------------------------------------------- ||\n");
        printf("\t\t||                           [Daftar Biaya]                             ||\n" );
        printf("\t\t||                                                                      ||\n");
        printf("\t\t||   Kategori           : %s \n", kategori[j]);
        printf("\t\t||   Total Pemakaian    : %.2f m3\n", totalPemakaian[j]);
        printf("\t\t||   Tanggal            : %d-%d-%d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
        printf("\t\t||   Jatuh Tempo        : %d-%d-%d\n", tempo, tm.tm_mon+1, tm.tm_year+1900);
        printf("\t\t||   Tarif Pemakaian    : Rp%.2f \n", tarifPemakaian[j]);
        printf("\t\t||   Biaya Administrasi : Rp%.2f \n", biayaAdmin);
        printf("\t\t||   Biaya Pemeliharaan : Rp%.2f \n", BPM[j]);
        printf("\t\t||   Denda              : Rp%.2f \n", Denda);
        printf("\t\t|| --------------------------------------------------------------------   \n");
        printf("\t\t||   Total Pembayaran   : Rp%.2f \n", totalBiaya[j]);
        biayaKeseluruhan = biayaKeseluruhan + totalBiaya[j];
    }
    printf("\t\t|| ==================================================================== ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||    Total biaya keseluruhan: %.2f\n", biayaKeseluruhan);
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n\n");
    cetakStruk();

    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                Pembayaran Air Minum Anda Telah Selesai.              ||\n");
    printf("\t\t||             Silahkan tekan ENTER untuk keluar dari program.          ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n\n");
    printf("\t\t  ");
    getchar();
    system("cls");
}



void cetakStruk()
{
    time_t waktuPembayaran;
    waktuPembayaran = time(NULL);
    struct tm tm = *localtime(&waktuPembayaran);

    FILE *struk;

    struk = fopen("strukPembayaran.txt", "a");
    if (struk == NULL) return 1;

    float biayaKeseluruhan;
    fprintf(struk, "\n\n\t\t ________________________________________________________________________\n");
    fprintf(struk, "\t\t|+______________________________________________________________________+|\n");
    fprintf(struk, "\t\t||                                                                      ||\n");
    fprintf(struk, "\t\t||                 PERUMDA AIR MINUM DENPASAR NUSANTARA                 ||\n");
    fprintf(struk, "\t\t||           S T R U K  P E M B A Y A R A N  A I R  M I N U M           ||\n");
    fprintf(struk, "\t\t||                                                                      ||\n");
    for(int j = 0 ; j <= i ; j++){
    fprintf(struk, "\t\t|| ==================================================================== ||\n");
    fprintf(struk, "\t\t||                        [Identitas Pelanggan]                         ||\n");
    fprintf(struk, "\t\t||                                                                      ||\n");
    fprintf(struk, "\t\t||   Nama     : %s ", nama[j]);
    fprintf(struk, "\t\t||   Alamat   : %s ", alamat[j]);
    fprintf(struk, "\t\t|| -------------------------------------------------------------------- ||\n");
    fprintf(struk, "\t\t||                           [Daftar Biaya]                             ||\n" );
    fprintf(struk, "\t\t||                                                                      ||\n");
    fprintf(struk, "\t\t||   Kategori           : %s \n", kategori[j]);
    fprintf(struk, "\t\t||   Total Pemakaian    : %.2f m3\n", totalPemakaian[j]);
    fprintf(struk, "\t\t||   Tanggal            : %d-%d-%d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    fprintf(struk, "\t\t||   Jatuh Tempo        : %d-%d-%d\n", tempo, tm.tm_mon+1, tm.tm_year+1900);
    fprintf(struk, "\t\t||   Tarif Pemakaian    : Rp%.2f \n", tarifPemakaian[j]);
    fprintf(struk, "\t\t||   Biaya Administrasi : Rp%.2f \n", biayaAdmin);
    fprintf(struk, "\t\t||   Biaya Pemeliharaan : Rp%.2f \n", BPM[j]);
    fprintf(struk, "\t\t||   Denda              : Rp%.2f \n", Denda);
    fprintf(struk, "\t\t|| -------------------------------------------------------------------- ||\n");
    fprintf(struk, "\t\t||   Total Pembayaran   : Rp%.2f \n", totalBiaya[j]);
    biayaKeseluruhan = biayaKeseluruhan + totalBiaya[j];
    }
    fprintf(struk, "\t\t|| ==================================================================== ||\n");
    fprintf(struk, "\t\t||                                                                      ||\n");
    fprintf(struk, "\t\t||   Total biaya keseluruhan: %.2f\n", biayaKeseluruhan);
    fprintf(struk, "\t\t|+______________________________________________________________________+|\n");
    fprintf(struk, "\t\t ________________________________________________________________________ \n\n");
    fprintf(struk, "\t\t ________________________________________________________________________ \n\n\n");

    fclose(struk);
}


void keluar()
{
    system("cls");
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||                       T E R I M A  K A S I H                         ||\n");
    printf("\t\t||                    Sampai jumpa di lain waktu!                       ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    exit (0);
}


float validasiFloat(float *var)
{
    fflush(stdin);
    char buffer[1024];
    char cek;
    if(fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if(sscanf(buffer, "%f %c", var, &cek) == 1)
        return *var;
    }
    return 0;
}


void validasiInput(float *var)
{
    while (1)
    {
      fflush(stdin);
      if (validasiFloat(var))
        break;
      printf("\t\t Masukan salah. Mohon masukkan input sesuai arahan.\n");
      printf("\t\t Masukkan input: ");
    }
}

void validasiNegatif(float *var)
{
    while (1)
    {
      validasiInput(var);
      fflush(stdin);
      if (*var > 0)
        break;
      printf("\t\t Masukan salah. Mohon masukkan input sesuai arahan.\n");
      printf("\t\t Masukkan input: ");
    }
}


void validasiMenu(float *var, int batas1, int batas2)
{
    while (1)
    {
      validasiInput(var);
      fflush(stdin);
      if (batas1 <= *var && *var <= batas2)
        break;
      printf("\t\t Masukan salah. Mohon masukkan input sesuai arahan.\n");
      printf("\t\t Masukkan input: ");
    }
}


void hapusStrukPembayaran()
{
    float pilMenu;
    printf("\t\t ________________________________________________________________________\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t||          Apakah Anda yakin ingin menghapus riwayat pembayaran?       ||\n");
    printf("\t\t||               Tekan [1] untuk YA dan [2] untuk TIDAK                 ||\n");
    printf("\t\t||                                                                      ||\n");
    printf("\t\t|+______________________________________________________________________+|\n");
    printf("\t\t ________________________________________________________________________ \n");
    printf("\t\t ");
    validasiMenu(&pilMenu, 1, 2);
    if(pilMenu == 1){
        FILE *riwayat;

        riwayat = fopen("strukPembayaran.txt", "w");
        if(riwayat == NULL) return 1;
        fclose(riwayat);

        printf("\t\t ________________________________________________________________________\n");
        printf("\t\t|+______________________________________________________________________+|\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t||               Seluruh riwayat pembayaran telah dihapus               ||\n");
        printf("\t\t||            Tekan ENTER untuk kembali ke menu administrator.          ||\n");
        printf("\t\t||                                                                      ||\n");
        printf("\t\t|+______________________________________________________________________+|\n");
        printf("\t\t ________________________________________________________________________ \n");
        printf("\t\t ");
        getchar();
        system("cls");
        menuAdmin();
    } else if(pilMenu==2){
        system("cls");
        menuAdmin();
    }
}


void riwayatStrukPembayaran()
{
    FILE *riwayat;

    riwayat = fopen("strukPembayaran.txt", "r");

    char *teks;
    long numbytes;

    if(riwayat == NULL) return 1;

    fseek(riwayat, 0L, SEEK_END);
    numbytes = ftell(riwayat);
    fseek(riwayat, 0L, SEEK_SET);

    teks = (char*)calloc(numbytes, sizeof(char));
    if(teks == NULL)
        return 1;

    fread(teks, sizeof(char), numbytes, riwayat);
    fclose(riwayat);

    printf("%s", teks);

    printf("\t\t  Tekan ENTER untuk melanjutkan.\n");
    printf("\t\t ");
    getchar();
    system("cls");
    menuAdmin();
}
