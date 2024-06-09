#include "Sound.h"



bool Sound::InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasteringVoice)
{
//XAudio2�̏������T�v
 //  https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--initialize-xaudio2

	//�G���[��Ԃ�
	HRESULT hr{};

	//COM(Component Object Mode)���C�u������������
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}

	//XAudio2�G���W���̏�����
	hr = XAudio2Create(ppXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return false;
	}

	//�}�X�^�����O�����𐶐�
	hr = (*ppXAudio2)->CreateMasteringVoice(ppMasteringVoice);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool Sound::InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster)
{
	//�G���[��Ԃ�
	 HRESULT hr{};

	//X3DAudio�C���X�^���X���쐬
	X3DAUDIO_HANDLE x3dInstance{};
	X3DAUDIO_HANDLE x3dInstanceMaster{};

	//X3DAudio�C���X�^���X��������
	hr = (X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, x3dInstance));
	if (FAILED(hr)) {
		return false;
	}

	//�}�X�^�[������X3DAudio�C���X�^���X��������
	hr = (X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, x3dInstanceMaster/*�G���[���*/));
	if (FAILED(hr)) {
		return false;
	}
}

void Sound::SetupEmitter(X3DAUDIO_EMITTER& emitter, const EmitterSettings& settings)
{

}

void Sound::SetupListener(X3DAUDIO_LISTENER& listener, const ListenerSettings& settings)
{

}


void Sound::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings)
{
	//���u���@�T�C�Y�ύX�̉\������
	FLOAT32 matrix[8] = {};

	
}

bool Sound::CreateAndPlaySourceVoice(IXAudio2* pXAudio2, IXAudio2SourceVoice** ppSourceVoice, WAVEFORMATEX& waveFormat, XAUDIO2_BUFFER& buffer)
{
	HRESULT hr{};

	//�\�[�X�������쐬
	hr = pXAudio2->CreateSourceVoice(ppSourceVoice, &waveFormat);
	if (FAILED(hr)) {
		return false;
	}

	//(�����L���[?)�ɐV�����I�[�f�B�I�o�b�t�@�[��ǉ�
	hr = (*ppSourceVoice)->SubmitSourceBuffer(&buffer);
	if (FAILED(hr)) {
		return false;
	}

	//�I�[�f�B�I�����X���b�h���J�n
	hr = (*ppSourceVoice)->Start(0);
	if (FAILED(hr)) {
		return false;
	}



	return true;
}
