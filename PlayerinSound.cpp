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
}

//�J��
void PlayerinSound::Release()
{
}
