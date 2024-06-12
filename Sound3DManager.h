#pragma once
#include<X3DAudio.h>
#include <xaudio2.h>


class Sound3DManager{
public:
	Sound3DManager();
	~Sound3DManager();

	bool Initialize(X3DAUDIO_HANDLE x3dInstance);
	void SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop);
	void SetEmitterParameters(const X3DAUDIO_VECTOR& position,const X3DAUDIO_VECTOR& velocity);
	void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& listener,X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice);

private:
	X3DAUDIO_LISTENER listener;
	X3DAUDIO_EMITTER emitter;
	X3DAUDIO_HANDLE x3dInstance;
};

