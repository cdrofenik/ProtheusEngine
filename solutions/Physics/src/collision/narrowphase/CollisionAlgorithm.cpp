#include "physics\collision\narrowphase\CollisionAlgorithm.h"
#include "physics\collision\collisionshapes\BoxShape.h"
#include "physics\collision\collisionshapes\SphereShape.h"

using namespace math;

namespace physics
{
	static void setUpCollisionData(
		const math::Vector3r& normal,
		const math::Vector3r& contactPoint,
		const Real& depth,
		CollisionInfo& cInfo)
	{
		cInfo.contactNormal = normal;
		cInfo.contactPoint = contactPoint;
		cInfo.penetration = depth;
	}

	static inline math::Vector3r contactPoint(
		const math::Vector3r& pOne,
		const math::Vector3r& dOne,
		Real oneSize,
		const math::Vector3r& pTwo,
		const math::Vector3r& dTwo,
		Real twoSize,

		// If this is true, and the contact point is outside
		// the edge (in the case of an edge-face contact) then
		// we use one's midpoint, otherwise we use two's.
		bool useOne)
	{
		math::Vector3r toSt, cOne, cTwo;
		Real dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
		Real denom, mua, mub;

		smOne = dOne.squareLength();
		smTwo = dTwo.squareLength();
		dpOneTwo = dTwo * dOne;

		toSt = pOne - pTwo;
		dpStaOne = dOne * toSt;
		dpStaTwo = dTwo * toSt;

		denom = smOne * smTwo - dpOneTwo * dpOneTwo;

		// Zero denominator indicates parrallel lines
		if (fabs(denom) < 0.0001f) {
			return useOne ? pOne : pTwo;
		}

		mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
		mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

		// If either of the edges has the nearest point out
		// of bounds, then the edges aren't crossed, we have
		// an edge-face contact. Our point is on the edge, which
		// we know from the useOne parameter.
		if (mua > oneSize ||
			mua < -oneSize ||
			mub > twoSize ||
			mub < -twoSize)
		{
			return useOne ? pOne : pTwo;
		}
		else
		{
			cOne = pOne + dOne * mua;
			cTwo = pTwo + dTwo * mub;

			return cOne * 0.5 + cTwo * 0.5;
		}
	}

	static inline Real transformToAxis(
		const CollisionObject* cObject,
		const math::Vector3r& axis
		)
	{
		const BoxShape* box = (BoxShape*)cObject->getCollisionShape();

		return box->halfSize.x * fabsf(axis * cObject->getTransformMatrix().getAxisValues(0)) +
			box->halfSize.y * fabsf(axis * cObject->getTransformMatrix().getAxisValues(1)) +
			box->halfSize.z * fabsf(axis * cObject->getTransformMatrix().getAxisValues(2));
	}

