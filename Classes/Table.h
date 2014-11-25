#ifndef __TABLE_H__
#define __TABLE_H__

#include "cocos2d.h"
#include <vector>
#include <iostream>

/**
 * �����, ������� ���������� ������� ����.
 *
 * ����� ���������� � ������ Positions ��� ����������� ��������� ������������ �������� �� �����.
 *
 * ���������� ����� Server. Server ������������� �� ��� ������ ����.
 * ������� ����� �������� ������ �� ���������� �������� � ����.
 * ������ ��������� ������� �� ��������� �������� ����� ������ TableScene; �� ���� ���������.
 * ������ �������: "���������� ��������� ����� 5", "�������� ������� ��������� �����". ��������� ��. � ������ Server.
 * �����! ���� ����� �� ������������� �������� ������ ���������� �� �������.
 * ���� ������� ���������� ��������� (��������: 2 ���� ������ �������� ����� #2) - ��� ��������� ��������
 * (���� �������� ��������� �� ������ � ��� �, ��������, �� �����).
 *
 * ����������� ��. � �������� ������ Server
 *
 * � ������� (��� 3� � ����� ����������) ����� ����� �������� "�������� ����������, ������� �������� ���������".
 * ��� ���� ����� ���������� ��� � ��� ����� ����� �������. ������ ����� �� ����� �����������.
 *
 * ��� ��������� ����� �������� ���� ���������. ��� �������� ����������� �����.
 * "err" - ��� ������ ������; ������� ������ ��������� � ����� ���� � ������� 0,1,2
 * "info" - ��� ������ ���������; ������� ��������� ��������� � ����� ���� � ������� 0,1,2,3,4,5,6,7
 * "cards" - ��� ����� ������ �� ������ ������������� � ����� ����; ��� ������� ����� ���������� ������� ���� ������ � ����� ����
 *     "o0",..,"o4" - ����� �� ����� � ���������
 *     "0",..,"4" - ����� � ���� ����
 *         "info" - ���������� � ���� �����
 *     "deck" - ��� �������� �����, ������� ����� �� ������� ������; ��������� � "cards"
 *     "top_r" - ������� ����� �������� ������
 * "deck_label" - ������� � ����������� ���������� ����
 * "turn_node" - �������� �������
 * "r", "g",..., "f" - ����� ��� ������ � ������ �����
 *
 * ������������.
 * image - ����� ����: "r2" ��� "w5". ���������� ���������� ����������� �����.
 * id - ������������� ����� �� ����; �� 0 �� 4. ������������ ��� �������� ������������ �������� �� ����� � ���� ���� ��� ���� ���������.
 * orderNum - ���������� ����� ����� � ����; �� 0 �� 4. ������������ ��� ��������, � ����� ������� ���� ������� �����.
 * 				������ ������ ����� ��� ���������� (����� �������� �� ������ �������). ������� ������ �� ������� �� � �������, � ������ ��� �������� �� �������.
 * serial - ���������� ����� ������� � ������� ������ ������������� �����; ��������� ���������� � 0.
 *
 * ����� � ����� ���� ������� ���������������� ���������.
 * ��� �������� ������� ���������� �����.
 * �������� � ����:
 * .) ����������� ���� ����� �� ������ �����
 * .) ���������� ���� ����� � ����� (�������� ������� ��� ���� ������)
 * .) ���������� ���� ����� � ����� (�������� �������� ��� �����)
 * .) �������� ����������
 *
 * �������� "�������� ����������" ���������� � ����� �� ����� ���������.
 * ���������� ���� � ������ � ��������� ��������� �����.
 * ����� ���� ������� �������������� ������ ����������� ���� �� ����� ������� � ���������� ��� ������. ����� ����� ���� �������: "� ���� ��� �������".
 *
 * ��������� ��� ���������� ������������ �� ���� ������, ���� � �� ������ ��� (����������� ���� �� ��������� �����).
 */

class MyCard;

class Table : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // ��������� �� �������� �����
    void cardPositionChanged(MyCard &draggingCard, cocos2d::Vec2 oldPos); // ����� ���������
    void cardReleased(MyCard &card); // ����� ���������

    // implement the "static create()" method manually
    CREATE_FUNC(Table);

    //
    static const std::vector<char> allColors; // ������� ������ � ����������� �������
    
