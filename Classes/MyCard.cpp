#include "MyCard.h"
#include "cocos2d.h"
#include "Table.h"

USING_NS_CC;

MyCard::MyCard(const std::string &filename, size_t orderNum, Table &table)
	: DragSprite(filename), orderNum(orderNum), table(table)
{
}

MyCard::~MyCard()
{
}

void MyCard::positionChanged(cocos2d::Vec2 oldPos)
{
	//log("pos changed");
	table.cardPositionChanged(*this, oldPos);
}

void MyCard::released()
{
	log("released");
	table.cardReleased(*this);
}

