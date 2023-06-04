#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Data
{
    string nama;
    int umur;
    string alamat;
};

int main()
{
    ifstream inputFile;
    inputFile.open("data.txt");

    if (inputFile.is_open())
    {
        Data data; // Deklarasi variabel struct
        string line;

        while (getline(inputFile, line))
        {
            string nama, alamat;
            int umur;

            // Mencari posisi spasi pertama
            size_t pos1 = line.find(' ');
            nama = line.substr(0, pos1);

            // Mencari posisi spasi kedua
            size_t pos2 = line.find(' ', pos1 + 1);
            string umurStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            umur = stoi(umurStr);

            // Mengambil sisa string sebagai alamat
            alamat = line.substr(pos2 + 1);

            data.nama = nama;
            data.umur = umur;
            data.alamat = alamat;

            // Lakukan operasi lain dengan struct
            cout << "Nama: " << data.nama << endl;
            cout << "Umur: " << data.umur << endl;
            cout << "Alamat: " << data.alamat << endl;
            cout << endl;
        }

        inputFile.close();
    }
    else
    {
        cout << "Gagal membuka file." << endl;
    }
    system("pause");
    return 0;
}
