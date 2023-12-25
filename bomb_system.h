//
// Created by  pascal gorselink on 10.12.2023.
//

#ifndef MANHATTAN_PROJEKT_BOMB_SYSTEM_H
#define MANHATTAN_PROJEKT_BOMB_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <cmath>
#include <string>


using namespace manhattan::ecs;

struct BombComponent{
  bool isActive; // Tells if bomb is active
};

struct PositionComponent{
  sf::Vector2f explosionPosition; // hold the current position
};

struct ExplodeComponent{
  // std::vector<sf::Vector2f> attackFields // save all fields that are affected in a list or... this solution
  int explosionRadius; // hold the current radius
};
class BombSystem: public System{
 public:
  void Init(); // initialization function
  void Update(sf::RenderWindow& window); // update function gets passed the sf::RenderWindow

  void CheckIfBombIsActive(bool BombActive);
 private:
  void setExplosionPosition(sf::Vector2f newExplosionPosition); // update position
  void setExplosionRadius(sf::Vector2f newExplosionRadius); // update radius
  std::set<Entity> entities_; // Set of all entities the system is keeping track of
};

#endif  // MANHATTAN_PROJEKT_BOMB_SYSTEM_H
