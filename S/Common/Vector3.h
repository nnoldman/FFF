#pragma once

//A class for representing a 3d vector or point in space
//written by Kyle Marchev
class Vector3 {
  public:
    Vector3();
    Vector3(float x, float y, float z);

    float X() const;
    float Y() const;
    float Z() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    float Length();
    float LengthSquared();

    float Distance(Vector3 other);
    float DistanceSquared(Vector3 other);

    float Dot(Vector3 other);
    Vector3 Cross(Vector3 other);

    void Normalize();
    Vector3 Normalized();

    Vector3 operator+(const Vector3 &rhs);
    Vector3& operator+=(const Vector3 &rhs);
    Vector3 operator-(const Vector3 &rhs);
    Vector3& operator-=(const Vector3 &rhs);
    Vector3 operator*(const float &rhs);
    Vector3& operator*=(const float &rhs);
    Vector3 operator/(const float &rhs);
    Vector3& operator/=(const float &rhs);

    float operator [](int i) const {
        switch (i) {
        case 0:
            return mX;
            break;

        case 1:
            return mY;
            break;

        default:
            return mZ;
            break;
        }
    }

    float & operator [](int i) {
        switch (i) {
        case 0:
            return mX;
            break;

        case 1:
            return mY;
            break;

        default:
            return mZ;
            break;
        }
    }

  private:

    float mX;
    float mY;
    float mZ;
};

inline Vector3::Vector3() {
    mX = 0;
    mY = 0;
    mZ = 0;
}

inline Vector3::Vector3(float x, float y, float z) {
    mX = x;
    mY = y;
    mZ = z;
}


inline float Vector3::X() const {
    return mX;
}

inline float Vector3::Y() const {
    return mY;
}

inline float Vector3::Z() const {
    return mZ;
}


inline void Vector3::SetX(float x) {
    mX = x;
}

inline void Vector3::SetY(float y) {
    mY = y;
}

inline void Vector3::SetZ(float z) {
    mZ = z;
}


inline float Vector3::Length() {
    return sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

inline float Vector3::LengthSquared() {
    return pow(mX, 2) + pow(mY, 2) + pow(mZ, 2);
}


inline float Vector3::Distance(Vector3 other) {
    return sqrt(pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2));
}

inline float Vector3::DistanceSquared(Vector3 other) {
    return pow(other.X() - mX, 2) + pow(other.Y() - mY, 2) + pow(other.Z() - mZ, 2);
}


inline float Vector3::Dot(Vector3 other) {
    return (mX * other.X()) + (mY * other.Y()) + (mZ * other.Z());
}

inline Vector3 Vector3::Cross(Vector3 other) {
    Vector3 result;

    result.SetX((mY * other.Z()) - (other.Y() * mZ));
    result.SetY((mZ * other.X()) - (other.Z() * mX));
    result.SetZ((mX * other.Y()) - (other.X() * mY));

    return result;
}


inline void Vector3::Normalize() {
    float length = Length();

    mX = mX / length;
    mY = mY / length;
    mZ = mZ / length;
}

inline Vector3 Vector3::Normalized() {
    Vector3 result;
    float length = Length();

    result.SetX(mX / length);
    result.SetY(mY / length);
    result.SetZ(mZ / length);

    return result;
}

inline Vector3 Vector3::operator+(const Vector3 &rhs) {
    Vector3 vector = *this;
    vector += rhs;
    return vector;
}

inline Vector3& Vector3::operator+=(const Vector3 &rhs) {
    mX += rhs.mX;
    mY += rhs.mY;
    mZ += rhs.mZ;
    return *this;
}

inline Vector3 Vector3::operator-(const Vector3 &rhs) {
    Vector3 vector = *this;
    vector -= rhs;
    return vector;
}

inline Vector3& Vector3::operator-=(const Vector3 &rhs) {
    mX -= rhs.mX;
    mY -= rhs.mY;
    mZ -= rhs.mZ;
    return *this;
}

inline Vector3 Vector3::operator*(const float &rhs) {
    Vector3 vector = *this;
    vector *= rhs;
    return vector;
}

inline Vector3& Vector3::operator*=(const float &rhs) {
    mX *= rhs;
    mY *= rhs;
    mZ *= rhs;
    return *this;
}

inline Vector3 Vector3::operator/(const float &rhs) {
    Vector3 vector = *this;
    vector /= rhs;
    return vector;
}

inline Vector3& Vector3::operator/=(const float &rhs) {
    mX /= rhs;
    mY /= rhs;
    mZ /= rhs;
    return *this;
}
