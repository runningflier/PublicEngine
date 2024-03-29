/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef LOOKUPOBJECTMESSAGE_H_
#define LOOKUPOBJECTMESSAGE_H_

#include "system/lang.h"

#include "engine/orb/DistributedObjectBroker.h"

#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class LookUpObjectMessage : public DOBMessage {
		String name;

		bool found;
		String className;
		uint64 objectID;

	public:	
		LookUpObjectMessage(const String& name) : DOBMessage(LOOKUPOBJECTMESSAGE, 40) {
			insertAscii(name);
		}

		LookUpObjectMessage(Packet* message) : DOBMessage(message) {
			message->parseAscii(name);
		}

		void execute() {
			DistributedObject* obj = DistributedObjectBroker::instance()->lookUp(name);

			if (obj != NULL) {
				insertBoolean(true);
				insertAscii(obj->_getClassName());
				insertLong(obj->_getObjectID());
			} else {
				insertBoolean(false);
			}

			client->sendReply(this);
		}

		void handleReply(Packet* message) {
			found = message->parseBoolean();

			if (found) {
				message->parseAscii(className);
				objectID = message->parseLong();
			}
		}

		bool isFound() {
			return found;
		}

		const String& getClassName() {
			return className;
		}

		uint64 getObjectID() {
			return objectID;
		}
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;

#endif /*LOOKUPOBJECTMESSAGE_H_*/
