#pragma once
#include <experimental/random>

#define RadToDeg(x) (x) * 57.295779513f;
#define DegToRad(x) (x) * 0.01745329252f;

class Vector2 {
public:
    Vector2(float X, float Y) : X(X), Y(Y) {};
    explicit Vector2(int Degrees) : X(1), Y(0) { rotate((float)Degrees); };
    Vector2() : X(0), Y(0) {};

    float X, Y;

    Vector2 operator+(const Vector2 &right) const;
    Vector2 operator-(const Vector2 &right) const;
    Vector2 operator*(const Vector2 &right) const;
    Vector2 operator/(const Vector2 &right) const;
    Vector2 &operator+=(const Vector2 &right);
    Vector2 &operator-=(const Vector2 &right);
    Vector2 &operator*=(const Vector2 &right);
    Vector2 &operator/=(const Vector2 &right);
    bool operator==(const Vector2 &right) const;
    Vector2 operator*(float Value);
    Vector2 &operator*=(float Value);

    void rotate(float Degrees);
    void normalize();
    [[nodiscard]] [[nodiscard]] Vector2 normalized() const;
    [[nodiscard]] float absolute() const;
    static float dot(const Vector2 &left, const Vector2 &right);

    static void GetRandomRotatedVector(Vector2 &Vector);
    static void GetRandomVector(int& Band, Vector2& RandomVector);
};
