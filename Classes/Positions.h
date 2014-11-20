#ifndef POSITIONS_H_INCLUDED
#define POSITIONS_H_INCLUDED

/**
 *
 * Класс, который инкапсулирует расстановку спрайтов (карт и т.д.) по игровому столу.
 * Есть синглтон, который делает доступным расстановку. Но только по константной ссылке.
 * Если не указано, то привязка идет по левому нижнему углу
 * Буква F (Flash) используется для обозначения радужного цвета.
 *
 * Размер экрана фиксирован как 1136х640. Это соответствует разрешению iphone5.
 * Задаётся этот размер в AppDelegate.cpp
 */

#include <math/Vec2.h>

struct Positions
{
	cocos2d::Vec2 deck; // колода

	cocos2d::Vec2 err; // центр верхнего жетона ошибки
	cocos2d::Vec2 errDelta; // дельта до следующего жетона
	float errScale;

	cocos2d::Vec2 info; // центр верхнего жетона подсказки
	cocos2d::Vec2 infoDelta; // дельта до следующего жетона
	float infoScale;

	float cardSpriteScale; // scale для всех полноразмерных карт (и включённых изображений)

	// места для салютов
	cocos2d::Vec2 salutR;
	cocos2d::Vec2 salutG;
	cocos2d::Vec2 salutB;
	cocos2d::Vec2 salutY;
	cocos2d::Vec2 salutW;
	cocos2d::Vec2 salutF;

	// своя рука
	cocos2d::Vec2 me; // первая моя карта
	cocos2d::Vec2 meDelta; // смещение следующей карты

	// оппонент
	cocos2d::Vec2 opponent; // первая карта оппонента
	cocos2d::Vec2 opponentDelta; // смещение следующей карты

	// сброс
	float dropScale; // scale для сброса
	cocos2d::Vec2 dropR; // первая карта сброса красных
	cocos2d::Vec2 dropRDelta; // смещение до следующей
	cocos2d::Vec2 dropG;
	cocos2d::Vec2 dropGDelta;
	cocos2d::Vec2 dropB;
	cocos2d::Vec2 dropBDelta;
	cocos2d::Vec2 dropY;
	cocos2d::Vec2 dropYDelta;
	cocos2d::Vec2 dropW;
	cocos2d::Vec2 dropWDelta;
	cocos2d::Vec2 dropF;
	cocos2d::Vec2 dropFDelta;

	// zones
	cocos2d::Rect tableCenter; // зона, отпускание в которой считается ходом
	cocos2d::Rect dropZone; // зона, отпускание в которой считается сбросом
	cocos2d::Rect changeZone; // зона, перемещение в которой приводит к изменению мест карт

	// меню выбора инфы
	cocos2d::Vec2 numMenu; // первый пункт меню выбора номиналов
	cocos2d::Vec2 numMenuDelta; // смещения следующего пункта меню выбора номиналов
	cocos2d::Vec2 colorMenu; // первый пункт меню выбора цветов
	cocos2d::Vec2 colorMenuDelta; // смещения следующего пункта меню выбора цветов

	static const Positions &getPositions();
};

#endif /* #ifndef POSITIONS_H_INCLUDED */
