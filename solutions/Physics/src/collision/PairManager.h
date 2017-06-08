#ifndef PAIRMANAGER_H
#define PAIRMANAGER_H

#include "core\collections\AlignedArray.hpp"
#include "narrowphase\CollisionAlgorithm.h"

namespace physics {

	struct PotentialPair {
		/*!
		Holds the bodies that might be in contact
		*/
		int bodyIdA = -1;
		int bodyIdB = -1;
	};

	class PairManager
	{
	public:
		PairManager::PairManager() {}

		PairManager::~PairManager()
		{
			m_potentialPairs.clear();
		}

		void PairManager::addPair(const int& indexA, const int& indexB)
		{
			PotentialPair pair;
			pair.bodyIdA = indexA;
			pair.bodyIdB =  indexB;
			m_potentialPairs.push_back(pair);
		}

		void PairManager::removePair(const int& indexA, const int& indexB)
		{
			for (int i = 0; i < m_potentialPairs.size(); i++)
			{
				auto currentPair = m_potentialPairs.at(i);
				if ((currentPair.bodyIdA ==  indexA && currentPair.bodyIdB ==  indexB) ||
					(currentPair.bodyIdA ==  indexB && currentPair.bodyIdB == indexA))
				{
					m_potentialPairs.removeAt(i);
				}
			}
		}

		collections::AlignedArray<PotentialPair> getPotentialPairs() {
			return m_potentialPairs;
		}

		void PairManager::addCollisionPairInfo(const CollisionInfo& info)
		{
			m_collidingPairInfos.push_back(info);
		}

		void PairManager::removeCollisionPairInfo(const CollisionInfo& info)
		{
			//TODO
		}

		collections::AlignedArray<CollisionInfo> getCollidingPairInfos() {
			return m_collidingPairInfos;
		}

	private:
		collections::AlignedArray<PotentialPair> m_potentialPairs = collections::AlignedArray<PotentialPair>();
		collections::AlignedArray<CollisionInfo> m_collidingPairInfos = collections::AlignedArray<CollisionInfo>();
	};
}
#endif