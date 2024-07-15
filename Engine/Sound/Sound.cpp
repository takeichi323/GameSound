#include "Sound.h"
#include <iostream>
#include "../Global.h"

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

	if (pMasteringVoice) {
		pMasteringVoice->DestroyVoice();
	}
	if (pXAudio2) {
		pXAudio2->Release();
	}
	CoUninitialize();
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

	//pXAudio2 = *ppXAudio2;
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
		attenuationFactor = clamp(attenuationFactor, 0.0f, 1.0f); // �ߓx�Ȍ����������
		pSourceVoice->SetVolume(volumeFactor * attenuationFactor);
	}
}

IXAudio2* Sound::GetXAudio2() const
{
	return pXAudio2;
}

void Sound::SetSourceVoice(IXAudio2SourceVoice* pSourceVoice_)
{
	pSourceVoice = pSourceVoice_;
}

void Sound::LoadSound(const std::string& filename, bool isLoop)
{
	//�t�@�C�����J��
	HANDLE hFile = CreateFile(filename.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		// �G���[���O���o��
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	DWORD dwBytes;
	//�`�����N�\����
	struct Chunk
	{
		char	id[5] = ""; 			// ID
		unsigned int	size = 0;	// �T�C�Y
	};
	Chunk riffChunk = {};
	// RIFF�`�����NID��ǂݎ��
	ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
	// RIFF�`�����N�̃T�C�Y��ǂݎ��
	ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);
	char wave[4] = {};
	// WAVE�t�H�[�}�b�g�ł��邱�Ƃ��m�F���邽�߂� "WAVE" �������ǂݎ��
	ReadFile(hFile, &wave, 4, &dwBytes, NULL);

	Chunk formatChunk = {};
	// �t�H�[�}�b�g�`�����N�������邽�߂Ƀ��[�v����
	while (formatChunk.id[0] != 'f') {
		ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL);
	}
	// �t�H�[�}�b�g�`�����N�̃T�C�Y��ǂݎ��
	ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);

	WAVEFORMATEX fmt = {};
	// WAVE�t�H�[�}�b�g�^�O��ǂݎ��
	ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);
	// �`���l������ǂݎ��
	ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);
	// �T���v�����[�g��ǂݎ��
	ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);
	// ���σo�C�g����ǂݎ��
	ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);
	// �u���b�N�A���C����ǂݎ��
	ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);
	// �T���v��������̃r�b�g����ǂݎ��
	ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);

	Chunk dataChunk = {};
	// �f�[�^�`�����N�������邽�߂Ƀ��[�v����
	while (true) {
		ReadFile(hFile, &dataChunk.id, 4, &dwBytes, NULL);
		if (strcmp(dataChunk.id, "data") == 0) {
			break;
		}
		else {
			// �f�[�^�`�����N�̃T�C�Y��ǂݎ��
			ReadFile(hFile, &dataChunk.size, 4, &dwBytes, NULL);
			// �`�����N�̃f�[�^���ꎞ�o�b�t�@�ɓǂݍ���
			char* pBuffer = new char[dataChunk.size];
			ReadFile(hFile, pBuffer, dataChunk.size, &dwBytes, NULL);
			delete[] pBuffer;
		}
	}
	// �f�[�^�`�����N�̃T�C�Y��ǂݎ��
	ReadFile(hFile, &dataChunk.size, 4, &dwBytes, NULL);

	// �f�[�^�`�����N�̃f�[�^���o�b�t�@�ɓǂݍ���
	char* pBuffer = new char[dataChunk.size];
	ReadFile(hFile, pBuffer, dataChunk.size, &dwBytes, NULL);
	CloseHandle(hFile); // �t�@�C���n���h�������

	// XAudio2�p�̃o�b�t�@��ݒ�
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = dataChunk.size; // �I�[�f�B�I�f�[�^�̃T�C�Y��ݒ�
	buffer.pAudioData = reinterpret_cast<BYTE*>(pBuffer); // �I�[�f�B�I�f�[�^�ւ̃|�C���^��ݒ�
	buffer.Flags = XAUDIO2_END_OF_STREAM; // �o�b�t�@�̏I���������t���O
	buffer.LoopCount = isLoop ? XAUDIO2_LOOP_INFINITE : 0; // ���[�v�񐔂�ݒ�

	// WAVE�t�H�[�}�b�g�̏ڍׂ�ݒ�
	WAVEFORMATEX waveFormat = {};
	waveFormat.wFormatTag = fmt.wFormatTag; // �t�H�[�}�b�g�^�O
	waveFormat.nChannels = fmt.nChannels; // �`���l����
	waveFormat.nSamplesPerSec = fmt.nSamplesPerSec; // �T���v�����[�g
	waveFormat.nAvgBytesPerSec = fmt.nAvgBytesPerSec; // ���σo�C�g��
	waveFormat.nBlockAlign = fmt.nBlockAlign; // �u���b�N�A���C��
	waveFormat.wBitsPerSample = fmt.wBitsPerSample; // �T���v��������̃r�b�g��

	// �\�[�X�{�C�X���쐬���A�I�[�f�B�I�f�[�^���Đ�����
	if (CreateAndPlaySourceVoice(pXAudio2, &pSourceVoice, waveFormat, buffer)) {
		pSourceVoice->Start(0); // �\�[�X�{�C�X�̍Đ����J�n
	}
	SAFE_DELETE_ARRAY(pBuffer); // �o�b�t�@�̃����������
}
