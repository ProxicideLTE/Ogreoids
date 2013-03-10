#ifndef UTIL_H_
#define UTIL_H_

namespace ogreoids {

	Ogre::Degree GetAbsYaw(Ogre::Vector2 dir1, Ogre::Vector2 dir2);
    Ogre::Degree GetSignedYaw(Ogre::Vector2 dir1, Ogre::Vector2 dir2);

    inline Ogre::Vector2 GetRightPerp(const Ogre::Vector2& v)
    {
        return Ogre::Vector2(-v.y, v.x);
    }

    inline Ogre::Vector2 GetLeftPerp(const Ogre::Vector2& v)
    {
        return Ogre::Vector2(v.y, -v.x);
    }
}

#endif