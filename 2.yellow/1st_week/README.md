# Суммирование матриц

В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. Более подробно, класс Matrix должен иметь:
* конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
* конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
* метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк и столбцов матрицы соответственно; метод Reset меняет размеры матрицы на заданные и обнуляет все её элементы
* константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
* неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
* константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно

Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.

Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.

Кроме того, для класса Matrix должны быть определены следующие операторы:
* оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
* оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
* оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
* оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.

### Решение
 classMatrix.cpp

# Средняя температура 2

Решите задачу «Средняя температура» в других ограничениях на входные данные.

Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

### Формат ввода

Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день. Гарантируется, что N не превышает миллиона (10^6), а значения температуры, измеряющиеся в миллионных долях градусов по Цельсию, лежат в диапазоне от −10^8 до 10^8. Проверять соблюдение этих ограничений не нужно: вы можете ориентироваться на них при выборе наиболее подходящих типов для переменных.

### Формат вывода

Первое число K — количество дней, значение температуры в которых выше среднего арифметического. Затем K целых чисел — номера этих дней.  

### Решение
 AbdTemperature.cpp

# Масса блоков

Вычислите суммарную массу имеющих форму прямоугольного параллелепипеда блоков одинаковой плотности, но разного размера.  

### Указание

Считайте, что размеры блоков измеряются в сантиметрах, плотность — в граммах на кубический сантиметр, а итоговая масса — в граммах. Таким образом, массу блока можно вычислять как простое произведение плотности на объём.  

### Формат ввода

В первой строке вводятся два целых положительных числа: количество блоков N и плотность каждого блока R. Каждая из следующих N строк содержит три целых положительных числа W, H, D — размеры очередного блока.

Гарантируется, что:
* количество блоков N не превосходит 10^5;
* плотность блоков R не превосходит 100;
* размеры блоков W, H, D не превосходят 10^4.

### Решение
 blockMass.cpp

# База регионов

Имеется база регионов, представленная вектором структур Region:

```cpp
enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};
```

Напишите функцию FindMaxRepetitionCount, принимающую базу регионов и определяющую, какое максимальное количество повторов (число вхождений одного и того же элемента) она содержит. Две записи (объекты типа Region) считаются различными, если они отличаются хотя бы одним полем.  

```cpp
int FindMaxRepetitionCount(const vector<Region>& regions);
```

Если все записи уникальны, считайте максимальное количество повторов равным 1. Если записи отсутствуют, верните 0. Гарантируется, что типа int достаточно для хранения ответа.

### Решение
 FindMaxRepetitionCount.cpp

# Трекер задач

Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков:  

```cpp
// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);
};
```

Метод PerformPersonTasks должен реализовывать следующий алгоритм:

1. Рассмотрим все невыполненные задачи разработчика person.
2. Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
3. Рассмотрим первые task_count задач и переведём каждую из них в следующий статус в соответствии с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
4. Вернём кортеж из двух элементов: информацию о статусах обновившихся задач (включая те, которые оказались в статусе DONE) и информацию о статусах остальных не выполненных задач.

В случае отсутствия разработчика с именем person метод PerformPersonTasks должен вернуть кортеж из двух пустых TasksInfo

Гарантируется, что task_count является положительным числом. Если task_count превышает текущее количество невыполненных задач разработчика, достаточно считать, что task_count равен количеству невыполненных задач: дважды обновлять статус какой-либо задачи в этом случае не нужно.

Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
Пример работы метода PerformPersonTasks

Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:

    NEW — 3
    IN_PROGRESS — 2
    TESTING — 4
    DONE — 1

Поступает команда PerformPersonTasks с параметром task_count = 4, что означает обновление статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS до TESTING. 
Если выписать статусы всех задач по порядку, а обновляемые заключить в квадратные скобки, то изменение можно изобразить следующим образом:

  [NEW, NEW, NEW, IN_PROGRESS,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE
  ==>
  [IN_PROGRESS, IN_PROGRESS, IN_PROGRESS, TESTING,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE

Таким образом, новые статусы задач будут следующими:

    IN_PROGRESS — 3 обновлённых, 1 старая
    TESTING — 1 обновлённая, 4 старых
    DONE — 1 старая

В этом случае необходимо вернуть кортеж из 2 словарей:

    Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
    Необновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.

Ни один из словарей не должен содержать лишних элементов, то есть статусов, которым соответствует ноль задач.

По условию, DONE задачи не нужно возвращать в необновлённых задачах (untouched_tasks).

### Примечание

Обновление словаря одновременно с итерированием по нему может привести к непредсказуемым последствиям. При возникновении такой необходимости рекомендуется сначала в отдельном временном словаре собрать информацию об обновлениях, а затем применить их к основному словарю.


# Все в квадрат

Реализуйте шаблонную функцию Sqr, которая работает не только для чисел, но и для контейнеров. Функция должна возвращать копию исходного контейнера, модифицировав его следующим образом:
* для vector элементы нужно возвести в квадрат;
* для map в квадрат нужно возвести только значения, но не ключи;
* для pair в квадрат нужно возвести каждый элемент пары.

Функция должна корректно работать не только для контейнеров, состоящих из чисел, но и для составных объектов, например, векторов словарей пар чисел.