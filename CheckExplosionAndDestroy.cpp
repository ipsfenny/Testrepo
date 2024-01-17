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
