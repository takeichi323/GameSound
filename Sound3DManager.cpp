#include "Sound3DManager.h"

Sound3DManager::Sound3DManager()
	:x3dInstance{}
{
}

Sound3DManager::~Sound3DManager()
{
}

bool Sound3DManager::Initialize(X3DAUDIO_HANDLE x3dInstance)
{
	
	return false;
}

void Sound3DManager::SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop)
{
	listener.Position = position;
	listener.OrientFront = orientFront;
	listener.OrientTop = orientTop;
	listener.Velocity = { 0.0f,0.0f,0.0f };
}

void Sound3DManager::SetEmitterParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& velocity)
{
	emitter.Position = position;
	emitter.Velocity = velocity;
	emitter.ChannelCount = 1;
	emitter.CurveDistanceScaler = 1.0f;
	emitter.DopplerScaler = 1.0f;
}

void Sound3DManager::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& listener, X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice)
{
	X3DAUDIO_DSP_SETTINGS dspSettings{};
	FLOAT32 matrix[2]{};
}