	static int processEdgeEdge(const CollisionObject* obj0,
		const CollisionObject* obj1,
		math::Vector3r& toCenter,
		const Real& penetration,
		const int& bestAxis,
		CollisionInfo& cInfo)
	{
		int resultingAxis = bestAxis - 6;
		unsigned oneAxisIndex = resultingAxis / 3;
		unsigned twoAxisIndex = resultingAxis % 3;
		math::Vector3r oneAxis = obj0->getTransformMatrix().getAxisValues(oneAxisIndex);
		math::Vector3r twoAxis = obj1->getTransformMatrix().getAxisValues(twoAxisIndex);
		math::Vector3r axis = oneAxis % twoAxis;
		axis.normalize();

		// The axis should point from box one to box two.
		if (axis * toCenter > 0) axis = axis * -1.0f;

		// We have the axes, but not the edges: each axis has 4 edges parallel
		// to it, we need to find which of the 4 for each object. We do
		// that by finding the point in the centre of the edge. We know
		// its component in the direction of the box's collision axis is zero
		// (its a mid-point) and we determine which of the extremes in each
		// of the other axes is closest.

		const BoxShape* box0 = (BoxShape*)obj0->getCollisionShape();
		const BoxShape* box1 = (BoxShape*)obj1->getCollisionShape();
		math::Vector3r ptOnOneEdge = box0->halfSize;
		math::Vector3r ptOnTwoEdge = box1->halfSize;
		for (unsigned i = 0; i < 3; i++)
		{
			if (i == oneAxisIndex)
				ptOnOneEdge.data[i] = 0;
			else if (obj0->getTransformMatrix().getAxisValues(i) * axis > 0)
				ptOnOneEdge.data[i] = -ptOnOneEdge.data[i];

			if (i == twoAxisIndex)
				ptOnTwoEdge.data[i] = 0;
			else if (obj1->getTransformMatrix().getAxisValues(i) * axis < 0)
				ptOnTwoEdge.data[i] = -ptOnTwoEdge.data[i];
		}

		// Move them into world coordinates (they are already oriented
		// correctly, since they have been derived from the axes).
		ptOnOneEdge = obj0->getTransformMatrix() * ptOnOneEdge;
		ptOnTwoEdge = obj1->getTransformMatrix() * ptOnTwoEdge;

		// So we have a point and a direction for the colliding edges.
		// We need to find out point of closest approach of the two
		// line-segments.
		math::Vector3r vertex = contactPoint(
			ptOnOneEdge, oneAxis, box0->halfSize.data[oneAxisIndex],
			ptOnTwoEdge, twoAxis, box1->halfSize.data[oneAxisIndex],
			bestAxis > 2
			);

		setUpCollisionData(axis, vertex, penetration, cInfo);
	}

	static int processFaceFace(const CollisionObject* obj0,
		const CollisionObject* obj1,
		math::Vector3r& toCenter,
		const Real& penetration,
		const int& bestAxis,
		CollisionInfo& cInfo)
	{
		math::Vector3r normal = obj0->getTransformMatrix().getAxisValues(bestAxis);
		if (obj0->getTransformMatrix().getAxisValues(bestAxis) * toCenter > 0)
		{
			normal = normal * -1.0f;
		}

		const BoxShape* box2 = (BoxShape*)obj1->getCollisionShape();
		math::Vector3r vertex = box2->halfSize;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.x = -vertex.x;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.y = -vertex.y;
		if (obj1->getTransformMatrix().getAxisValues(1) * normal < 0) vertex.z = -vertex.z;

		setUpCollisionData(normal, vertex, penetration, cInfo);
		return 1;
	}

	static bool SeparatingAxisTest(const CollisionObject* obj0,
		const CollisionObject* obj1,
		math::Vector3r& axis,
		math::Vector3r& toCenter,
		unsigned int testId,
		Real& smallestPenetration,
		unsigned int& result)
	{
		// Project this onto the axis
		Real distance = fabsf(toCenter * axis);

		// Check projection distance
		Real projectionDistance = transformToAxis(obj0, axis) + transformToAxis(obj1, axis) - distance;
		
		if (projectionDistance < 0)
			return false;
		if (projectionDistance < smallestPenetration) {
			smallestPenetration = projectionDistance;
			result = testId;
		}
		return true;
	}

	//preprocessor definition used to shorten function call to SeparatingAxisTest
	#define SEPARATING_AXIS_TEST(axis, index) \
		SeparatingAxisTest(obj0, obj1, (axis), toCenter, (index), penetration, bestTestId)

	#define MERGE_AXIS_VALUES(index0, index1) \
		obj0->getTransformMatrix().getAxisValues(index0) % obj0->getTransformMatrix().getAxisValues(index1)

