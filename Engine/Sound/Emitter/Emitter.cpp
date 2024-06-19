#include "Emitter.h"

Emitter::Emitter(const EmitterSettings& settings):settings(settings)
{
}

void Emitter::SetupEmitter(X3DAUDIO_EMITTER& emitter) const
{
	emitter.Position = settings.position_;
	emitter.Velocity = settings.speed_;
	emitter.InnerRadius = settings.innnerRadius;
	emitter.InnerRadiusAngle = settings.innnerRadiusAngle;
	emitter.CurveDistanceScaler = settings.curveDistanceScaler;
	emitter.DopplerScaler = settings.dopplerScaler;
	emitter.ChannelCount = settings.channelCount;
	emitter.pChannelAzimuths = settings.pChannelAzimuths;

}


