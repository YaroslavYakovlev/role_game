#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#define HERO
// #define PRINT_HERO
// #define PRINT_ENUMY

const int col = 40;
const int row = 40;
int countEnumy = 5;
char arena[col][row];
std::string steps[] = {"left", "right", "top", "bottom"};
std::string word = "";
bool bConflict = false;
bool bDeadHero = false;
bool bDeadEnumy = false;
bool bFlag = false;

struct Person {
  std::string namePerson = "Unknown";
  int hpPerson = 0;
  int armorPerson = 0;
  int damagePerson = 0;
  int X = 0;
  int Y = 0;
};

struct Steps {
  std::string left = "left";      // Лево
  std::string right = "right";    // Право
  std::string top = "top";        // Вверх
  std::string bottom = "bottom";  // Низ
};

void creating_enemies(std::vector<Person>& p, int i) {
  p[i].namePerson = ("Enumy #" + std::to_string(i + 1));
  p[i].hpPerson = rand() % 100 + 50;
  p[i].armorPerson = rand() % 51;
  p[i].damagePerson = rand() % 15 + 15;
  p[i].X = rand() % 9 + 0;
  p[i].Y = rand() % 9 + 0;
}

void conflict(Person& p, Person& h) {
  std::cout << "GOOD" << std::endl;
  p.armorPerson -= h.damagePerson;
  h.armorPerson -= p.damagePerson;
  if (p.armorPerson < 0) {
    std::cout << "conflict - 1" << std::endl;
    p.hpPerson += p.armorPerson;
    p.armorPerson = 0;
  }
  if (h.armorPerson < 0) {
    std::cout << "conflict - 2" << std::endl;
    h.hpPerson += h.armorPerson;
    h.armorPerson = 0;
  }

  if (p.hpPerson < 0) {
    std::cout << "conflict - 3" << std::endl;
    bFlag = true;
    countEnumy--;
    if (countEnumy < 1)
      bDeadEnumy = true;
    std::cout << "arena[p.X][p.Y] " << arena[p.X][p.Y] << std::endl;
  } else if (h.hpPerson < 0) {
    std::cout << "conflict - 4" << std::endl;
    arena[h.X][h.Y] = '.';
    bDeadHero = true;
  }
}

