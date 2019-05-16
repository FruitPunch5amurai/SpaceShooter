#pragma once

#include <string>
#include <GLTexture.h>
#include <SpriteBatch.h>
#include <Camera.h>
#include <Window.h>
class CameraBackdrop {
public:
	CameraBackdrop();
	~CameraBackdrop();

	void Init(std::string texturePath, Rasengine::Window* m_window, Rasengine::Camera2D &camera);
	void Draw();
private:
	Rasengine::GLTexture m_texture;
	Rasengine::Camera2D* m_camera;

	Rasengine::SpriteBatch m_spriteBatch;
};