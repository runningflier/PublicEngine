/*
 * Matrix4.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Vector4.h"
#include "system/lang/Object.h"

namespace engine {
 namespace util {
  namespace u3d {

 class Matrix3;

 class Matrix4 : public Object {
	 Vector4 matrix[4];

 public:
	 Matrix4() {
		 identity();
	 }

	 Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);

	 Matrix4(const Matrix4& mat);

	 Matrix4& operator=(const Matrix4& op);

	 void identity();

	 inline Vector4& operator [] (uint32 index) {
		 if (index > 3)
			 throw ArrayIndexOutOfBoundsException(index);

		 return matrix[index];
	 }

	 inline Vector4 operator [] (uint32 index) const {
		 if (index > 3)
			 throw ArrayIndexOutOfBoundsException(index);

		 return matrix[index];
	 }

	 inline void setTranslation(float x, float y, float z) {
		 matrix[3][0] = x;
		 matrix[3][1] = y;
		 matrix[3][2] = z;
		 matrix[3][3] = 1.f;
	 }

	 void setRotationMatrix(const Matrix3& rot);

	 Matrix4 operator*(const Matrix4& mat) const;

 };

  } // u3d
 } // util
} // engine

using namespace engine::util::u3d;

#endif /* MATRIX4_H_ */
