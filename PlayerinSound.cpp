#include "PlayerinSound.h"
#include "Engine/Model.h"

//�R���X�g���N�^
PlayerinSound::PlayerinSound(GameObject* parent)
    :GameObject(parent, "PlayerinSound"), hModel_(-1)
{
}

//�f�X�g���N�^
PlayerinSound::~PlayerinSound()
{
}

//������
void PlayerinSound::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);

 /*--------------------��------------------*/
    //���ꂼ��̏��������Ă���֐����Ăяo��
    
    //XAudio2�̏�����
    sound_.InitializeXAudio2(/*��������*/);
    //X3DAudio�̏�����
    sound_.InitializeX3DAudio(/*��������*/);
   /*----------------------------------------*/
}

//�X�V
void PlayerinSound::Update()
{
    //�G�~�b�^�[�̈ʒu���X�V
    sound_.SetupEmitter(/*��������*/);
}

//�`��
void PlayerinSound::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void PlayerinSound::Release()
{
}

//�����̃��[�h�ƍĐ�
//���̃R�[�h�͕ʂ�(Sound)�N���X�Ɉڂ��ׂ�
void PlayerinSound::LoadPlaySound(const std::string& filename)
{
    WAVEFORMATEX waveFormat{};
    XAUDIO2_BUFFER buffer{};
    
    //
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    if (sound_.CreateAndPlaySourceVoice(sound_.GetXAudio2(), &pSourceVoice, waveFormat, buffer))
    {
        sound_.SetSourceVoice(pSourceVoice);
    }

}
