#include "DragSprite.h"

using namespace cocos2d;

DragSprite::DragSprite(const std::string &filename)
{
    initWithFile(filename);
	autorelease();
	addEvents();
	setName(filename);
}

DragSprite::~DragSprite() {}

void DragSprite::addEvents()
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

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        this->released();
        //log("touched DragSprite");
    };

    //cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void DragSprite::moveEvent(cocos2d::Touch* touch)
{
	Vec2 oldPos = getPosition();
	setPosition(getPosition() + touch->getDelta());
	positionChanged(oldPos);
    //log("moved DragSprite %s", getName().c_str());
}