void print_field(std::vector<Person>& p, Person& h) {
  std::cout << std::endl;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      arena[i][j] = '.';
      for (int k = 0; k < p.size(); k++) {
        if (p[k].X < row || p[k].Y < col) {
          if (bFlag) {
            p.erase(p.begin() + k);
            arena[p[k].X][p[k].Y] = '.';
            bFlag = false;
          } else
            arena[p[k].X][p[k].Y] = 'E';
        }
        if (h.X < row || h.Y < col)
          arena[h.X][h.Y] = 'P';
      }
      std::cout << arena[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
/**
 * ? Выставление "." только на момент совпадене координат
 **/
void enemy_move(std::vector<Person>& p, int i) {
  word = steps[rand() % 4];
  if (word == "top") {
    p[i].X -= 1;
  } else if (word == "bottom") {
    p[i].X += 1;
  } else if (word == "left") {
    p[i].Y -= 1;
  } else if (word == "right") {
    p[i].Y += 1;
  }
  std::cout << "Word - " << word << std::endl;
}

void save_progress(std::ofstream& file, Person& p, Person& h) {
  int lenP = p.namePerson.length();
  int lenH = h.namePerson.length();

  file.write((char*)&lenP, sizeof(lenP));
  file.write((char*)&lenH, sizeof(lenH));

  file.write(p.namePerson.c_str(), lenP);
  file.write(h.namePerson.c_str(), lenH);

  file.write((char*)&p.hpPerson, sizeof(p.hpPerson));
  file.write((char*)&h.hpPerson, sizeof(h.hpPerson));

  file.write((char*)&p.armorPerson, sizeof(p.armorPerson));
  file.write((char*)&h.armorPerson, sizeof(h.armorPerson));
}

void load_progress(std::ifstream& file, Person& p, Person& h) {
  int lenP;
  int lenH;

  file.read((char*)&lenP, sizeof(lenP));
  file.read((char*)&lenH, sizeof(lenH));

  p.namePerson.resize(lenP);
  h.namePerson.resize(lenH);

  file.read((char*)p.namePerson.c_str(), lenP);
  file.read((char*)h.namePerson.c_str(), lenH);

  file.read((char*)&p.hpPerson, sizeof(p.hpPerson));
  file.read((char*)&h.hpPerson, sizeof(h.hpPerson));

  file.read((char*)&p.armorPerson, sizeof(p.armorPerson));
  file.read((char*)&h.armorPerson, sizeof(h.armorPerson));
}

int main() {
  std::cout << "Role game" << std::endl;
  std::string stepHero;
  std::vector<Person> pers(countEnumy);
  Person hero;
  Steps step;
  std::ofstream save("..\\src\\File\\save.bin", std::ios::binary);
  std::ifstream load("..\\src\\File\\save.bin", std::ios::binary);

  srand(time(NULL));
#ifdef HERO
  std::cout << "Enter name, HP, armor, damage your person" << std::endl;
  std::cin >> hero.namePerson;
  std::cin >> hero.hpPerson;
  std::cin >> hero.armorPerson;
  std::cin >> hero.damagePerson;
  hero.X = rand() % 9 + 0;
  hero.Y = rand() % 9 + 0;

#endif
  for (int i = 0; i < countEnumy; i++) {
    creating_enemies(pers, i);
  }
  print_field(pers, hero);

  while (countEnumy > 0 || hero.hpPerson > 0) {
    std::cout << "The hero walks" << std::endl;
    std::cin >> stepHero;
    if (stepHero == "save")
      for (int i = 0; i < countEnumy; i++) {
        save_progress(save, pers[i], hero);
      }
    else if (stepHero == "load")
      for (int i = 0; i < countEnumy; i++) {
        load_progress(load, pers[i], hero);
      }
    else if (stepHero == step.top) {
      hero.X -= 1;
    } else if (stepHero == step.bottom) {
      hero.X += 1;
    } else if (stepHero == step.left) {
      hero.Y -= 1;
    } else if (stepHero == step.right) {
      hero.Y += 1;
    }
    for (int i = 0; i < pers.size(); i++) {
      /**
       * ! Перемещение противников
       **/
      enemy_move(pers, i);

      if ((hero.X == pers[i].X) && (hero.Y == pers[i].Y)) {
        conflict(pers[i], hero);
        if (bDeadEnumy) {
          std::cout << "All enemies killed, you won!" << std::endl;
          return 0;
        }
        if (bDeadHero) {
          std::cout << "Your hero died, you lost!" << std::endl;
          return 0;
        }
      }
      std::cout << "p.X " << pers[i].X << " p.Y " << pers[i].Y << std::endl;
      std::cout << "h.X " << hero.X << " h.Y " << hero.Y << std::endl;
      std::cout << "arena[pers.X][pers.Y] " << arena[pers[i].X][pers[i].Y] << std::endl;
      // if (bFlag) {
      //   for (int i = 0; i < pers.size(); i++) {
      //     arena[pers[i].X][pers[i].Y] = '.';
      //     bFlag = false;
      //   }
      // }
    }
    print_field(pers, hero);
  }

#ifdef PRINT_ENUMY
  for (int i = 0; i < countEnumy; i++) {
    std::cout << "Name - " << pers[i].namePerson << std::endl;
    std::cout << "HP - " << pers[i].hpPerson << std::endl;
    std::cout << "Armor - " << pers[i].armorPerson << std::endl;
    std::cout << "Damage - " << pers[i].damagePerson << std::endl;
    std::cout << "Coordinats X - " << pers[i].X << std::endl;
    std::cout << "Coordinats Y - " << pers[i].Y << std::endl;

    std::cout << std::endl;
  }
#endif
#ifdef PRINT_HERO
  std::cout << "Name - " << hero.namePerson << std::endl;
  std::cout << "HP - " << hero.hpPerson << std::endl;
  std::cout << "Armor - " << hero.armorPerson << std::endl;
  std::cout << "Damage - " << hero.damagePerson << std::endl;
  std::cout << "Coordinats X - " << hero.X << std::endl;
  std::cout << "Coordinats Y - " << hero.Y << std::endl;
  std::cout << std::endl;
#endif
  return 0;
}
