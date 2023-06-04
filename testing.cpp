#include <iostream>
#include <cstdlib>

using namespace std;

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
    {"Item E", 50},
};

int totalItems = sizeof(magicWheel) / sizeof(magicWheel[0]);

Item spinMagicWheel()
{
    srand(time(0));

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
        system("pause");
        Item selectedItem = spinMagicWheel();
        cout << "Anda mendapatkan: " << selectedItem.name << endl;

        cout << "Apakah Anda ingin memutar roda lagi? (Y/N): ";
        char input;
        cin >> input;

        if (input == 'N' || input == 'n')
        {
            break;
        }
    }

    cout << "Terima kasih telah bermain Gacha Magic Wheel!" << endl;

    return 0;
}
