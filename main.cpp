/*
* Два режима работы:
* 1) играть:
*	Список слов храниться в файле в зашифрованном виде.
*   При запуске программа загружает весь список слов.
*	Слово из базы выбирается случайно.
*	Пройденное слово удаляется из списка игры, но не из базы(файла).
*	Когда список исчерпан, программа предлагает восстановить весь изначальный список.
*	На каждое слово дается 7 попыток.
*   За неправильную букву рисуется очередная часть висящего человечка.
* 
*	Во время раунда на каждом шаге выводится:
*		- Виселица
*		- Искомое слово без угаданных букв
*		- Все введенные игроком буквы
*		- Количество ошибок <N of 7>
*		
* 
*	В конце раунда выводится информация:
*		- искомое слово
*		- искомое слово без угаданных букв
*		- список введенных игроком букв
*		- Время (в формате 25.534 сек), потраченное на раунд
* 
* 2) изменить базу слов:
*	(для входа набрать в главном меню "секретный код" - 333)
*	добавить, изменить, удалить слово;
*	импорт/экспорт базы слов из файла;
* 
* В базе всего 5 слов для тестирования:
*	ALLIGATOR
*	ELEPHANT
*	CROCODILE
*	TORTOISE
*	CHAMELEON
*/


#include "Header.h"

using namespace std;

int main()
{
	Welcome();
	Menu();

	return 0;
}