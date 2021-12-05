#include <iostream>
#include <vector>
#include <ctime>

struct Person {
  std::string namePeron = "Unknown";
  int hp = 0;
  int armor = 0;
  int damage = 0;
};

void takeDamage(Person* p, int damage_received){
  p->armor -= damage_received;
  if(p->armor < 0){
    p->hp += p->armor;
    p->armor = 0;
  }
};

int main(){
  std::cout << "Role game" << std::endl;
  Person pers;
  int damagePeron = 0;
  // std::vector<Person> persons;
  srand(time(NULL));

  for (int i = 0; i < 5; i++) {
    pers.namePeron = ("Enumy #" + std::to_string(i+1));
  pers.hp = rand() % 100 + 50;
  
  // // std::cout << pers.hp << std::endl;

  pers.armor = rand() % 50;
  // // std::cout << pers.armor << std::endl;

  pers.damage = rand() % 15 + 15;
  // persons.push_back({pers.hp, pers.armor, pers.damage});
  // // std::cout << pers.damage << std::endl;
  }
  // takeDamage(&pers, damagePeron);
  for(int i = 0; i < 5; i++) {
    std::cout << "Name - " << pers.namePeron << std::endl;
    std::cout << "HP - " << pers.hp << std::endl;
    std::cout << "Armor - " << pers.armor << std::endl;
    std::cout << "Damage - " << pers.damage << std::endl;
    std::cout << std::endl;
  }
  return 0;
}
