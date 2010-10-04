#ifndef SETTINGS_H
#define SETTINGS_H

struct Settings
{
	Settings() :
		hz(60.0f),
		iterationCount(10),
		drawStats(0),
		drawShapes(1),
		drawJoints(1),
		drawCoreShapes(0),
		drawAABBs(0),
		drawOBBs(0),
		drawPairs(0),
		drawContactPoints(0),
		drawContactNormals(0),
		drawContactForces(0),
		drawFrictionForces(0),
		drawCOMs(0),
		enableWarmStarting(1),
		enablePositionCorrection(1),
		enableTOI(1),
		pause(0),
		singleStep(0)
		{}

	float32 hz;
	int32 iterationCount;
	int32 drawShapes;
	int32 drawJoints;
	int32 drawCoreShapes;
	int32 drawAABBs;
	int32 drawOBBs;
	int32 drawPairs;
	int32 drawContactPoints;
	int32 drawContactNormals;
	int32 drawContactForces;
	int32 drawFrictionForces;
	int32 drawCOMs;
	int32 drawStats;
	int32 enableWarmStarting;
	int32 enablePositionCorrection;
	int32 enableTOI;
	int32 pause;
	int32 singleStep;
};

#endif
