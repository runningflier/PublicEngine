/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "system/io/Serializable.h"
#include "system/lang/Math.h"
#include "system/lang/DivisionByZeroException.h"

#include "Matrix4.h"

namespace engine {
  namespace util {
  	namespace u3d {

	class Vector3 : public Variable {
	protected:
		float x, y, z;

	public:
		static const Vector3 ZERO;

		//Axis Representations
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;

	public:
		inline Vector3() {
			x = 0;
			y = 0;
			z = 0;

			//addSerializableVariables();
		}

		Vector3(const Vector3& vec) : Variable() {
			x = vec.x;
			y = vec.y;
			z = vec.z;

			//addSerializableVariables();
		}

		inline Vector3(const float fx, const float fy, const float fz) {
			x = fx;
			y = fy;
			z = fz;

			//addSerializableVariables();
		}

		/**
		 * Converts a 3 dimensional float array into a Vector3.
		 */
		inline explicit Vector3(const float coord[3]) {
			x = coord[0];
			y = coord[1];
			z = coord[2];

			//addSerializableVariables();
		}

		/**
		 * Converts a 3 dimensional int array into a Vector3.
		 */
		inline explicit Vector3(const int coord[3]) {
			x = (float) coord[0];
			y = (float) coord[1];
			z = (float) coord[2];

			//addSerializableVariables();
		}

		/**
		 * Converts a float scalar to a Vector3.
		 */
		inline explicit Vector3(const float scalar) {
			x = scalar;
			y = scalar;
			z = scalar;;

			//addSerializableVariables();
		}

		virtual ~Vector3() {
		}

		/*inline void addSerializableVariables() {
			addSerializableVariable("x", &x);
			addSerializableVariable("y", &y);
			addSerializableVariable("z", &z);
		}*/

	public:

		bool toBinaryStream(ObjectOutputStream* stream) {
			stream->writeFloat(x);
			stream->writeFloat(z);
			stream->writeFloat(y);

			return true;
		}

		bool parseFromBinaryStream(ObjectInputStream* stream) {
			x = stream->readFloat();
			z = stream->readFloat();
			y = stream->readFloat();

			return true;
		}

		/**
		 * Returns the exact length of the vector. Should be used sparingly as it
		 * uses much CPU power. Use squaredLength for comparing lengths.
		 */
		inline float length() const {
			return Math::sqrt(x * x + y * y + z * z);
		}

		/**
		 * Returns the length before being squared. Good for comparing lengths.
		 */
		inline float squaredLength() const {
			return (x * x + y * y + z * z);
		}

		/**
		 * Returns the real distance to another vector. Should not be used for comparisons.
		 * See squaredDistanceTo(.
		 * \param v The vector to get the distance to.
		 * \return Returns the float representation of the distance between the two vectors.
		 */
		inline float distanceTo(const Vector3& v) const {
			return (*this - v).length();
		}

		/**
		 * Good for comparisons of distance. Saves the cpu usage needed for sqrt.
		 * \param v The vector to get the distance to.
		 * \return Returns the float representation of the distance between two points prior to application of a square root.
		 */
		inline float squaredDistanceTo(const Vector3& v) const {
			return (*this - v).squaredLength();
		}

		/**
		 * This method returns the midpoint between this vector and another vector.
		 * \param v The vector to find a midpoint in conjunction with.
		 * \return Returns a vector half way in between this vector and the passed in vector.
		 */
		inline Vector3 midPoint(const Vector3& v) const {
			return Vector3((x + v.x) * 0.5f, (y + v.y) * 0.5f, (z + v.z) * 0.5f);
		}

		/**
		 * This method is used to calculate the angle between two vectors. If both
		 * are unit vectors then the product is the cosine of the angle; otherwise,
		 * the dot product must be divided by the product of the length
		 */
		inline float dotProduct(const Vector3& v) const {
			return (x * v.x + y * v.y + z * v.z);
		}

		inline float product() {
			return dotProduct(Vector3(x, y, z));
		}

