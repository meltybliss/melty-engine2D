#pragma once

class GCManager;

class GCObject {
public:

	virtual void AddReferencedObjects(GCManager& gcm) {};

	bool IsPendingKill() const {
		return isPendingKill;
	}

	void MarkPendingKill() {
		isPendingKill = true;
	}

private:
	bool isPendingKill = false;
};