#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>

//���C�u�����ǂݍ���
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

class Sound
{
  //XAudio2�̏�����
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudio�̏�����
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //�G�~�b�^�̐ݒ�
   void SetupEmitter(X3DAUDIO_EMITTER& emitter);

   //���X�i�[�̐ݒ�
   void SetupListener(X3DAUDIO_LISTENER& listener);

   //3D�I�[�f�B�I�v�Z�֐�
   void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& dspSettings);

   //�T�E���h�o�b�t�@�̍쐬�ƍĐ��p�֐�
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
};

