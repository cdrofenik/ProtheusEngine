#ifndef SORTANDPRUNE_H
#define SORTANDPRUNE_H

#include "core\collections\AlignedArray.hpp"

#include "IBroadPhase.hpp"

namespace physics
{
	struct SweepObject
	{
		int min[3];
		int max[3];
		int bodyIdx;
	};

	struct EndPoint
	{
		unsigned int value;
		int soIndex;
		bool isMax;
	};

	class SweepAndPrune : public IBroadPhase
	{
	public:
		SweepAndPrune(PairManager* _pairManager);
		~SweepAndPrune();

		virtual void insert(const Aabb& volume, const int& bodyIdx);
		virtual void update(const AabbUpdateData& volumeData, const int& bodyIdx);
		virtual bool remove(const Aabb& volume, const int& bodyIdx);
		virtual void getPotentialContacts(PairManager* _pairManager) {}

	private:
		int m_sObjectCounter;
		int m_ePointCounter;
		EndPoint* m_endPoints[3];
		collections::AlignedArray<SweepObject> m_sObjects;
		PairManager* ref_pairManager;

		unsigned int quantize(const math::Real& value);
		bool isColliding(const int& axis1, const SweepObject& so1,
			const int& axis2, const SweepObject& so2);
		void checkIfColliding(const int& axis, const SweepObject& activeSo,
			const SweepObject& so, const bool& adding, bool _updateOverlaps);
		void printEndPoints(int axis, int limit);
		void sortMin(const int& axis, const int& startIndex,
			const bool& updateOverlaps, const bool& ascending);
		void sortMax(const int& axis, const int& startIndex,
			const bool& updateOverlaps, const bool& ascending);
	};
}
#endif