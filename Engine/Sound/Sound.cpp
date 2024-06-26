#include "Sound.h"

/*
  各関数や内容の説明を書く。
  その関数、コードがなぜ必要なのかどのように使うのかを書く
  　→自分で見たときに理解できるように。*/

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

	pMasteringVoice = *ppMasteringVoice;

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

	return true;
	
}

void Sound::SetupEmitter(const EmitterSettings& settings)
{
	if (!emitter) {
		emitter = new Emitter(settings);
	}
	else {
		//publicにしたのでエラーは消えた(とりあえずアクセス可能)
		emitter->settings = settings;
	}
}

void Sound::SetupListener(const ListenerSettings& settings)
{
	if (!listener) {
		listener = new Listener(settings);
	}
	else {
		//publicにしたのでエラーは消えた(とりあえずアクセス可能)
		listener->settings = settings;
	}
}




/*void Sound::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings)
{
	

}*/

void Sound::Update3DAudio()
{
	//もしエミッタとリスナーが両方存在していたら
	if (emitter && listener) {
	   //X3DAUDIO_EMITTERのインスタンスを生成
		X3DAUDIO_EMITTER x3dEmitter{};
	  //X3DAUDIO_LISTENERのインスタンスを生成
		X3DAUDIO_LISTENER x3dListener{};

		emitter->SetupEmitter(x3dEmitter);
		listener->SetupListener(x3dListener);

		sound3DManager.Calculate3DAudio(x3DInstance, x3dListener, x3dEmitter, pSourceVoice, pMasteringVoice);
	}
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
	
	if (pSourceVoice) {
		//周波数の設定
		XAUDIO2_VOICE_DETAILS voiceDetails{};
		pSourceVoice->GetVoiceDetails(&voiceDetails);
		float pitch = params.frequency / 44100.0f;//数値は仮（chatGPT案）
		//SetFrequencyRatio：周波数調整比メソッド
		pSourceVoice->SetFrequencyRatio(pitch);

		// 音量の設定
		float volumeFactor = std::pow(10.0f, params.volume / 20.0f);
		pSourceVoice->SetVolume(volumeFactor);

		// 減衰率の設定
		float attenuationFactor = 1.0f / (distance * distance);
		// Min Max で代用してみる
		attenuationFactor = std::clamp(attenuationFactor, 0.0f, 1.0f); // 過度な減衰を避ける
		pSourceVoice->SetVolume(volumeFactor * attenuationFactor);
	}
}
