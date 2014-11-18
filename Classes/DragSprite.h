#ifndef _MYSPRITE_HPP_
#define _MYSPRITE_HPP_

#include "cocos2d.h"

class MySprite : public cocos2d::Sprite
{
    public:
        MySprite();
        ~MySprite();
        static MySprite* create(const std::string &name);

        void initOptions();

        void addEvents();
        void moveEvent(cocos2d::Touch* touch);

    private:

};

#endif // _MYSPRITE_HPP_
