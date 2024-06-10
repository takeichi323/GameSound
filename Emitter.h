#include<x3daudio.h>

/*//�G�~�b�^�[�\����
struct EmitterSettings {
	//�G�~�b�^�[�ʒu
	X3DAUDIO_VECTOR position_;
	//�G�~�b�^�[���x
	X3DAUDIO_VECTOR speed_;
	//�G�~�b�^�[�������a���w��
	float innnerRadius = 2.0f;
	//�G�~�b�^�[�������a�̊p�x���w��
	float innnerRadiusAngle = X3DAUDIO_PI / 4.0;
	//���̋��������X�P�[�����O�W��(��׋�)
	float curveDistanceScaler = 1.0f;
	//�h�b�v���[���ʂ̃X�P�[�����O�W��(��׋�)
	float dopplerScaler = 1.0f;
	//�����̃`�����l�������w��
	uint32_t channelCount = 1;
	//�`�����l�����Ƃ̕��ʊp���i�[����z��ւ̃|�C���^(��׋�)
	float* pChannelAzimuths = nullptr;
};*/

class Emitter
{
public:
	//�����ɏ����̂͂ǂ����낤��?
	Emitter(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& velocity, float innerRadius = 2.0f, float innerRadiusAngle = X3DAUDIO_PI / 4.0f, 
		    float curveDistanceScaler = 1.0f, float dopplerScaler = 1.0f, uint32_t channelCount = 1,float* pChannelAzimuths = nullptr);
	void SetupEmitter(X3DAUDIO_EMITTER& emitter);
private:
	X3DAUDIO_VECTOR position;
	X3DAUDIO_VECTOR velocity;


};

