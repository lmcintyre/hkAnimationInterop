#pragma once

#include <vector>

#include "Transform.h"

class Animation;
class Skeleton;

class AnimationContainer
{
public:
    AnimationContainer(Skeleton* skeleton, const void* animationData, const int animationSize);
    ~AnimationContainer();

    Skeleton* getSkeleton() { return this->m_Skeleton; }
    const int getNumAnimations() { return this->m_Animations.size(); }
    Animation* getAnimation(const int index) { return this->m_Animations[index]; }
private:
    Skeleton* m_Skeleton;
    std::vector<Animation*> m_Animations;
};

