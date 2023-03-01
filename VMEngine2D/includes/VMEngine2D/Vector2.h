#pragma once

class Vector2 {
public:
	//initialise vectors with 0 and y
	Vector2() { x = y = 0.0f; }
	Vector2(float x, float y);
	~Vector2() {}

	// Below are the math operators for our vector class
	// Addition Operators
	Vector2 operator+(const Vector2& OtherVector);
	Vector2 operator+=(const Vector2& OtherVector);

	//Subtraction Operators
	Vector2 operator-(const Vector2& OtherVector);
	Vector2 operator-=(const Vector2& OtherVector);

	//Multiplication operators
	Vector2 operator*(const float& Scalar);
	Vector2 operator*=(const float& Scalar);

	//Division operators
	Vector2 operator/(const float& Scalar);
	Vector2 operator/=(const float& Scalar);

	//Boolean Operators
	bool operator==(const Vector2& OtherVector);
	bool operator!=(const Vector2& OtherVector);

	// Get the magnitude/length of the vector
	float Length();

	// normalise the vector
	// same as direction in most cases
	void Normalise();
	Vector2 Normalised();

	// return a zero vector
	static Vector2 Zero();

public:
	//variables
	float x, y;

};