	static int BoxBoxGenerateContacts(CollisionObject* obj0, CollisionObject* obj1, CollisionInfo& cInfo)
	{
		math::Vector3r toCenter = obj0->getWorldPosition() - obj1->getWorldPosition();
		const BoxShape* box0 = (BoxShape*)obj0->getCollisionShape();
		const BoxShape* box1 = (BoxShape*)obj1->getCollisionShape();

		Real penetration = REAL_MAX;
		unsigned int bestTestId = -1;

		//Check 15 axes 
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(0), 0) &&
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(1), 1) &&
		SEPARATING_AXIS_TEST(obj0->getTransformMatrix().getAxisValues(2), 2) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(0), 3) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(1), 4) &&
		SEPARATING_AXIS_TEST(obj1->getTransformMatrix().getAxisValues(2), 5);

		Real smallestPenetration = penetration;

		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 0), 6) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 1), 7) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(0, 2), 8) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 0), 9) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 1), 10) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(1, 2), 11) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 0), 12) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 1), 13) &&
		SEPARATING_AXIS_TEST(MERGE_AXIS_VALUES(2, 2), 14);

		if (bestTestId < 0)
			return 0;
		if (bestTestId < 6)
		{
			return processFaceFace(
				bestTestId < 3 ? obj0 : obj1,
				bestTestId < 3 ? obj1 : obj0,
				bestTestId < 3 ? toCenter : toCenter*-1.0f,
				penetration,
				bestTestId < 3 ? bestTestId : bestTestId - 3,
				cInfo);
		}
		else
		{
			return processFaceFace(obj0, obj1, toCenter, smallestPenetration, bestTestId, cInfo);
		}
	}

	static int SphereBoxGenerateContacts(CollisionObject* obj0, CollisionObject* obj1, CollisionInfo& cInfo)
	{
		const SphereShape* sphere = (SphereShape*)obj0->getCollisionShape();
		const BoxShape* box = (BoxShape*)obj1->getCollisionShape();

		math::Vector3r sphereCenter = obj0->getWorldPosition();
		math::Vector3r relCenter = obj1->getTransformMatrix().transformInverse(sphereCenter);
		
		math::Vector3r closestPoint;
		box->closestPoint(relCenter, closestPoint);

		// Check collision
		Real distance = (closestPoint - relCenter).squareLength();
		if (distance > (sphere->getRadius() * sphere->getRadius()))
			return 0;

		math::Vector3r closesPntWorldPos = obj1->getTransformMatrix().transform(closestPoint);

		setUpCollisionData((closesPntWorldPos - sphereCenter).normalize(),
			closesPntWorldPos,
			sphere->getRadius() - (closestPoint - relCenter).length(),
			cInfo);
		return 1;
	}

	static int SphereSphereGenerateContacts(CollisionObject* obj0, CollisionObject* obj1, CollisionInfo& cInfo)
	{
		const SphereShape* sphere0 = (SphereShape*)obj0->getCollisionShape();
		const SphereShape* sphere1 = (SphereShape*)obj1->getCollisionShape();

		math::Vector3r distanceVector = obj0->getWorldPosition() - obj1->getWorldPosition();
		Real distance = distanceVector.length();

		if (distance <= 0.0f || distance >= (sphere0->getRadius() + sphere1->getRadius()))
			return 0;

		math::Vector3r normal = distanceVector * (((Real)1.0) / distance);
		setUpCollisionData(normal,
			obj0->getWorldPosition() + distanceVector * (Real)0.5,
			sphere0->getRadius() + sphere1->getRadius() - distance,
			cInfo);
		return 1;
	}

	int CollisionAlgorithm::processCollision(CollisionObject* obj0, CollisionObject* obj1, CollisionInfo& cInfo)
	{
		if (obj0->getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE &&
			obj1->getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE)
		{
			return BoxBoxGenerateContacts(obj0, obj1, cInfo);
		}

		if ((obj0->getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE &&
			obj1->getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE) ||
			(obj0->getCollisionShape()->getType() == CollisionShapeType::BOX_SHAPE &&
			obj1->getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE))
		{
			if (obj1->getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE)
				return SphereBoxGenerateContacts(obj1, obj0, cInfo);
			else
				return SphereBoxGenerateContacts(obj0, obj1, cInfo);
		}

		if (obj0->getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE &&
			obj1->getCollisionShape()->getType() == CollisionShapeType::SPHERE_SHAPE)
		{
			return SphereSphereGenerateContacts(obj0, obj1, cInfo);
		}

		return 0;
	}
}