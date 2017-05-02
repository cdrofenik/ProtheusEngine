#ifndef BROAD_SEARCH_H
#define BROAD_SEARCH_H

#include "physics\collision\collisionshapes\BoundingVolumes.h"
#include "physics\collision\PairManager.h"

namespace physics {

	class IBroadPhase {

	public:
		virtual void insert(const Aabb& volume, const int& bodyIdx) = 0;
		virtual void update(const AabbUpdateData& volumeData, const int& bodyIdx) = 0;
		virtual bool remove(const Aabb& volume, const int& bodyIdx) = 0;
		virtual void getPotentialContacts(PairManager* _pairManager) = 0;
	};
}

#endif