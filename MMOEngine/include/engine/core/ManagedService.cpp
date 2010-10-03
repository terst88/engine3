/*
 *	engine/core/ManagedService.cpp generated by engine3 IDL compiler 0.60
 */

#include "ManagedService.h"


// Imported class dependencies

#include "engine/core/ObjectUpdateToDatabaseTask.h"

/*
 *	ManagedServiceStub
 */

ManagedService::ManagedService(DummyConstructorParameter* param) : ManagedObject(param) {
}

ManagedService::~ManagedService() {
}


DistributedObjectServant* ManagedService::_getImplementation() {
	return getForUpdate();}

void ManagedService::_setImplementation(DistributedObjectServant* servant) {
	setObject((ManagedObjectImplementation*) servant);}

/*
 *	ManagedServiceImplementation
 */

ManagedServiceImplementation::ManagedServiceImplementation() : ManagedObjectImplementation() {
	_initializeImplementation();
}

ManagedServiceImplementation::ManagedServiceImplementation(DummyConstructorParameter* param) : ManagedObjectImplementation(param) {
	_initializeImplementation();
}


ManagedServiceImplementation::~ManagedServiceImplementation() {
}


void ManagedServiceImplementation::finalize() {
}

void ManagedServiceImplementation::_initializeImplementation() {
	_setClassHelper(ManagedServiceHelper::instance());

	_serializationHelperMethod();
}

void ManagedServiceImplementation::_setStub(DistributedObjectStub* stub) {
	_this = (ManagedService*) stub;
	ManagedObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ManagedServiceImplementation::_getStub() {
	return _this;
}

ManagedServiceImplementation::operator const ManagedService*() {
	return _this;
}

TransactionalObject* ManagedServiceImplementation::clone() {
	return (TransactionalObject*) new ManagedServiceImplementation(*this);
}


void ManagedServiceImplementation::lock(bool doLock) {
}

void ManagedServiceImplementation::lock(ManagedObject* obj) {
}

void ManagedServiceImplementation::rlock(bool doLock) {
}

void ManagedServiceImplementation::wlock(bool doLock) {
}

void ManagedServiceImplementation::wlock(ManagedObject* obj) {
}

void ManagedServiceImplementation::unlock(bool doLock) {
}

void ManagedServiceImplementation::runlock(bool doLock) {
}

void ManagedServiceImplementation::_serializationHelperMethod() {
	ManagedObjectImplementation::_serializationHelperMethod();

	_setClassName("ManagedService");

}

/*
 *	ManagedServiceAdapter
 */

ManagedServiceAdapter::ManagedServiceAdapter(ManagedServiceImplementation* obj) : ManagedObjectAdapter(obj) {
}

Packet* ManagedServiceAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	default:
		return NULL;
	}

	return resp;
}

/*
 *	ManagedServiceHelper
 */

ManagedServiceHelper* ManagedServiceHelper::staticInitializer = ManagedServiceHelper::instance();

ManagedServiceHelper::ManagedServiceHelper() {
	className = "ManagedService";

	DistributedObjectBroker::instance()->registerClass(className, this);
}

void ManagedServiceHelper::finalizeHelper() {
	ManagedServiceHelper::finalize();
}

DistributedObject* ManagedServiceHelper::instantiateObject() {
	return new ManagedService(DummyConstructorParameter::instance());
}

DistributedObjectServant* ManagedServiceHelper::instantiateServant() {
	return new ManagedServiceImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ManagedServiceHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ManagedServiceAdapter((ManagedServiceImplementation*) obj->_getImplementation());

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

