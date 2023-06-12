#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

const int MAX_LEVEL = 10;

struct Fish
{
    string name;
    double weight;
    int rarity;
    int price;
    Fish *next;
};

struct Player
{
    string name;
    int XP;
    int level;
    int money;
    string item[3];
    Fish *inventory;
    int xpNeededToUp[MAX_LEVEL + 1] = {0, 100, 200, 400, 650, 800, 1000, 1300, 1550, 1750, 2000};
};

Fish FishesData[30];
Player player;
string pesan;
bool levelup = false;

void addFishToInventory(Player &player, string fishName, float fishWeight, int fishRarity, int fishPrice);
void displayInventory();
void loadDataFish();
Fish luckGetFish();
void fishing();
void levelUp(Player &player);

int main()
{
    loadDataFish();
    player.name = "John Doe";
    player.XP = 0;
    player.level = 1;
    player.money = 1000;
    int selected = 1, input;
    while (true)
    {
        system("cls");
        cout << "========================================\n"
             << "======= Silahkan Pilih Aksi Anda =======\n"
             << "========================================\n";
        switch (selected)
        {
        case 1:
            cout << "\t>>>   Mancing   <<<\n"
                 << "\t       Shope       \n"
                 << "\t       Exit        \n";
            break;
        case 2:
            cout << "\t      Mancing      \n"
                 << "\t>>>    Shope    <<<\n"
                 << "\t       Exit        \n";
            break;
        case 3:
            cout << "\t      Mancing      \n"
                 << "\t       Shope       \n"
                 << "\t>>>    Exit     <<<\n";
            break;
        }
        input = getch();
        switch (input)
        {
        case 80:
        {
            selected++;
            if (selected > 3)
            {
                selected = 1;
            }
            break;
        }
        case 72:
            selected--;
            if (selected < 1)
            {
                selected = 3;
            }
            break;
        }
        if (input == 13)
        {
            break;
        }
        else if (input == 'i')
        {
            displayInventory();
        }
    }
    switch (selected)
    {
    case 1:
        fishing();
        break;

    case 2:
        break;

    case 3:
        char input;
        cout << "Yakin Mau Keluar [Y/N] = ";
        cin >> input;
        if (input == 'Y' || input == 'y')
        {
            return 0;
        }
        else if (input == 'N' || input == 'n')
        {
            main();
        }
        break;
    }
    system("pause");
    return 0;
}

void addFishToInventory(Player &player, string fishName, float fishWeight, int fishRarity, int fishPrice)
{
    Fish *newFish = new Fish;
    newFish->name = fishName;
    newFish->weight = fishWeight;
    newFish->rarity = fishRarity;
    newFish->price = fishPrice;
    newFish->next = nullptr;

    if (player.inventory == nullptr)
    {
        player.inventory = newFish;
    }
    else
    {
        Fish *current = player.inventory;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newFish;
    }
}

void displayInventory()
{
    cout << "Inventory Ikan:\n";
    if (player.inventory == nullptr)
    {
        cout << "Tidak ada ikan dalam inventory.\n";
    }

    int count = 1;
    Fish *current = player.inventory;
    while (current != nullptr)
    {
        cout << count << ". Nama: " << current->name << "\n";
        cout << "   Berat: " << current->weight << " lbs\n";
        cout << "   Kelangkaan: " << current->rarity << "\n";
        cout << "   Harga: $" << current->price << "\n";
        cout << "-----------------\n";

        current = current->next;
        count++;
    }
    system("pause");
}

void loadDataFish()
{
    ifstream fileFish;
    fileFish.open("ikan.txt");
    if (fileFish.is_open())
    {
        int index = 0;
        string line;
        while (getline(fileFish, line) && index < 30)
        {
            int pos = line.find(',');
            FishesData[index].name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            FishesData[index].rarity = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(',');
            FishesData[index].price = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            FishesData[index].weight = stod(line);
            index++;
        }
        fileFish.close();
    }
    else
    {
        cout << "File ikan.txt is missing" << endl;
    }
}

Fish luckGetFish()
{
    srand(time(0));
    int maxRarity = 0;
    for (int i = 0; i < 30; i++)
    {
        if (FishesData[i].rarity > maxRarity)
        {
            maxRarity = FishesData[i].rarity;
        }
    }

    int fishIndex = -1;
    while (fishIndex == -1)
    {
        int randomIndex = rand() % 30;
        int rarityDifference = maxRarity - FishesData[randomIndex].rarity;
        int randomValue = rand() % maxRarity;
        if (randomValue >= rarityDifference)
        {
            fishIndex = randomIndex;
        }
    }

    addFishToInventory(player, FishesData[fishIndex].name, FishesData[fishIndex].weight, FishesData[fishIndex].rarity, FishesData[fishIndex].price);
    return FishesData[fishIndex];
}

void fishing()
{
    int selected = 1, input;
    int fishCount = 0;
    Fish selectedItem;
    while (true)
    {
        while (true)
        {
            if (levelup)
            {
                system("cls");
                cout << pesan << endl;
                cout << "tekan Enter untuk keluar\n";
                system("pause");
            }
            system("cls");
            cout << "========================================\n"
                 << "=============== Memancing ==============\n"
                 << "========================================\n"
                 << "Money : " << player.money << "  Xp : " << player.XP << " Level : " << player.level << endl;
            if (selectedItem.name != "\0")
            {
                cout << "Get " << selectedItem.name << " (" << selectedItem.weight << " lbs)"
                     << "\nPrice : " << selectedItem.price << "\nGain " << selectedItem.price / 1000 << "Xp" << endl;
                player.XP += selectedItem.price / 1000;
            }
            cout << endl;
            switch (selected)
            {
            case 1:
                cout << "(PANCING)    "
                     << "     SHOP      "
                     << "     KE MENU     \n";
                break;
            case 2:
                cout << "PANCING      "
                     << "    (SHOP)     "
                     << "     KE MENU     \n";
                break;
            case 3:
                cout << "PANCING      "
                     << "     SHOP      "
                     << "    (KE MENU)    \n";
                break;
            }
            input = getch();
            switch (input)
            {
            case 77:
            {
                selected++;
                if (selected > 3)
                {
                    selected = 1;
                }
                break;
            }
            case 75:
                selected--;
                if (selected < 1)
                {
                    selected = 3;
                }
                break;
            }
            if (input == 13)
            {
                break;
            }
        }
        switch (selected)
        {
        case 1:
            selectedItem = luckGetFish();
            levelUp(player);
            break;

        case 2:
            break;

        case 3:
            main();
            break;
        }
    }
}

void levelUp(Player &player)
{
    int xpNeeded = player.xpNeededToUp[player.level];

    if (player.XP >= xpNeeded && player.level < MAX_LEVEL)
    {
        player.level++;
        player.XP -= xpNeeded;

        player.money += player.level * 1000;

        levelup = true;

        pesan = "Selamat! Level Anda telah naik menjadi " + to_string(player.level) + "!\n" + "Kamu Mendapatkan Rp" + to_string(player.level * 1000) + "\n";
    }
}