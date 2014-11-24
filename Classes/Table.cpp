#include "Table.h"
#include "Positions.h"
#include "ui/UIButton.h"
#include <functional>
#include "MyCard.h"
#include <vector>
#include "base/CCVector.h"
#include <fstream>
#include <string>

USING_NS_CC;

void Table::sendToServer(const std::string &cmd)
{
	log("cmd to server:'%s'", cmd.c_str());
}

void Table::cardPositionChanged(MyCard &draggingCard, cocos2d::Vec2 oldPos)
{
    const Positions &pos = Positions::getPositions();
	bool wasInsideHand = pos.changeZone.containsPoint(oldPos);
	bool isInsideHand = pos.changeZone.containsPoint(draggingCard.getPosition());

	if (isInsideHand)
	{
		// todo: переставлять карты не чаще, чем раз в 0.1 секунды

		// расставить карты в руке освободив место перетаскиваемой карте
		size_t newOrderNum = calculateOrderNum(draggingCard.getPosition());
		auto order2Place = calculateNewOrder(draggingCard.getOrderNum(), newOrderNum);

		auto cards = getChildByName("cards");
		for (size_t id = 0; id < 5; ++id)
		{
			auto card = cards->getChildByName(StringUtils::format("%lu", id));
			MyCard *myCard = dynamic_cast<MyCard *>(card);
			if (myCard->getOrderNum() != draggingCard.getOrderNum()) // перетаскиваемую не трогаем. Расставляем остальные.
			{
				myCard->stopAllActions();
				myCard->setPosition(pos.me + pos.meDelta * order2Place[myCard->getOrderNum()]);
			}
		}
	}
	else if (wasInsideHand) // outside now
	{
		// все карты, кроме данной вернуть на места
		moveAllInPlaces(draggingCard.getOrderNum());
	}
}

size_t Table::calculateOrderNum(cocos2d::Vec2 cardPos)
{
	int retVal = 0;
    const Positions &pos = Positions::getPositions();
    retVal = (int)(cardPos.x + pos.meDelta.x / 2 - pos.me.x) / (int)pos.meDelta.x;
    if (retVal < 0) retVal = 0;
    if (retVal > 4) retVal = 4;
    return (size_t)retVal;
}

std::vector<size_t> Table::calculateNewOrder(size_t oldOrderNum, size_t newOrderNum)
{
	std::vector<size_t> order2Place = {0, 1, 2, 3, 4}; // место карты в зависимости от orderNum
	int delta;
	size_t minO, maxO; // границы изменения порядковых номеров
	if (newOrderNum > oldOrderNum)
	{
		delta = -1; // у всех порядковый номер будет вычитаться
		minO = oldOrderNum + 1;
		maxO = newOrderNum;
	}
	else
	{
		delta = 1; // у всех порядковый номер будет прибавляться
		minO = newOrderNum;
		maxO = oldOrderNum - 1;
	}

	// изменить порядковые номера
	for (size_t order = 0; order < 5; ++order)
	{
		if (order == oldOrderNum)
		{
			order2Place[order] = newOrderNum;
		}
		else if (minO <= order && order <= maxO)
		{
			order2Place[order] = order + delta;
		}
	}
	return order2Place;
}

void Table::changeCardOrder(const std::vector<size_t> &order2Place)
{
	// пройтись по всей руке и изменить порядковые номера
	auto cards = getChildByName("cards");
	for (size_t id = 0; id < 5; ++id)
	{
		auto card = cards->getChildByName(StringUtils::format("%lu", id));
		MyCard *myCard = dynamic_cast<MyCard *>(card);
		size_t order = myCard->getOrderNum();
		myCard->setOrderNum(order2Place[order]);
	}
}

