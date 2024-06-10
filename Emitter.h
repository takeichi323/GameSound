#include<x3daudio.h>

/*//エミッター構造体
struct EmitterSettings {
	//エミッター位置
	X3DAUDIO_VECTOR position_;
	//エミッター速度
	X3DAUDIO_VECTOR speed_;
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
};*/

class Emitter
{
public:
	//ここに書くのはどうだろうか?
	Emitter(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& velocity, float innerRadius = 2.0f, float innerRadiusAngle = X3DAUDIO_PI / 4.0f, 
		    float curveDistanceScaler = 1.0f, float dopplerScaler = 1.0f, uint32_t channelCount = 1,float* pChannelAzimuths = nullptr);
	void SetupEmitter(X3DAUDIO_EMITTER& emitter);
private:
	X3DAUDIO_VECTOR position;
	X3DAUDIO_VECTOR velocity;


};

