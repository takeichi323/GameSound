#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>
#include "Emitter.h"
#include "Listener.h"

//���C�u�����ǂݍ���
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")
/*
 ���̌����v�Z���s��*/


class Sound
{
  //XAudio2�̏�����
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudio�̏�����
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //�G�~�b�^�̐ݒ�
   void SetupEmitter(const EmitterSettings& settings);

   //���X�i�[�̐ݒ�
   void SetupListener(const ListenerSettings& settings);

   //3D�I�[�f�B�I�v�Z�֐�
   void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& dspSettings);

   //�T�E���h�o�b�t�@�̍쐬�ƍĐ��p�֐�
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
};