void Table::cardReleased(MyCard &card)
{
    const Positions &pos = Positions::getPositions();
	log("card %lu released", card.getOrderNum());

	// проверим нахождение в пределах середины стола, сброса и своей руки
	if (pos.changeZone.containsPoint(card.getPosition()))
	{
		size_t newOrderNum = calculateOrderNum(card.getPosition());
		if (newOrderNum != card.getOrderNum())
		{
			sendToServer(StringUtils::format("move %s, %lu; //<-%lu"
					, card.getName().c_str(), newOrderNum, card.getOrderNum()));

			auto order2Place = calculateNewOrder(card.getOrderNum(), newOrderNum);
			changeCardOrder(order2Place);
		}
	}
	else if (pos.tableCenter.containsPoint(card.getPosition()))
	{
		clearShowInfo();
		sendToServer(StringUtils::format("go %s", card.getName().c_str()));
	}
	else if (pos.dropZone.containsPoint(card.getPosition()))
	{
		clearShowInfo();
		sendToServer(StringUtils::format("drop %s", card.getName().c_str()));
	}

	// выбранную карту начать перемещать на место
    auto move = MoveBy::create(1, pos.me + pos.meDelta * card.getOrderNum() - card.getPosition());
    card.runAction(move);

	// все карты, кроме данной вернуть на места
	moveAllInPlaces(card.getOrderNum());
}

void Table::moveAllInPlaces(size_t exceptOrderNum)
{
    const Positions &pos = Positions::getPositions();
	auto cards = getChildByName("cards");
	for (size_t id = 0; id < 5; ++id)
	{
		auto card = cards->getChildByName(StringUtils::format("%lu", id));
		MyCard *myCard = dynamic_cast<MyCard *>(card);
		if (myCard->getOrderNum() != exceptOrderNum)
		{
			myCard->stopAllActions();
			myCard->setPosition(pos.me + pos.meDelta * myCard->getOrderNum());
		}
	}
}

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

Sprite *Table::addCardSprite(const std::string &filename, cocos2d::Vec2 pos, int z)
{
    auto sprite = Sprite::create(filename);
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(pos);
    sprite->setScale(Positions::getPositions().cardSpriteScale);
    this->addChild(sprite, z);
    return sprite;
}

cocos2d::Sprite *Table::loadNumSprite(size_t num)
{
    auto sprite = Sprite::create(StringUtils::format("is_%lu.png", num));
    sprite->setAnchorPoint(Vec2::ZERO);
    //sprite->setScale(Positions::getPositions().cardSpriteScale);
    return sprite;
}

cocos2d::Sprite *Table::loadColorSprite(char c)
{
	std::string color = "red";
	switch(c)
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
    auto sprite = Sprite::create(StringUtils::format("is_%c.png", c));
    sprite->setAnchorPoint(Vec2::ZERO);
    return sprite;
}

