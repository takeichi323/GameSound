#pragma once
#include "Engine/GameObject.h"
#include "Engine/Sound/Sound.h"

//◆◆◆を管理するクラス
class PlayerinSound : public GameObject
{
private:
    int hModel_;    //モデル番号
    //Soundクラスのインスタンス
    Sound sound_;

    //サウンド番号
    int hSound_;

public:
    //コンストラクタ
    PlayerinSound(GameObject* parent);

    //デストラクタ
    ~PlayerinSound();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //音声のロードと再生
    void LoadPlaySound(const std::string& filename);
};

