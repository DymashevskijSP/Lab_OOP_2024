# Лабораторные работы по Объектно-ориентированному программированию, Дымашевский Сергей 3388

# Сборка и запуск
Для сборки необходимо из корневой папки с игрой запустить пару команд `cmake .` и `make`
После для запуска необходимо запустить исполняемый файл  `sea_battle`

# Доступные команды
При расстановки команда для установки корабля имеет формат `<x> <y> <v/h>`, где `v` или `h` отвечает за вертикальное или же горизонтальное расположение корабля.
После расстановки доступные команды
1. `move <x> <y>` -- сделать ход в точку x y
2. `ability` -- активировать способность. После этой команды для направленной способности будет также запрошены координаты.
3. `save` сохранение игры в текущем состоянии после этого будет запрошено имя файла для сохранения
4. `load` загрузка игры из сохраненного состояния. После команды будет запрошено имя файла откуда брать сохранение. При этом, для тестирования есть готовые сохранения `good_save_1` `good_save_2` `bad_save`, которые можно загрузить. В первых двух случаях сохранение будет загружено, в последнем -- будет выдана ошибка.
5. `quit` -- выход из игры. Завершает программу.

# Отчет
Отчеты находятся в папке docs
