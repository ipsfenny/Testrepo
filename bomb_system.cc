//
// Created by pascal gorselink on 10.12.2023.
//
#include "bomb_system.h"

void BombSystem::Init() {
  // Not quite sure how to initialize the System...
}

void BombSystem::set(sf::Vector2f newExplosionPosition) {
  auto& oldPosition = Engine.GetComponent<PositionComponent>(this);
  oldPosition = newExplosionPosition;
}

void BombSystem::set(sf::Vector2f newExplosionRadius) {
  auto& oldExplosionRadius = Engine.GetComponent<ExplodeComponent>(this);
  oldExplosionRadius = newExplosionRadius;
}

int BombSystem::CheckIfBombIsActive() {
  auto& bomb = Engine.GetComponent<BombComponent>(this);
  if (bomb.isActive == true) {
    auto& oldPosition = Engine.GetComponent<PositionComponent>(this);
    auto& explode = Engine.GetComponent<ExplodeComponent>(this);

    void set(sf::Vector2f newExplosionPosition);  // update position
    void set(sf::Vector2f newExplosionRadius);    // update radius

    //... play Bomb animation here

    Engine.DestroyEnitiy(this);  // since the values have been updated, we can
                                 // destroy the bomb after the animation
  }
}
}

void BombSystem : Update() {
  for (auto& entity : entities_) {
    entity.CheckIfBombIsActive();
  }
}
