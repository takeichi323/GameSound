#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>
#include<cmath>
#include<algorithm>
#include "Emitter/Emitter.h"
#include "Listener/Listener.h"
#include "Sound3DManager/Sound3DManager.h"

//���C�u�����ǂݍ���
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

//clamp�̃G���[���������邽�߁E�E�E

template<typename T>
const T& clamp(const T& value, const T& low, const T& high) {
	return std::min(std::max(value, low), high);

	/*std::min��std::max���g�p
  �^����ꂽ�l value ��͈� [low, high] �ɐ���
  std::min�͍ŏ��l���擾���Astd::max�͍ő�l���擾���邱�ƂŁA�͈͊O�̒l���C��*/

}

/*���̌����v�Z���s��*/
struct SoundParameters
{
	float frequency; //���g��
	float volume;    //����
	float attenuation;//������

};


class Sound
{
private:
	IXAudio2SourceVoice* pSourceVoice;
	IXAudio2MasteringVoice* pMasteringVoice;
	X3DAUDIO_HANDLE x3DInstance;// X3DAUDIO_HANDLE �̃C���X�^���X
	X3DAUDIO_HANDLE x3DInstanceMaster;

	Emitter* emitter;
	Listener* listener;
	Sound3DManager sound3DManager; // Sound3DManager �̃C���X�^���X��ǉ�
public:
	//�R���X�g���N�^
	Sound();
	//�f�X�g���N�^
	~Sound();
  //XAudio2�̏�����
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudio�̏�����
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //�G�~�b�^�̐ݒ�
   void SetupEmitter(const EmitterSettings& settings);

   //���X�i�[�̐ݒ�
   void SetupListener(const ListenerSettings& settings);

   //3D�I�[�f�B�I�v�Z�֐�
   /*void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings);*/
   //
   void Update3DAudio();

   //�T�E���h�o�b�t�@�̍쐬�ƍĐ��p�֐�
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
   //�T�E���h�̐ݒ�(���̌������A���ʁA���g��)
   void SetSoundParameters(const SoundParameters& params, float distance);
};

