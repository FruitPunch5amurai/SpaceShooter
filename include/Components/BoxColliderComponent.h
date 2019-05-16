#pragma once
#include <chipmunk/chipmunk.h>
#include <GLM/glm.hpp>
#include <Vertex.h>
#include <GLTexture.h>

struct BoxColliderComponent : public entityx::Component<BoxColliderComponent>
{
	BoxColliderComponent(cpSpace* space,
		const glm::vec2& position,
		const glm::vec2& dimensions,
		Rasengine::GLTexture texture,
		Rasengine::ColorRGBA8 color,		
		entityx::Entity ent,
		bool fixedRot = true,
		unsigned int catMask = 0x0,
		unsigned int colMask = 0x0,
		glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) {

		m_space = space;
		m_entityHandle = ent;
		//Create Body
		m_body = cpSpaceAddBody(space, cpBodyNew(1.0f, cpMomentForBox(1.0f, dimensions.x, dimensions.y)));
		cpBodySetPosition(m_body, cpv(position.x, position.y));
		if (fixedRot) cpBodySetMoment(m_body, INFINITY);

		/*Create Shape*/
		m_shape = cpSpaceAddShape(space, cpBoxShapeNew(m_body, dimensions.x, dimensions.y, 0.0));
		cpShapeSetCollisionType(m_shape, catMask);
		cpShapeFilter filter = { CP_NO_GROUP, catMask, colMask };
		cpShapeSetFilter(m_shape, filter);
		cpShapeSetElasticity(m_shape, 0.0f);
		cpShapeSetFriction(m_shape, 0.8f);
		cpShapeSetUserData(m_shape, this);

		m_dimensions = dimensions;
		m_texture = texture;
		m_color = color;
		m_uvRect = uvRect;
	}
	~BoxColliderComponent()
	{
		if (m_body)
		{
			cpSpaceRemoveShape(m_space, m_shape);
			cpShapeFree(m_shape);
		}
		if (m_shape)
		{
			cpSpaceRemoveBody(m_space, m_body);
			cpBodyFree(m_body);
		}
		m_space = nullptr;
	}
	cpSpace* m_space = nullptr;
	cpBody * m_body = nullptr;
	cpShape* m_shape = nullptr;
	entityx::Entity m_entityHandle;

	glm::vec2 m_dimensions;
	glm::vec4 m_uvRect;

	Rasengine::ColorRGBA8 m_color;
	Rasengine::GLTexture m_texture;
};