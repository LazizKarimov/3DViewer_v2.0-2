# 3DViewer v2.0
3DViewer v2.0 - это программа для визуализации каркасной модели в трехмерном пространстве. Она разработана на языке C++ стандарта C++17 и придерживается Google Style при написании кода. Код программы находится в папке src.

Программа предоставляет удобный интерфейс для работы с трехмерными моделями и может быть использована для различных задач визуализации и анализа данных.

## Функционал
Программа предоставляет следующий функционал:

- Загрузка каркасной модели из файла формата obj.
  
- Перемещение модели на заданное расстояние относительно осей X, Y, Z.
  
- Поворот модели на заданный угол относительно своих осей X, Y, Z.
  
- Масштабирование модели на заданное значение.

- Возможность просмотра информации о загруженной модели: название файла, количество вершин и ребер.

- Возможность выбора типа проекции (параллельная и центральная).
  
- Тип линий (сплошная, пунктирная), способ отображения вершин(отсутствует, круг, квадрат), толщину линий и точек, цвет фона, линий и точек.
    
- Сохранять полученные ("отрендеренные") изображения в файл в форматах bmp и jpeg, а также создать gif-анимацию 

- Настройки сохраняются между перезапусками программы.

## Как использовать приложение

Из папки src выполните команду make install.

После установки откройте приложение выполнив make open, либо откройте вручную приложеине *.app из папки build

Загрузите фаил с расширением *.obj,нажав на кнопку "открыть фаил" 

Используйте приложение.


Авторы: Максим (brenettg), Лера(carrjohn), Лазиз(halfempt).

https://disk.yandex.ru/d/FwF6RbjMFqxscA
