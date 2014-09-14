/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef LUAOBJECT_H_
#define LUAOBJECT_H_

#include "Lua.h"

namespace engine {
namespace lua {

	class LuaObject {
		lua_State* L;

		String objectName;

	public:
		LuaObject(lua_State* lState, const String& name) {
			L = lState;
			objectName = name;
		}

		LuaObject(lua_State* lState) {
			L = lState;
		}

		virtual ~LuaObject() {

		}

		virtual String getStringField(const String& key);
		virtual sys::uint32 getIntField(const String& key);
		virtual sys::uint16 getShortField(const String& key);
		virtual sys::uint8 getByteField(const String& key);
		virtual float getFloatField(const String& key);
		virtual uint64 getLongField(const String& key);
		virtual LuaObject getObjectField(const String& key);
		virtual bool getBooleanField(const String& key);

		virtual void setField(const String& key, sys::uint64 value);
		virtual void setField(const String& key, const String& value);

		virtual String getStringAt(int idx);
		virtual sys::uint32 getIntAt(int idx);
		virtual float getFloatAt(int idx);
		virtual LuaObject getObjectAt(int idx);
		virtual sys::uint64 getLongAt(int idx);
		virtual bool getBooleanAt(int idx);


		virtual int getTableSize();

		virtual bool isValidTable();

		virtual void pop();

		inline lua_State* getLuaState() {
			return L;
		}

		inline void operator=(lua_State* lState) {
			L = lState;
		}

	};
}
}


#endif /* LUAOBJECT_H_ */
