#pragma once
#include<X3DAudio.h>
#include <xaudio2.h>


class Sound3DManager{
public:
	//コンストラクタ
	Sound3DManager();
	//デストラクタ
	~Sound3DManager();

	//X3DAUDIOの初期化
	bool Initialize(X3DAUDIO_HANDLE x3dInstance);
	//リスナーの位置、方向を設定
	void SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop);
	//エミッターの位置、速度を設定
	void SetEmitterParameters(const X3DAUDIO_VECTOR& position,const X3DAUDIO_VECTOR& velocity);
	//3Dオーディオの計算する関数
	void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& listener,X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice);

private:
	X3DAUDIO_LISTENER listener;
	X3DAUDIO_EMITTER emitter;
	X3DAUDIO_HANDLE x3dInstance;
};

