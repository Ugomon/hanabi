#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

/**
 * Для клиента этот класс делает вид, что он сервер.
 * В него можно отсылать команды (=желаемое действие).
 * От него приходят команды (по изменению игровой ситуации на столе), которые надо отобразить.
 *

 * Терминология.
 * id - идентификатор карты на руке; от 0 до 4.
 * orderNum - порядковый номер карты в руке; от 0 до 4.
 * serial - порядковый номер позиции в столбце сброса определенного цвета; нумерация начинается с 0.
 * цвета идентифицируются буквами: r g b y w f
 *
 *
 * Команды клиент -> сервер.
 * Все команды серверу (кроме move) носят пожелательный характер; и клиент их сам никак не пытается выполнить.
 *
 * go 2;
 * Сделать ход картой с id == 2.
 *
 * drop 0;
 * Сбросить карту с id == 0;
 *
 * info 2;
 * Сообщить оппоненту информацию обо всех его двойках.
 *
 * info b;
 * Сообщить оппоненту информацию обо всех его синих картах.
 *
 * move 0, 1;
 * Передвинуть карту с id == 0 в позицию 1;
 * Это единственная команда серверу, которую, предполагается, что он выполнит обязательно.
 * Что делать, если возникнуть случаи, когда будут ошибки в выполнении этой команды, буду думать, когда они (случаи) появятся.
 *
 *
 * Команды сервер -> клиент.
 *
 * +newGame 6;
 * Очистить стол для новой игры. 6 - количество цветов в новой игре.
 *
 * +reveal 3, f3;
 * Предъявить свою карту с id == 3; на карте отобразить радужную тройку.
 *
 * +revealDeck f3;
 * Предъявить карту с верха колоды; на карте отобразить радужную тройку.
 *
 * +take 2, 0;
 * Взять себе из колоды карту в позицию 0 и присвоить ей id == 2;
 *
 * +takeOp 2, 0;
 * Взять оппоненту карту из колоды в позицию 0 и присвоить ей id == 2.
 *
 * +drop 3, y, 0;
 * Сбросить свою карту с id == 3 в самое начало сброса жёлтого цвета.
 *
 * +dropOp 3, y, 9;
 * Сбросить карту оппонента с id == 3 в самый конец сброса жёлтого цвета.
 *
 * +deck 17;
 * В колоде осталось 17 карт.
 *
 * +turn 0;
 * Сейчас ход мой. (Если аргумент == 1, значит сейчас ход оппонента).
 *
 * +info 2;
 * Оставшихся подсказок стало 2;
 *
 * +err 1;
 * Оставшихся ошибок стало 1;
 *
 * +show 2, 00101;
 * Показать двойки в своих картах. Порядок карт для второго аргумента соответствует порядку карт в руке (orderNum)
 *
 * +show g, 00101;
 * Показать зеленые в своих картах. Порядок карт для второго аргумента соответствует порядку карт в руке (orderNum)
 *
 * +moveOp 0, 1;
 * Передвинуть карту оппонента с id == 0 в позицию 1;
 *
 * move 0, 1;
 * Передвинуть мою карту с id == 0 в позицию 1; Это нужно для взятия новой карты в крайнюю правую позицию (иначе придется каждый раз мышкой перекладывать).
 *
 * +lay 4, r;
 * Выложить свою карту с id == 4 в красный салют
 *
 * +layOp 4, g;
 * Выложить карту оппонента с id == 4 в зелёный салют
 *
 * +gameOver 30;
 * Игра закончена, вы набрали 30 очков;
 *
 */

#endif /* #ifndef SERVER_H_INCLUDED */
