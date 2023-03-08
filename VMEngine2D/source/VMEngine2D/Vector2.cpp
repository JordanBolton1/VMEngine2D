#include "VMEngine2D/Vector2.h"
#include <iostream>

Vector2::Vector2(float x, float y)
{
	//this->x is the class variable
	//x is the paramater
	//all functions will use the paramatar name over the class name
	this->x = x;
	this->y = y;


}

Vector2 Vector2::operator+(const Vector2& OtherVector)
{
	//add the current vectors x with the other vectors x
	// do the same with y
	// example: Vector2(1.0f, 2.0f) + Vector(1.0f, 1.0f) = Vector2(2.0f, 3.0f)
	return Vector2(this->x + OtherVector.x, this->y + OtherVector.y);
}

Vector2 Vector2::operator+=(const Vector2& OtherVector)
{
	// increment the x and y values of this vector by the other vector
	// example: a = Vector(1.0f, 1.0f) += b = Vector(2.0f, 1.0f)
	// a = Vector(3.0f, 2.0f)

	this->x += OtherVector.x;
	this->y += OtherVector.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& OtherVector)
{
	// subtract the current vectors x with the other vectors x
	// do the same with y
	// example: Vector2(1.0f, 2.0f) - Vector2(1.0f, 1.0f) = Vector2(0.0f, 1.0f)
	return Vector2(this->x - OtherVector.x, this->y - OtherVector.y);
}

Vector2 Vector2::operator-=(const Vector2& OtherVector)
{
	//decrement the x and y values of this vector by the other vector
	// example: a = Vector(1.0f, 1.0f) -= b = Vector(2.0f, 1.0f)
	// a = Vector(1.0f, 0.0f)

	this->x -= OtherVector.x;
	this->y -= OtherVector.y;

	return *this;
}

Vector2 Vector2::operator*(const float& Scalar)
{
	// Multiplying the x and y of this current vector by the x and y of a Scalar value
	// Example: Vector2 (1.0f, 2.0f) * 5.0f = Vector2(5.0f, 10.0f)
	return Vector2(this->x * Scalar, this->y * Scalar);
}

Vector2 Vector2::operator*=(const float& Scalar)
{
	//multiply the vector by itself and a float value.
	// example: a = Vector2(1.0f, 2.0f) *= 5.0f
	//a = Vector2(5.0f, 10.0f)
	this->x *= Scalar;
	this->y *= Scalar;

	return *this;
}

Vector2 Vector2::operator/(const float& Scalar)
{
	//Divide the vector x and y by a float value
	//Example: Vector2(2.0f, 1.0f) / 2.0f = Vector(1.0f, 0.5f)
	Vector2 DividedVector = Vector2(0.0f, 0.0f);

	// Only do the division if we don't divide by 0.0f
	if (Scalar != 0.0f) {
		DividedVector.x = this->x / Scalar;
		DividedVector.y = this->y / Scalar;
	}
	else {
		//Warn the programmer they divided by 0.0f
		std::cout << "Cannot divide Vector2 by 0!" << std::endl;
	}

	return DividedVector;
}

Vector2 Vector2::operator/=(const float& Scalar)
{
	//We're dividing the current vector by a float value
	//Example: a = Vector2(2.0f, 5.0f) /= 2.0f
	// a = Vector2(1.0f, 2.5f)


	// Only do the division if we don't divide by 0.0f
	if (Scalar != 0.0f) {
		this->x / Scalar;
		this->y / Scalar;
	}
	else {
		//Warn the programmer they divided by 0.0f
		std::cout << "Cannot divide Vector2 by 0!" << std::endl;
	}

	return *this;
}

bool Vector2::operator==(const Vector2& OtherVector)
{
	//return true if the 2 vectors match both x and y
	bool bMatchX = this->x == OtherVector.x;
	bool bMatchY = this->y == OtherVector.y;

	//the boolean operator && will return false if one of them isn't true.
	return bMatchX && bMatchY;
}

bool Vector2::operator!=(const Vector2& OtherVector)
{
	//return true if the 2 vectors don't match x or y
	bool bMatchX = this->x != OtherVector.x;
	bool bMatchY = this->y != OtherVector.y;

	//the boolean operator && will return false if one of them isn't true.
	return bMatchX && bMatchY;
}

float Vector2::Length()
{
	//return the size of the vector using its x and y
	return sqrtf(x * x + y * y);
}

void Vector2::Normalise()
{
	//if the length is above 0.0f then /= the x and y by the length of the vector
	// This will change the vector
	*this /= std::max(Length(), 1.0f);
}

Vector2 Vector2::Normalised()
{
	//Divide the vector by its length and return the value but not change the vector

	Vector2 Result = Vector2(0.0f, 0.0f);

	Result = *this / std::max(Length(),1.0f);

	return Result;

}

Vector2 Vector2::Zero()
{
	//returning a 0.0f vector
	return Vector2(0, 0);
}