#include "physics\collision\broadphase\PUniformGrid.h"

#include <iostream>

using namespace math;
using namespace collections;

namespace physics
{
	inline static Real getCellBorder(const Real& origin, const Real& size, const int index)
	{
		return origin + (size * index) + size / 2;
	}

	void PUniformGrid::printGrid()
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

	void PUniformGrid::generateCells()
	{

	}

	Vector3ui PUniformGrid::getLocationIndex(const math::Vector3r& centerPos) const
	{
		unsigned int xCellIdx = static_cast<unsigned int>(floor((centerPos.x - m_origin.x) / m_cellSize.x));
		unsigned int yCellIdx = static_cast<unsigned int>(floor((centerPos.y - m_origin.y) / m_cellSize.y));
		unsigned int zCellIdx = static_cast<unsigned int>(floor((centerPos.z - m_origin.z) / m_cellSize.z));

		return Vector3ui(xCellIdx, yCellIdx, zCellIdx);
	}

	void PUniformGrid::insertCellBorderEnity(const Vector3ui& cellPos, ObjectEntity * oEntity)
	{
		Cell* currCell =&m_cells[cellPos.x][cellPos.y][cellPos.z];
		if (currCell->borderEntitiesCount > 0)
		{
			ObjectEntity* oePntr = currCell->borderEntity;
			int cellBorderCount = currCell->borderEntitiesCount;
			while (cellBorderCount > 0)
			{
				if (cellBorderCount == 1) {
					break;
				}
				else {
					oePntr = oePntr->next;
					cellBorderCount--;
				}
			}

			oEntity->previous = oePntr;
			oePntr->next = oEntity;
			currCell->borderEntitiesCount++;
		}
		else
		{
			currCell->borderEntity = oEntity;
			currCell->borderEntitiesCount++;
		}
	}

	void PUniformGrid::updateCellBorderEntity(const Vector3ui& cellPos, const Sphere& volume, const int& id)
	{
		Cell* currCell =& m_cells[cellPos.x][cellPos.y][cellPos.z];
		ObjectEntity* oePntr = currCell->borderEntity;
		int cellEntryCount = currCell->borderEntitiesCount;
		while (cellEntryCount > 0)
		{
			if (oePntr->id == id) {
				break;
			}
			oePntr = oePntr->next;
		}
		oePntr->bSphere = volume;
	}

	void PUniformGrid::removeCellBorderEnity(const Vector3ui& cellPos, const int& data)
	{
		Cell* currCell =& m_cells[cellPos.x][cellPos.y][cellPos.z];
		if (currCell->entityCount > 1)
		{
			ObjectEntity* oePntr = currCell->borderEntity;
			int cellEntryCount = currCell->borderEntitiesCount;
			while (cellEntryCount > 0)
			{
				if (oePntr->id == data) {
					if (cellEntryCount > 1) {
						oePntr->bSphere = oePntr->next->bSphere;
						oePntr->id = oePntr->next->id;
						oePntr->next = oePntr->next->next;

						oePntr = DEF_NULL;
					}
					else {
						oePntr = DEF_NULL;
					}
					currCell->borderEntitiesCount--;
					return;
				}
				oePntr = oePntr->next;
				cellEntryCount--;
			}
		}
		else
		{
			currCell->borderEntitiesCount = 0;
			currCell->borderEntity = DEF_NULL;
		}
	}

	void PUniformGrid::addEntityToCell(const Vector3ui& cellPos, ObjectEntity * oEntity)
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

	void PUniformGrid::removeEntityFromCell(const Vector3ui& cellPos, const int& data)
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
						oePntr->bSphere = oePntr->next->bSphere;
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

