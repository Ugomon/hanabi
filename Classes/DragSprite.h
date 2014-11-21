#ifndef _DRAGSPRITE_HPP_
#define _DRAGSPRITE_HPP_

/**
 * Таскаемый спрайт.
 * Применяется для карт своей руки.
 * Карты своей руки можно таскать мышкой по экрану.
 * Это используется для большинства игровых действий.
 *
 * См. функции positionChanged() и released().
 */

#include "cocos2d.h"

class DragSprite : public cocos2d::Sprite
{
    public:
		DragSprite(const std::string &filename);
        ~DragSprite();

        void addEvents();
        void moveEvent(cocos2d::Touch* touch);

        void setDragEnabled(bool val); // включить или выключить перетаскивание

        virtual void positionChanged(cocos2d::Vec2 oldPos) {} // вызывается при каждом смещении спрайта
        virtual void released() {} // вызывается при отпускании спрайта (используется для выравнивания отпущенного спрайта)

    private:
        cocos2d::EventListenerTouchOneByOne *listener;
};

#endif // _DRAGSPRITE_HPP_
