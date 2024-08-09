#include "PlayerinSound.h"
#include "Engine/Model.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Audio.h"
/*
 8/10
  �t�@�C���̃G���[������
  �ݒ��������
  �Q�[���J���ɖ߂�*/

//�R���X�g���N�^
PlayerinSound::PlayerinSound(GameObject* parent)
    :GameObject(parent, "PlayerinSound"), hModel_(-1),hSound_(-1)
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
    hModel_ = Model::Load("BoxCollider.fbx");
    assert(hModel_ >= 0);

 /*--------------------��------------------*/
//GameObject�N���X�ōs���Ă���
    //���ꂼ��̏��������Ă���֐����Ăяo��
    
    //sound_.AllInitialize();
   /* �@2�̏�����
          ��*/
    //XAudio2�̏�����
    //sound_.InitializeXAudio2(/*��������*/);
    //X3DAudio�̏�����
    //sound_.InitializeX3DAudio(/*��������*/);
   /*----------------------------------------*/

    //3D�T�E���h���[�h
    hSound_=sound_.LoadSound("footsteps.wav");
    assert(hSound_ >= 0);
}

//�X�V
void PlayerinSound::Update()
{
}

//�`��
void PlayerinSound::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�T�E���h�Đ�
    sound_.Play(hSound_);

    
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
