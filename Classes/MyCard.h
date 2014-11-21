#ifndef MYCARD_H_INCLUDED
#define MYCARD_H_INCLUDED

/**
 * ����� ��� ���� ���� ����
 */

#include "DragSprite.h"

class Table;

class MyCard : public DragSprite
{
	public:
		MyCard(const std::string &filename, size_t orderNum, Table &table);
		~MyCard();
		bool reinit(const std::string &filename);

        virtual void positionChanged(cocos2d::Vec2 oldPos) override;
        virtual void released() override;

        void setOrderNum(size_t num) { orderNum = num; }
        size_t getOrderNum() const { return orderNum; }

	private:
        size_t orderNum; // ���������� ����� ����� � ����
        Table &table; // ������ ��� ��������� ������� � ����������� �����
};

#endif /* #ifndef MYCARD_H_INCLUDED */
