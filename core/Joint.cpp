#include "Joint.h"

CJoint::CJoint(IPhysicsWorld & world, const b2JointDef &def)
    : m_world(world)
    , m_joint(m_world.CreateJoint(def))
{
}

CJoint::~CJoint()
{
}
