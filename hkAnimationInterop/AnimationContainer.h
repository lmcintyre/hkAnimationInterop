#pragma once

#include <vector>

#include "Transform.h"

class Animation;
class hkaSkeleton;

class AnimationContainer
{
public:
    AnimationContainer(const void* rigData, const int rigSize, const void* animationData, const int animationSize);
    ~AnimationContainer();

    hkaSkeleton* getSkeleton() { return this->m_Skeleton; }
    const int getNumAnimations() { return this->m_Animations.size(); }
    Animation* getAnimation(const int index) { return this->m_Animations[index]; }
    std::vector<const char*> getBoneNames();
    const int getNumBones();

    Transform* getReferencePose();
private:
    hkaSkeleton* m_Skeleton;
    std::vector<Animation*> m_Animations;
};

