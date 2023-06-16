#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

const int MAX_LEVEL = 10;

struct Fish
{
  string name;
  float weight;
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
  int numOfbait;
  int itemLevel[2];
  Fish *inventory;
  int xpNeededToUp[MAX_LEVEL + 1] = {0, 100, 200, 400, 650, 800, 1000, 1300, 1550, 1750, 2000};
};

Fish FishesData[30];
Player player;
string pesan;
bool levelup = false, registed;
int loadCount = 0;

void loadDataFish();
void fishing();
void inventory();
void shop();
void levelUp(Player &player);
void sortFishNames(Fish *head);
void addFishToInventory(Player &player, string fishName, float fishWeight, int fishRarity, int fishPrice);
Fish luckGetFish(int level);
void saveGame(const Player &player);
void loadGame();

int main()
{
  loadGame();
  loadDataFish();
  if (player.name == "\0")
  {
    cout << "========================================\n"
         << "============ SELAMAT DATANG ============\n"
         << "========================================\n";
    player.level = 1;
    player.money = 1000;
    player.numOfbait = 10;
    player.itemLevel[0] = 1;
    player.itemLevel[1] = 1;
    player.XP = 0;
    cout << "Selamat Datang\nSilahkan Masukkan Nickname Anda = ";
    cin >> player.name;
    registed = true;
  }
  int selected = 1, input;
  while (true)
  {
    system("cls");
    cout << "========================================\n"
         << "============ SELAMAT DATANG ============\n"
         << "========================================\n"
         << "Level :" << player.level << "\tUang :Rp" << player.money << "\n"
         << "XP :" << player.XP << "\t\tUmpan :" << player.numOfbait << "\n"
         << "========================================\n"
         << "======= Silahkan Pilih Aksi Anda =======\n"
         << "========================================\n";
    switch (selected)
    {
    case 1:
      cout << "\t>>>   Mancing   <<<\n"
           << "\t     Inventory      \n"
           << "\t       Shop        \n"
           << "\t       Exit        \n";
      break;
    case 2:
      cout << "\t      Mancing      \n"
           << "\t>>>  Inventory  <<<\n"
           << "\t       Shop        \n"
           << "\t       Exit        \n";
      break;
    case 3:
      cout << "\t      Mancing      \n"
           << "\t     Inventory     \n"
           << "\t>>>    Shop     <<<\n"
           << "\t       Exit        \n";
      break;
    case 4:
      cout << "\t      Mancing      \n"
           << "\t     Inventory     \n"
           << "\t       Shop        \n"
           << "\t>>>    Exit     <<<\n";
      break;
    }
    input = getch();
    switch (input)
    {
    case 80:
    {
      selected++;
      if (selected > 4)
      {
        selected = 1;
      }
      break;
    }
    case 72:
      selected--;
      if (selected < 1)
      {
        selected = 4;
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
    fishing();
    break;

  case 2:
    inventory();
    break;

  case 3:
    shop();
    break;
  case 4:
    cout << "Apakah Anda Yakin Ingin Keluar [Y/N] = ";
    char exitInput;
    cin >> exitInput;
    if (exitInput == 'y' || exitInput == 'Y')
    {
      saveGame(player);
      exit(0);
    }
    else
    {
      player.inventory = nullptr;
      main();
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
      FishesData[index].name = line.substr(0, pos);
      line.erase(0, pos + 1);
      pos = line.find(',');
      FishesData[index].rarity = stoi(line.substr(0, pos));
      line.erase(0, pos + 1);
      pos = line.find(',');
      FishesData[index].price = stoi(line.substr(0, pos));
      line.erase(0, pos + 1);
      FishesData[index].weight = stof(line);
      index++;
    }
    fileFish.close();
  }
  else
  {
    cout << "File ikan.txt is missing" << endl;
  }
}

void inventory()
{
  int selected = 1, input;
  while (true)
  {
    while (true)
    {
      system("cls");
      Fish *current = player.inventory;
      cout << "Inventory Ikan:\n";
      if (player.inventory == nullptr)
      {
        cout << "Tidak ada ikan dalam inventory.\n";
      }
      else
      {
        sortFishNames(current);
        cout << setw(4) << "No." << setw(15) << "Nama" << setw(10) << "Berat" << setw(10) << "Jumlah" << setw(10) << "Harga" << endl;
        cout << "------------------------------------------------------\n";

        int count = 1;
        string nameFish;
        while (current != nullptr)
        {
          int jumlah = 1;
          Fish *temp = current->next;
          while (temp != nullptr)
          {
            if (temp->name == current->name)
            {
              jumlah++;
            }
            temp = temp->next;
          }
          if (current->name != nameFish)
          {
            cout << setw(4) << count << setw(15) << current->name << setw(10) << current->weight << setw(10) << jumlah << setw(7) << "Rp" << current->price * jumlah << endl;
            count++;
          }
          nameFish = current->name;
          current = current->next;
        }
      }
      cout << endl;
      switch (selected)
      {
      case 1:
        cout << "(Jual Semua)" << setw(15) << " Kembali ";
        break;

      case 2:
        cout << " Jual Semua " << setw(15) << "(Kembali)";
        break;
      }
      input = getch();
      switch (input)
      {
      case 77:
        selected++;
        if (selected > 2)
        {
          selected = 1;
        }
        break;

      case 75:
        selected--;
        if (selected < 1)
        {
          selected = 2;
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
    {
      bool selled = false;
      Fish *current = player.inventory;
      while (current != nullptr)
      {
        player.money += current->price;
        Fish *temp = current;
        current = current->next;
        delete temp;
        selled = true;
      }
      if (!selled)
      {
        system("cls");
        cout << "Tidak ada ikan yang dapat di jual" << endl;
        system("pause");
        saveGame(player);
        main();
      }
      player.inventory = nullptr;
      system("cls");
      cout << "Anda Telah Menjual Semua Ikan\nUang Anda Sekarang Rp" << player.money << endl;
      system("pause");
      saveGame(player);
      main();
    }
    break;
    case 2:
      saveGame(player);
      player.inventory = nullptr;
      main();
      break;
    }
  }
  saveGame(player);
}

void fishing()
{
  int selected = 1, input;
  int fishCount = 0;
  Fish selecteditemLevel;
  while (true)
  {
    while (true)
    {
      if (levelup)
      {
        system("cls");
        cout << pesan << endl;
        cout << "tekan Enter untuk keluar\n";
        levelup = false;
        system("pause");
      }
      system("cls");
      cout << "==========================================\n"
           << "================ Memancing ===============\n"
           << "==========================================\n"
           << "Level :" << player.level << "\tUang :Rp" << player.money << "\n"
           << "XP :" << player.XP << "\t\tUmpan :" << player.numOfbait << "\n";
      if (player.numOfbait == 0)
      {
        cout << "\n         Kehabisan Umpan\n";
      }
      else
      {
        if (selecteditemLevel.name != "\0")
        {
          cout << "\nMendapatkan " << selecteditemLevel.name << " (" << selecteditemLevel.weight << " lbs)"
               << "\nHarga : Rp" << selecteditemLevel.price << endl;
          if (selecteditemLevel.price / 1000 == 0)
          {
            player.XP += 1;
            cout << "Memperoleh " << 1 << "XP" << endl;
          }
          else
          {
            player.XP += selecteditemLevel.price / 1000;
            cout << "Memperoleh " << selecteditemLevel.price / 1000 << "XP" << endl;
          }
        }
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
      if (player.numOfbait > 0)
      {
        player.numOfbait--;
        selecteditemLevel = luckGetFish(player.level);
        levelUp(player);
      }
      break;

    case 2:
      saveGame(player);
      shop();
      break;

    case 3:
      saveGame(player);
      player.inventory = nullptr;
      main();
      break;
    }
  }
}

Fish luckGetFish(int level)
{
  srand(time(0));
  int minIndex = level - 1;
  int maxIndex = level + 4;
  if (minIndex < 0)
  {
    minIndex = 0;
  }
  if (maxIndex >= 30)
  {
    maxIndex = 29;
  }

  int maxRarity = 0;
  for (int i = minIndex; i <= maxIndex; i++)
  {
    if (FishesData[i].rarity > maxRarity)
    {
      maxRarity = FishesData[i].rarity + player.itemLevel[0] * 10 + player.itemLevel[1] * 5;
    }
  }

  int fishIndex = -1;
  while (fishIndex == -1)
  {
    int randomIndex = rand() % (maxIndex - minIndex + 1) + minIndex;
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

void shop()
{
  int selected = 1, input;
  while (true)
  {
    while (true)
    {
      system("cls");
      cout << "Shop\t\tUang :Rp" << player.money << endl;
      switch (selected)
      {
      case 1:
        cout << "> Menaikkan Level Pancingan\tRp" << player.itemLevel[0] * 50000 << "\n  Menaikkan Level Umpan\t\tRp" << player.itemLevel[1] * 10000 << "\n  Beli Umpan (10pcs)\t\tRp" << player.itemLevel[1] * 2500 << "\n  Kembali\n";
        break;

      case 2:
        cout << "  Menaikkan Level Pancingan\tRp" << player.itemLevel[0] * 50000 << "\n> Menaikkan Level Umpan\t\tRp" << player.itemLevel[1] * 10000 << "\n  Beli Umpan (10pcs)\t\tRp" << player.itemLevel[1] * 2500 << "\n  Kembali\n";
        break;

      case 3:
        cout << "  Menaikkan Level Pancingan\tRp" << player.itemLevel[0] * 50000 << "\n  Menaikkan Level Umpan\t\tRp" << player.itemLevel[1] * 10000 << "\n> Beli Umpan (10pcs)\t\tRp" << player.itemLevel[1] * 2500 << "\n  Kembali\n";
        break;
      case 4:
        cout << "  Menaikkan Level Pancingan\tRp" << player.itemLevel[0] * 50000 << "\n  Menaikkan Level Umpan\t\tRp" << player.itemLevel[1] * 10000 << "\n  Beli Umpan (10pcs)\t\tRp" << player.itemLevel[1] * 2500 << "\n> Kembali\n";
        break;
      }

      input = getch();
      switch (input)
      {
      case 72:
        selected--;
        if (selected < 1)
        {
          selected = 4;
        }
        break;

      case 80:
        selected++;
        if (selected > 4)
        {
          selected = 1;
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
      if (player.money >= player.itemLevel[0] * 50000)
      {
        player.money -= player.itemLevel[0] * 50000;
        player.itemLevel[0]++;
        cout << "Pancingan berhasil ditingkatkan menjadi level " << player.itemLevel[0] << endl;
      }
      else
      {
        cout << "Maaf, uang Anda tidak mencukupi untuk menaikkan level pancingan." << endl;
      }
      system("pause");
      break;

    case 2:
      if (player.money >= player.itemLevel[1] * 10000)
      {
        player.money -= player.itemLevel[1] * 10000;
        player.itemLevel[1]++;
        cout << "Umpan berhasil ditingkatkan menjadi level " << player.itemLevel[1] << endl;
      }
      else
      {
        cout << "Maaf, uang Anda tidak mencukupi untuk menaikkan level umpan." << endl;
      }
      system("pause");
      break;
    case 3:
      if (player.money >= player.itemLevel[1] * 2500)
      {
        player.numOfbait += 10;
        player.money -= player.itemLevel[1] * 2500;
        cout << "Umpan berhasil dibeli dengan level " << player.itemLevel[1] << " sebanyak 10pcs" << endl;
      }
      else
      {

        cout << "Maaf, uang Anda tidak mencukupi untuk membeli umpan." << endl;
      }
      system("pause");
      break;
    case 4:
      saveGame(player);
      player.inventory = nullptr;
      main();
    }
  }
}

void sortFishNames(Fish *head)
{
  if (head == nullptr || head->next == nullptr)
  {
    return;
  }

  bool swapped;
  Fish *current;
  Fish *last = nullptr;

  do
  {
    swapped = false;
    current = head;

    while (current->next != last)
    {
      if (current->name > current->next->name)
      {
        swap(current->name, current->next->name);
        swapped = true;
      }
      current = current->next;
    }
    last = current;
  } while (swapped);
}

void saveGame(const Player &player)
{
  ofstream file("savegame.txt");
  if (file.is_open())
  {
    file << player.name << endl;
    file << player.XP << endl;
    file << player.level << endl;
    file << player.money << endl;
    file << player.numOfbait << endl;
    file << player.itemLevel[0] << endl;
    file << player.itemLevel[1] << endl;
    int index = 1;
    Fish *current = player.inventory;
    while (current != nullptr)
    {
      file << current->name << ",";
      file << current->weight << ",";
      file << current->rarity << ",";
      file << current->price << " " << index << endl;
      current = current->next;
    }

    file.close();
    cout << "Progres permainan berhasil disimpan." << endl;
  }
  else
  {
    cout << "Gagal menyimpan progres permainan." << endl;
  }
}

void loadGame()
{
  ifstream file("savegame.txt");

  if (file.is_open())
  {
    string line;
    getline(file, line);
    player.name = line;
    getline(file, line);
    player.XP = stoi(line);
    getline(file, line);
    player.level = stoi(line);
    getline(file, line);
    player.money = stoi(line);
    getline(file, line);
    player.numOfbait = stoi(line);
    getline(file, line);
    player.itemLevel[0] = stoi(line);
    getline(file, line);
    player.itemLevel[1] = stoi(line);

    while (getline(file, line))
    {
      stringstream ss(line);
      string fishName;
      float fishWeight;
      int fishRarity, fishPrice;
      getline(ss, fishName, ',');
      ss >> fishWeight;
      ss.ignore();
      ss >> fishRarity;
      ss.ignore();
      ss >> fishPrice;
      addFishToInventory(player, fishName, fishWeight, fishRarity, fishPrice);
    }

    file.close();
    registed = true;
  }
  else
  {
    registed = false;
  }
}