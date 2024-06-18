#include "Sound.h"

/*
  各関数や内容の説明を書く。
  その関数、コードがなぜ必要なのかどのように使うのかを書く
  　→自分で見たときに理解できるように。*/

Sound::Sound()
{
}

Sound::~Sound()
{
}

bool Sound::InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasteringVoice)
{
//XAudio2の初期化概要
 //  https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--initialize-xaudio2

	//エラーを返す
	HRESULT hr{};

	//COM(Component Object Mode)ライブラリを初期化
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return false;
	}

	//XAudio2エンジンの初期化
	hr = XAudio2Create(ppXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr)) {
		return false;
	}

	//マスタリング音声を生成
	hr = (*ppXAudio2)->CreateMasteringVoice(ppMasteringVoice);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool Sound::InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster)
{
	//エラーを返す
	 HRESULT hr{};

	//X3DAudioインスタンスを作成
	X3DAUDIO_HANDLE x3dInstance{};
	X3DAUDIO_HANDLE x3dInstanceMaster{};

	//X3DAudioインスタンスを初期化
	hr = (X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, x3dInstance));
	if (FAILED(hr)) {
		return false;
	}

	//マスター音源のX3DAudioインスタンスを初期化
	hr = (X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, x3dInstanceMaster/*エラー候補*/));
	if (FAILED(hr)) {
		return false;
	}

	
}

void Sound::SetupEmitter(const EmitterSettings& settings)
{
	if (!emitter) {
		emitter = new Emitter(settings);
	}
	else {
		emitter->
	}
}

void Sound::SetupListener(const ListenerSettings& settings)
{
}




void Sound::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings)
{
	

	
}

bool Sound::CreateAndPlaySourceVoice(IXAudio2* pXAudio2, IXAudio2SourceVoice** ppSourceVoice, WAVEFORMATEX& waveFormat, XAUDIO2_BUFFER& buffer)
{
	HRESULT hr{};

	//ソース音声を作成
	hr = pXAudio2->CreateSourceVoice(ppSourceVoice, &waveFormat);
	if (FAILED(hr)) {
		return false;
	}

	//(音声キュー?)に新しいオーディオバッファーを追加
	hr = (*ppSourceVoice)->SubmitSourceBuffer(&buffer);
	if (FAILED(hr)) {
		return false;
	}

	//オーディオ処理スレッドを開始
	hr = (*ppSourceVoice)->Start(0);
	if (FAILED(hr)) {
		return false;
	}



	return true;
}

void Sound::SetSoundParameters(const SoundParameters& params, float distance)
{
}
