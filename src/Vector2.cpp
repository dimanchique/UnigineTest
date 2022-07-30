#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2 &right) const {
    Vector2 temp(*this);
    temp += right;
    return temp;
}

Vector2 Vector2::operator-(const Vector2 &right) const {
    Vector2 temp(*this);
    temp -= right;
    return temp;
}

Vector2 Vector2::operator*(const Vector2 &right) const {
    Vector2 temp(*this);
    temp *= right;
    return temp;
}

Vector2 Vector2::operator/(const Vector2 &right) const {
    Vector2 temp(*this);
    temp /= right;
    return temp;
}

Vector2 &Vector2::operator+=(const Vector2 &right) {
    X += right.X;
    Y += right.Y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &right) {
    X -= right.X;
    Y -= right.Y;
    return *this;
}

Vector2 &Vector2::operator*=(const Vector2 &right) {
    X *= right.X;
    Y *= right.Y;
    return *this;
}

Vector2 &Vector2::operator/=(const Vector2 &right) {
    if(right.X != 0 && right.Y != 0){
        X /= right.X;
        Y /= right.Y;
    }
    return *this;
}

bool Vector2::operator==(const Vector2 &right){
    return (X == right.X && Y == right.Y);
}

void Vector2::normalize() {
    if(X != 0 || Y != 0){
        const float length = absolute();
        X /= length;
        Y /= length;
    }
}

float Vector2::absolute() const {
    return sqrt(pow(X, 2) + pow(Y, 2));
}

float Vector2::dot(const Vector2 &left, const Vector2 &right) {
    return left.X * right.X + left.Y * right.Y;
}

float Vector2::distance(const Vector2 &left, const Vector2 &right) {
    return (left-right).absolute();
}

void Vector2::rotate(float Degrees) {
    float Radians = DegToRad(Degrees);
    float x_1 = X;
    X = (X * cos(Radians)) - (Y * sin(Radians));
    Y = (x_1 * sin(Radians)) + (Y * cos(Radians));
}

Vector2 Vector2::GetRandomRotatedVector() {
    return {std::experimental::randint(0, 360)};
}

Vector2 Vector2::operator*(const float Value) {
    Vector2 temp(*this);
    temp *= Value;
    return temp;
}

Vector2 &Vector2::operator*=(const float Value) {
    X *= Value;
    Y *= Value;
    return *this;
}
