#ifndef DBVT_H
#define DBVT_H

#include "core\collections\AlignedArray.hpp"

#include "physics\collision\broadphase\IBroadPhase.hpp"

namespace physics {

	struct DbvtNode
	{
		DbvtNode* parent;
		Aabb volume;

		union {
			DbvtNode* children[2];
			int bodyIdx;
		};

		bool isLeaf() const { return (children[1] == 0); }
		bool isInternal() const { return (!isLeaf()); }
	};

	class Dbvt : public IBroadPhase
	{
	public:
		Dbvt();
		~Dbvt();

		virtual void insert(const Aabb& volume, const int& bodyIdx);
		virtual void update(const AabbUpdateData& volumeData, const int& bodyIdx);
		virtual bool remove(const Aabb& volume, const int& bodyIdx);
		virtual void getPotentialContacts(PairManager* pairManager);

		void DebugPrintTree();

		DbvtNode* m_root;
		int m_leaves;

	private:
		void Dbvt::clean();
	};

}

#endif