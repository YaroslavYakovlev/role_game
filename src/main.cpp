#include <iostream>
#include <vector>
#include <ctime>

#define HERO
#define PRINT

const int col = 10;
const int row = 10; 
char arena[col][row];

struct Person {
  std::string namePerson = "Unknown";
  int hpPerson = 0;
  int armorPerson = 0;
  int damagePerson = 0;
  int X = 0;
  int Y = 0;
};

// void coordinates(std::vector<Person>& p){
//   p.X = rand() % 11;
//   Y = rand() % 11;
//   std::cout << "X - " << X << " Y - " << Y << std::endl;
// }

void creating_enemies(std::vector<Person>& p, int i){
    p[i].namePerson = ("Enumy #" + std::to_string(i+1));
    p[i].hpPerson = rand() % 100 + 50;
    p[i].armorPerson = rand() % 51;
    p[i].damagePerson = rand() % 15 + 15;
    p[i].X = rand() % 10 + 1;
    p[i].Y = rand() % 10 + 1;
    // coordinates();
}

void takeDamage(Person& p, int damage_received){
  p.armorPerson -= damage_received;
  if(p.armorPerson < 0){
    p.hpPerson += p.armorPerson;
    p.armorPerson = 0;
  }
}

void field(char _arena[row][col], std::vector<Person>& p){
    std::cout << std::endl;
      for(int i = 1; i <= row; ++i){
          for(int j = 1; j <= col; ++j){
            _arena[i][j] = '.';
              for(int k = 0; k < p.size(); k++){
                _arena[p[k].X][p[k].Y] = 'E';
                // _arena[p[k].X][p[k].Y] = 'P';
              }
            // _arena[_X][_Y] = 'P';
              std::cout << _arena[i][j] << " ";
          }
          std::cout << std::endl;
      }
    std::cout << std::endl;    
std::cout << "Size Person - " << p.size() << std::endl;
      for(int i = 0; i < p.size(); i++){
        std::cout << "p " << p[i].X << " " << p[i].Y <<std::endl;
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
  hero.X = rand() % 10 + 1;
  hero.Y = rand() % 10 + 1;
  #endif 
  // coordinates(hero);

  for (int i = 0; i < countEnumy; i++) {
    creating_enemies(pers, i);
  }
  field(arena, pers);

  // takeDamage(pers, 10);


#ifdef PRINT
  for(int i = 0; i < countEnumy; i++) {
    std::cout << "Name - " << pers[i].namePerson << std::endl;
    std::cout << "HP - " << pers[i].hpPerson << std::endl;
    std::cout << "Armor - " << pers[i].armorPerson << std::endl;
    std::cout << "Damage - " << pers[i].damagePerson << std::endl;
    std::cout << "Coordinats X - " << pers[i].X << std::endl;
    std::cout << "Coordinats Y - " << pers[i].Y << std::endl;

    std::cout << std::endl;
  }
#endif
#ifdef HERO
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
