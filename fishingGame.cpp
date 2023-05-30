#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct player
{
    int xp;
    int level;
    int luck;
    int money;
};

struct fish
{
    string name;
    int xp;
    int price;
};

void memancing();
int getFish(int playerLevel);

int main()
{
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
                 << "\t     Inventory   \n"
                 << "\t       Shope   \n";
            break;
        case 2:
            cout << "\t      Mancing      \n"
                 << "\t>>>  Inventory  <<<\n"
                 << "\t       Shope   \n";
            break;
        case 3:
            cout << "\t      Mancing      \n"
                 << "\t     Inventory   \n"
                 << "\t>>>    Shope    <<<\n";
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
    }
    switch (selected)
    {
    case 1:
        memancing();
        break;

    case 2:
        break;

    case 3:
        break;
    }
    system("pause");
}

void memancing()
{
    int selected = 1, input;
    int fishCount = 0;
    while (true)
    {
        while (true)
        {
            system("cls");
            cout << "========================================\n"
                 << "=============== Memancing ==============\n"
                 << "========================================\n";
            if (fishCount != 0)
            {
                cout << "Anda mendapatkan " << fishCount << " ikan!" << endl;
            }
            switch (selected)
            {
            case 1:
                cout << "(PANCING)    "
                     << "    SHOPE    "
                     << "    KE MENU    \n";
                break;
            case 2:
                cout << "PANCING    "
                     << "    (SHOPE)    "
                     << "    KE MENU    \n";
                break;
            case 3:
                cout << "PANCING    "
                     << "    SHOPE    "
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
            fishCount = getFish(1);
            break;

        case 2:
            break;

        case 3:
            main();
            break;
        }
    }
}

int getFish(int playerLevel)
{
    srand(time(0));

    int lowerBound = playerLevel * 5;
    int upperBound = playerLevel * 10;
    int fishCount = rand() % (upperBound - lowerBound + 1) + lowerBound;

    return fishCount;
}