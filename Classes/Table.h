#ifndef __TABLE_H__
#define __TABLE_H__

#include "cocos2d.h"
#include <vector>

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
 * � ������� (��� 3� � ����� ����������) ����� ����� �������� "�������� ����������, ������� �������� ���������".
 * ��� ���� ����� ���������� ��� � ��� ����� ����� �������. ������ ����� �� ����� �����������.
 *
 * ��� ��������� ����� �������� ���� ���������. ��� �������� ����������� �����.
 * "err" - ��� ������ ������; ������� ������ ��������� � ����� ���� � ������� 0,1,2
 * "info" - ��� ������ ���������; ������� ��������� ��������� � ����� ���� � ������� 0,1,2,3,4,5,6,7
 * "cards" - ��� ����� ������ �� ������ ������������� � ����� ����; ��� ������� ����� ���������� ������� ���� ������ � ����� ����
 * "o0",..,"o4" - ����� �� ����� � ���������
 * "0",..,"4" - ����� � ���� ����
 *
 * ������������.
 * image - ����� ����: "r2" ��� "w5". ���������� ���������� ����������� �����.
 * id - ������������� ����� �� ����; �� 0 �� 4. ������������ ��� �������� ������������ �������� �� ����� � ���� ���� ��� ���� ���������.
 * orderNum - ���������� ����� ����� � ����; �� 0 �� 4. ������������ ��� ��������, � ����� ������� ���� ������� �����.
 * 				������ ������ ����� ��� ���������� (����� �������� �� ������ �������). ������� ������ �� ������� �� � �������, � ������ ��� �������� �� �������.
 * serial - ���������� ����� ������� � ������� ������; ��������� ���������� � 0.
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

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // ����������� ���������� ���������� �������� �� ����
    void addCardSprite(const std::string &filename, cocos2d::Vec2 pos, int z);

    // �������� ������ ����� �� image
    cocos2d::Sprite *loadCardSprite(const std::string &image);

    // �������� ������ ����� �� �����
    cocos2d::Sprite *loadNumSprite(size_t num);

    // �������� ������ ����� �� �����
    cocos2d::Sprite *loadColorSprite(char c);

    // ���������� ������ ���������� �� �������
    void newGame();
    void take(size_t orderNum, size_t id); // � ���� ����� �� ������
    void take1(size_t orderNum, const std::string &image, size_t id); // �������� ����� ����� �� ������
    void drop1(size_t id, char color, size_t serial); // �������� ������� ��������� �����; � �������� �� ���� � ����� �� ���������� ������
    void deck(size_t qty); // � ���� �������� qty ����
    void takeDropTest(const std::string &image, char color, size_t serial);

    // �������� ������� �������
    void sendToServer(const std::string &cmd);

    // ��������� �� �������� �����
    void cardPositionChanged(MyCard &draggingCard, cocos2d::Vec2 oldPos); // ����� ���������
    void cardReleased(MyCard &card); // ����� ���������

    // ���������� ������ ������� ��� ��������������
    void moveAllInPlaces(size_t exceptOrderNum); // ���������� ���� ����� �� ����� ������
    static size_t calculateOrderNum(cocos2d::Vec2 cardPos); // ��������� ���������� ����� ����� � ���� �� � ���������
    std::vector<size_t> calculateNewOrder(size_t oldOrderNum, size_t newOrderNum); // ���������� ������ � ��������� ����� ���� ��� �����, ��� ������, ����� ����� oldOrderNum ������������� � ������� newOrderNum
    void changeCardOrder(const std::vector<size_t> &order2Place); // ������ orderNum ���� ������ ����� ���� ���, ��� �������� � ������������ ���������

    // ��������� ����������
    void opponentTouched(size_t orderNum); // �������� ����� ��������� � ���������� ������� orderNum
    void infoNumTouched(size_t num); // �������� ����: �������� ���� �� ��������� ��������
    void infoColorTouched(char c); // �������� ����: �������� ���� �� ��������� �����

    // implement the "static create()" method manually
    CREATE_FUNC(Table);
};

#endif // __TABLE_H__
