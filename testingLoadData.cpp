#include <iostream>
#include <fstream>
#include <string>

// Fungsi untuk mengenkripsi data progres
std::string EncryptData(const std::string &data, int shift)
{
    std::string encryptedData = data;

    for (char &c : encryptedData)
    {
        if (std::isalpha(c))
        {
            c = (c - 'a' + shift) % 26 + 'a'; // Melakukan pergeseran sesuai dengan nilai shift
        }
    }

    return encryptedData;
}

// Fungsi untuk mendekripsi data progres
std::string DecryptData(const std::string &encryptedData, int shift)
{
    std::string decryptedData = encryptedData;

    for (char &c : decryptedData)
    {
        if (std::isalpha(c))
        {
            c = (c - 'a' - shift + 26) % 26 + 'a'; // Melakukan pergeseran balik sesuai dengan nilai shift
        }
    }

    return decryptedData;
}

// Fungsi untuk menyimpan progres dengan enkripsi ke dalam berkas
void SaveProgressToFile(const std::string &encryptedData)
{
    std::ofstream file(".encrypted_progress.txt");

    if (file.is_open())
    {
        file << encryptedData << std::endl;

        file.close();
        std::cout << "Progres berhasil disimpan dengan enkripsi." << std::endl;
    }
    else
    {
        std::cout << "Gagal membuka berkas untuk penyimpanan progres." << std::endl;
    }
}

// Fungsi untuk memuat progres dengan enkripsi dari berkas
std::string LoadProgressFromFile()
{
    std::string encryptedData;

    std::ifstream file(".encrypted_progress.txt");

    if (file.is_open())
    {
        std::getline(file, encryptedData);

        file.close();
        std::cout << "Progres berhasil dimuat dengan enkripsi." << std::endl;
    }
    else
    {
        std::cout << "Gagal membuka berkas untuk memuat progres." << std::endl;
    }

    return encryptedData;
}

int main()
{
    int choice;

    while (true)
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Save progress" << std::endl;
        std::cout << "2. Load progress" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Pilih opsi: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Lakukan operasi save
            std::string playerProgress;
            std::cout << "Masukkan data progres: ";
            std::cin.ignore(); // Mengabaikan karakter newline sebelum membaca string
            std::getline(std::cin, playerProgress);

            int encryptionShift;
            std::cout << "Masukkan nilai shift enkripsi: ";
            std::cin >> encryptionShift;

            std::string encryptedProgress = EncryptData(playerProgress, encryptionShift);
            SaveProgressToFile(encryptedProgress);
            break;
        }
        case 2:
        {
            // Lakukan operasi load
            int encryptionShift;
            std::cout << "Masukkan nilai shift enkripsi: ";
            std::cin >> encryptionShift;

            std::string loadedProgress = LoadProgressFromFile();
            std::string decryptedProgress = DecryptData(loadedProgress, encryptionShift);
            std::cout << "Progres yang didekripsi: " << decryptedProgress << std::endl;
            break;
        }
        case 3:
            return 0;
        default:
            std::cout << "Opsi tidak valid." << std::endl;
            break;
        }

        std::cout << std::endl;
    }
}