protected:
    // ����������� ���������� ���������� �������� �� ����
    cocos2d::Sprite *addCardSprite(const std::string &filename, cocos2d::Vec2 pos, int z);

    // �������� ������ ����� �� image
    cocos2d::Sprite *loadCardSprite(const std::string &image);

    // �������� ������ ����� �� �����
    cocos2d::Sprite *loadNumSprite(size_t num);

    // �������� ������ ����� �� �����
    cocos2d::Sprite *loadColorSprite(char c);

    // ���������� ������ ���������� �� ������� (����������� �������)
    void cmdFromServer(const std::string &cmd); // ���������� ������� ���������� � ��������� �� ����������
    void cmdNext(); // ��������� ��������� ������� �� �����. ������������ ��� ������.
    void take1(size_t orderNum, const std::string &image, size_t id); // �������� ����� ����� �� ������
    void dropAll(); // ��������� ���� ����� (������� ��� ������)
    void takeDropTest(const std::string &image, char color, size_t serial);
    void clearShowInfo(); // ������� ����������� ���������� � ���� ������
    void moveAllInPlacesOp(); // ���������� ��� ����� ��������� �� ������
    void layCard(cocos2d::Node *card, char c); // �������� ��������� ��������� ����� � ����� <c>

    // ��������� ������ �� �������
    void newGame(size_t colorQty); // �������� ���� ��� ����� ����. colorQty - ���������� ������ � ����� ����.
    void take(size_t id, size_t orderNum); // � ���� ����� �� ������
    void takeOp(size_t id, size_t orderNum); // �������� ���� ����� �� ������
    void reveal(size_t id, const std::string &image); // ������� ���� �����
    void revealDeck(const std::string &image); // ������� ������� ����� � ������
    void drop(size_t id, char c, size_t serial); // � ������� ��������� �����; � �������� �� ���� � ����� �� ���������� ������
    void dropOp(size_t id, char c, size_t serial); // �������� ������� ��������� �����; � �������� �� ���� � ����� �� ���������� ������
    void info(size_t qty); // ���������� ��������� ����� qty
    void err(size_t qty); // ���������� ������ ����� qty
    void deck(size_t qty); // � ���� �������� qty ����
    void turn(size_t side); // ������ ���: 0 - ���, 1 - ���������.
    void showNum(size_t num, const std::string &orderMask); // ��������, ��� � ���� ����������� ����� ������������ num (orderMask: '00101')
    void showColor(char c, const std::string &orderMask); // ��������, ��� � ���� ����������� ����� ����� c (orderMask: '00101')
    void moveOp(size_t id, size_t newOrderNum); // �������� ���������� ����� id �� ������� newOrderNum
    void move(size_t id, size_t newOrderNum); // � ���������� ����� id �� ������� newOrderNum
    void lay(size_t id, char c); // � ������� ��������� ��������� ����� � ����� <c>
    void layOp(size_t id, char c); // �������� ������� ��������� ��������� ����� � ����� <c>
    void gameOver(size_t score); // ���� ���������, ����: score

    // �������� ������� �������
    void sendToServer(const std::string &cmd);

    // ���������� ������ ������� ��� ��������������
    void moveAllInPlaces(size_t exceptOrderNum, bool immediately = true); // ���������� ���� ����� �� ����� ������
    static size_t calculateOrderNum(cocos2d::Vec2 cardPos); // ��������� ���������� ����� ����� � ���� �� � ���������
    static std::vector<size_t> calculateNewOrder(size_t oldOrderNum, size_t newOrderNum); // ���������� ������ � ��������� ����� ���� ��� �����, ��� ������, ����� ����� oldOrderNum ������������� � ������� newOrderNum

    // ��������� ����������
    void opponentTouched(size_t orderNum); // �������� ����� ��������� � ���������� ������� orderNum
    void infoNumTouched(size_t num); // �������� ����: �������� ���� �� ��������� ��������
    void infoColorTouched(char c); // �������� ����: �������� ���� �� ��������� �����

private:
    std::istream *cmdEmulator; // ���� � ��������� ��� �������� �������
};

#endif // __TABLE_H__
