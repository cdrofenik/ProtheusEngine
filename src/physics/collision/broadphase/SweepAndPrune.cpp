#include "physics\collision\broadphase\SweepAndPrune.h"

// system dependency
#include <iostream>

using namespace math;
using namespace collections;

namespace physics
{
    void SweepAndPrune::printEndPoints(int axis, int limit)
    {
        std::cout << "Endpoints for axis: " << axis << std::endl;
        for (int i = 0; i < limit; i++)
        {
            EndPoint* currEp = m_endPoints[axis] + i;
            std::cout << "Endpoint: " << i << " - values: " << currEp->value << " /Max: ";
            std::cout << currEp->isMax << " /soIndex: " << currEp->soIndex << std::endl;
        }
    }

    inline unsigned int SweepAndPrune::quantize(const Real& inValue)
    {
        unsigned int value = 0;
        memcpy(&value,&inValue, sizeof(value));

        if (value&  0x80000000)
            value = ~value;
        else
            value |= 0x80000000;

        return value;
    }

    bool SweepAndPrune::isColliding(const int& axis0, const SweepObject& so0,
        const int& axis1, const SweepObject& so1)
    {
        bool firstAxisTest = false;
        if (so0.min[axis0] < so1.max[axis0] && so0.max[axis0] > so1.min[axis0])
        {
            firstAxisTest = true;
        }

        bool secondAxisTest = false;
        if (so0.min[axis1] < so1.max[axis1] && so0.max[axis1] > so1.min[axis1])
        {
            secondAxisTest = true;
        }

        return firstAxisTest && secondAxisTest;
    }

    void SweepAndPrune::checkIfColliding(const int& axis, const SweepObject& activeSo,
        const SweepObject& soOther, const bool& adding, bool updateOverlaps)
    {
        const int axis1 = (1 << axis) & 3;
        const int axis2 = (1 << axis1) & 3;
        if (updateOverlaps && isColliding(axis1, activeSo, axis2, soOther)) {
            //Add to or remove from pair manager
            if (adding)
                ref_pairManager->addPair(activeSo.bodyIdx, soOther.bodyIdx);
            else
                ref_pairManager->removePair(activeSo.bodyIdx, soOther.bodyIdx);

        }
    }

    bool isAscending(unsigned int a, unsigned int b)
    {
        return a > b;
    }

    bool isDecending(unsigned int a, unsigned int b)
    {
        return a < b;
    }

    void SweepAndPrune::sortMin(const int& axis,
        const int& startIndex,
        const bool& updateOverlaps,
        const bool& ascending = false)
    {
        int shiftValue = ascending ? 1 : -1;
        bool (*evaluationFunc)(unsigned int, unsigned int) = ascending ? isAscending : isDecending;

        EndPoint* activeEP = m_endPoints[axis] + startIndex;
        EndPoint* nextEP = activeEP + shiftValue;
        SweepObject activeSo = m_sObjects.at(activeEP->soIndex);

        while (evaluationFunc(activeEP->value, nextEP->value))
        {
            SweepObject so = m_sObjects.at(nextEP->soIndex);
            if (nextEP->isMax)
            {
                checkIfColliding(axis, activeSo, so, !ascending, updateOverlaps);
                m_sObjects.at(nextEP->soIndex).max[axis] += (shiftValue * -1);
            }
            else {
                m_sObjects.at(nextEP->soIndex).min[axis] += (shiftValue * -1);
            }

            m_sObjects.at(activeEP->soIndex).min[axis] += shiftValue;

            //swap edgepoints
            EndPoint tmp = *activeEP;
            *activeEP = *nextEP;
            *nextEP = tmp;

            //increment or decrement depending on _ascending
            activeEP += shiftValue;
            nextEP += shiftValue;
        }
    }

    void SweepAndPrune::sortMax(const int& axis,
        const int& startIndex,
        const bool& updateOverlaps,
        const bool& ascending = false)
    {
        int shiftValue = ascending ? 1 : -1;
        bool(*evaluationFunc)(unsigned int, unsigned int) = ascending ? isAscending : isDecending;
    
        EndPoint* activeEP = m_endPoints[axis] + startIndex;
        EndPoint* nextEP = activeEP + shiftValue;
        SweepObject activeSo = m_sObjects.at(activeEP->soIndex);

        while (evaluationFunc(activeEP->value, nextEP->value))
        {
            SweepObject so = m_sObjects.at(nextEP->soIndex);
            if (!nextEP->isMax)
            {
                checkIfColliding(axis, activeSo, so, ascending, updateOverlaps);
                m_sObjects.at(nextEP->soIndex).min[axis] += (shiftValue * -1);
            }
            else
                m_sObjects.at(nextEP->soIndex).max[axis] += (shiftValue * -1);

            m_sObjects.at(activeEP->soIndex).max[axis] += shiftValue;

            //swap edgepoints
            EndPoint tmp = *activeEP;
            *activeEP = *nextEP;
            *nextEP = tmp;

            //increment or decrement depending on ascending
            activeEP += shiftValue;
            nextEP += shiftValue;
        }
    }

