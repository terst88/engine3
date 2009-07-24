/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "system/lang.h"

#include "ServiceClient.h"

#include "engine/orb/object/DistributedObject.h"

namespace engine {
  namespace service {

	class Message : public Packet, public DistributedObject {
	protected:
		ReferenceSlot<ServiceClient*> client;
	
		uint64 timestampMili;
		
	public:
		Message() : Packet(), DistributedObject() {
			client = NULL;
		}
	
		Message(int size) : Packet(size), DistributedObject() {
			client = NULL;
		}
	
		virtual ~Message() {
		}
		
		int compareTo(Message* m) {
			uint64 t1 = timestampMili;
			uint64 t2 = m->timestampMili;
			
			if (t1 < t2)
				return 1;
			else if (t1 > t2)
				return -1;
			else
				return 0; 
		}
	
		Message* clone(int startoffs = 0) {
			Message* pack = new Message();
			copy(pack, startoffs);
			
			return pack;
		}
	
		// setters and getters
		inline void setClient(ServiceClient* c) {
			client = c;
		}
	
		inline void setTimeStampMili(uint64 ts) {
			timestampMili = ts;
		}
	
		inline uint64 getTimeStampMili() {
			return timestampMili;
		}
	
		inline ServiceClient* getClient() {
			return client;
		}
	};

  } // namespace service
} // namespace engine

using namespace engine::service;

#endif /*MESSAGE_H_*/
