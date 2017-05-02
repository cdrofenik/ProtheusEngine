#include "physics\collision\broadphase\UniformGrid.h"

#include <iostream>
#include <math.h>

using namespace math;
using namespace collections;

namespace physics {

	inline static void processCellOwnCell(Cell* cell, ObjectEntity* entity, PairManager* pM)
	{
		int entryNum = cell->entityCount;
		ObjectEntity* activeOE = cell->entity;
		while (entryNum > 1)
		{
			pM->addPair(entity->id, activeOE->id);
			activeOE = activeOE->next;
			entryNum--;
		}
	}

	inline static void processCell(Cell* cell, ObjectEntity* entity, PairManager* pM)
	{
		int entryNum = cell->entityCount;
		ObjectEntity* activeOE = cell->entity;
		while (entryNum >= 1)
		{
			//quick distance check
			pM->addPair(entity->id, activeOE->id);
			activeOE = activeOE->next;
			entryNum--;
		}
	}

	inline static Real getCellBorder(const Real& origin, const Real& size, const int index)
	{
		return origin + (size * index) + size / 2;
	}

	static void copyObjectEntity(ObjectEntity* source,
		ObjectEntity* destination)
	{
		destination->previous = source->previous;
		destination->next = source->next;
		destination->bbox = source->bbox;
		destination->id = source->id;
	}

	void UniformGrid::printGrid()
	{
		for (size_t x = 0; x < m_xExtent; x++)
		{
			std::cout << "Cell z-axis: " << x << std::endl;
			for (size_t y = 0; y < m_yExtent; y++)
			{
				std::cout << "Cell x-axis: " << y << std::endl;
				for (size_t z = 0; z < m_zExtent; z++)
				{

					std::cout << "Cell y-axis: " << z << std::endl;
					Cell* cell =& m_cells[x][y][z];

					std::cout << "Cell: " << cell->center.x << " , " << cell->center.y << " , ";
					std::cout << cell->center.z << " /entryCount: " << cell->entityCount << std::endl;
				}
			}
		}
	}

	void UniformGrid::generateCells()
	{
		m_cells = new Cell**[m_xExtent];
		for (unsigned int x = 0; x < m_xExtent; ++x) {
			m_cells[x] = new Cell*[m_yExtent];
			for (unsigned int y = 0; y < m_yExtent; ++y) {
				m_cells[x][y] = new Cell[m_zExtent];
				for (unsigned int z = 0; z < m_zExtent; ++z) {
					Cell* cell =& m_cells[x][y][z];
					cell->center.x = m_origin.x + m_cellSize.x * x;
					cell->center.y = m_origin.y + m_cellSize.y * y;
					cell->center.z = m_origin.z + m_cellSize.z * z;
				}
			}
		}

		//printGrid();
	}

	Vector3ui UniformGrid::getLocationIndex(const math::Vector3r& topLeftPos) const
	{
		unsigned int xCellIdx = static_cast<unsigned int>(floor((topLeftPos.x - m_origin.x) / m_cellSize.x));
		unsigned int yCellIdx = static_cast<unsigned int>(floor((topLeftPos.y - m_origin.y) / m_cellSize.y));
		unsigned int zCellIdx = static_cast<unsigned int>(floor((topLeftPos.z - m_origin.z) / m_cellSize.z));

		return Vector3ui(xCellIdx, yCellIdx, zCellIdx);
	}

	void UniformGrid::addEntityToCell(const Vector3ui& cellPos, ObjectEntity* oEntity)
	{
		Cell* currCell =& m_cells[cellPos.x][cellPos.y][cellPos.z];
		if (currCell->entityCount > 0)
		{
			ObjectEntity* oePntr = currCell->entity;
			int cellEntryCount = currCell->entityCount;
			while (cellEntryCount > 0)
			{
				if (cellEntryCount == 1) {
					break;
				}
				else {
					oePntr = oePntr->next;
					cellEntryCount--;
				}
			}

			oEntity->previous = oePntr;
			oePntr->next = oEntity;
			currCell->entityCount++;
		}
		else
		{
			currCell->entity = oEntity;
			currCell->entityCount++;
		}
	}

	void UniformGrid::removeEntityFromCell(const Vector3ui& cellPos, const int& data)
	{
		Cell* currCell =& m_cells[cellPos.x][cellPos.y][cellPos.z];
		if (currCell->entityCount > 1)
		{
			ObjectEntity* oePntr = currCell->entity;
			int cellEntryCount = currCell->entityCount;
			while (cellEntryCount > 0)
			{
				if (oePntr->id == data) {
					if (cellEntryCount > 1) {
						oePntr->bbox = oePntr->next->bbox;
						oePntr->id = oePntr->next->id;
						oePntr->next = oePntr->next->next;

						oePntr = DEF_NULL;
					}
					else {
						oePntr = DEF_NULL;
					}
					currCell->entity--;
					return;
				}
				oePntr = oePntr->next;
				cellEntryCount--;
			}
		}
		else
		{
			currCell->entityCount = 0;
			currCell->entity = DEF_NULL;
		}
	}

