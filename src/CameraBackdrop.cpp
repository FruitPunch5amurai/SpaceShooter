//Rasengine
#include <ResourceManager.h>

#include "CameraBackdrop.h"

CameraBackdrop::CameraBackdrop()
{
}

CameraBackdrop::~CameraBackdrop()
{
}

void CameraBackdrop::Init(std::string texturePath, Rasengine::Window* m_window,Rasengine::Camera2D &camera)
{
	m_texture = Rasengine::ResourceManager::GetTexture(texturePath);
	m_camera = &camera;
	m_spriteBatch.Init();

	glm::vec4 destRect(m_camera->GetPosition().x - m_window->getScreenWidth() / 2,
		m_camera->GetPosition().y - m_window->getScreenHeight() / 2,
		m_window->getScreenWidth(),
		m_window->getScreenHeight());
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	m_spriteBatch.Begin();

	m_spriteBatch.Draw(destRect,
		uvRect,
		m_texture.id,
		0.0f,
		Rasengine::ColorRGBA8(255.0f, 255.0f, 255.0f, 255.0f));

	m_spriteBatch.End();
}

void CameraBackdrop::Draw()
{
	m_spriteBatch.RenderBatch();
}
