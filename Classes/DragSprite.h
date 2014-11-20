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

        virtual void positionChanged(cocos2d::Vec2 oldPos) {} // ���������� ��� ������ �������� �������
        virtual void released() {} // ���������� ��� ���������� ������� (������������ ��� ������������ ����������� �������)
    private:

};

#endif // _DRAGSPRITE_HPP_
