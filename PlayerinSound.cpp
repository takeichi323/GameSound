#include "PlayerinSound.h"
#include "Engine/Model.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Audio.h"
/*
 8/10
  ファイルのエラーが発生
  設定を見直す
  ゲーム開発に戻る*/

//コンストラクタ
PlayerinSound::PlayerinSound(GameObject* parent)
    :GameObject(parent, "PlayerinSound"), hModel_(-1),hSound_(-1)
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
    hModel_ = Model::Load("BoxCollider.fbx");
    assert(hModel_ >= 0);

 /*--------------------仮------------------*/
//GameObjectクラスで行っている
    //それぞれの初期化している関数を呼び出す
    
    //sound_.AllInitialize();
   /* 　2つの初期化
          ↓*/
    //XAudio2の初期化
    //sound_.InitializeXAudio2(/*引数書く*/);
    //X3DAudioの初期化
    //sound_.InitializeX3DAudio(/*引数書く*/);
   /*----------------------------------------*/

    //3Dサウンドロード
    hSound_=sound_.LoadSound("footsteps.wav");
    assert(hSound_ >= 0);
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

    //サウンド再生
    sound_.Play(hSound_);

    
}

//開放
void PlayerinSound::Release()
{
}

//音声のロードと再生
//このコードは別の(Sound)クラスに移すべき
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