Sprite *Table::loadCardSprite(const std::string &image)
{
    auto sprite = Sprite::create(image + ".png");
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
    {
		addCardSprite("card_back.png", pos.deck, -1);

		// оставшеесе количество карт в колоде
		auto deckLabel = Label::createWithBMFont("fonts/number.fnt", "25");
		deckLabel->setPosition(pos.deckLabel);
		deckLabel->setName("deck_label");
		this->addChild(deckLabel);
    }

    // добавить анимацию думания противника
    {
        auto turnNode = Sprite::create("turn.jpg", Rect(0, 0, 96, 96));
        turnNode->setAnchorPoint(Vec2::ZERO);
        turnNode->setPosition(150, 400);
        turnNode->setName("turn_node");
        turnNode->setVisible(false);

        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(10);
        for (size_t i = 0; i < 10; ++i)
        {
            animFrames.pushBack(SpriteFrame::create("turn.jpg", Rect(96 * i, 0, 96, 96)));
        }

        // create the animation out of the frames
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        Animate* animate = Animate::create(animation);

        // run it and repeat it forever
        turnNode->runAction(RepeatForever::create(animate));

        this->addChild(turnNode);
    }

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
			errItem->setName(StringUtils::format("%lu", i));
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
			infoItem->setName(StringUtils::format("%lu", i));
			info->addChild(infoItem, 1);
		}
    }

    // add salutes
	for (size_t i = 0; i < allColors.size(); ++i)
	{
		char c = allColors[i];

		// нарисовать место для карты
		auto colorPlace = addCardSprite("card_face.png", pos.getSalut(c), -2);
		colorPlace->setName(std::string(1, c)); // именем будет буква цвета

		// сверху приделать цветную рамку
	    auto sprite = Sprite::create(StringUtils::format("is_%c.png", c));
	    sprite->setAnchorPoint(Vec2::ZERO);
	    sprite->setPosition(Vec2::ZERO);
	    colorPlace->addChild(sprite, 1);
	}

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
			//this->newGame();
		});
		labelItem->setPosition(Vec2(50, 150));

		auto label1 = Label::createWithSystemFont("Drop", "Arial", 48);
		MenuItemLabel *labelItem1 = MenuItemLabel::create(label1,[&](Ref* sender){
			this->dropAll();
		});
		labelItem1->setPosition(Vec2(50, 100));

		auto label2 = Label::createWithSystemFont("Step", "Arial", 48);
		MenuItemLabel *labelItem2 = MenuItemLabel::create(label2,[&](Ref* sender){
			this->cmdNext();
		});
		labelItem2->setPosition(Vec2(50, 50));

		auto menuLabel = Menu::create(labelItem, labelItem1, labelItem2, nullptr);
		menuLabel->setPosition(Vec2::ZERO);
		this->addChild(menuLabel, 20);
    }

    // create opponent menu
    {
    	Vector<MenuItem *> arrayOfItems;

    	for (size_t i = 0; i < 5; ++i)
    	{
			auto opponentItem = MenuItemImage::create("card_back.png", "card_back.png", [=](Ref* sender){
				this->opponentTouched(i);
			});
			opponentItem->setPosition(pos.opponent + pos.opponentDelta * i);
			opponentItem->setAnchorPoint(Vec2::ZERO);
			opponentItem->setScale(pos.cardSpriteScale);
			opponentItem->setOpacity(0);

			arrayOfItems.pushBack(opponentItem);
    	}

		auto menu = Menu::createWithArray(arrayOfItems);
		menu->setPosition(Vec2::ZERO);
		addChild(menu, 20);
    }

    // открыть файл эмулятора команд от сервера
    cmdEmulator = new std::ifstream("Resources/cmd_emulator.txt");

    // добавить заник
    {
    	Size visibleSize = Director::getInstance()->getVisibleSize();
    	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    	auto sprite = Sprite::create("bg.jpg");
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
                origin.y + visibleSize.height / 2));
		sprite->setScale(Positions::getPositions().bgScale);
		this->addChild(sprite, -100);
    }

    return true;
}

void Table::infoNumTouched(size_t num)
{
	log("info '%lu' touched", num);
	clearShowInfo();
	sendToServer(StringUtils::format("info %lu;", num));
	removeChildByName("info_menu");
}

void Table::infoColorTouched(char c)
{
	log("info '%c' touched", c);
	clearShowInfo();
	sendToServer(StringUtils::format("info %c;", c));
	removeChildByName("info_menu");
}

void Table::opponentTouched(size_t orderNum)
{
	const Positions &pos = Positions::getPositions();
	log("opponent %lu touched", orderNum);

	// удалить такое меню, если оно уже есть
	removeChildByName("info_menu");

	// создать айтемы номеров
	Vector<MenuItem *> arrayOfItems;
	for (size_t i = 0; i < 5; ++i)
	{
		auto numItem = MenuItemImage::create("card_face.png", "card_face.png", [=](Ref* sender){
			this->infoNumTouched(i + 1);
		});
		numItem->setPosition(pos.numMenu + pos.numMenuDelta * i);
		numItem->setAnchorPoint(Vec2::ZERO);
		numItem->setScale(pos.cardSpriteScale);

		// приделать цифру
		auto numSprite = loadNumSprite(i + 1);
		numItem->addChild(numSprite, 1);

		arrayOfItems.pushBack(numItem);
	}

	// создать айтемы цветов
	for (size_t i = 0; i < allColors.size(); ++i)
	{
		auto numItem = MenuItemImage::create("card_face.png", "card_face.png", [=](Ref* sender){
			this->infoColorTouched(allColors[i]);
		});
		numItem->setPosition(pos.colorMenu + pos.colorMenuDelta * i);
		numItem->setAnchorPoint(Vec2::ZERO);
		numItem->setScale(pos.cardSpriteScale);

		// приделать цвет
		auto numSprite = loadColorSprite(allColors[i]);
		numItem->addChild(numSprite, 1);

		arrayOfItems.pushBack(numItem);
	}

	// создать меню и добавить его на стол
	auto menu = Menu::createWithArray(arrayOfItems);
	menu->setPosition(Vec2::ZERO);
	menu->setName("info_menu");
	addChild(menu, 30);
}

