#include "cocos2d.h"
#include "Positions.h"

USING_NS_CC;

static Positions makeIph5Positions()
{
	Positions pos;
	pos.deck = Vec2(125, 250);

	pos.err = Vec2(25, 600);
	pos.errDelta = Vec2(0, -50);
	pos.errScale = 0.3;

	pos.info = Vec2(75, 600);
	pos.infoDelta = pos.errDelta;
	pos.infoScale = pos.errScale;

	pos.cardSpriteScale = 1.3;

	int salutx0 = 325;
	int salutDx = 35 + 125;
	int salutY1 = 335;
	int salutY2 = 175;
	pos.salutR = Vec2(salutx0 + salutDx * 0, salutY2);
	pos.salutG = Vec2(salutx0 + salutDx * 1, salutY2);
	pos.salutB = Vec2(salutx0 + salutDx * 2, salutY2);
	pos.salutY = Vec2(salutx0 + salutDx * 0, salutY1);
	pos.salutW = Vec2(salutx0 + salutDx * 1, salutY1);
	pos.salutF = Vec2(salutx0 + salutDx * 2, salutY1);

	pos.opponent = Vec2(100, 500);
	pos.opponentDelta = Vec2(20 + 125, 0);

	pos.me = Vec2(100, 15);
	pos.meDelta = Vec2(20 + 125, 0);

	// Drop
	pos.dropScale = 0.5;

	int dropx0 = 825;
	int dropyDy = -50;
	int dropDx = 50 + 12;
	int dropy0 = 575;
	pos.dropR = Vec2(dropx0 + dropDx * 0, dropy0);
	pos.dropRDelta = Vec2(0, dropyDy);
	pos.dropG = Vec2(dropx0 + dropDx * 1, dropy0);
	pos.dropGDelta = Vec2(0, dropyDy);
	pos.dropB = Vec2(dropx0 + dropDx * 2, dropy0);
	pos.dropBDelta = Vec2(0, dropyDy);
	pos.dropY = Vec2(dropx0 + dropDx * 3, dropy0);
	pos.dropYDelta = Vec2(0, dropyDy);
	pos.dropW = Vec2(dropx0 + dropDx * 4, dropy0);
	pos.dropWDelta = Vec2(0, dropyDy);
	pos.dropF = Vec2(dropx0, 50);
	pos.dropFDelta = Vec2(dropDx, 0);

	// zones
	pos.tableCenter = Rect(325, 175, 325, 175);
	pos.dropZone = Rect(825, 50, 300, 525);
	pos.changeZone = Rect(50, 0, 650, 125);

	// меню выбора инфы
	pos.numMenu = Vec2(100, 350);
	pos.numMenuDelta = Vec2(20 + 125, 0);
	pos.colorMenu = Vec2(100, 200);
	pos.colorMenuDelta = Vec2(10 + 125, 0);

	return pos;
}

static Positions iph5Positions = makeIph5Positions();
const Positions &Positions::getPositions()
{
	return iph5Positions;
}

cocos2d::Vec2 Positions::getSalut(char c) const
{
	switch(c)
	{
	default:
	case 'r':
		return salutR;
	case 'g':
		return salutG;
	case 'b':
		return salutB;
	case 'y':
		return salutY;
	case 'w':
		return salutW;
	case 'f':
		return salutF;
	}
}

cocos2d::Vec2 Positions::getDrop(char c) const
{
	switch(c)
	{
	default:
	case 'r':
		return dropR;
	case 'g':
		return dropG;
	case 'b':
		return dropB;
	case 'y':
		return dropY;
	case 'w':
		return dropW;
	case 'f':
		return dropF;
	}
}

cocos2d::Vec2 Positions::getDropDelta(char c) const
{
	switch(c)
	{
	default:
	case 'r':
		return dropRDelta;
	case 'g':
		return dropGDelta;
	case 'b':
		return dropBDelta;
	case 'y':
		return dropYDelta;
	case 'w':
		return dropWDelta;
	case 'f':
		return dropFDelta;
	}
}
