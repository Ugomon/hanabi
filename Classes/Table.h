#ifndef __TABLE_H__
#define __TABLE_H__

#include "cocos2d.h"
#include <vector>
#include <iostream>
#include <sstream>

/**
 * Сцена, которая отображает игровой стол.
 *
 * Сцена обращается к классу Positions для определения координат всевозможных объектов на столе.
 *
 * Существует класс Server. Server ответственнен за всю логику игры.
 * Серверу можно отослать запрос на выполнение действия в игре.
 * Сервер присылает команды по изменению игрового стола классу TableScene; их надо выполнить.
 * Пример команды: "количество подсказок стало 5", "оппонент сбросил указанную карту". Подробнее см. в классе Server.
 * ВАЖНО! Этот класс не перепроверяет верность команд полученных от сервера.
 * Если команду невозможно выполнить (например: 2 раза подряд сбросить карту #2) - это нештатная ситуация
 * (надо написать сообщение об ошибке в лог и, возможно, на экран).
 *
 * Подробности см. в описании класса Server
 *
 * В будущем (для 3х и более оппонентов) будет нужна комманда "показать информацию, которую сообщили оппоненту".
 * При этом нужно показывать ЧТО и про какие карты сказали. Сейчас этого не будет реализовано.
 *
 * Для изменения сцены ключевые ноды именуются. Вот перечень именовынных нодов.
 * "err" - все жетоны ошибок; спрайты ошибок подвешены к этому ноду с именами 0,1,2
 * "info" - все жетоны подсказок; спрайты подсказок подвешены к этому ноду с именами 0,1,2,3,4,5,6,7
 * "cards" - все карты взятые из колоды подвешиваются к этому ноду; для очистки стола достаточно удалить всех чилдов у этого нода
 *     "o0",..,"o4" - карты на руках у оппонента
 *     "0",..,"4" - карты в моей руке
 *         "info" - информация о моей карте
 *     "deck" - уже открытая карта, которая лежит на вершине колоды; приделана к "cards"
 *     "top_r" - верхняя карта красного салюта
 * "deck_label" - надпись с количеством оставшихся карт
 * "turn_node" - анимация думания
 * "r", "g",..., "f" - места для цветов в центре стола
 *
 * Терминология.
 * image - текст вида: "r2" или "w5". Однозначно определяет изображение карты.
 * id - идентификатор карты на руке; от 0 до 4. Используется для простого однозначного указания на карту в моей руке или руке оппонента.
 * orderNum - порядковый номер карты в руке; от 0 до 4. Используется для указания, с какой позиции надо забрать карту.
 * 				Сервер обязан знать эту информацию (чтобы сообщать ее другим игрокам). Поэтому решено не хранить ее в спрайте, а каждый раз получать от сервера.
 * serial - порядковый номер позиции в столбце сброса определенного цвета; нумерация начинается с 0.
 *
 * Карты в своей руке сделаны перетаскиваемыми спрайтами.
 * Это основной элемент управления игрой.
 * Действия в игре:
 * .) переставить свою карту на другое место
 * .) перетащить свою карту в центр (означает сделать ход этой картой)
 * .) перетащить свою карту в сброс (означает сбросить эту карту)
 * .) сообщить информацию
 *
 * Действие "сообщить информацию" начинается с клика по карте оппонента.
 * Появляется меню с цветом и номиналом выбранной карты.
 * Позже надо сделать дополнительную кнопку открывающую меню со всеми цветами и номиналами для выбора. Чтобы можно было сказать: "у тебя нет красных".
 *
 * Сказанная мне информация отображается на моих картах, пока я не сделаю ход (перемещение карт не считается ходом).
 */

class MyCard;

class Table : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // сообщения от дочерних нодов
    void cardPositionChanged(MyCard &draggingCard, cocos2d::Vec2 oldPos); // карту подвинули
    void cardReleased(MyCard &card); // карту отпустили

    // implement the "static create()" method manually
    CREATE_FUNC(Table);

    //
    static const std::vector<char> allColors; // символы цветов в стандартном порядке
    static bool isAllZero(const std::string &str); // вернет true, если в строке - все символы == '0'

