#pragma once
//Rasengine
#include <SpriteBatch.h>
//EntityX
#include <EntityX/System.h>
//SpaceShooter
#include "Components\SpriteComponent.h"
#include "Components\TransformComponent.h"
#include "Components/BoxColliderComponent.h"

#include <iostream>
#include <GLM/glm.hpp>
using namespace entityx;
struct AnimationSystem : public System<AnimationSystem>
{
	AnimationSystem(Rasengine::Camera2D* camera)
	{
		m_spriteBatch.Init();
		m_debugRenderer.Init();
		this->m_camera = camera;
	}
	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{

	}
	void render(EntityManager &entities)
	{
		ComponentHandle<SpriteComponent> sprite;
		ComponentHandle<TransformComponent> pos;
		//TODO: Move calculation to different System

		m_spriteBatch.Begin();

		//Draw Logic		
		for (Entity ent : entities.entities_with_components(pos,sprite))
		{
			sprite->destRect.x = pos.get()->position.x - (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x) / 2.0f;
			sprite->destRect.y = pos.get()->position.y - (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.y) / 2.0f;
			sprite->destRect.z = (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x);
			sprite->destRect.w = (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.y);

			sprite->uvRect = sprite->m_spriteSheet->GetUVs(sprite->m_currentAnimation, sprite->m_currentFrame);

			m_spriteBatch.Draw(sprite->destRect,
				sprite->uvRect,
				sprite->m_spriteSheet->texture.id,
				0.0f,
				Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f), sprite->m_dir);

			//Update Animation Step
			if (!sprite->isStatic)
			{
				sprite->m_lastAnimationStep = sprite->m_lastAnimationStep + sprite->m_currentAnimation->at(sprite->m_currentFrame).animationSpeed;
				sprite->m_currentFrame = (int)sprite->m_lastAnimationStep % sprite->m_currentAnimation->size();
			}
		}
		m_spriteBatch.End();
		m_spriteBatch.RenderBatch();
		if (m_debugDraw)
		{
			ComponentHandle<TransformComponent> pos;
			glm::vec4 destRect;
			for (Entity ent : entities.entities_with_components(pos, sprite))
			{
				destRect.x = pos.get()->position.x - (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x) / 2.0f;
				destRect.y = pos.get()->position.y - (float)(sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.y) / 2.0f;

				destRect.z = (float)sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.x;
				destRect.w = (float)sprite->m_currentAnimation->at(sprite->m_currentFrame).dims.y;
				m_debugRenderer.DrawBox(destRect,
					Rasengine::ColorRGBA8(255, 255, 255, 255), 0);
				m_debugRenderer.End();
				m_debugRenderer.Render(m_camera->GetCameraMatrix(), 2.0f);
			}
		}
	}
private:
	Rasengine::SpriteBatch m_spriteBatch;
	Rasengine::DebugRenderer m_debugRenderer;
	Rasengine::Camera2D* m_camera;
	bool m_debugDraw = false;
};
