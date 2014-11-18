#include "DragSprite.h"

using namespace cocos2d;

MySprite::MySprite() {}

MySprite::~MySprite() {}

MySprite* MySprite::create(const std::string &name)
{
    MySprite* pSprite = new MySprite();

    if (pSprite->initWithFile(name))
    {
        pSprite->autorelease();
        pSprite->initOptions();
        pSprite->addEvents();

        pSprite->setName(name);
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void MySprite::initOptions()
{
    // do things here like setTag(), setPosition(), any custom logic.
}

void MySprite::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = event->getCurrentTarget()->getBoundingBox();

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }
        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
    	//log ("sprite %s moved", event->getCurrentTarget()->getName().c_str());
    	this->moveEvent(touch);
    };

    listener->onTouchEnded = [](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        //MySprite::touchEvent(touch, p);
        CCLOG("touched MySprite");
    };

    //cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void MySprite::moveEvent(cocos2d::Touch* touch)
{
	setPosition(getPosition() + touch->getDelta());
    log("moved MySprite %s", getName().c_str());
}
