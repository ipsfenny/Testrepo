void CheckExplosionAndDestroy(ecs::Entity explosion)
{
  // Referenz auf die Kollisionskomponente der Explosion erhalten
  auto& explosion_bounds = ecs::Engine::singleton().GetComponent<CollisionComponent>(explosion);

  // Die Schleife durchläuft alle Entitäten (Blöcke oder Objekte) im Spiel
  for (auto& entity : entities_)
  {
    // Referenzen auf die Kollisionskomponente und den Zerstörungsstatus der aktuellen Entität erhalten
    auto& entity_bounds = ecs::Engine::singleton().GetComponent<CollisionComponent>(entity);
    auto& destruction_status = ecs::Engine::singleton().GetComponent<DestructibleComponent>(entity);

    // Überprüfen, ob die Entität noch nicht zerstört ist und sich im Explosionsradius befindet
    if (!destruction_status.is_destroyed && IsInsideRadius(entity_bounds, explosion_bounds))
    {
      // Hier sollte Code eingefügt werden, um eine Zerstörungsanimation abzuspielen
      // und die Explosion zu stoppen, falls erforderlich.

      // Die Entität als zerstört markieren
      destruction_status.is_destroyed = true;

      // Die Entität zerstören (aus der Spielwelt entfernen)
      ecs::Engine::singleton().DestroyEntity(entity);
    }
    // Das 'else continue;' kann entfernt werden, da die Schleife standardmäßig zur nächsten Iteration übergeht
  }
}


// Engine des Projektes

#ifndef ENGINE_H_
#define ENGINE_H_

#include <memory>

#include "component_manager.h"
#include "entity_manager.h"
#include "system_manager.h"
#include "type_def.h"

namespace manhattan::ecs {
class Engine final {
 public:
  // This instantiates the engine as a singleton so that it can be ensured
  // that there is only one engine instance during runtime.
  static Engine& singleton() {
    // https://webkit.org/code-style-guidelines/#singleton-pattern
    // for more prayers see below
    static Engine instance = Engine();
    return instance;
  }

  // https://codereview.stackexchange.com/questions/173929/modern-c-singleton-template
  // lets pray this works
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(Engine&&) = delete;

  Entity CreateEntity() { return entity_manager_->CreateEntity(); }

  void DestroyEntity(const Entity entity) {
    entity_manager_->DestroyEntity(entity);
    component_manager_->EntityWasDestroyed(entity);
    system_manager_->EntityWasDestroyed(entity);
  }

  template <typename T>
  void RegisterComponent() {
    component_manager_->RegisterComponent<T>();
  }

  template <typename T>
  void AddComponent(const Entity entity, const T component) {
    component_manager_->AddComponent<T>(entity, component);
    Signature entity_signature = entity_manager_->GetSignature(entity);
    ComponentType component_id = component_manager_->GetComponentType<T>();
    entity_signature.set(component_id,true);
    entity_manager_->SetSignature(entity,entity_signature);
    system_manager_->EntitySignatureChanged(entity,entity_signature);
  };

  template <typename T>
  void RemoveComponent(const Entity entity) {
    component_manager_->RemoveComponent<T>(entity);
    Signature entity_signature = entity_manager_->GetSignature(entity);
    ComponentType component_id =component_manager_->GetComponentType<T>();
    entity_signature.set(component_id,false);
    entity_manager_->SetSignature(entity,entity_signature);
    system_manager_->EntitySignatureChanged(entity,entity_signature);
  }

  template <typename T>
  T& GetComponent(const Entity entity) {
    return component_manager_->GetComponent<T>(entity);
  }

  template <typename T>
  ComponentType GetComponentType() {
    return component_manager_->GetComponentType<T>();
  }

  template <typename T>
  std::shared_ptr<T> RegisterSystem() {
    return system_manager_->RegisterSystem<T>();
  }

  template <typename T>
  void SetSystemSignature(const Signature signature) {
    system_manager_->SetSystemSignature<T>(signature);
  }

 private:
  const std::unique_ptr<EntityManager> entity_manager_;
  const std::unique_ptr<ComponentManager> component_manager_;
  const std::unique_ptr<SystemManager> system_manager_;

  Engine()
      : entity_manager_(std::make_unique<EntityManager>()),
        component_manager_(std::make_unique<ComponentManager>()),
        system_manager_(std::make_unique<SystemManager>()) {}
};
}  // namespace manhattan::ecs

#endif  // ENGINE_H_
