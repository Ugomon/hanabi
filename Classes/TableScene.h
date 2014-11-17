#ifndef __TABLE_SCENE_H__
#define __TABLE_SCENE_H__

#include "cocos2d.h"

// id ����� - ��� ����� "R2, W5".

class TableScene : public cocos2d::Layer
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

    // �������� ������ ����� �� id
    cocos2d::Sprite *loadCardSprite(const std::string &id);

    // ���������� ������ ���������� �� �������
    void newGame();
    void take(size_t orderNum); // � ���� ����� �� ������
    void take1(size_t orderNum, const std::string &id, size_t name); // �������� ����� ����� �� ������
    void drop1(size_t name, char color, size_t serial); // �������� ������� ��������� �����; � �������� �� ���� � ����� �� ���������� ������
    void deck(size_t qty); // � ���� �������� qty ����
    void takeDropTest(const std::string &id, char color, size_t serial);

    // implement the "static create()" method manually
    CREATE_FUNC(TableScene);
};

#endif // __TABLE_SCENE_H__
