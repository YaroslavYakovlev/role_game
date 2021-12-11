#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>

const int col = 10;
const int row = 10; 
char arena[col][row];

struct Person {
  std::string namePerson = "Unknown";
  int hpPerson = 0;
  int armorPerson = 0;
  int damagePerson = 0;
};

void creating_enemies(std::vector<Person>& p, int countEnumy){
  for (int i = 0; i < countEnumy; i++) {
    p[i].namePerson = ("Enumy #" + std::to_string(i+1));
    p[i].hpPerson = rand() % 100 + 50;
    p[i].armorPerson = rand() % 51;
    p[i].damagePerson = rand() % 15 + 15;
  }
}

void takeDamage(Person& p, int damage_received){
  p.armorPerson -= damage_received;
  if(p.armorPerson < 0){
    p.hpPerson += p.armorPerson;
    p.armorPerson = 0;
  }
}

void field(char (& _arena), int _col, int _row){

    // int columns = sizeof(field[0]) / sizeof(field[0][0]);
    std::cout << std::endl;
    for(int i = 0; i < _col; ++i){
        for(int j = 0; j < _row; ++j){
          _arena[i][j];
            // std::cout << "." << " ";
        }
        std::cout << std::endl;
    }
}

int main(){
  std::cout << "Role game" << std::endl;
  const int countEnumy = 5;
  std::vector<Person> pers(countEnumy);
  Person hero;
  int damagePerson = 0;

  srand(time(NULL));
  std::cout << "Enter name, HP, armor, damage your person" << std::endl;
  std::cin >> hero.namePerson;
  std::cin >> hero.hpPerson;
  std::cin >> hero.armorPerson;
  std::cin >> hero.damagePerson;

  creating_enemies(pers, countEnumy);

  field(arena, col, row);
  // takeDamage(pers, damagePeron);



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

  return 0;
}