	void PUniformGrid::updateEntityInCell(const Vector3ui& cellPos, const Sphere& volume, const int& id)
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
		oePntr->bSphere = volume;
	}

	#define CHECK_BIT(var,pos) ((var)&  (1<<(pos)))
	#define SET_BIT(var, pos) ((var) + (1<<(pos)))

	void PUniformGrid::insert(const Aabb& volume, const int& bodyIdx)
	{
		Sphere boundingSphere = volume.getBoundingSphere();
		Vector3ui cellIdx = getLocationIndex(boundingSphere.center);
		ObjectEntity* objE = new ObjectEntity(boundingSphere, bodyIdx);

		//Insert element in proper cell based on centroid
		addEntityToCell(cellIdx, objE);


		//check if element crosses any cell borders
		int checkFlag = 0;
		unsigned int zAxis = cellIdx.z;
		int passCount = 0;
		while (passCount < 2) {

			//check N border
			if (CHECK_BIT(checkFlag, 3) ||
				(objE->bSphere.getMax(1) > getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y + 1)))
			{
				insertCellBorderEnity(Vector3ui(cellIdx.x, cellIdx.y + 1, zAxis), objE);
				SET_BIT(checkFlag, 3);
			}
			
			//check S border
			if (CHECK_BIT(checkFlag, 1) ||
				(objE->bSphere.getMin(1) > getCellBorder(m_origin.y, m_cellSize.y, cellIdx.y)))
			{
				insertCellBorderEnity(Vector3ui(cellIdx.x, cellIdx.y - 1, zAxis), objE);
				SET_BIT(checkFlag, 1);
			}

			//check E border
			if (CHECK_BIT(checkFlag, 0) ||
				(objE->bSphere.getMax(0) > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x + 1)))
			{
				insertCellBorderEnity(Vector3ui(cellIdx.x + 1, cellIdx.y, zAxis), objE);
				SET_BIT(checkFlag, 0);
			}

			//check W border
			if (CHECK_BIT(checkFlag, 2) ||
				(objE->bSphere.getMin(0) > getCellBorder(m_origin.x, m_cellSize.x, cellIdx.x)))
			{
				insertCellBorderEnity(Vector3ui(cellIdx.x - 1, cellIdx.y, zAxis), objE);
				SET_BIT(checkFlag, 2);
			}

			//// NW
			//if(CHECK_BIT(checkFlag, 3)& & CHECK_BIT(checkFlag, 2))
			//	addToCellBorderList();

			//// NE
			//if (CHECK_BIT(checkFlag, 3)& & CHECK_BIT(checkFlag, 0))
			//	addToCellBorderList();

			//// SW
			//if (CHECK_BIT(checkFlag, 1)& & CHECK_BIT(checkFlag, 2))
			//	addToCellBorderList();

			//// SE
			//if (CHECK_BIT(checkFlag, 1)& & CHECK_BIT(checkFlag, 0))
			//	addToCellBorderList();

			// Front
			if (objE->bSphere.getMin(2) > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z + 1))
			{
				zAxis++;
				insertCellBorderEnity(Vector3ui(cellIdx.x, cellIdx.y, zAxis), objE);
			}

			//Back
			if ((objE->bSphere.getMax(2) > getCellBorder(m_origin.z, m_cellSize.z, cellIdx.z)))
			{
				zAxis--;
				insertCellBorderEnity(Vector3ui(cellIdx.x, cellIdx.y, zAxis), objE);
			}

			passCount++;
		}
	}

	void PUniformGrid::update(const AabbUpdateData& volumeData, const int& bodyIdx)
	{
		Vector3ui oldCellIdx = getLocationIndex(volumeData.originalAabb.getTopLeft());
		Aabb updatedAabb(volumeData.originalAabb.m_minVec + volumeData.directionDiff,
			volumeData.originalAabb.m_maxVec + volumeData.directionDiff);
		Vector3ui newCellIdx = getLocationIndex(updatedAabb.getTopLeft());
		
		remove(volumeData.originalAabb, bodyIdx);
		insert(updatedAabb, bodyIdx);

		m_activeCellIds.push_back(newCellIdx);
	}

	bool PUniformGrid::remove(const Aabb& volume, const int& bodyIdx)
	{
		Vector3ui cellPos = getLocationIndex(volume.getTopLeft());
		removeEntityFromCell(cellPos, bodyIdx);

		//check if element crosses any cell borders
		int checkFlag = 0;
		unsigned int zAxis = cellPos.z - 1;
		int passCount = 0;
		while (passCount < 2) {

			removeCellBorderEnity(Vector3ui(cellPos.x, cellPos.y + 1, cellPos.z), bodyIdx);
			removeCellBorderEnity(Vector3ui(cellPos.x, cellPos.y - 1, cellPos.z), bodyIdx);
			removeCellBorderEnity(Vector3ui(cellPos.x + 1, cellPos.y, cellPos.z), bodyIdx);
			removeCellBorderEnity(Vector3ui(cellPos.x - 1, cellPos.y, cellPos.z), bodyIdx);

			//NE
			removeCellBorderEnity(Vector3ui(cellPos.x + 1, cellPos.y + 1, cellPos.z), bodyIdx);
			
			//SE
			removeCellBorderEnity(Vector3ui(cellPos.x + 1, cellPos.y - 1, cellPos.z), bodyIdx);
			
			//NW
			removeCellBorderEnity(Vector3ui(cellPos.x - 1, cellPos.y + 1, cellPos.z), bodyIdx);
			
			//SW
			removeCellBorderEnity(Vector3ui(cellPos.x - 1, cellPos.y - 1, cellPos.z), bodyIdx);

			zAxis += 2;
			passCount++;
		}

		removeCellBorderEnity(Vector3ui(cellPos.x, cellPos.y, cellPos.z + 1), bodyIdx);
		removeCellBorderEnity(Vector3ui(cellPos.x, cellPos.y, cellPos.z - 1), bodyIdx);

		return true;
	}

	void PUniformGrid::getPotentialContacts(PairManager* pairManager)
	{
		//TODO: parallel magic!

		//Based on activeCellIds size generate dim element for blocks/threads for CUDA

		//copy data to working elements

		//do work

		//copy data back to result elements
	}

	PUniformGrid::PUniformGrid(const int& gridSize, const math::Vector3r& cellSize)
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

	PUniformGrid::~PUniformGrid()
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