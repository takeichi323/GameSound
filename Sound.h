#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>

//���C�u�����ǂݍ���
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

//�G�~�b�^�[�\����
struct EmitterSettings{

 //�G�~�b�^�[�ʒu
  X3DAUDIO_VECTOR position_;
 //�G�~�b�^�[���x
  X3DAUDIO_VECTOR velocity_;
 //�G�~�b�^�[�������a���w��
  float innnerRadius = 2.0f;
 //�G�~�b�^�[�������a�̊p�x���w��
  float innnerRadiusAngle = X3DAUDIO_PI / 4.0;
 //���̋��������X�P�[�����O�W��(��׋�)
  float curveDistanceScaler = 1.0f;
 //�h�b�v���[���ʂ̃X�P�[�����O�W��(��׋�)
  float dopplerScaler = 1.0f;
 //�����̃`�����l�������w��
  uint32_t channelCount = 1;
 //�`�����l�����Ƃ̕��ʊp���i�[����z��ւ̃|�C���^(��׋�)
  float* pChannelAzimuths = nullptr;
};

struct ListenerSettings{
	X3DAUDIO_VECTOR position;
	X3DAUDIO_VECTOR orientFront;
	X3DAUDIO_VECTOR orientTop;
	X3DAUDIO_VECTOR velocity;
};

class Sound
{
  //XAudio2�̏�����
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudio�̏�����
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //�G�~�b�^�̐ݒ�
   void SetupEmitter(X3DAUDIO_EMITTER& emitter, const EmitterSettings& settings);

   //���X�i�[�̐ݒ�
   void SetupListener(X3DAUDIO_LISTENER& listener, const ListenerSettings& settings);

   //3D�I�[�f�B�I�v�Z�֐�
   void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& dspSettings);

   //�T�E���h�o�b�t�@�̍쐬�ƍĐ��p�֐�
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
};

