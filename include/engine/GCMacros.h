#pragma once

#define GC_REFERENCES_BEGIN() \
	void AddReferencedObjects(GCManager& gcm) override {


#define GC_REFERENCES_ADD(NAME) \
	gcm.MarkObject(NAME);

#define GC_REFERENCES_END() \
	}