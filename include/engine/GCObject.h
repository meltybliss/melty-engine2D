#pragma once

class GCManager;

class GCObject {
public:

	virtual ~GCObject() = default;

	GCObject* GetOwner() const {
		return owner;
	}

	void SetOwner(GCObject* owner) {
		this->owner = owner;
	}

	virtual void AddReferencedObjects(GCManager& gcm) {};

	virtual void DestroyObject(GCObject*& object) {
		if (object) {
			object = nullptr;
		}
	}

private:
	GCObject* owner = nullptr;
};