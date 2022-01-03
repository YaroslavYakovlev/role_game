#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#define HERO
// #define PRINT_HERO
// #define PRINT_ENUMY

const int col = 10;
const int row = 10;
const int countEnumy = 5;
char arena[col][row];
std::string steps[] = {"left", "right", "top", "bottom"};
std::string word = "";
bool bConflict = false;

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
  p[i].X = rand() % 10 + 1;
  p[i].Y = rand() % 10 + 1;
}

void takeDamage(Person& p, int damage_received) {
  p.armorPerson -= damage_received;
  if (p.armorPerson < 0) {
    p.hpPerson += p.armorPerson;
    p.armorPerson = 0;
  }
}

void conflict() {
  std::cout << "GOOD" << std::endl;
}

void field(char _arena[row][col], std::vector<Person>& p, Person& h) {
  std::cout << std::endl;
  for (int i = 1; i <= row; ++i) {
    for (int j = 1; j <= col; ++j) {
      _arena[i][j] = '.';
      for (int k = 0; k < p.size(); k++) {
        _arena[p[k].X][p[k].Y] = 'E';
        if (h.X <= row || h.Y <= col)
          _arena[h.X][h.Y] = 'P';
        if ((h.X == p[k].X) && (h.Y == p[k].Y)) {
          bConflict = true;
        }
      }
      std::cout << _arena[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

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
  hero.X = rand() % 10 + 1;
  hero.Y = rand() % 10 + 1;
#endif
  for (int i = 0; i < countEnumy; i++) {
    creating_enemies(pers, i);
  }
  field(arena, pers, hero);

  // takeDamage(pers, 10);
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
    /**
     * * Закоментировал рабочий код (передвижение врагов)
    for (int i = 0; i < countEnumy; i++)
      enemy_move(pers, i);
     */
    field(arena, pers, hero);
    if (bConflict)
      conflict();
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
