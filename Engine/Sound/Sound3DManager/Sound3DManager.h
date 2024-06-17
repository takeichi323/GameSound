#pragma once
#include<X3DAudio.h>
#include <xaudio2.h>


class Sound3DManager{
public:
	//�R���X�g���N�^
	Sound3DManager();
	//�f�X�g���N�^
	~Sound3DManager();

	//X3DAUDIO�̏�����
	bool Initialize(X3DAUDIO_HANDLE x3dInstance);
	//���X�i�[�̈ʒu�A������ݒ�
	void SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop);
	//�G�~�b�^�[�̈ʒu�A���x��ݒ�
	void SetEmitterParameters(const X3DAUDIO_VECTOR& position,const X3DAUDIO_VECTOR& velocity);
	//3D�I�[�f�B�I�̌v�Z����֐�
	void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& listener,X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice);

private:
	X3DAUDIO_LISTENER listener;
	X3DAUDIO_EMITTER emitter;
	X3DAUDIO_HANDLE x3dInstance;
};

