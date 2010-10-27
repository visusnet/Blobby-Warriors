#include "Simulator.h"

Simulator::Simulator()
{
//	b2Vec2 gravity = b2Vec2(0.0f, -9.81f);
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	bool doSleep = false;
	this->world = new b2World(gravity, doSleep);

	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position = pixel2meter(b2Vec2(400.0f, 300.0f));
	bodyDef.angle = 0.25f * b2_pi;
	bodyDef.active = true;
	bodyDef.allowSleep = false;
	bodyDef.awake = true;
	bodyDef.bullet = true;
	bodyDef.type = b2BodyType::b2_dynamicBody;

	b2Body *body = this->world->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(pixel2meter(300.0f), pixel2meter(300.0f));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	body->ResetMassData();

	this->mainBody = body;

	// TODO: Level setup, etc.
	this->level = new Level();
}

Simulator::~Simulator()
{
	delete this->level;
	delete this->world;
}

void DrawSolidPolygon(b2Vec2 *vertices, int vertexCount)
{
	b2Color color;
	color.r = 0.5f;
	color.g = 0.5f;
	color.b = 0.3f;
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		debug("%f %f", vertices[i].x * SCALING_FACTOR, vertices[i].y * SCALING_FACTOR);
		glVertex2f(vertices[i].x * SCALING_FACTOR, vertices[i].y * SCALING_FACTOR);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color.r, color.g, color.b, 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < vertexCount; ++i)
	{
		glVertex2f(vertices[i].x * SCALING_FACTOR, vertices[i].y * SCALING_FACTOR);
	}
	glEnd();
}

void DrawShape(b2Fixture* fixture, const b2Transform& xf)
{
	switch (fixture->GetType())
	{
	case b2Shape::e_polygon:
		{
			b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
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


void Simulator::step()
{
	this->world->Step(1.0f / 62.5f, 10, 10);

	const b2Transform& xf = this->mainBody->GetTransform();
	b2Fixture *fixture = this->mainBody->GetFixtureList();

	DrawShape(fixture, xf);

	debug("%f %f", this->mainBody->GetPosition().x, this->mainBody->GetPosition().y);
}