		/**
		 * The cross product returns the vector which is perpendicular to this vector
		 * and the vector passed in. For example, if you have two vectors in the same
		 * geometric plane, then the vector would be on the plane perpendicular to that
		 * plane, and the vector perpendicular to the two vectors. Imagine a 3D o
		 */
		inline Vector3 crossProduct(const Vector3& v) const {
			return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		/**
		 * Returns the string representation of the vector in (x, y, z) format.
		 */
		inline String toString() {
			StringBuffer sb;
			sb <<"(x:" << x << ", y:" << y << ", z:" << z << ")";
			return sb.toString();
		}

		inline float operator [] (uint32 index) const {
			if (index > 2)
				throw ArrayIndexOutOfBoundsException(index);

			return *(&x+index);
		}

		inline float& operator [] (uint32 index) {
			if (index > 2)
				throw ArrayIndexOutOfBoundsException(index);

			return *(&x+index);
		}

		inline Vector3& operator = (const Vector3& v) {
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		inline Vector3& operator = (const float scalar) {
			x = scalar;
			y = scalar;
			z = scalar;

			return *this;
		}

		inline Vector3 operator + (const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		inline Vector3 operator - (const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		inline Vector3 operator * (const Vector3& v) const {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		Vector3 operator*(const Matrix4& mat) const {
			return Vector3(x * mat[0][0] + y * mat[1][0] + z * mat[2][0] + mat[3][0],
					x * mat[0][1] + y * mat[1][1] + z * mat[2][1] + mat[3][1],
					x * mat[0][2] + y * mat[1][2] + z * mat[2][2] + mat[3][2]);
		}

		inline Vector3 operator / (const Vector3& v) const {
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		inline Vector3& operator += (const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		inline Vector3& operator -= (const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		inline Vector3& operator *= (const Vector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		inline Vector3& operator /= (const Vector3& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		inline friend Vector3 operator + (const Vector3& v, const float scalar) {
			return Vector3(v.x + scalar, v.y + scalar, v.z + scalar);
		}

		inline friend Vector3 operator + (const float scalar, const Vector3& v) {
			return Vector3(scalar + v.x, scalar + v.y, scalar + v.z);
		}

		inline friend Vector3 operator - (const Vector3& v, const float scalar) {
			return Vector3(v.x - scalar, v.y - scalar, v.z - scalar);
		}

		inline friend Vector3 operator - (const float scalar, const Vector3& v) {
			return Vector3(scalar - v.x, scalar - v.y, scalar - v.z);
		}

		inline friend Vector3 operator * (const Vector3& v, const float scalar) {
			return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
		}

		inline friend Vector3 operator * (const float scalar, const Vector3& v) {
			return Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
		}

		inline friend Vector3 operator / (const Vector3& v, const float scalar) {
			if (scalar == 0.0f)
				throw DivisionByZeroException();

			return Vector3(v.x / scalar, v.y / scalar, v.z / scalar);
		}

		inline friend Vector3 operator / (const float scalar, const Vector3& v) {
			return Vector3(scalar / v.x, scalar / v.y, scalar / v.z);
		}

		//Boolean operators
		inline bool operator == (const Vector3& v) const {
			return (x == v.x && y == v.y && z == v.z);
		}

		inline bool operator != (const Vector3& v) const {
			return (x != v.x || y != v.y || z != v.z);
		}

		inline bool operator < (const Vector3& v) const {
			if (x < v.x && y < v.y && z < v.z)
				return true;

			return false;
		}

		inline bool operator > (const Vector3& v) const {
			if (x > v.x && y > v.y && z > v.z)
				return true;

			return false;
		}

		Vector3 getMin(const Vector3& vec) const {
			Vector3 minVector;

			if (x < vec.x)
				minVector.setX(x);
			else
				minVector.setX(vec.x);

			if (y < vec.y)
				minVector.setY(y);
			else
				minVector.setY(vec.y);

			if (z < vec.z)
				minVector.setZ(z);
			else
				minVector.setZ(vec.z);

			return minVector;
		}

		inline Vector3 getMax(const Vector3& vec) const {
			Vector3 maxVector;

			if (x > vec.x)
				maxVector.setX(x);
			else
				maxVector.setX(vec.x);

			if (y > vec.y)
				maxVector.setY(y);
			else
				maxVector.setY(vec.y);

			if (z > vec.z)
				maxVector.setZ(z);
			else
				maxVector.setZ(vec.z);

			return maxVector;
		}

		inline float normalize() {
			float magnitude = length();

			x /= magnitude;
			y /= magnitude;
			z /= magnitude;

			return magnitude;
		}

		//Getters
		inline float getX() const {
			return x;
		}

		inline float getY() const {
			return y;
		}

		inline float getZ() const {
			return z;
		}

		//Setters
		inline void setX(float xv) {
			x = xv;
		}

		inline void setY(float yv) {
			y = yv;
		}

		inline void setZ(float zv) {
			z = zv;
		}

		inline void set(float x, float z, float y) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		friend class Quaternion;
	};

  	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;

#endif /* VECTOR3_H_ */
