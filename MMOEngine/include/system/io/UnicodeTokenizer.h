/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef UNICODETOKENIZER_H_
#define UNICODETOKENIZER_H_

#include "../platform.h"

#include "../lang/Exception.h"

#include "../lang/UnicodeString.h"

#include "../lang/StringBuffer.h"

namespace sys {
  namespace io {

	class UnicodeTokenizer {
		UnicodeString str;

		int index;
		UnicodeString delimeter;

	public:
		UnicodeTokenizer(const UnicodeString& u);
		UnicodeTokenizer(const String& s);
		UnicodeTokenizer(const char* ascii);
		UnicodeTokenizer(const char* ascii, int len);

		int getIntToken();
		uint32 getHexIntToken();
		uint64 getLongToken();
		float getFloatToken();

		void getStringToken(String& token);
		void getStringToken(StringBuffer& token);
		void getUnicodeToken(UnicodeString& token);

		void finalToken(String& s);
		void finalToken(UnicodeString& u);

		void shiftTokens(int count);

		bool hasMoreTokens() const;

		inline void setDelimeter(const String& del) {
			delimeter = del;
		}

		inline void setDelimiter(const UnicodeString& del) {
			delimeter = del;
		}

		inline void setDelimiter(const char* ascii) {
			delimeter = ascii;
		}
	private:
		void nextToken(UnicodeString& s);

	};

  } // namespace io
} // namespace sys

using namespace sys::io;


#endif /* UNICODETOKENIZER_H_ */
