#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>

// #define HERO
// #define PRINT

const int col = 10;
const int row = 10; 
char arena[col][row];
int X = -1;
int Y = -1;
bool bEnumy = false;
bool bHero = false;

struct Person {
  std::string namePerson = "Unknown";
  int hpPerson = 0;
  int armorPerson = 0;
  int damagePerson = 0;
};

void coordinates(){
  X = rand() % 11;
  Y = rand() % 11;
  std::cout << "X - " << X << " Y - " << Y << std::endl;
}

void creating_enemies(std::vector<Person>& p, int i){
    p[i].namePerson = ("Enumy #" + std::to_string(i+1));
    p[i].hpPerson = rand() % 100 + 50;
    p[i].armorPerson = rand() % 51;
    p[i].damagePerson = rand() % 15 + 15;
    // coordinates();
    bEnumy = true;
}

void takeDamage(Person& p, int damage_received){
  p.armorPerson -= damage_received;
  if(p.armorPerson < 0){
    p.hpPerson += p.armorPerson;
    p.armorPerson = 0;
  }
}

void field(char _arena[col][row], int _X, int _Y){

    // int columns = sizeof(field[0]) / sizeof(field[0][0]);
    std::cout << std::endl;
    for(int i = 0; i < col; ++i){
        for(int j = 0; j < row; ++j){
          _arena[i][j] = '.';
          if(bEnumy){
            _arena[_X][_Y] = 'E';
            // bEnumy = false;
            }
          else if(bHero){
            _arena[_X][_Y] = 'P';
            // bHero = false;
          }
            std::cout << _arena[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
  std::cout << "Role game" << std::endl;
  const int countEnumy = 5;
  std::vector<Person> pers(countEnumy);
  Person hero;

  srand(time(NULL));
  #ifdef HERO
  std::cout << "Enter name, HP, armor, damage your person" << std::endl;
  std::cin >> hero.namePerson;
  std::cin >> hero.hpPerson;
  std::cin >> hero.armorPerson;
  std::cin >> hero.damagePerson;
  #endif 
  bHero = true;
  coordinates();

  for (int i = 0; i < countEnumy; i++) {
    creating_enemies(pers, i);
    coordinates();
  std::cout << "X = " << X << std::endl;
  std::cout << "Y = " << Y << std::endl;
  }
  field(arena, X, Y);

  // takeDamage(pers, damagePeron);


#ifdef PRINT
  for(int i = 0; i < countEnumy; i++) {
    std::cout << "Name - " << pers[i].namePerson << std::endl;
    std::cout << "HP - " << pers[i].hpPerson << std::endl;
    std::cout << "Armor - " << pers[i].armorPerson << std::endl;
    std::cout << "Damage - " << pers[i].damagePerson << std::endl;
    std::cout << std::endl;
  }

    std::cout << "Name - " << hero.namePerson << std::endl;
    std::cout << "HP - " << hero.hpPerson << std::endl;
    std::cout << "Armor - " << hero.armorPerson << std::endl;
    std::cout << "Damage - " << hero.damagePerson << std::endl;
    std::cout << std::endl;
#endif 
  return 0;
}
