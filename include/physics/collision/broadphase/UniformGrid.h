#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include "core/math/Vector3.hpp"
#include "core\collections\AlignedArray.hpp"

#include "IBroadPhase.hpp"

namespace physics {

	struct ObjectEntity
	{
		ObjectEntity(const Aabb& bbox = Aabb(), const int& idd = -1) : bbox(bbox), id(idd)
		{
			ObjectEntity* previous = DEF_NULL;
			ObjectEntity* next = DEF_NULL;
		}

		ObjectEntity* previous;
		ObjectEntity* next;
		Aabb bbox;
		int id;
	};

	struct Cell
	{
		Cell(const math::Real& x = 0.0, const math::Real& y = 0.0, const math::Real& z = 0.0) {
			center = math::Vector3r(x, y, z);
			entityCount = DEF_NULL;
			entity = DEF_NULL;
		}

		int entityCount;
		math::Vector3r center;
		ObjectEntity* entity;
	};

	class UniformGrid : public IBroadPhase
	{
	public:
		UniformGrid(const int& gridSize, const math::Vector3r& cellSize);
		~UniformGrid();

		virtual void insert(const Aabb& volume, const int& bodyIdx);
		virtual void update(const AabbUpdateData& volumeData, const int& bodyIdx);
		virtual bool remove(const Aabb& volume, const int& bodyIdx);
		virtual void getPotentialContacts(PairManager* pairManager);

	private:
		unsigned int m_xExtent;
		unsigned int m_yExtent;
		unsigned int m_zExtent;

		Cell*** m_cells;
		collections::AlignedArray<math::Vector3ui> m_activeCellIds;

		math::Vector3r m_origin;
		math::Vector3r m_cellSize;
	
		void printGrid();
		void generateCells();
		math::Vector3ui getLocationIndex(const math::Vector3r& centerPos) const;
		void addEntityToCell(const math::Vector3ui& cellPos, ObjectEntity* oEntity);
		void removeEntityFromCell(const math::Vector3ui& cellPos, const int& data);
		void updateEntityInCell(const math::Vector3ui& cellPos, const Aabb& volume, const int& id);
	};
}
#endif