#include "Table.h"
#include "Positions.h"
#include "ui/UIButton.h"
#include <functional>

USING_NS_CC;

Scene* Table::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Table::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void Table::addCardSprite(const std::string &filename, cocos2d::Vec2 pos, int z)
{
    auto sprite = Sprite::create(filename);
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(pos);
    sprite->setScale(Positions::getPositions().cardSpriteScale);
    this->addChild(sprite, z);
}

Sprite *Table::loadCardSprite(const std::string &image)
{
	int num = 1;
	std::string color = "red";
	if (image.length() == 2)
	{
		switch(image.at(0))
		{
		case 'r':
			color = "red"; break;
		case 'g':
			color = "green"; break;
		case 'b':
			color = "blue"; break;
		case 'y':
			color = "yellow"; break;
		case 'w':
			color = "white"; break;
		case 'f':
			color = "rainbow"; break;
		}

		num = image.at(1) - '0';
		if (1 > num || num > 5)
		{
			num = 1;
		}
	}

    auto sprite = Sprite::create(StringUtils::format("%d_%s.png", num, color.c_str()));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setScale(Positions::getPositions().cardSpriteScale);
    return sprite;
}

// on "init" you need to initialize your instance
bool Table::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // get Positions
    const Positions &pos = Positions::getPositions();

    // add Deck
    addCardSprite("card_back.png", pos.deck, -1);

    // add errs
    {
    	// create root Node
		auto err = Node::create();
		err->setName("err");
		err->setPosition(pos.err);
		this->addChild(err);

		// create array of err chips
		for (size_t i = 0; i < 3; ++i)
		{
			// empty place
			auto errItemNo = Sprite::create("chip_red_no.png");
			errItemNo->setPosition(pos.errDelta * i);
			errItemNo->setScale(pos.errScale);
			err->addChild(errItemNo, -1);

			// red chip
			auto errItem = Sprite::create("chip_red_is.png");
			errItem->setPosition(pos.errDelta * i);
			errItem->setScale(pos.errScale);
			errItem->setName(StringUtils::format("%d", i));
			if (i > 1) errItem->setVisible(false);
			err->addChild(errItem, 1);
		}
    }

    // add infos
    {
    	// create root Node
		auto info = Node::create();
		info->setName("info");
		info->setPosition(pos.info);
		this->addChild(info);

		// create array of err chips
		for (size_t i = 0; i < 8; ++i)
		{
			// empty place
			auto infoItemNo = Sprite::create("chip_blue_no.png");
			infoItemNo->setPosition(pos.infoDelta * i);
			infoItemNo->setScale(pos.infoScale);
			info->addChild(infoItemNo, -1);

			// red chip
			auto infoItem = Sprite::create("chip_blue_is.png");
			infoItem->setPosition(pos.infoDelta * i);
			infoItem->setScale(pos.infoScale);
			infoItem->setName(StringUtils::format("%d", i));
			if (i > 5) infoItem->setVisible(false);
			info->addChild(infoItem, 1);
		}
    }

    // add salutes
    addCardSprite("card_face.png", pos.salutR, -2);
    addCardSprite("is_red.png", pos.salutR, -1);

    addCardSprite("card_face.png", pos.salutG, -2);
    addCardSprite("is_green.png", pos.salutG, -1);

    addCardSprite("card_face.png", pos.salutB, -2);
    addCardSprite("is_blue.png", pos.salutB, -1);

    addCardSprite("card_face.png", pos.salutY, -2);
    addCardSprite("is_yellow.png", pos.salutY, -1);

    addCardSprite("card_face.png", pos.salutW, -2);
    addCardSprite("is_white.png", pos.salutW, -1);

    addCardSprite("card_face.png", pos.salutF, -2);
    addCardSprite("is_rainbow.png", pos.salutF, -1);

    // create Cards Node
    auto cards = Node::create();
    cards->setAnchorPoint(Vec2::ZERO);
    cards->setPosition(Vec2::ZERO);
    cards->setName("cards");
    this->addChild(cards, 10);

    // create menu
    {
		auto label = Label::createWithSystemFont("Go", "Arial", 48);
		MenuItemLabel *labelItem = MenuItemLabel::create(label,[&](Ref* sender){
			this->newGame();
		});
		labelItem->setPosition(Vec2(50, 150));

		auto label1 = Label::createWithSystemFont("Drop", "Arial", 48);
		MenuItemLabel *labelItem1 = MenuItemLabel::create(label1,[&](Ref* sender){
			this->deck(18);
		});
		labelItem1->setPosition(Vec2(50, 100));


		auto menuLabel = Menu::create(labelItem, labelItem1, nullptr);
		menuLabel->setPosition(Vec2::ZERO);
		this->addChild(menuLabel);
    }

    return true;
}

