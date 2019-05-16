function createPlayer()
ent = Entity.new()
ent:assign_SpriteComponent("Animation/PlayerShip.json","Idle")
ent:assign_PhysicsComponent(150)

end