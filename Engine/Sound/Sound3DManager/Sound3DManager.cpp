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
	
	//this->x3dInstance = x3dInstance;
	return true;
}

void Sound3DManager::SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop)
{
	//���X�i�[
	//�ʒu
	listener.Position = position;
	//�O���x�N�g��
	listener.OrientFront = orientFront;
	//������x�N�g��
	listener.OrientTop = orientTop;
	//���x
	listener.Velocity = { 0.0f,0.0f,0.0f };
}

void Sound3DManager::SetEmitterParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& velocity)
{
	//�G�~�b�^�[
	//�ʒu
	emitter.Position = position;
	//���x
	emitter.Velocity = velocity;
	//�`�����l�����Z�b�g
	emitter.ChannelCount = 1;
	//�o�̓`�����l��
	emitter.CurveDistanceScaler = 1.0f;
	emitter.DopplerScaler = 1.0f;
}

void Sound3DManager::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& listener, X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice)
{
	//DSP�ݒ�̏�����
	X3DAUDIO_DSP_SETTINGS dspSettings{};
	//�}�g���b�N�X�̏�����
	FLOAT32 matrix[2]{};
	//�G�~�b�^�`�����l��
	dspSettings.SrcChannelCount = emitter.ChannelCount;
	dspSettings.DstChannelCount = 2;//�X�e���I�o��
	//�}�g���b�N�X�W��
	dspSettings.pMatrixCoefficients = matrix;
	//X3DAudioCalculate�֐����Ăяo����3D�I�[�f�B�I���ʂ��v�Z
	X3DAudioCalculate(x3dInstance, &listener, &emitter, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER, &dspSettings);
	//�v�Z���ꂽ�h�b�v���[�t�@�N�^�[���\�[�X�{�C�X�ɐݒ�
	pSourceVoice->SetFrequencyRatio(dspSettings.DopplerFactor);
	//�v�Z���ꂽ�o�̓}�g���b�N�X���\�[�X�{�C�X�ɐݒ�
	pSourceVoice->SetOutputMatrix(pMasteringVoice, 1, 2, dspSettings.pMatrixCoefficients);

}
