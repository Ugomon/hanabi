#ifndef POSITIONS_H_INCLUDED
#define POSITIONS_H_INCLUDED

/**
 *
 * �����, ������� ������������� ����������� �������� (���� � �.�.) �� �������� �����.
 * ���� ��������, ������� ������ ��������� �����������. �� ������ �� ����������� ������.
 * ���� �� �������, �� �������� ���� �� ������ ������� ����
 * ����� F (Flash) ������������ ��� ����������� ��������� �����.
 *
 * ������ ������ ���������� ��� 1136�640. ��� ������������� ���������� iphone5.
 * ������� ���� ������ � AppDelegate.cpp
 */

#include <math/Vec2.h>

struct Positions
{
	cocos2d::Vec2 deck; // ������

	cocos2d::Vec2 err; // ����� �������� ������ ������
	cocos2d::Vec2 errDelta; // ������ �� ���������� ������
	float errScale;

	cocos2d::Vec2 info; // ����� �������� ������ ���������
	cocos2d::Vec2 infoDelta; // ������ �� ���������� ������
	float infoScale;

	float cardSpriteScale; // scale ��� ���� �������������� ���� (� ���������� �����������)

	// ����� ��� �������
	cocos2d::Vec2 salutR;
	cocos2d::Vec2 salutG;
	cocos2d::Vec2 salutB;
	cocos2d::Vec2 salutY;
	cocos2d::Vec2 salutW;
	cocos2d::Vec2 salutF;

	// ���� ����
	cocos2d::Vec2 me; // ������ ��� �����
	cocos2d::Vec2 meDelta; // �������� ��������� �����

	// ��������
	cocos2d::Vec2 opponent; // ������ ����� ���������
	cocos2d::Vec2 opponentDelta; // �������� ��������� �����

	// �����
	float dropScale; // scale ��� ������
	cocos2d::Vec2 dropR; // ������ ����� ������ �������
	cocos2d::Vec2 dropRDelta; // �������� �� ���������
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
	cocos2d::Rect tableCenter; // ����, ���������� � ������� ��������� �����
	cocos2d::Rect dropZone; // ����, ���������� � ������� ��������� �������
	cocos2d::Rect changeZone; // ����, ����������� � ������� �������� � ��������� ���� ����

	// ���� ������ ����
	cocos2d::Vec2 numMenu; // ������ ����� ���� ������ ���������
	cocos2d::Vec2 numMenuDelta; // �������� ���������� ������ ���� ������ ���������
	cocos2d::Vec2 colorMenu; // ������ ����� ���� ������ ������
	cocos2d::Vec2 colorMenuDelta; // �������� ���������� ������ ���� ������ ������

	static const Positions &getPositions();
};

#endif /* #ifndef POSITIONS_H_INCLUDED */
