#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>
#include "Emitter/Emitter.h"
#include "Listener/Listener.h"
#include "Sound3DManager/Sound3DManager.h"

//ライブラリ読み込み
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")
/*
 音の減衰計算を行う*/
struct SoundParameters
{
	float frequency; //周波数
	float volume;    //音量
	float attenuation;//減衰率

};


class Sound
{
private:
	IXAudio2SourceVoice* pSourceVoice;
	IXAudio2MasteringVoice* pMasteringVoice;
	X3DAUDIO_HANDLE x3DInstance;
	X3DAUDIO_HANDLE x3DInstanceMaster;

	Emitter* emitter;
	Listener* listener;
	Sound3DManager* sound3DManager;
public:
	//コンストラクタ
	Sound();
	//デストラクタ
	~Sound();
  //XAudio2の初期化
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudioの初期化
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //エミッタの設定
   void SetupEmitter(const EmitterSettings& settings);

   //リスナーの設定
   void SetupListener(const ListenerSettings& settings);

   //3Dオーディオ計算関数
   void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& dspSettings);

   //サウンドバッファの作成と再生用関数
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
};

