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

 /*--------------------仮------------------*/
    //それぞれの初期化している関数を呼び出す
    
    //XAudio2の初期化
    sound_.InitializeXAudio2(/*引数書く*/);
    //X3DAudioの初期化
    sound_.InitializeX3DAudio(/*引数書く*/);
   /*----------------------------------------*/
}

//更新
void PlayerinSound::Update()
{
    //エミッターの位置を更新
    sound_.SetupEmitter(/*引数書く*/);
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
