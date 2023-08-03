#include "Component.h"

Component::Component(GameObject& associated) : associated(associated) {
}

Component::~Component() {
}

void Component::Start() {
}

void Component::NotifyCollision(GameObject& other) {
}

void Component::Obliterate() {}

void Component::FallToTable() {}

void Component::ResetDestination(Vec2) {}

