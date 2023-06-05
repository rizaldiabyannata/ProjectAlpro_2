#include <iostream>
#include <cstdlib>

using namespace std;

const int MAX_INPUT_SIZE = 100;

struct Item
{
    string name;
    int rarity;
};

Item magicWheel[] = {
    {"Item A", 5},
    {"Item B", 10},
    {"Item C", 15},
    {"Item D", 20},
    {"Item E", 1},
};

int totalItems = sizeof(magicWheel) / sizeof(magicWheel[0]);

void clearInputBuffer()
{
    while (cin.get() != '\n')
    {
        continue;
    }
}

Item spinMagicWheel()
{

    int totalRarity = 0;
    for (int i = 0; i < totalItems; i++)
    {
        totalRarity += magicWheel[i].rarity;
    }

    int randomNumber = rand() % totalRarity + 1;
    int accumulatedRarity = 0;
    for (int i = 0; i < totalItems; i++)
    {
        accumulatedRarity += magicWheel[i].rarity;
        if (randomNumber <= accumulatedRarity)
        {
            return magicWheel[i];
        }
    }

    // Jika terjadi kesalahan
    return {"Item Default", 0};
}

int main()
{
    cout << "Selamat datang di Gacha Magic Wheel!" << endl;

    while (true)
    {
        cout << "Tekan Enter untuk memutar roda...";
        clearInputBuffer();

        Item selectedItem = spinMagicWheel();
        cout << "Anda mendapatkan: " << selectedItem.name << endl;

        cout << "Apakah Anda ingin memutar roda lagi? (Y/N): ";
        char input[MAX_INPUT_SIZE];
        cin.getline(input, MAX_INPUT_SIZE);

        if (input[0] == 'N' || input[0] == 'n')
        {
            break;
        }
    }

    cout << "Terima kasih telah bermain Gacha Magic Wheel!" << endl;

    return 0;
}
