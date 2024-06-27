#pragma once
#include<Windows.h>
#include<x3daudio.h>
#include<xaudio2.h>
#include<cmath>
#include<algorithm>
#include "Emitter/Emitter.h"
#include "Listener/Listener.h"
#include "Sound3DManager/Sound3DManager.h"

//ライブラリ読み込み
#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "X3DAudio.lib")

//clampのエラーを解消するため・・・

template<typename T>
const T& clamp(const T& value, const T& low, const T& high) {
	return std::min(std::max(value, low), high);

	/*std::minとstd::maxを使用
  与えられた値 value を範囲 [low, high] に制限
  std::minは最小値を取得し、std::maxは最大値を取得することで、範囲外の値を修正*/

}

/*音の減衰計算を行う*/
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
	X3DAUDIO_HANDLE x3DInstance;// X3DAUDIO_HANDLE のインスタンス
	X3DAUDIO_HANDLE x3DInstanceMaster;

	Emitter* emitter;
	Listener* listener;
	Sound3DManager sound3DManager; // Sound3DManager のインスタンスを追加
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
   /*void Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& dspSettings);*/
   //
   void Update3DAudio();

   //サウンドバッファの作成と再生用関数
   bool CreateAndPlaySourceVoice(IXAudio2* pXAudio2,IXAudio2SourceVoice** ppSourceVoice,
	                                      WAVEFORMATEX& waveFormat,XAUDIO2_BUFFER& buffer);
   //サウンドの設定(音の減衰率、音量、周波数)
   void SetSoundParameters(const SoundParameters& params, float distance);
};

