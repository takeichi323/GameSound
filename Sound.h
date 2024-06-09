#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>

//ライブラリ読み込み
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

//エミッター構造体
struct EmitterSettings{

 //エミッター位置
  X3DAUDIO_VECTOR position_;
 //エミッター速度
  X3DAUDIO_VECTOR velocity_;
 //エミッター内部半径を指定
  float innnerRadius = 2.0f;
 //エミッター内部半径の角度を指定
  float innnerRadiusAngle = X3DAUDIO_PI / 4.0;
 //音の距離減衰スケーリング係数(後勉強)
  float curveDistanceScaler = 1.0f;
 //ドップラー効果のスケーリング係数(後勉強)
  float dopplerScaler = 1.0f;
 //音源のチャンネル数を指定
  uint32_t channelCount = 1;
 //チャンネルごとの方位角を格納する配列へのポインタ(後勉強)
  float* pChannelAzimuths = nullptr;
};

struct ListenerSettings{
	X3DAUDIO_VECTOR position;
	X3DAUDIO_VECTOR orientFront;
	X3DAUDIO_VECTOR orientTop;
	X3DAUDIO_VECTOR velocity;
};

class Sound
{
  //XAudio2の初期化
   bool InitializeXAudio2(IXAudio2** ppXAudio2, IXAudio2MasteringVoice** ppMasterVoice);

   //X3DAudioの初期化
   bool InitializeX3DAudio(X3DAUDIO_HANDLE* pX3DInstance, X3DAUDIO_HANDLE* pX3DInstanceMaster);

   //エミッタの設定
   void SetupEmitter(X3DAUDIO_EMITTER& emitter, const EmitterSettings& settings);

   //リスナーの設定
   void SetupListener(X3DAUDIO_LISTENER& listener, const ListenerSettings& settings);

   //3Dオーディオ計算関数
   void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance,X3DAUDIO_LISTENER& dspSettings);

   //サウンドバッファの作成と再生用関数
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
};

