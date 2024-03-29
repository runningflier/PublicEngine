/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "../platform.h"

#include "String.h"

#include "StackTrace.h"

namespace sys {
  namespace lang {

	class Exception {
	protected:
		String message;

		StackTrace trace;

	public:
		Exception();
		Exception(const String& msg);

		virtual ~Exception();

		void printStackTrace() const;

		// setters and getters
		inline void setMessage(const String& msg) {
			message = msg;
		}

	 	inline const String& getMessage() const {
			return message;
		}

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*EXCEPTION_H_*/
