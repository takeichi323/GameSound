#include<x3daudio.h>

//�G�~�b�^�[�\����
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
};

class Emitter
{
public:
	Emitter(const EmitterSettings& settings);
	void SetupEmitter(X3DAUDIO_EMITTER& emitter) const;
	void UpdateSettings(const EmitterSettings& newSettings);

private:
	EmitterSettings settings;


};

