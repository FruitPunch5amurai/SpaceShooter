#pragma once
//Rasengine
#include <SpriteSheet.h>
#include <GLM/glm.hpp>
#include <ResourceManager.h>

struct SpriteComponent : public entityx::Component<SpriteComponent>
{
	SpriteComponent(const char* filePath,const char* startAnimation) {
	
		m_spriteSheet = Rasengine::ResourceManager::GetSpriteSheet(filePath);
		if (startAnimation != nullptr)
		{
			m_currentAnimation = m_spriteSheet->SetAnimation(startAnimation);
			m_currentAnimationName = (char*)startAnimation;
		}
	}
	Rasengine::SpriteSheet* m_spriteSheet;
	std::vector<Rasengine::FrameData>* m_currentAnimation;
	std::string m_currentAnimationName;
	glm::vec2 m_dir = glm::vec2(1.0f,0.0f);	//Rotation in Vectors
	int m_currentFrame = 0;
	float m_lastAnimationStep = 0.0f;
	glm::vec4 destRect;
	glm::vec4 uvRect;
	bool isStatic = false;
};