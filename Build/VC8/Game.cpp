#include "Game.h"

Game::Game()
{
	this->m_worldAABB.lowerBound.Set(-2000.0f, -2000.0f);
	this->m_worldAABB.upperBound.Set(2000.0f, 2000.0f);
	b2Vec2 gravity;
	gravity.Set(0.0f, -40.0f);
	bool doSleep = true;
	this->m_world = new b2World(m_worldAABB, gravity, doSleep);
	this->m_bomb = NULL;
	this->m_textLine = 30;
	this->m_mouseJoint = NULL;
	this->m_pointCount = 0;

	this->m_destructionListener.game = this;
	this->m_boundaryListener.game = this;
	this->m_contactListener.game = this;
	this->m_world->SetDestructionListener(&m_destructionListener);
	this->m_world->SetBoundaryListener(&m_boundaryListener);
	this->m_world->SetContactListener(&m_contactListener);
	this->m_world->SetDebugDraw(&m_debugDraw);

	this->InitializeLevel();
	this->playerBlobby = this->CreateBlobby();
}

Game::~Game()
{
	printf("~Game called\n");
}

void Game::Step(Settings* settings)
{
	//printf("Game::Step\n");
	float32 timeStep = settings->hz > 0.0f ? 1.0f / settings->hz : float32(0.0f);

	m_textLine = 30;

	if (settings->pause)
	{
		if (settings->singleStep)
		{
			settings->singleStep = 0;
		}
		else
		{
			timeStep = 0.0f;
		}

		DrawString(5, m_textLine, "****PAUSED****");
		m_textLine += 15;
	}

	uint32 flags = 0;
	flags += settings->drawShapes			* b2DebugDraw::e_shapeBit;
	flags += settings->drawJoints			* b2DebugDraw::e_jointBit;
	flags += settings->drawCoreShapes		* b2DebugDraw::e_coreShapeBit;
	flags += settings->drawAABBs			* b2DebugDraw::e_aabbBit;
	flags += settings->drawOBBs				* b2DebugDraw::e_obbBit;
	flags += settings->drawPairs			* b2DebugDraw::e_pairBit;
	flags += settings->drawCOMs				* b2DebugDraw::e_centerOfMassBit;
	m_debugDraw.SetFlags(flags);

	m_world->SetWarmStarting(settings->enableWarmStarting > 0);
	m_world->SetPositionCorrection(settings->enablePositionCorrection > 0);
	m_world->SetContinuousPhysics(settings->enableTOI > 0);

	m_pointCount = 0;

	int angle = (int)(abs((int) playerBlobby->body->GetAngle()) * (180/b2_pi)) % 360;

	if (angle >= 305)
	{
		playerBlobby->body->SetAngularVelocity(0);
		playerBlobby->body->SetXForm(playerBlobby->body->GetXForm().position, 0);
		playerBlobby->isRotating = false;
		playerBlobby->jumpLevel = 0;
	}

	m_world->Step(timeStep, settings->iterationCount);

	m_world->Validate();

	if (m_bomb != NULL && m_bomb->IsFrozen())
	{
		m_world->DestroyBody(m_bomb);
		m_bomb = NULL;
	}

	if (settings->drawStats)
	{
		DrawString(5, m_textLine, "proxies(max) = %d(%d), pairs(max) = %d(%d)",
			m_world->GetProxyCount(), b2_maxProxies,
			m_world->GetPairCount(), b2_maxPairs);
		m_textLine += 15;

		DrawString(5, m_textLine, "bodies/contacts/joints = %d/%d/%d",
			m_world->GetBodyCount(), m_world->GetContactCount(), m_world->GetJointCount());
		m_textLine += 15;

		DrawString(5, m_textLine, "heap bytes = %d", b2_byteCount);
		m_textLine += 15;
	}

	if (m_mouseJoint)
	{
		b2Body* body = m_mouseJoint->GetBody2();
		b2Vec2 p1 = body->GetWorldPoint(m_mouseJoint->m_localAnchor);
		b2Vec2 p2 = m_mouseJoint->m_target;

		glPointSize(4.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glEnd();
		glPointSize(1.0f);

		glColor3f(0.8f, 0.8f, 0.8f);
		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glEnd();
	}
}

void Game::InitializeLevel()
{
	/**
	 * Apply demo ground
	 */
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f / scalingFactor, 10.0f / scalingFactor);
	b2Body* groundBody = this->m_world->CreateBody(&groundBodyDef);
	b2PolygonDef groundShapeDef;
	groundShapeDef.SetAsBox(2000.0f / scalingFactor, 10.0f / scalingFactor);
	groundBody->CreateShape(&groundShapeDef);
}

Blobby* Game::CreateBlobby()
{
	Blobby* blobby = new Blobby();
	b2BodyDef bodyDef;
	bodyDef.position.Set(0, 20); // TODO: Position?
	bodyDef.fixedRotation = true;
	blobby->body = this->m_world->CreateBody(&bodyDef);
	blobby->type = BLOBBY;
	blobby->body->SetUserData(blobby);

	/**
	 * Apply demo shape.
	 */
	b2CircleDef circleDefHead;
	circleDefHead.radius = 13 / scalingFactor;
	circleDefHead.density = 1;
	circleDefHead.friction = 4; // 0.5;
	circleDefHead.restitution = 0.0;
	circleDefHead.localPosition.Set(1 / scalingFactor, 7 / scalingFactor);
	circleDefHead.userData = blobby;
	//circleDefHead.filter.categoryBits = 0x0001;
	//circleDefHead.filter.maskBits = 0x0001;
	//circleDefHead.filter.groupIndex = groupIndex;

	b2CircleDef circleDefBody;
	circleDefBody.radius = 17 / scalingFactor;
	circleDefBody.density = 0.6f;
	circleDefBody.friction = 8; // 1;
	circleDefBody.restitution = 0.0;
	circleDefBody.localPosition.Set(1 / scalingFactor, -9 / scalingFactor);
	circleDefBody.userData = blobby;
	//circleDefBody.filter.categoryBits = 0x0000;
	//circleDefBody.filter.maskBits = 0x0001;
	//circleDefBody.filter.groupIndex = groupIndex;

	blobby->body->CreateShape(&circleDefHead);
	blobby->body->CreateShape(&circleDefBody);

	b2MassData mass;
	mass.mass = 20;
	mass.I = 3;
	mass.center.SetZero();
	blobby->body->SetMass(&mass);

	return blobby;
}
