#pragma once

#include "IPhysicsWorld.h"
#include <boost/noncopyable.hpp>

class CJoint : private boost::noncopyable
{
public:
    CJoint(IPhysicsWorld & world, b2JointDef const& def);
    ~CJoint();

private:
    IPhysicsWorld &m_world;
    b2Joint *m_joint;
};

using CJointUniquePtr = std::unique_ptr<CJoint>;