    void SweepAndPrune::insert(const Aabb& volume, const int& bodyIdx)
    {
        SweepObject so;
        so.bodyIdx = bodyIdx;
        for (int axis = 0; axis < 3; axis++)
        {
            m_endPoints[axis][m_ePointCounter + 1] = m_endPoints[axis][m_ePointCounter - 1];

            unsigned int val = quantize(volume.m_minVec.getValue(axis));
            m_endPoints[axis][m_ePointCounter - 1].value = val;
            m_endPoints[axis][m_ePointCounter - 1].soIndex = m_sObjectCounter;
            m_endPoints[axis][m_ePointCounter - 1].isMax = false;

            val = quantize(volume.m_maxVec.getValue(axis));
            m_endPoints[axis][m_ePointCounter].value = val;
            m_endPoints[axis][m_ePointCounter].soIndex = m_sObjectCounter;
            m_endPoints[axis][m_ePointCounter].isMax = true;

            so.min[axis] = m_ePointCounter - 1;
            so.max[axis] = m_ePointCounter;
        }

        m_sObjects.push_back(so);

        sortMin(0, so.min[0], false);
        sortMax(0, so.max[0], false);
        sortMin(1, so.min[0], false);
        sortMax(1, so.max[0], false);
        sortMin(2, so.min[0], true);
        sortMax(2, so.max[0], true);

        m_ePointCounter += 2;
        m_sObjectCounter++;
    }

    void SweepAndPrune::update(const AabbUpdateData& volumeData, const int& bodyIdx)
    {
        Aabb updatedAabb;
        updatedAabb.m_minVec = volumeData.originalAabb.m_minVec + volumeData.directionDiff;
        updatedAabb.m_maxVec = volumeData.originalAabb.m_maxVec + volumeData.directionDiff;

        SweepObject activeSo = m_sObjects.at(bodyIdx);
        for (int axis = 0; axis < 3; axis++)
        {

            int minIdx = activeSo.min[axis];
            int maxIdx = activeSo.max[axis];

            unsigned int volumeMin = quantize(updatedAabb.m_minVec.getValue(axis));
            unsigned int volumeMax = quantize(updatedAabb.m_maxVec.getValue(axis));

            unsigned int dMin = volumeMin - m_endPoints[axis][minIdx].value;
            unsigned int dMax = volumeMax - m_endPoints[axis][maxIdx].value;

            m_endPoints[axis][minIdx].value = volumeMin;
            m_endPoints[axis][maxIdx].value = volumeMax;

            if (dMin != 0)
                sortMin(axis, minIdx, true, dMin > 0);

            if (dMax != 0)
                sortMax(axis, maxIdx, true, dMax > 0);
        }
    }

    bool SweepAndPrune::remove(const Aabb& volume, const int& bodyIdx)
    {
        //TODO: implement remove function
        return false;
    }

    SweepAndPrune::SweepAndPrune(PairManager* pairManager)
    {
        m_sObjects = AlignedArray<SweepObject>();
        m_sObjectCounter = 0;

        ref_pairManager = pairManager;

        for (int i = 0; i < 3; i++)
        {
            m_endPoints[i] = new EndPoint[20 * 2];
        }

        m_ePointCounter = 2;
        //Adding sentinels to all axises
        for (int axis = 0; axis < 3; axis++)
        {
            m_endPoints[axis][0].isMax = false;
            m_endPoints[axis][0].soIndex = -1;
            m_endPoints[axis][0].value = 0;

            m_endPoints[axis][1].isMax = true;
            m_endPoints[axis][1].soIndex = -1;
            m_endPoints[axis][1].value = ULONG_MAX;
        
            printEndPoints(axis, m_ePointCounter);
        }
    }

    SweepAndPrune::~SweepAndPrune()
    {
        delete[]& m_endPoints;
        m_sObjects.clear();
    }
}