#include "stdafx.h"

#include "AnimationContainer.h"
#include "Skeleton.h"
#include "Animation.h"

#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/hkaAnimation.h>

AnimationContainer::AnimationContainer(Skeleton* skeleton, const void* animationData, const int animationSize)
{
    this->m_Skeleton = skeleton;
    {
        hkRootLevelContainer *container = hkSerializeUtil::loadObject<hkRootLevelContainer>(animationData, animationSize);
        hkaAnimationContainer *ac = reinterpret_cast<hkaAnimationContainer*>(container->findObjectByType(hkaAnimationContainerClass.getName()));

        int numAnimations = ac->m_bindings.getSize();

        for (int i = 0; i < numAnimations; ++i)
            this->m_Animations.push_back(new Animation(this, ac->m_bindings[i]));
    }
}


AnimationContainer::~AnimationContainer()
{
    for (int i = 0; i < this->m_Animations.size(); ++i)
        delete this->m_Animations[i];
    this->m_Animations.clear();
}
