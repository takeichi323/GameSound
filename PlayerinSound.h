#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class PlayerinSound : public GameObject
{

    int hModel_;    //���f���ԍ�

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
};

