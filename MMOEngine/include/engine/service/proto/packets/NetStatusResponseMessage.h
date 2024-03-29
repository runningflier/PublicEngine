/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef NETSTATUSRESPONSEMESSAGE_H_
#define NETSTATUSRESPONSEMESSAGE_H_

#include "../BaseProtocol.h"

namespace engine {
  namespace service {
    namespace proto {

	class NetStatusResponseMessage : public BasePacket {
	public:
		NetStatusResponseMessage(sys::uint16 tick) : BasePacket(40) {
			insertShort(0x0800);
			insertShort(tick);
			
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			insertInt(0x00000000);
			
			
		    setSequencing(false);
			setCompression(true);
			setCRCChecking(false);
		}
	
		inline static sys::uint16 parseTick(Packet* pack) {
			return pack->parseShort(2);
		}
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;

#endif /*NETSTATUSRESPONSEMESSAGE_H_*/
