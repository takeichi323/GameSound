#include "Listener.h"


Listener::Listener(const ListenerSettings& settings)
	:settings(settings)
{
}

void Listener::SetupListener(X3DAUDIO_LISTENER& listener) const
{
	listener.Position = settings.position;
	listener.OrientFront = settings.orientFront;
	listener.OrientTop = settings.orientTop;
	listener.Velocity = settings.speed;
}

