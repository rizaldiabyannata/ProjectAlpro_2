#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_FISHES = 30;

struct playerAtribut
{
    string name;
    int XP = 0;
    int level = 0;
    int money = 1000;
};

struct fish
{
    string name;
    float weight;
    int rarity;
    int price;
};

struct inventory
{
};

void memancing();
void loadDataFish();
void cheatDataFishes();
fish luckGetFish();
void getPlayerName();
int luckCheck();

playerAtribut Player;
fish Fishes[MAX_FISHES];
bool created = false;

int main()
{
    int selected = 1, input;
    loadDataFish();
    if (created)
    {
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
                     << "\t       Shope   \n"
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
            else if (input == 'c')
            {
                string cheat;
                cout << "cheat = ";
                cin >> cheat;
                if (cheat == "datafish")
                {
                    cheatDataFishes();
                }
                else if (cheat == "checkluck")
                {
                    int random = luckCheck();
                    cout << random;
                    system("pause");
                }
            }
        }
        switch (selected)
        {
        case 1:
            memancing();
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
    }
    else
    {
        getPlayerName();
    }
    system("pause");
}

void memancing()
{
    int selected = 1, input;
    int fishCount = 0;
    fish selectedItem;
    while (true)
    {
        while (true)
        {
            system("cls");
            Player.XP += selectedItem.price / 1000;
            cout << "========================================\n"
                 << "=============== Memancing ==============\n"
                 << "========================================\n"
                 << "Money : " << Player.money << "  Xp : " << Player.XP << endl;
            if (selectedItem.name != "\0")
            {
                cout << "Get " << selectedItem.name << " (" << selectedItem.weight << " lbs)"
                     << "\nPrice : " << selectedItem.price << "\nGain " << selectedItem.price / 1000 << "Xp" << endl;
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
            break;

        case 2:
            break;

        case 3:
            main();
            break;
        }
    }
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
            Fishes[index].name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            Fishes[index].rarity = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(',');
            Fishes[index].price = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            Fishes[index].weight = stof(line);
            index++;
        }
        fileFish.close();
    }
    else
    {
        cout << "File ikan.txt is missing" << endl;
    }
}

void getPlayerName()
{
    cout << "================= Create Character ================\n"
         << "Name : ";
    cin >> Player.name;
    created = true;
    main();
}

void cheatDataFishes()
{
    for (int i = 0; i < 30; i++)
    {
        cout << " " << Fishes[i].name << " " << Fishes[i].price << " " << Fishes[i].rarity << " " << Fishes[i].weight << endl;
    }
    system("pause");
}

fish luckGetFish()
{
    srand(time(0));

    int totalRarity = 0;
    for (int i = 0; i < MAX_FISHES; i++)
    {
        totalRarity += Fishes[i].rarity;
    }
    int randomNumber = rand() % totalRarity + 1;
    int accumulatedRarity = 0;
    for (int i = 0; i < MAX_FISHES; i++)
    {
        accumulatedRarity += Fishes[i].rarity;
        if (randomNumber <= accumulatedRarity)
        {
            return Fishes[i];
        }
    }
    return {"Item Default", 0};
}

int luckCheck()
{
    srand(time(0));

    int totalRarity = 0;
    for (int i = 0; i < MAX_FISHES; i++)
    {
        totalRarity += Fishes[i].rarity;
    }

    if (totalRarity == 0)
    {
        // Mengembalikan nilai khusus atau melakukan tindakan lain sesuai kebutuhan Anda
        return 0;
    }

    int randomNumber = rand() % totalRarity + 1;
    return randomNumber;
}
