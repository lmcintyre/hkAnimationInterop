#include "stdafx.h"

#include <iostream>

#include "AnimationContainer.h"
#include "Animation.h"

#include <Common/Base/System/Io/IStream/hkIStream.h>

#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>

AnimationContainer::AnimationContainer(const void* rigData, const int rigSize, const void* animationData, const int animationSize)
{
    {
        hkRootLevelContainer *container = hkSerializeUtil::loadObject<hkRootLevelContainer>(rigData, rigSize);
        hkaAnimationContainer *ac = reinterpret_cast<hkaAnimationContainer*>(container->findObjectByType(hkaAnimationContainerClass.getName()));

        this->m_Skeleton = ac->m_skeletons[0];
    }
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

std::vector<const char*> AnimationContainer::getBoneNames()
{
    int numBones = this->m_Skeleton->m_bones.getSize();

    std::vector<const char*> names;
    
    for (int i = 0; i < numBones; ++i) {
        names.push_back(this->m_Skeleton->m_bones[i].m_name.cString());
    }

    return names;
}

const int AnimationContainer::getNumBones() {
    return this->m_Skeleton->m_bones.getSize();
}

Transform * AnimationContainer::getReferencePose()
{
    const hkQsTransform *transforms = this->m_Skeleton->m_referencePose.begin();

    int num = this->m_Skeleton->m_bones.getSize();
    Transform *result = new Transform[num];
    for (int i = 0; i < num; ++i) {
        hkQsTransform currentIn = transforms[i];
        hkVector4f translation = currentIn.getTranslation();
        hkVector4f scale = currentIn.getScale();
        hkVector4f rotation = currentIn.getRotation().m_vec;

        Transform currentOut;

        currentOut.Translation.X = translation(0);
        currentOut.Translation.Y = translation(1);
        currentOut.Translation.Z = translation(2);
        currentOut.Translation.W = translation(3);

        currentOut.Scale.X = scale(0);
        currentOut.Scale.Y = scale(1);
        currentOut.Scale.Z = scale(2);
        currentOut.Scale.W = scale(3);

        currentOut.Rotation.X = rotation(0);
        currentOut.Rotation.Y = rotation(1);
        currentOut.Rotation.Z = rotation(2);
        currentOut.Rotation.W = rotation(3);

        result[i] = currentOut;
    }

    return result;
}
