#include <iostream>
#include <vector>
#include <ctime>

struct Person {
  std::string namePerson = "Unknown";
  int hpPerson = 0;
  int armorPerson = 0;
  int damagePerson = 0;
};

void creating_enemies(Person* p, int countEnumy){
  for (int i = 1; i < countEnumy; i++) {
    p[i].namePerson = ("Enumy #" + std::to_string(i));
    p[i].hpPerson = rand() % 100 + 50;
    p[i].armorPerson = rand() % 50;
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

int main(){
  std::cout << "Role game" << std::endl;
  int countEnumy = 6;
  Person pers[countEnumy];
  int damagePerson = 0;
  std::string name;
  int hp;
  int armor;
  int damage;
  srand(time(NULL));
  std::cout << "Enter name, HP, armor, damage your person" << std::endl;
  std::cin >> name;
  std::cin >> hp;
  std::cin >> armor;
  std::cin >> damage;

  pers[0].namePerson = name;
  pers[0].hpPerson = hp;
  pers[0].armorPerson = armor;
  pers[0].damagePerson = damage;

  creating_enemies(pers, countEnumy);
  // takeDamage(pers, damagePeron);



  for(int i = 0; i < countEnumy; i++) {
    std::cout << "Name - " << pers[i].namePerson << std::endl;
    std::cout << "HP - " << pers[i].hpPerson << std::endl;
    std::cout << "Armor - " << pers[i].armorPerson << std::endl;
    std::cout << "Damage - " << pers[i].damagePerson << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
