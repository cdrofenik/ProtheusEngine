#include "physics\collision\broadphase\Dbvt.h"

// system dependency
#include <iostream>

namespace physics {


	static int indexOf(const DbvtNode* node)
	{
		return (node->parent->children[1] == node);
	}

	static int selectLeaf(const Aabb& volume, const Aabb& leafVol1, const Aabb& leafVol2)
	{
		return npProximityAabbAabb(leafVol1, volume) < npProximityAabbAabb(leafVol2, volume) ? 0 : 1;
	}

	static DbvtNode* createNode(DbvtNode* parent, const Aabb& volume, const int& bodyIdx)
	{
		DbvtNode* node = new DbvtNode();
		node->parent = parent;
		node->volume = volume;
		node->bodyIdx = bodyIdx;
		node->children[1] = 0;
		return (node);
	}

	static DbvtNode* createInternalNode(DbvtNode* parent,
		const Aabb& volume1,
		const Aabb& volume2,
		const int& bodyIdx)
	{
		DbvtNode* node = createNode(parent, volume1, bodyIdx);
		npMergeAabbAabb(volume1, volume2, node->volume);
		return node;
	}

	static void insertLeaf(Dbvt* pdbvt, DbvtNode* root, DbvtNode* leaf)
	{
		//Is tree root set
		if (!pdbvt->m_root) {
			pdbvt->m_root = leaf;
			leaf->parent = 0;
		}
		else
		{
			//is root an internal node
			if (!root->isLeaf())
			{
				do {
					root = root->children[selectLeaf(leaf->volume,
						root->children[0]->volume,
						root->children[1]->volume)];
				} while (!root->isLeaf());
			}
			DbvtNode* previous = root->parent;
			DbvtNode* newInternalNode = createInternalNode(previous,
				leaf->volume, root->volume, 0);

			//does parent exist
			if (previous) {
				previous->children[indexOf(root)] = newInternalNode;
				newInternalNode->children[0] = root;
				root->parent = newInternalNode;
				newInternalNode->children[1] = leaf;
				leaf->parent = newInternalNode;
				do {
					if (!previous->volume.contains(newInternalNode->volume))
						npMergeAabbAabb(previous->children[0]->volume, previous->children[1]->volume, previous->volume);
					else
						break;

					newInternalNode = previous;
				} while (0 != (previous = newInternalNode->parent));
			}
			else{
				newInternalNode->children[0] = root;
				root->parent = newInternalNode;
				newInternalNode->children[1] = leaf;
				leaf->parent = newInternalNode;
				pdbvt->m_root = newInternalNode;
			}
		}
	}

	static void recursivlyDeleteNode(DbvtNode* node)
	{
		if (node->isInternal()) {
			recursivlyDeleteNode(node->children[0]);
			recursivlyDeleteNode(node->children[1]);
		}
		else {
			delete node;
		}
	}

	static bool removeNode(Dbvt* pdbvt, DbvtNode* node, const Aabb& volume, const int& id)
	{
		DbvtNode* currentNode = node;
		int childIndex = -1;

		do {
			childIndex = selectLeaf(volume,
				currentNode->children[0]->volume,
				currentNode->children[1]->volume);
			currentNode = currentNode->children[childIndex];
		} while (!currentNode->isLeaf());
		
		if (currentNode->bodyIdx == id) {
			DbvtNode* parent = currentNode->parent;
			auto vol = parent->children[!childIndex]->volume;
			auto idx = parent->children[!childIndex]->bodyIdx;
			parent->volume = parent->children[!childIndex]->volume;
			parent->bodyIdx = parent->children[!childIndex]->bodyIdx;
			parent->children[0] = parent->children[!childIndex]->children[0];
			parent->children[1] = parent->children[!childIndex]->children[1];

			return true;
		}
		else {
			return false;
		}
	}
	
	static void printLeafOrNode(DbvtNode* node)
	{
		if (node->isLeaf()) {
			std::cout << "\\LEAF!" << std::endl;
		}
		else {
			std::cout << "\\NODE - LEFT!" << std::endl;
			printLeafOrNode(node->children[0]);


			std::cout << "\\NODE - RIGHT" << std::endl;
			printLeafOrNode(node->children[1]);
		}
	}

	static void checkCollision(PairManager* pairManager, DbvtNode* a, DbvtNode* b, const int& limit)
	{
		if (!npTestAabbAabb(a->volume, b->volume))
		{
			if (limit == 0)
				return;
			else {
				if (a->isInternal())
					checkCollision(pairManager, a->children[0], a->children[1], limit - 1);

				if (b->isInternal())
					checkCollision(pairManager, b->children[0], b->children[1], limit - 1);

				return;
			}
		}
		if (a->isLeaf() && b->isLeaf())
		{
			//add leaves to potential contacts
			pairManager->addPair(a->bodyIdx, b->bodyIdx);
		}
		else
		{
			if (!a->isLeaf())
			{
				checkCollision(pairManager, a->children[0], b, limit - 1);
				checkCollision(pairManager, a->children[1], b, limit - 1);
			}
			else
			{
				checkCollision(pairManager, a, b->children[0], limit - 1);
				checkCollision(pairManager, a, b->children[1], limit - 1);
			}

		}
	}

	void Dbvt::clean() {
		recursivlyDeleteNode(m_root);
		m_root = 0;
	}

	void Dbvt::insert(const Aabb& volume, const int& bodyIdx)
	{
		DbvtNode* newNode = createNode(0, volume, bodyIdx);
		insertLeaf(this, m_root, newNode);
		++m_leaves;
	}

	void Dbvt::update(const AabbUpdateData& volumeData, const int& bodyIdx)
	{
		if (remove(volumeData.originalAabb, bodyIdx)) {
			Aabb aabb(volumeData.originalAabb.m_minVec + volumeData.directionDiff,
				volumeData.originalAabb.m_maxVec + volumeData.directionDiff);

			insert(aabb, bodyIdx);
		}
	}

	bool Dbvt::remove(const Aabb& volume, const int& bodyIdx)
	{
		bool result = removeNode(this, m_root, volume, bodyIdx);
		if (result)
			m_leaves--;

		return result;
	}

	void Dbvt::getPotentialContacts(PairManager* pairManager)
	{
		int limit = 3;
		checkCollision(pairManager, m_root->children[0], m_root->children[1], limit);
	}

	void Dbvt::DebugPrintTree()
	{
		if (!m_root) {
			return;
		}

		printLeafOrNode(m_root);

	}

	Dbvt::Dbvt()
	{
		m_root = 0;
		m_leaves = 0;
	}

	Dbvt::~Dbvt()
	{
		clean();
	}
}