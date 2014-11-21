#ifndef _DRAGSPRITE_HPP_
#define _DRAGSPRITE_HPP_

/**
 * ��������� ������.
 * ����������� ��� ���� ����� ����.
 * ����� ����� ���� ����� ������� ������ �� ������.
 * ��� ������������ ��� ����������� ������� ��������.
 *
 * ��. ������� positionChanged() � released().
 */

#include "cocos2d.h"

class DragSprite : public cocos2d::Sprite
{
    public:
		DragSprite(const std::string &filename);
        ~DragSprite();

        void addEvents();
        void moveEvent(cocos2d::Touch* touch);

        void setDragEnabled(bool val); // �������� ��� ��������� ��������������

        virtual void positionChanged(cocos2d::Vec2 oldPos) {} // ���������� ��� ������ �������� �������
        virtual void released() {} // ���������� ��� ���������� ������� (������������ ��� ������������ ����������� �������)

    private:
        cocos2d::EventListenerTouchOneByOne *listener;
};

#endif // _DRAGSPRITE_HPP_
