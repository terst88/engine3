/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include "DatagramServiceThread.h"

#ifdef VERSION_PUBLIC
#include "proto/events/BaseClientCleanUpEvent.hpp"
#endif

#include "../db/ObjectDatabaseManager.h"

DatagramServiceThread::DatagramServiceThread() : ServiceMessageHandlerThread("") {
	setLogging(false);
}

DatagramServiceThread::DatagramServiceThread(const String& s) : ServiceMessageHandlerThread(s) {
	setLogging(false);
}

DatagramServiceThread::~DatagramServiceThread() {
}

void DatagramServiceThread::start(int p, int mconn) {
	port = p;

	clients = new ServiceClientMap(mconn);

	if (serviceHandler == NULL)
		throw ServiceException("no service handler assigned");

	try {
		SocketAddress addr(port);
		socket = new UDPServerSocket(&addr);

		socket->setBlocking(true);
	} catch (SocketException& e) {
		socket = NULL;

		StringBuffer msg;
		msg << "unable to connect to socket on port " << port;
		error(msg);

		throw ServiceException(e.getMessage());
	}

	serviceHandler->initialize();

	ServiceThread::start();

	StringBuffer msg;
	msg << "started on port " << port;
	info(msg, true);
}

void DatagramServiceThread::stop() {
	if (socket != NULL) {
		ServiceThread::stop();

		socket->close();

		removeConnections();

		info("stopped", true);
	}
}

void DatagramServiceThread::run() {
	receiveMessages();
}

void DatagramServiceThread::receiveMessages() {
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	Packet packet;

	#ifdef VERSION_PUBLIC
		int time = (3600 + System::random(100)) * 1000;
		taskManager->scheduleTask(new BaseClientCleanUpEvent(this), time);
	#endif

	while (doRun) {
		ServiceClient* client = NULL;

		try	{
			SocketAddress addr;

			if (!socket->recieveFrom(&packet, &addr))
				continue;

			uint64 netid = addr.getNetworkID();

			lock();

			ObjectDatabaseManager::instance()->startLocalTransaction();

			client = clients->get(netid);

			if (client == NULL)	{
				if ((client = serviceHandler->createConnection(socket, addr)) == NULL) {
					ObjectDatabaseManager::instance()->commitLocalTransaction();
					unlock();
					continue;
				}

				clients->add(client);

				#ifdef VERSION_PUBLIC
					if (clients->size() > CONNECTION_LIMIT) {
						ObjectDatabaseManager::instance()->commitLocalTransaction();
						unlock();
						return;
					}
				#endif
			}

			unlock();

			if (client->isAvailable()) {
				serviceHandler->handleMessage(client, &packet);
			}

			ObjectDatabaseManager::instance()->commitLocalTransaction();

		} catch (SocketException& e) {
			ObjectDatabaseManager::instance()->commitLocalTransaction();

			if (client == NULL) {
				info(e.getMessage());
			} else if (!serviceHandler->handleError(client, e))
				return;
		} catch (...) {
			ObjectDatabaseManager::instance()->commitLocalTransaction();

			error("unreported Exception caught");

			#ifdef VERSION_PUBLIC
				return;
			#endif
		}


	}
}
