#include "Sound.h"

/*
  �e�֐�����e�̐����������B
  ���̊֐��A�R�[�h���Ȃ��K�v�Ȃ̂��ǂ̂悤�Ɏg���̂�������
  �@�������Ō����Ƃ��ɗ����ł���悤�ɁB*/

Sound::Sound():pSourceVoice(nullptr), pMasteringVoice(nullptr), emitter(nullptr), listener(nullptr)
{
}

Sound::~Sound()
{
	if (pSourceVoice) {
		pSourceVoice->DestroyVoice();
	}
	delete emitter;
	delete listener;
	//CoUninitialize();
}

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

	pMasteringVoice = *ppMasteringVoice;

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

	return true;
	
}

void Sound::SetupEmitter(const EmitterSettings& settings)
{
	if (!emitter) {
		emitter = new Emitter(settings);
	}
	else {
		//public�ɂ����̂ŃG���[�͏�����(�Ƃ肠�����A�N�Z�X�\)
		emitter->settings = settings;
	}
}

void Sound::SetupListener(const ListenerSettings& settings)
{
	if (!listener) {
		listener = new Listener(settings);
	}
	else {
		//public�ɂ����̂ŃG���[�͏�����(�Ƃ肠�����A�N�Z�X�\)
		listener->settings = settings;
	}
}




/*void Sound::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings)
{
	

}*/

void Sound::Update3DAudio()
{
	//�����G�~�b�^�ƃ��X�i�[���������݂��Ă�����
	if (emitter && listener) {
	   //X3DAUDIO_EMITTER�̃C���X�^���X�𐶐�
		X3DAUDIO_EMITTER x3dEmitter{};
	  //X3DAUDIO_LISTENER�̃C���X�^���X�𐶐�
		X3DAUDIO_LISTENER x3dListener{};

		emitter->SetupEmitter(x3dEmitter);
		listener->SetupListener(x3dListener);

		sound3DManager.Calculate3DAudio(x3DInstance, x3dListener, x3dEmitter, pSourceVoice, pMasteringVoice);
	}
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

void Sound::SetSoundParameters(const SoundParameters& params, float distance)
{
	
	if (pSourceVoice) {
		//���g���̐ݒ�
		XAUDIO2_VOICE_DETAILS voiceDetails{};
		pSourceVoice->GetVoiceDetails(&voiceDetails);
		float pitch = params.frequency / 44100.0f;//���l�͉��ichatGPT�āj
		//SetFrequencyRatio�F���g�������䃁�\�b�h
		pSourceVoice->SetFrequencyRatio(pitch);

		// ���ʂ̐ݒ�
		float volumeFactor = std::pow(10.0f, params.volume / 20.0f);
		pSourceVoice->SetVolume(volumeFactor);

		// �������̐ݒ�
		float attenuationFactor = 1.0f / (distance * distance);
		// Min Max �ő�p���Ă݂�
		attenuationFactor = std::clamp(attenuationFactor, 0.0f, 1.0f); // �ߓx�Ȍ����������
		pSourceVoice->SetVolume(volumeFactor * attenuationFactor);
	}
}
