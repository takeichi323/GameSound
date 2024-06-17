#include "Sound3DManager.h"

Sound3DManager::Sound3DManager()
	:x3dInstance{}
{
}

Sound3DManager::~Sound3DManager()
{
}

bool Sound3DManager::Initialize(X3DAUDIO_HANDLE x3dInstance)
{
	
	//this->x3dInstance = x3dInstance;
	return true;
}

void Sound3DManager::SetListenerParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop)
{
	//リスナー
	//位置
	listener.Position = position;
	//前方ベクトル
	listener.OrientFront = orientFront;
	//上方向ベクトル
	listener.OrientTop = orientTop;
	//速度
	listener.Velocity = { 0.0f,0.0f,0.0f };
}

void Sound3DManager::SetEmitterParameters(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& velocity)
{
	//エミッター
	//位置
	emitter.Position = position;
	//速度
	emitter.Velocity = velocity;
	//チャンネル数セット
	emitter.ChannelCount = 1;
	//出力チャンネル
	emitter.CurveDistanceScaler = 1.0f;
	emitter.DopplerScaler = 1.0f;
}

void Sound3DManager::Calculate3DAudio(X3DAUDIO_HANDLE x3DInstance, X3DAUDIO_LISTENER& listener, X3DAUDIO_EMITTER& emitter, IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice)
{
	//DSP設定の初期化
	X3DAUDIO_DSP_SETTINGS dspSettings{};
	//マトリックスの初期化
	FLOAT32 matrix[2]{};
	//エミッタチャンネル
	dspSettings.SrcChannelCount = emitter.ChannelCount;
	dspSettings.DstChannelCount = 2;//ステレオ出力
	//マトリックス係数
	dspSettings.pMatrixCoefficients = matrix;
	//X3DAudioCalculate関数を呼び出して3Dオーディオ効果を計算
	X3DAudioCalculate(x3dInstance, &listener, &emitter, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER, &dspSettings);
	//計算されたドップラーファクターをソースボイスに設定
	pSourceVoice->SetFrequencyRatio(dspSettings.DopplerFactor);
	//計算された出力マトリックスをソースボイスに設定
	pSourceVoice->SetOutputMatrix(pMasteringVoice, 1, 2, dspSettings.pMatrixCoefficients);

}
