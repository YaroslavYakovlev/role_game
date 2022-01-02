#include <ctime>
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

void field(char _arena[row][col], std::vector<Person>& p, Person& h) {
  std::cout << std::endl;
  for (int i = 1; i <= row; ++i) {
    for (int j = 1; j <= col; ++j) {
      _arena[i][j] = '.';
      for (int k = 0; k < p.size(); k++) {
        _arena[p[k].X][p[k].Y] = 'E';
        if (h.X <= row || h.Y <= col)
          _arena[h.X][h.Y] = 'P';
        // if((h.X == p[k].X) && (h.Y == p[k].Y)){
        //   std::cout << "GOOD" << std::endl;
        // }
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

int main() {
  std::cout << "Role game" << std::endl;
  std::string stepHero;
  std::vector<Person> pers(countEnumy);
  Person hero;
  Steps step;

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
    if (stepHero == step.top) {
      hero.X -= 1;
    } else if (stepHero == step.bottom) {
      hero.X += 1;
    } else if (stepHero == step.left) {
      hero.Y -= 1;
    } else if (stepHero == step.right) {
      hero.Y += 1;
    }
    for (int i = 0; i < countEnumy; i++)
      enemy_move(pers, i);
    field(arena, pers, hero);
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