void Table::drop1(size_t id, char color, size_t serial)
{
	const Positions &pos = Positions::getPositions();

	auto cards = getChildByName("cards");
	auto card = cards->getChildByName(StringUtils::format("o%u", id));
	card->setName("");

	Vec2 dropPos, dropDelta;
	switch(color)
	{
	default:
	case 'r':
		dropPos = pos.dropR;
		dropDelta = pos.dropRDelta;
		break;
	case 'g':
		dropPos = pos.dropG;
		dropDelta = pos.dropGDelta;
		break;
	case 'b':
		dropPos = pos.dropB;
		dropDelta = pos.dropBDelta;
		break;
	case 'y':
		dropPos = pos.dropY;
		dropDelta = pos.dropYDelta;
		break;
	case 'w':
		dropPos = pos.dropW;
		dropDelta = pos.dropWDelta;
		break;
	case 'f':
		dropPos = pos.dropF;
		dropDelta = pos.dropFDelta;
		break;
	}

	Vec2 res = dropPos + dropDelta * serial;
	Vec2 originalPos = pos.opponent + pos.opponentDelta * id;
    auto move = MoveBy::create(1, res - originalPos);
    card->runAction(move);

    auto scale = ScaleTo::create(1, pos.dropScale);
    card->runAction(scale);
}

void Table::takeDropTest(const std::string &image, char color, size_t serial)
{
	take1(0, image, 0);
	drop1(0, color, serial);
}

void Table::deck(size_t qty)
{
	log("drop");
	//drop1(0, 'r', 0);
	/*take1(0, "g1", 0);
	drop1(0, 'r', 1);
	take1(0, "b1", 0);
	drop1(0, 'r', 2);
	//take1(0, "y2", 0);

	takeDropTest("w1", 'r', 3);*/

	//takeDropTest("r2", 'r', 3);


	char colors[] = "rgbyw";
	for(size_t cc = 0; cc < sizeof(colors) - 1; ++cc)
	{
		char c = colors[cc];
		size_t serial = 0;
		takeDropTest(StringUtils::format("%c%u", c, 1), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 1), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 1), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 2), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 2), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 3), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 3), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 4), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 4), c, serial++);
		takeDropTest(StringUtils::format("%c%u", c, 5), c, serial++);
	}

	takeDropTest("f1", 'f', 0);
	takeDropTest("f2", 'f', 1);
	takeDropTest("f3", 'f', 2);
	takeDropTest("f4", 'f', 3);
	takeDropTest("f5", 'f', 4);

	//take1(0, "y2", 0);
}

void Table::newGame()
{
	log("new game");

	take1(0, "r1", 0);
	take1(1, "w2", 1);
	take1(2, "b4", 2);
	take1(3, "r5", 3);
	take1(4, "g2", 4);

	take(0);
	take(1);
	take(2);
	take(3);
	take(4);
}

// TODO надо назначать с сервера Name(==id) для этой карты (для манипуляций)
void Table::take(size_t orderNum)
{
	const Positions &pos = Positions::getPositions();

    auto card = Sprite::create("card_back.png");
    card->setAnchorPoint(Vec2::ZERO);
    card->setScale(Positions::getPositions().cardSpriteScale);
	card->setPosition(pos.deck);

	auto cards = getChildByName("cards");
	cards->addChild(card);

    auto move = MoveTo::create(1, pos.me + pos.meDelta * orderNum);
    card->runAction(move);
}

void Table::take1(size_t orderNum, const std::string &image, size_t id)
{
	const Positions &pos = Positions::getPositions();

	Sprite *card = loadCardSprite(image);
	card->setPosition(pos.deck);
	card->setName(StringUtils::format("o%u", id));

	auto cards = getChildByName("cards");
	cards->addChild(card);

    auto move = MoveBy::create(1, pos.opponent + pos.opponentDelta * orderNum - pos.deck);
    card->runAction(move);
}

void Table::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
