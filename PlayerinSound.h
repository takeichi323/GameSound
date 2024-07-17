#pragma once
#include "Engine/GameObject.h"
#include "Engine/Sound/Sound.h"

//���������Ǘ�����N���X
class PlayerinSound : public GameObject
{
private:
    int hModel_;    //���f���ԍ�
    //Sound�N���X�̃C���X�^���X
    Sound sound_;

    //�T�E���h�ԍ�
    int hSound_;

public:
    //�R���X�g���N�^
    PlayerinSound(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerinSound();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����̃��[�h�ƍĐ�
    void LoadPlaySound(const std::string& filename);
};

