#include "AbstractEntity.h"

AbstractEntity::AbstractEntity()
{
	this->isDestroyed = false;
	GameWorld::getInstance()->addEntity(this);
}

void AbstractEntity::destroy()
{
	if (!this->isDestroyed) {
		this->isDestroyed = true;
		GameWorld::getInstance()->destroyEntity(this);
	}
}

void AbstractEntity::step()
{
}

void DrawSolidPolygon(b2Vec2 *vertices, int vertexCount)
{
	b2Color color;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	/*	color.r = 0.5f;
	color.g = 0.5f;
	color.b = 0.3f;*/
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex3f(vertices[i].x * SCALING_FACTOR, vertices[i].y * SCALING_FACTOR, 0.0f);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex3f(vertices[i].x * SCALING_FACTOR, vertices[i].y * SCALING_FACTOR, 0.0f);
	}
	glEnd();
}

void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis)
{
	b2Color color;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
/*	color.r = 0.5f;
	color.g = 0.5f;
	color.b = 0.3f;*/
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * SCALING_FACTOR * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * SCALING_FACTOR * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();

	b2Vec2 p = center + SCALING_FACTOR * radius * axis;
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(p.x, p.y);
	glEnd();
}

void DrawShape(b2Fixture* fixture, const b2Transform& xf)
{
	switch (fixture->GetType())
	{
	case b2Shape::e_circle:
		{
			b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();
			b2Transform xf2 = xf;
			xf2.position = meter2pixel(xf2.position);
			b2Vec2 center = b2Mul(xf2, SCALING_FACTOR * circle->m_p);
			float32 radius = circle->m_radius;
			b2Vec2 axis = xf.R.col1;

			DrawSolidCircle(center, radius, axis);
		}
		break;
	case b2Shape::e_polygon:
		{
			b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();
			int32 vertexCount = poly->m_vertexCount;
			b2Assert(vertexCount <= b2_maxPolygonVertices);
			b2Vec2 vertices[b2_maxPolygonVertices];

			for (int32 i = 0; i < vertexCount; ++i)
			{
				vertices[i] = b2Mul(xf, poly->m_vertices[i]);
			}

			DrawSolidPolygon(vertices, vertexCount);
		}
		break;
	}
}

void AbstractEntity::draw()
{
	for (vector<b2Body*>::iterator it = this->bodies.begin(); it != this->bodies.end(); ++it) {
		b2Body *body = *it;
		const b2Transform& xf = body->GetTransform();
		b2Fixture *fixture = body->GetFixtureList();

		while (fixture != 0) {
			DrawShape(fixture, xf);
			fixture = fixture->GetNext();
		}
	}
}

void AbstractEntity::addBody(b2Body *body)
{
	body->SetUserData((void*)this);
	this->bodies.push_back(body);
}

b2Body* AbstractEntity::getBody(unsigned int i)
{
	if (0 <= i && i < this->bodies.size()) {
		return this->bodies.at(i);
	}
	return 0;
}

unsigned int AbstractEntity::getBodyCount()
{
	return this->bodies.size();
}

void AbstractEntity::addTexture(Texture *texture)
{
	this->textures.push_back(texture);
}

Texture* AbstractEntity::getTexture(unsigned int i)
{
	if (0 <= i && i < this->textures.size()) {
		return this->textures.at(i);
	}
	return 0;
}

unsigned int AbstractEntity::getTextureCount()
{
	return this->textures.size();
}