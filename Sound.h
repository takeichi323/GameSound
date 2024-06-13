#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>
#include "Emitter.h"
#include "Listener.h"

//ライブラリ読み込み
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")
/*
 音の減衰計算を行う*/


class Sound
{
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