void Table::drop(size_t id, char c, size_t serial)
{
	const Positions &pos = Positions::getPositions();

	auto cards = getChildByName("cards");
	auto card = cards->getChildByName(StringUtils::format("%lu", id));
	card->setName("");

	Vec2 dropPos = pos.getDrop(c);
	Vec2 dropDelta = pos.getDropDelta(c);
	Vec2 res = dropPos + dropDelta * serial;

	card->stopAllActions();
    auto move = MoveTo::create(1, res);
    card->runAction(move);

    auto scale = ScaleTo::create(1, pos.dropScale);
    card->runAction(scale);
}

void Table::dropOp(size_t id, char c, size_t serial)
{
	const Positions &pos = Positions::getPositions();

	auto cards = getChildByName("cards");
	auto card = cards->getChildByName(StringUtils::format("o%lu", id));
	card->setName("");

	Vec2 dropPos = pos.getDrop(c);
	Vec2 dropDelta = pos.getDropDelta(c);
	Vec2 res = dropPos + dropDelta * serial;

	card->stopAllActions();
    auto move = MoveTo::create(1, res);
    card->runAction(move);

    auto scale = ScaleTo::create(1, pos.dropScale);
    card->runAction(scale);
}

void Table::takeDropTest(const std::string &image, char color, size_t serial)
{
	take1(0, image, 0);
	dropOp(0, color, serial);
}

