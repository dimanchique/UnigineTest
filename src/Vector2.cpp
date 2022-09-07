#include "Vector2.h"
#include <cmath>

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

bool Vector2::operator==(const Vector2 &right) const{
    return (X == right.X && Y == right.Y);
}

void Vector2::normalize() {
    if(X != 0 || Y != 0){
        const float length = absolute();
        X /= length;
        Y /= length;
    }
}

Vector2 Vector2::normalized() const {
    if(X != 0 || Y != 0){
        const float length = absolute();
        return { X / length, Y / length};
    }
    return {};
}

float Vector2::absolute() const {
    auto quad = X*X + Y*Y;
    float x = 1.0f;
    for (;;) {
        float nx = (x + quad / x) / 2;
        if (std::abs (x - nx) < 1e-5)
            break;
        x = nx;
    }
    return x;
}

float Vector2::dot(const Vector2 &left, const Vector2 &right) {
    return left.X * right.X + left.Y * right.Y;
}

void Vector2::rotate(float Degrees) {
    float Radians = DegToRad(Degrees)
    float x_1 = X;
    auto cos_rad = std::cos(Radians);
    float sin_rad = std::sin(Radians);
    X = ((X * cos_rad) - (Y * sin_rad));
    Y = (x_1 * sin_rad) + (Y * cos_rad);
}

void Vector2::GetRandomRotatedVector(Vector2 &RotatingVector) {
    RotatingVector = Vector2(std::experimental::randint(0, 360)).normalized();
}

void Vector2::GetRandomVector(int& Band, Vector2& RandomVector){
    RandomVector = Vector2((float)std::experimental::randint(-Band, Band - 1),
                           (float)std::experimental::randint(-Band, Band - 1));
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
