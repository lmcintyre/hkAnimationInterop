#include "stdafx.h"
#include "Skeleton.h"

#include <iostream>

#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>

#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>

Skeleton::Skeleton(const void* rigData, const int rigSize)
{
    {
        hkRootLevelContainer *container = hkSerializeUtil::loadObject<hkRootLevelContainer>(rigData, rigSize);
        hkaAnimationContainer *ac = reinterpret_cast<hkaAnimationContainer*>(container->findObjectByType(hkaAnimationContainerClass.getName()));

        this->m_HavokSkeleton = ac->m_skeletons[0];
    }
}


Skeleton::~Skeleton()
{
    delete this->m_HavokSkeleton;
}

char ** Skeleton::getBoneNames(int & count)
{
    count = this->m_HavokSkeleton->m_bones.getSize();

    char** names = (char**) CoTaskMemAlloc(count * sizeof(char*));

    for (int i = 0; i < count; ++i) {
        STRSAFE_LPCSTR name = this->m_HavokSkeleton->m_bones[i].m_name.cString();
        size_t len;

        StringCchLengthA(name, STRSAFE_MAX_CCH, &len);
        len += 1;

        names[i] = (STRSAFE_LPSTR) CoTaskMemAlloc(len);
        StringCchCopyA(names[i], len, name);
    }

    return names;
}

const int Skeleton::getNumBones()
{
    return this->m_HavokSkeleton->m_bones.getSize();
}

Transform * Skeleton::getReferencePose()
{
    const hkQsTransform *transforms = this->m_HavokSkeleton->m_referencePose.begin();

    int num = this->m_HavokSkeleton->m_bones.getSize();
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