	void UniformGrid::updateEntityInCell(const Vector3ui& cellPos,
		const Aabb& volume,
		const int& id)
	{
		Cell* currCell =& m_cells[cellPos.x][cellPos.y][cellPos.z];
		ObjectEntity* oePntr = currCell->entity;
		int cellEntryCount = currCell->entityCount;
		while (cellEntryCount > 0)
		{
			if (oePntr->id == id) {
				break;
			}
			oePntr = oePntr->next;
		}
		oePntr->bbox = volume;
	}

	void UniformGrid::insert(const Aabb& volume, const int& bodyIdx)
	{
		Vector3ui cellIdx = getLocationIndex(volume.getTopLeft());
		ObjectEntity* objE = new ObjectEntity(volume, bodyIdx);
		addEntityToCell(cellIdx, objE);
	}

	void UniformGrid::update(const AabbUpdateData& volume, const int& bodyIdx)
	{
		Vector3ui oldCellIdx = getLocationIndex(volume.originalAabb.getTopLeft());
		Aabb updatedAabb(volume.originalAabb.m_minVec + volume.directionDiff,
			volume.originalAabb.m_maxVec + volume.directionDiff);
		Vector3ui newCellIdx = getLocationIndex(updatedAabb.getTopLeft());

		if (oldCellIdx != newCellIdx)
		{
			removeEntityFromCell(oldCellIdx, bodyIdx);

			ObjectEntity* objE = new ObjectEntity(updatedAabb, bodyIdx);
			addEntityToCell(newCellIdx, objE);
		}
		else
		{
			updateEntityInCell(newCellIdx, updatedAabb, bodyIdx);
		}

		m_activeCellIds.push_back(newCellIdx);
	}

	bool UniformGrid::remove(const Aabb& volume, const int& bodyIdx)
	{
		Vector3ui cellPos = getLocationIndex(volume.getTopLeft());
		removeEntityFromCell(cellPos, bodyIdx);
		return true;
	}

	void UniformGrid::getPotentialContacts(PairManager* pairManager)
	{
		for (int i = 0; i < m_activeCellIds.size(); i++)
		{
			Vector3ui cellIdx = m_activeCellIds.at(i);
			Cell* activeCell =& m_cells[cellIdx.x][cellIdx.y][cellIdx.z];

			int entityCount = activeCell->entityCount;
			ObjectEntity* activeOE = activeCell->entity;
			while (entityCount > 0)
			{
				//Check own cell
				processCellOwnCell(activeCell, activeOE, pairManager);

				//check neighbours
				while (true) {
					//SW - same z axis
					processCell(&m_cells[cellIdx.x - 1][cellIdx.y + 1][cellIdx.z], activeOE, pairManager);

					//E border
					if (activeOE->bbox.m_maxVec.x > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x))
						processCell(&m_cells[cellIdx.x + 1][cellIdx.y][cellIdx.z], activeOE, pairManager);

					//S border
					if (activeOE->bbox.m_minVec.y < getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y))
					{
						processCell(&m_cells[cellIdx.x][cellIdx.y + 1][cellIdx.z], activeOE, pairManager);
						//SE border
						if (activeOE->bbox.m_maxVec.x > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x))
							processCell(&m_cells[cellIdx.x + 1][cellIdx.y + 1][cellIdx.z], activeOE, pairManager);
					}

					//Back border
					if (activeOE->bbox.m_maxVec.z > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z))
					{
						cellIdx.z++;
						processCell(&m_cells[cellIdx.x][cellIdx.y][cellIdx.z], activeOE, pairManager);
					}
					else
						break;
				}

				activeOE = activeOE->next;
				entityCount--;
			}

			
		}
		m_activeCellIds.clear();
	}

	UniformGrid::UniformGrid(const int& gridSize, const math::Vector3r& cellSize)
	{
		//Init
		m_xExtent = 100;
		m_yExtent = 100;
		m_zExtent = 100;

		m_cellSize = cellSize;

		m_origin = math::Vector3r(
			-(cellSize.x * (gridSize / 2)) + (cellSize.x / 2),
			-(cellSize.y * (gridSize / 2)) + (cellSize.y / 2),
			-(cellSize.z * (gridSize / 2)) + (cellSize.z / 2)
		);

		generateCells();
		m_activeCellIds = AlignedArray<Vector3ui>();
	}

	UniformGrid::~UniformGrid()
	{
		for (unsigned int x = 0; x < m_xExtent; ++x) {
			m_cells[x] = new Cell*[m_yExtent];
			for (unsigned int y = 0; y < m_yExtent; ++y) {
				m_cells[x][y] = new Cell[m_zExtent];
				for (unsigned int z = 0; z < m_zExtent; ++z) {
					m_cells[x][y][z] = DEF_NULL;
				}
			}
		}
		m_activeCellIds.clear();
	}
}