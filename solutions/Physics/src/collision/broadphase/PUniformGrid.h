#ifndef PUNIFORMGRID_H
#define PUNIFORMGRID_H

#include "IBroadPhase.hpp"
#include "physics\collision\collisionshapes\SphereShape.h"

namespace physics
{
	//Test function
	extern "C" int cuda_func(int& a, const int& b);

	class PUniformGrid : public IBroadPhase
	{
	public:
		PUniformGrid(const int& gridSize, const math::Vector3r& cellSize);
		~PUniformGrid();

		virtual void insert(const Aabb& volume, const int& bodyIdx);
		virtual void update(const AabbUpdateData& volumeData, const int& bodyIdx);
		virtual bool remove(const Aabb& volume, const int& bodyIdx);
		virtual void getPotentialContacts(PairManager* pairManager);

	private:
		struct ObjectEntity
		{
			ObjectEntity(const Sphere& bVol = Sphere(), const int& id = -1) :
				bSphere(bVol), id(id)
			{
				ObjectEntity* previous = DEF_NULL;
				ObjectEntity* next = DEF_NULL;
			}

			ObjectEntity* previous;
			ObjectEntity* next;
			Sphere bSphere;
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
			unsigned int borderEntitiesCount;
			ObjectEntity* borderEntity;
		};

		unsigned int m_xExtent;
		unsigned int m_yExtent;
		unsigned int m_zExtent;
		bool m_initialized;

		Cell*** m_cells;
		collections::AlignedArray<math::Vector3ui> m_activeCellIds;

		math::Vector3r m_origin;
		math::Vector3r m_cellSize;

		void printGrid();
		void generateCells();
		math::Vector3ui getLocationIndex(const math::Vector3r& centerPos) const;
		void addEntityToCell(const math::Vector3ui& cellPos, ObjectEntity* oEntity);
		void removeEntityFromCell(const math::Vector3ui& cellPos, const int& data);
		void updateEntityInCell(const math::Vector3ui& cellPos, const Sphere& volume, const int& id);
	
		void insertCellBorderEnity(const math::Vector3ui& cellPos, ObjectEntity * oEntity);
		void updateCellBorderEntity(const math::Vector3ui&  cellPos, const Sphere&  volume, const int&  id);
		void removeCellBorderEnity(const math::Vector3ui&  cellPos, const int&  data);
	};
}

#endif