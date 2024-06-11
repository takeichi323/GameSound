#include<x3daudio.h>

struct ListenerSettings {
	//リスナー位置xyz
	X3DAUDIO_VECTOR position;
	//リスナーの前方方向：方向を表すベクトル
	X3DAUDIO_VECTOR orientFront;
	//リスナー上方向
	X3DAUDIO_VECTOR orientTop;
	//リスナー速度
	X3DAUDIO_VECTOR speed;
};

class Listener
{
public:
	Listener(const ListenerSettings& settings);
	/*Listener(X3DAUDIO_LISTENER& listener, const ListenerSettings& settings);*/
	/*関数()const:
	　    　　関数内の変数が書き換えできなくなる*/
	void SetupListener(X3DAUDIO_LISTENER& listener) const;

private:
	ListenerSettings settings;
	
};

