#include "Sound.h"
#include <iostream>
#include "../Global.h"

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

	//pXAudio2 = *ppXAudio2;
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
		attenuationFactor = clamp(attenuationFactor, 0.0f, 1.0f); // 過度な減衰を避ける
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
	//ファイルを開く
	HANDLE hFile = CreateFile(filename.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		// エラーログを出力
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	DWORD dwBytes;
	//チャンク構造体
	struct Chunk
	{
		char	id[5] = ""; 			// ID
		unsigned int	size = 0;	// サイズ
	};
	Chunk riffChunk = {};
	// RIFFチャンクIDを読み取る
	ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
	// RIFFチャンクのサイズを読み取る
	ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);
	char wave[4] = {};
	// WAVEフォーマットであることを確認するために "WAVE" 文字列を読み取る
	ReadFile(hFile, &wave, 4, &dwBytes, NULL);

	Chunk formatChunk = {};
	// フォーマットチャンクを見つけるためにループする
	while (formatChunk.id[0] != 'f') {
		ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL);
	}
	// フォーマットチャンクのサイズを読み取る
	ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);

	WAVEFORMATEX fmt = {};
	// WAVEフォーマットタグを読み取る
	ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);
	// チャネル数を読み取る
	ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);
	// サンプルレートを読み取る
	ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);
	// 平均バイト数を読み取る
	ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);
	// ブロックアラインを読み取る
	ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);
	// サンプルあたりのビット数を読み取る
	ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);

	Chunk dataChunk = {};
	// データチャンクを見つけるためにループする
	while (true) {
		ReadFile(hFile, &dataChunk.id, 4, &dwBytes, NULL);
		if (strcmp(dataChunk.id, "data") == 0) {
			break;
		}
		else {
			// データチャンクのサイズを読み取る
			ReadFile(hFile, &dataChunk.size, 4, &dwBytes, NULL);
			// チャンクのデータを一時バッファに読み込む
			char* pBuffer = new char[dataChunk.size];
			ReadFile(hFile, pBuffer, dataChunk.size, &dwBytes, NULL);
			delete[] pBuffer;
		}
	}
	// データチャンクのサイズを読み取る
	ReadFile(hFile, &dataChunk.size, 4, &dwBytes, NULL);

	// データチャンクのデータをバッファに読み込む
	char* pBuffer = new char[dataChunk.size];
	ReadFile(hFile, pBuffer, dataChunk.size, &dwBytes, NULL);
	CloseHandle(hFile); // ファイルハンドルを閉じる

	// XAudio2用のバッファを設定
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = dataChunk.size; // オーディオデータのサイズを設定
	buffer.pAudioData = reinterpret_cast<BYTE*>(pBuffer); // オーディオデータへのポインタを設定
	buffer.Flags = XAUDIO2_END_OF_STREAM; // バッファの終了を示すフラグ
	buffer.LoopCount = isLoop ? XAUDIO2_LOOP_INFINITE : 0; // ループ回数を設定

	// WAVEフォーマットの詳細を設定
	WAVEFORMATEX waveFormat = {};
	waveFormat.wFormatTag = fmt.wFormatTag; // フォーマットタグ
	waveFormat.nChannels = fmt.nChannels; // チャネル数
	waveFormat.nSamplesPerSec = fmt.nSamplesPerSec; // サンプルレート
	waveFormat.nAvgBytesPerSec = fmt.nAvgBytesPerSec; // 平均バイト数
	waveFormat.nBlockAlign = fmt.nBlockAlign; // ブロックアライン
	waveFormat.wBitsPerSample = fmt.wBitsPerSample; // サンプルあたりのビット数

	// ソースボイスを作成し、オーディオデータを再生する
	if (CreateAndPlaySourceVoice(pXAudio2, &pSourceVoice, waveFormat, buffer)) {
		pSourceVoice->Start(0); // ソースボイスの再生を開始
	}
	SAFE_DELETE_ARRAY(pBuffer); // バッファのメモリを解放
}
