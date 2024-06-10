#include "Listener.h"

Listener::Listener(const X3DAUDIO_VECTOR& position, const X3DAUDIO_VECTOR& orientFront, const X3DAUDIO_VECTOR& orientTop, const X3DAUDIO_VECTOR& velocity)
	: position(position), orientFront(orientFront), orientTop(orientTop), velocity(velocity) {}


void Listener::SetupListener(X3DAUDIO_LISTENER& listener) const
{
	listener.Position = position;
	listener.OrientFront = orientFront;
	listener.OrientTop = orientTop;
	listener.Velocity = velocity;
}

