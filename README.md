hanabi
======

board game hanabi.

Used cocos2d-x.

'doc' dir - just some project documentation.

Game rules
====

Есть колода: 5 цветов номиналами 1,1,1,2,2,3,3,4,4,5.
Каждому раздаётся по 5 карт.
Смотреть можно ТОЛЬКО ЧУЖИЕ карты!
Задача собрать 12345 каждого цвета на столе. Как пасьянс.

В свой ход можно:
1) подсказать: сообщить другому игроку информацию о его картах
1.а) указать ВСЕ его карты озвученного цвета
1.б) указать ВСЕ его карты озвученного номинала
2) сбросить свою карту
3) сделать ход своей картой. Т.е. попытаться уложить её в пасьянс на столе.
В конце хода: добрать карты до 5 из колоды.

Подсказок изначально 8. Сброс карты даёт +1 подсказку.

За неверный ход (не укладывается в пасьянс) - ошибка. 3 ошибки - конец игры.

*После того, как взята последняя карта из колоды, подсказывать больше нельзя.

Можно добавить в колоду радужный цвет (номиналы: 1,2,3,4,5). Теперь нужно собрать пасьянс из 6 цветов.

How to build under Linux
====

Install cocos2d-x 3.0 or later.

Create new project: 'cocos new MyGame -p com.your_company.mygame -l cpp -d NEW_PROJECTS_DIR'.

Link Classes to Classes dir in project.

Link Resources to Resources dir in project.

Link CMackLists.txt to CMackLists.txt in project.

How to build under Mac (differences)
====

Do the same as for Linux.

open proj.ios_mac/hanabi.xcodeproj in Xcode

Add all files from Classes into Classes folder in Xcode project (for Mac && for IOs)

Add all files from Resources into Resources folder in Xcode project (for Mac && for IOs)

