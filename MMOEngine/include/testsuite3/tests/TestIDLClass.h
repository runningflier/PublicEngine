/*
 *	testsuite3/tests/TestIDLClass.h generated by engine3 IDL compiler 0.60
 */

#ifndef TESTIDLCLASS_H_
#define TESTIDLCLASS_H_

#include "engine/core/Core.h"

#include "engine/core/ManagedReference.h"

#include "engine/core/ManagedWeakReference.h"

#include "engine/core/ManagedObject.h"

namespace testsuite3 {
namespace tests {

class TestIDLClass : public ManagedObject {
public:
	TestIDLClass(int val);

	int getValue();

	void setValue(int val);

	DistributedObjectServant* _getImplementation();
	DistributedObjectServant* _getImplementationForRead();

	void _setImplementation(DistributedObjectServant* servant);

protected:
	TestIDLClass(DummyConstructorParameter* param);

	virtual ~TestIDLClass();

	friend class TestIDLClassHelper;
};

} // namespace tests
} // namespace testsuite3

using namespace testsuite3::tests;

namespace testsuite3 {
namespace tests {

class TestIDLClassImplementation : public ManagedObjectImplementation {
	int value;

public:
	TestIDLClassImplementation(int val);

	TestIDLClassImplementation(DummyConstructorParameter* param);

	int getValue();

	void setValue(int val);

	WeakReference<TestIDLClass*> _this;

	operator const TestIDLClass*();

	DistributedObjectStub* _getStub();
	virtual void readObject(ObjectInputStream* stream);
	virtual void writeObject(ObjectOutputStream* stream);
protected:
	virtual ~TestIDLClassImplementation();

	void finalize();

	void _initializeImplementation();

	void _setStub(DistributedObjectStub* stub);

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void _serializationHelperMethod();
	bool readObjectMember(ObjectInputStream* stream, const uint32& nameHashCode);
	int writeObjectMembers(ObjectOutputStream* stream);

	friend class TestIDLClass;
};

class TestIDLClassAdapter : public ManagedObjectAdapter {
public:
	TestIDLClassAdapter(TestIDLClass* impl);

	void invokeMethod(sys::uint32 methid, DistributedMethod* method);

	int getValue();

	void setValue(int val);

};

class TestIDLClassHelper : public DistributedObjectClassHelper, public Singleton<TestIDLClassHelper> {
	static TestIDLClassHelper* staticInitializer;

public:
	TestIDLClassHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectServant* instantiateServant();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class Singleton<TestIDLClassHelper>;
};

} // namespace tests
} // namespace testsuite3

using namespace testsuite3::tests;

#endif /*TESTIDLCLASS_H_*/
