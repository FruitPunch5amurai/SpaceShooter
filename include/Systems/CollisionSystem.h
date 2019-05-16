#pragma once
//Rasengine
#include <DebugRenderer.h>

//EntityX
#include <EntityX/System.h>
//ChipMunk
#include <chipmunk/chipmunk.h>

//SpaceShooter
#include "Components/BoxColliderComponent.h"
#include "Components\HealthComponent.h"
#include "Components\DamageComponent.h"
#include "CollisionBitMasks.h"
#include "EntityXManager.h"

#include <iostream>
#include <GLM/glm.hpp>
using namespace entityx;

/*Functions to remove shapes and bodies from space*/
static void ShapeFreeWrap(cpSpace *space, cpShape *shape, void *unused) {
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
}
static void PostShapeFree(cpShape *shape, cpSpace *space) {
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)ShapeFreeWrap, shape, NULL);
}
static void BodyFreeWrap(cpSpace *space, cpBody *body, void *unused) {
	cpSpaceRemoveBody(space, body);
	cpBodyFree(body);
}
static void PostBodyFree(cpBody *body, cpSpace *space) {
	cpSpaceAddPostStepCallback(space, (cpPostStepFunc)BodyFreeWrap, body, NULL);
}

struct CollisionSystem : public System<CollisionSystem>
{
	cpSpace* m_space;

	CollisionSystem()
	{
		m_space = cpSpaceNew();
		cpSpaceSetIterations(m_space, 10);
		cpSpaceSetGravity(m_space, cpv(0, 0.0f));
		cpSpaceSetCollisionSlop(m_space, 0.0);
		m_debugRenderer.Init();

		//Set up Collision Handlers
		cpCollisionHandler *handler = cpSpaceAddCollisionHandler(m_space, ENEMY_CATAGORY, PLAYER_BULLET_CATAGORY);
		handler->preSolveFunc = CollisionSystem::TakeDamage;
		handler = cpSpaceAddCollisionHandler(m_space, ENEMY_CATAGORY, PLAYER_CATAGORY);
		handler->preSolveFunc = CollisionSystem::TakeDamage;
		handler = cpSpaceAddCollisionHandler(m_space, ENEMY_BULLET_CATAGORY, PLAYER_CATAGORY);
		handler->preSolveFunc = CollisionSystem::TakeDamage;
	}
	~CollisionSystem()
	{
		cpSpaceEachShape(m_space, (cpSpaceShapeIteratorFunc)PostShapeFree, m_space);
		cpSpaceEachBody(m_space, (cpSpaceBodyIteratorFunc)PostBodyFree, m_space);
		cpSpaceFree(m_space);
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{

	}
	void render(EntityManager &entities, Rasengine::Camera2D* camera)
	{
		//DebugRendering
		if (m_renderDebug)
		{
			glm::vec4 destRect;
			ComponentHandle<BoxColliderComponent> b;

			for (Entity ent : entities.entities_with_components(b))
			{
				destRect.x = cpBodyGetPosition(b->m_body).x;
				destRect.y = cpBodyGetPosition(b->m_body).y;

				destRect.z = b->m_dimensions.x;
				destRect.w = b->m_dimensions.y;
				m_debugRenderer.DrawBox(destRect,
					Rasengine::ColorRGBA8(255, 0, 0, 255),
					cpBodyGetAngle(b->m_body));
				m_debugRenderer.End();
				m_debugRenderer.Render(camera->GetCameraMatrix(), 2.0f);
			}
		}
	}

	/*Take Damage*/
	static cpBool TakeDamage(cpArbiter *arb, cpSpace *space, cpDataPointer data)
	{
		
		cpShape *a, *b; 
		cpArbiterGetShapes(arb, &a, &b);

		BoxColliderComponent* boxColla = (BoxColliderComponent*) cpShapeGetUserData(a);
		BoxColliderComponent* boxCollb = (BoxColliderComponent*)cpShapeGetUserData(b);

		ComponentHandle<DamageComponent> d1, d2;
		ComponentHandle<HealthComponent> h1, h2;

		boxColla->m_entityHandle.unpack<DamageComponent, HealthComponent>(d1, h1);
		boxCollb->m_entityHandle.unpack<DamageComponent, HealthComponent>(d2, h2);

		if (d1.valid())
		{
			if (h2.valid())
			{
				h2.get()->currentHp -= d1.get()->damage;				
			}
		}
		if (d2.valid())
		{
			if (h1.valid())
			{
				h1.get()->currentHp -= d2.get()->damage;
			}
		}
		//if (h2.valid())
		//{
		//	if (h2.get()->currentHp <= 0)
		//	{
		//		PostShapeFree(boxCollb->m_shape, space);
		//		PostBodyFree(boxCollb->m_body, space);

		//		boxCollb->m_shape = nullptr;
		//		boxCollb->m_body = nullptr;

		//		boxCollb->m_entityHandle.destroy();
		//	}
		//}
		//if (h1.valid())
		//{
		//	if (h1.get()->currentHp <= 0)
		//	{
		//		PostShapeFree(boxColla->m_shape, space);
		//		PostBodyFree(boxColla->m_body, space);

		//		boxColla->m_shape = nullptr;
		//		boxColla->m_body = nullptr;

		//		boxColla->m_entityHandle.destroy();
		//	}
		//}
		return cpFalse;
	}
private:
	bool m_renderDebug = true;
	Rasengine::DebugRenderer m_debugRenderer;
};
