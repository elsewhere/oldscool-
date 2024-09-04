#include "global.h"
#include "bpm.hpp"

BPM::BPM(float value, float offset)
{
	this->framecount = 0;
	this->value = (float)value;
	this->offset = offset;
	this->previousbeatdist = 0;

	changed = false;

//	this->value = 151.875f;
}

BPM::~BPM()
{
	this->framecount = 0;
	this->value = 0;
	this->offset = 0;
	this->previousbeatdist = 0;

}

void BPM::update(int ptime)
{
    time = ptime;

}

float BPM::getValue()
{
	const int bpmmicroseconds = (int)(60000000/value);
	aika = time*1000;

	changed = false;

	//lasketaan et�isyys biittiin
	int beatdist = aika % bpmmicroseconds;

	if (beatdist < previousbeatdist)
	{
		changed = true;
		framecount++;
	}

	float beat = (bpmmicroseconds-beatdist)/(float)bpmmicroseconds;
/*
	dmsMsg("BPM::aika = %d\n", aika);
	dmsMsg("BPM::beatdist = %d\n", beatdist);
	dmsMsg("BPM::previousbeatdist = %d\n", previousbeatdist);
	dmsMsg("BPM::framecount = %d\n", framecount);
	dmsMsg("BPM::beat = %f\n", beat);
*/
	previousbeatdist = beatdist;
	return beat;
}

int BPM::getBeatcount()
{
	return this->framecount;
}

bool BPM::getChanged()
{
	return this->changed;
}