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
    listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)
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
    	this->moveEvent(touch);
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = touch->getLocation();
        this->released();
    };

    setDragEnabled(true);
}

void DragSprite::setDragEnabled(bool val)
{
	if (val)
	{
	    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else
	{
	    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	}
}

void DragSprite::moveEvent(cocos2d::Touch* touch)
{
	Vec2 oldPos = getPosition();
	setPosition(getPosition() + touch->getDelta());
	positionChanged(oldPos);
}
