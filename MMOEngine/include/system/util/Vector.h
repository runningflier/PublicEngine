/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include "system/lang/Object.h"

#include "ArrayList.h"

namespace sys {
 namespace util {

   template<class E> class SynchronizedVector;
   template<class E> class SynchronizedSortedVector;

   template<class E> class Vector : public ArrayList<E>, public Object {
   public:
       Vector();
       Vector(int incr);
       Vector(int initsize, int incr);
       Vector(const Vector<E>& vector);

       Vector<E>& operator=(const Vector<E>& vector);

       virtual ~Vector();

       void clone(Vector<E>& vector) const ;

       bool toBinaryStream(ObjectOutputStream* stream);

       bool parseFromBinaryStream(ObjectInputStream* stream);

       bool operator==(const Vector<E>& v) const;

       Object* clone();

       static int getObjectData(const String& str, String& obj);

       friend class SynchronizedVector<E>;
       friend class SynchronizedSortedVector<E>;

   };

   template<class E> Vector<E>::Vector() : ArrayList<E>() {
   }

   template<class E> Vector<E>::Vector(int incr) : ArrayList<E>(10, incr) {
   }

   template<class E> Vector<E>::Vector(int initsize, int incr) : ArrayList<E>(initsize, incr) {
   }

   template<class E> Vector<E>::Vector(const Vector<E>& vector) : ArrayList<E>(vector), Object() {
   }

   template<class E> Vector<E>& Vector<E>::operator=(const Vector<E>& vector) {
	   if (this == &vector)
		   return *this;

	   ArrayList<E>::operator=(vector);

	   return *this;
   }

   template<class E> Vector<E>::~Vector() {
   }

   template<class E> void Vector<E>::clone(Vector<E>& array) const {
	   ArrayList<E>::clone(array);
   }

   template<class E> bool Vector<E>::toBinaryStream(ObjectOutputStream* stream) {
	   int size = Vector<E>::size();

	   Integer::toBinaryStream(size, stream);

	   for (int i = 0; i < Vector<E>::size(); ++i) {
		   E* obj = &Vector<E>::get(i);

		   TypeInfo<E>::toBinaryStream(obj, stream);
	   }

	   return true;
   }

   template<class E> bool Vector<E>::parseFromBinaryStream(ObjectInputStream* stream) {
	   Vector<E>::removeAll();

	   int size;

	   Integer::parseFromBinaryStream(size, stream);

	   for (int i = 0; i < size; ++i) {
		   E object;

		   if (TypeInfo<E>::parseFromBinaryStream(&object, stream))
			   ArrayList<E>::add(object);
	   }

	   return true;
   }

   template<class E> Object* Vector<E>::clone() {
	   return new Vector<E>(*this);
   }

   template<class E>  bool Vector<E>::operator==(const Vector<E>& v) const {
	   if (this == &v)
		   return true;

	   return false;
   }

   template<class E> int Vector<E>::getObjectData(const String& str, String& obj) {
	   int opening = str.indexOf("{");

	   if (opening == -1)
		   return 0;

	   int i, subObjects = 0;
	   bool subString = false;


	   for (i = opening + 1; i < str.length(); ++i) {
		   char openingCharacter = str.charAt(i);

		   if (subString && openingCharacter == '\\') {
			   ++i;
			   continue;
		   }

		   if (openingCharacter == '"') {
			   subString = !subString;
			   continue;
		   }

		   if (!subString) {
			   if (openingCharacter == '{') {
				   ++subObjects;
			   } else if (openingCharacter == '}') {
				   --subObjects;
			   }
		   }

		   if (subObjects < 0) {
			   break;
		   }
	   }

	   if (subObjects < 0) {
		   obj = str.subString(opening, i + 1);

		   //System::out << obj << "\n";

		   return i + 1;
	   } else
		  // System::out << "WARNING expecting \"}\" in " << str << " at " << i;

	   return 0;
   }

  } // namespace util
} // namespace sys

using namespace sys::util;

#endif /*VECTOR_H_*/
