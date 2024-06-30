#include "PlayerinSound.h"
#include "Engine/Model.h"

//コンストラクタ
PlayerinSound::PlayerinSound(GameObject* parent)
    :GameObject(parent, "PlayerinSound"), hModel_(-1)
{
}

//デストラクタ
PlayerinSound::~PlayerinSound()
{
}

//初期化
void PlayerinSound::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void PlayerinSound::Update()
{
}

//描画
void PlayerinSound::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void PlayerinSound::Release()
{
}