void Table::dropAll()
{
	log("drop");

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

void Table::take1(size_t orderNum, const std::string &image, size_t id)
{
	const Positions &pos = Positions::getPositions();

	Sprite *card = loadCardSprite(image);
	card->setPosition(pos.deck);
	card->setName(StringUtils::format("o%lu", id));

	auto cards = getChildByName("cards");
	cards->addChild(card);

    auto move = MoveBy::create(1, pos.opponent + pos.opponentDelta * orderNum - pos.deck);
    card->runAction(move);
}

void Table::cmdNext()
{
	std::string line;
	do
	{
		std::getline(*cmdEmulator, line);
		cmdFromServer(line.c_str());
	} while (!line.empty());
}

void Table::cmdFromServer(const std::string &cmd)
{
	const char *p = cmd.c_str();
	size_t id, serial, colorQty, orderNum, qty, side, num;
	char c[128];
	char image[128];
	char orderMask[128];
	log("cmd from server: '%s'", p);

	if (sscanf(p, "new_game %lu;", &colorQty) == 1)
	{
		newGame(colorQty);
	}
	else if (sscanf(p, "take %lu, %lu;", &id, &orderNum) == 2)
	{
		take(id, orderNum);
	}
	else if (sscanf(p, "takeOp %lu, %lu;", &id, &orderNum) == 2)
	{
		takeOp(id, orderNum);
	}
	else if (sscanf(p, "reveal %lu, %[rbgywf1-5];", &id, image) == 2)
	{
		reveal(id, image);
	}
	else if (sscanf(p, "revealDeck %[rbgywf1-5];", image) == 1)
	{
		revealDeck(image);
	}
	else if (sscanf(p, "drop %lu, %[rgbywf], %lu;", &id, c, &serial) == 3)
	{
		drop(id, c[0], serial);
	}
	else if (sscanf(p, "dropOp %lu, %[rgbywf], %lu;", &id, c, &serial) == 3)
	{
		dropOp(id, c[0], serial);
	}
	else if (sscanf(p, "info %lu;", &qty) == 1)
	{
		info(qty);
	}
	else if (sscanf(p, "err %lu;", &qty) == 1)
	{
		err(qty);
	}
	else if (sscanf(p, "deck %lu;", &qty) == 1)
	{
		deck(qty);
	}
	else if (sscanf(p, "turn %lu;", &side) == 1)
	{
		turn(side);
	}
	else if (sscanf(p, "show %lu, %[01];", &num, orderMask) == 2)
	{
		showNum(num, orderMask);
	}
	else
	{
		log("unknown cmd from server: '%s'", p);
	}
}

const std::vector<char> Table::allColors = {'r', 'g', 'b', 'y', 'w', 'f'};

void Table::newGame(size_t colorQty)
{
	for (size_t i = 0; i < allColors.size(); ++i)
	{
		char c = allColors[i];
		auto colorPlace = getChildByName(std::string(1, c));
		colorPlace->setVisible(i < colorQty);
	}
}

void Table::take(size_t id, size_t orderNum)
{
	const Positions &pos = Positions::getPositions();

    auto card = new MyCard("card_back.png", orderNum, *this);
    card->setAnchorPoint(Vec2::ZERO);
    card->setScale(Positions::getPositions().cardSpriteScale);
	card->setPosition(pos.deck);
	card->setName(StringUtils::format("%lu", id));

	auto cards = getChildByName("cards");
	cards->addChild(card);

    auto move = MoveBy::create(1, pos.me + pos.meDelta * orderNum - pos.deck);
    card->runAction(move);
}

void Table::takeOp(size_t id, size_t orderNum)
{
	const Positions &pos = Positions::getPositions();

	auto cards = getChildByName("cards");
	auto deckCard = cards->getChildByName("deck"); // карта должна быть предварительно предъявлена : revealDeck()
	deckCard->setName(StringUtils::format("o%lu", id));

    auto move = MoveBy::create(1, pos.opponent + pos.opponentDelta * orderNum - pos.deck);
    deckCard->runAction(move);
}

void Table::reveal(size_t id, const std::string &image)
{
	// расставим все по своим местам на случай, если передвигали в это время
	moveAllInPlaces(100); //всех расставить

	auto cards = getChildByName("cards");
	auto card = cards->getChildByName(StringUtils::format("%lu", id));
	MyCard *myCard = dynamic_cast<MyCard *>(card);

	// заменить картинку
	myCard->reinit(StringUtils::format("%s.png", image.c_str()));
	myCard->setDragEnabled(false);
}

void Table::revealDeck(const std::string &image)
{
	const Positions &pos = Positions::getPositions();

	// создать карту и установить на колоду
	Sprite *card = loadCardSprite(image);
	card->setPosition(pos.deck);
	card->setName("deck");

	// добавить в контейнер карт
	auto cards = getChildByName("cards");
	cards->addChild(card);
}

void Table::info(size_t qty)
{
	auto info = getChildByName("info");

	for (size_t i = 0; i < 8; ++i)
	{
		auto infoItem = info->getChildByName(StringUtils::format("%lu", i));
		infoItem->setVisible(i < qty);
	}
}

void Table::err(size_t qty)
{
	auto info = getChildByName("err");

	for (size_t i = 0; i < 3; ++i)
	{
		auto infoItem = info->getChildByName(StringUtils::format("%lu", i));
		infoItem->setVisible(i < qty);
	}
}

void Table::deck(size_t qty)
{
	auto node = getChildByName("deck_label");
	Label *deckLabel = dynamic_cast<Label *>(node);
	deckLabel->setString(StringUtils::format("%lu", qty));
}

void Table::turn(size_t side)
{
	auto node = getChildByName("turn_node");
	node->setVisible(side);
}

void Table::showNum(size_t num, const std::string &orderMask)
{
	clearShowInfo();

	auto cards = getChildByName("cards");
	for (size_t id = 0; id < 5; ++id)
	{
		auto card = cards->getChildByName(StringUtils::format("%lu", id));
		MyCard *myCard = dynamic_cast<MyCard *>(card);

		// приделать is_2.png
	    auto spriteIs = Sprite::create(StringUtils::format("is_%lu.png", num));
	    spriteIs->setAnchorPoint(Vec2::ZERO);
	    spriteIs->setPosition(Vec2::ZERO);
	    spriteIs->setName("info");
	    myCard->addChild(spriteIs, 1);

		if (orderMask.at(myCard->getOrderNum()) != '1')
		{
			// приделать no.png
		    auto spriteNo = Sprite::create("no.png");
		    spriteNo->setAnchorPoint(Vec2::ZERO);
		    spriteNo->setPosition(Vec2::ZERO);
		    spriteIs->addChild(spriteNo, 1);
		}
	}
}

void Table::clearShowInfo()
{
	auto cards = getChildByName("cards");
	for (size_t id = 0; id < 5; ++id)
	{
		auto card = cards->getChildByName(StringUtils::format("%lu", id));
		card->removeChildByName("info");
	}
}
