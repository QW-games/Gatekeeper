#include "Vec2.h"
float Vec2::Magnitude() {
	return sqrt((x * x) + (y * y));
}
Vec2 Vec2::operator+(Vec2 const& vect) {
	return Vec2(x + vect.x, y+ vect.y);
}
Vec2 Vec2::operator-(Vec2 const& vect) {
	return Vec2(x - vect.x, y - vect.y);
}
Vec2 Vec2::operator*(Vec2 const& vect) {
	return Vec2(x * vect.x, y * vect.y);
}
Vec2 Vec2::operator*(float const& esc) {
	return Vec2(x * esc, y * esc);
}

bool Vec2::operator==(Vec2 d) {
	return d.x == x && d.y == y;
}

Vec2::Vec2(float x, float y){
	this->x = x;
	this->y = y;
}
Vec2 Vec2::Normalizado(){
	return Vec2(x / Magnitude(), y / Magnitude());
}
Vec2::Vec2(){
	x = 0;
	y = 0;
}

Vec2 Vec2::Rotate(double angleDeg) {
    double angleRad = M_PI * angleDeg / 180;

    Vec2 result;
    result.x = x * cos(angleRad) - y * sin(angleRad);
    result.y = y * cos(angleRad) + x * sin(angleRad);

    return result;
}

float Vec2::Inclinacao() {
	return atan2(y, x);
}

void Vec2::operator+=(Vec2 b) {
	x += b.x;
	y += b.y;
}

Vec2 Vec2::operator/(float d) const{
	return Vec2(x/d, y/d);
}