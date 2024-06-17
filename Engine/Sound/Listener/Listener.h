#include<x3daudio.h>

struct ListenerSettings {
	//���X�i�[�ʒuxyz
	X3DAUDIO_VECTOR position;
	//���X�i�[�̑O�������F������\���x�N�g��
	X3DAUDIO_VECTOR orientFront;
	//���X�i�[�����
	X3DAUDIO_VECTOR orientTop;
	//���X�i�[���x
	X3DAUDIO_VECTOR speed;
};

class Listener
{
public:
	Listener(const ListenerSettings& settings);
	/*Listener(X3DAUDIO_LISTENER& listener, const ListenerSettings& settings);*/
	/*�֐�()const:
	�@    �@�@�֐����̕ϐ������������ł��Ȃ��Ȃ�*/
	void SetupListener(X3DAUDIO_LISTENER& listener) const;

private:
	ListenerSettings settings;
	
};