protected:
    // стандартное добавление безимянных спрайтов на стол
    cocos2d::Sprite *addCardSprite(const std::string &filename, cocos2d::Vec2 pos, int z);

    // получить спрайт карты по image
    cocos2d::Sprite *loadCardSprite(const std::string &image);

    // получить спрайт карты по цифре
    cocos2d::Sprite *loadNumSprite(size_t num);

    // получить спрайт карты по цвету
    cocos2d::Sprite *loadColorSprite(char c);

    // выполнение команд полученных от сервера (управляющие функции)
    void cmdFromServer(const std::string &cmd); // полученную команду распарсить и отправить на выполнение
    void cmdNext(); // выполнить следующую команду из файла. Используется для тестов.
    void take1(size_t orderNum, const std::string &image, size_t id); // оппонент берет карту из колоды
    void dropAll(); // заполнить весь сброс (функция для тестов)
    void takeDropTest(const std::string &image, char color, size_t serial);
    void clearShowInfo(); // удалить отображение информации о моих картах
    void moveAllInPlacesOp(); // расставить все карты оппонента по местам
    void layCard(cocos2d::Node *card, char c); // выложить указанную указанную карту в салют <c>

    // обработка команд от сервера
    void newGame(size_t colorQty); // Очистить стол для новой игры. colorQty - количество цветов в новой игре.
    void take(size_t id, size_t orderNum); // я взял карту из колоды
    void takeOp(size_t id, size_t orderNum); // оппонент взял карту из колоды
    void reveal(size_t id, const std::string &image); // открыть свою карту
    void revealDeck(const std::string &image); // открыть верхнюю карту в колоде
    void drop(size_t id, char c, size_t serial); // я сбросил указанную карту; и положить ее надо в сброс по указонному адресу
    void dropOp(size_t id, char c, size_t serial); // оппонент сбросил указанную карту; и положить ее надо в сброс по указонному адресу
    void info(size_t qty); // количество подсказок стало qty
    void err(size_t qty); // количество ошибок стало qty
    void deck(size_t qty); // в деке осталось qty карт
    void turn(size_t side); // Сейчас ход: 0 - мой, 1 - оппонента.
    void showNum(size_t num, const std::string &orderMask); // показать, где у меня расположены карты достоинством num (orderMask: '00101')
    void showColor(char c, const std::string &orderMask); // показать, где у меня расположены карты цвета c (orderMask: '00101')
    void moveOp(size_t id, size_t newOrderNum); // оппонент передвинул карту id на позицию newOrderNum
    void move(size_t id, size_t newOrderNum); // я передвинул карту id на позицию newOrderNum
    void lay(size_t id, char c); // я выложил указанную указанную карту в салют <c>
    void layOp(size_t id, char c); // оппонент выложил указанную указанную карту в салют <c>
    void gameOver(size_t score); // игра закончена, счет: score

    // отослать команду серверу
    void sendToServer(const std::string &cmd);

    // управление своими картами при перетаскивании
    void moveAllInPlaces(size_t exceptOrderNum, bool immediately = true); // расставить свои карты по своим местам
    static size_t calculateOrderNum(cocos2d::Vec2 cardPos); // вычисляет порядковый номер карты в руке по её положению
    static std::vector<size_t> calculateNewOrder(size_t oldOrderNum, size_t newOrderNum); // возвращает массив с указанием новый мест для карты, для случая, когда карта oldOrderNum переместилась в позицию newOrderNum

    // сообщение информации
    void opponentTouched(size_t orderNum); // кликнута карта оппонента с порядковым номером orderNum
    void infoNumTouched(size_t num); // кликнуто меню: сообщить инфу об указанном номинале
    void infoColorTouched(char c); // кликнуто меню: сообщить инфу об указанном цвете

private:
	std::string cmdData; // строка с данными для эмуляции
    std::istringstream *cmdEmulator; // файл с командами для эмуляции сервера
};

#endif // __TABLE_H__
