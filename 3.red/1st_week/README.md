# Максимальный элемент по предикату

Реализуйте шаблонную функцию  
```cpp
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate pred);
```
возвращающую итератор на максимальный элемент в диапазоне [first, last), для которого предикат pred возвращает true. Если диапазон содержит несколько подходящих элементов с максимальным значением, то результатом будет первое вхождение такого элемента. Если диапазон не содержит подходящих элементов, то функция должна вернуть last.

### Решение
 max_element_if.cpp

# Макрос LOG

Вам дан класс Logger и макрос LOG

```cpp
class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) ...
```

Параметры макроса LOG — объект класса Logger и строковое сообщение, которое должно быть передано в метод Log. В зависимости от настроек объекта класса Logger логируемое сообщение должно предваряться именем файла или номером строки. Смотрите юнит-тесты в заготовке решения для более подробного описания поведения.

Реализуйте макрос LOG так, чтобы он добавлял в логируемое сообщение имя файла и номер строки в зависимости от настроек объекта logger. Пришлите на проверку cpp-файл, содержащий

* реализацию макроса LOG
* объявление класса Logger, при этом вы можете при необходимости добавлять в него дополнительные поля и методы
* определения всех методов класса Logger

### Решение
 log.cpp


# Генератор компараторов

Давайте представим, что вы разрабатываете инновационный сервис поиска авиабилетов AviaScanner. В вашем сервисе авиабилет представляется в виде структуры 

```cpp
struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  uint64_t price;
};
```

В данный момент вы работаете над функцией сортировки результатов поиска. Пользователь вводит свой запрос и получает список подходящих билетов. Дальше он может задавать параметры сортировки этого списка. Например, сначала по цене, затем по времени вылета и, наконец, по аэропорту прилёта.

Чтобы реализовать сортировку как в примере, можно воспользоваться алгоритмом цифровой сортировки:
```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.to < rhs.to;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.departure_time < rhs.departure_time;
  });
  stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
    return lhs.price < rhs.price;
  });
}
```

Как видите, в примере выше есть дублирование кода — нам пришлось написать три лямбда-функции, которые отличаются только полем, по которому выполняется сортировка. От этого дублирования можно избавиться, написав макрос SORT_BY и применив его следующим образом:

```cpp
void SortTickets(vector<AirlineTicket>& tixs) {
  stable_sort(begin(tixs), end(tixs), SORT_BY(to));
  stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
  stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}
```

Напишите макрос SORT_BY, который принимает в качестве параметра имя поля структуры AirlineTicket. Вызов sort(begin(tixs), end(tixs), SORT_BY(some_field)) должен приводить к сортировке вектора tixs по полю some_field.

Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket, а также заготовка решения в виде cpp-файла sort_by.cpp. Пришлите на проверку cpp-файл, который

* подключает заголовочный файл airline_ticket.h
* содержит макрос SORT_BY
* содержит определения операторов, необходимых для использования классов Date и Time в алгоритме сортировки и макросе ASSERT_EQUAL (формат вывода в поток можете выбрать произвольный)

### Решение
 airlines/sort_by.cpp

# Макрос UPDATE_FIELD

Продолжим работу над сервисом поиска авиабилетов AviaScanner. Наш сервис хранит базу данных билетов в виде vector<AirlineTicket>, где AirlineTicket — такая же структура, как и в предыдущей задаче. Периодически наш сервис обходит сайты авиакомпаний, собирает свежую информацию о доступных билетах и обновляет записи в своей базе данных. Делается это с помощью функции void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates). Параметр updates содержит пары (имя поля; новое значение). При этом он содержит только те поля, которые поменялись. Пример работы функции UpdateTicket:  

```cpp
void UpdateTicketExample() {
  AirlineTicket t;
  t.price = 5000;
  t.from = "DME";
  t.to = "AER";

  const map<string, string> updates = {
    {"price", "3500"},
    {"from", "VKO"}
  };
  UpdateTicket(t, updates);
  ASSERT_EQUAL(t.from, "VKO");
  ASSERT_EQUAL(t.to, "AER");
  ASSERT_EQUAL(t.price, 3500);
}
```

  Функцию UpdateTicket можно было бы реализовать так:

```cpp
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }

  ...
}
```

Здесь налицо дублирование кода — блоки кода внутри функции UpdateTicket отличаются только именем поля (конечно, первые два блока не такие, как третий, но их легко к нему свести). При этом имя поля используется не только для обращения к структуре AirlineTicket, но и как строковый литерал. Поэтому можно написать макрос, который существенно упростит функцию UpdateTicket:  

```cpp
#define UPDATE_FIELD(ticket, field, values) ...

void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
  ...
}
```

Напишите макрос UPDATE_FIELD. Вам дан файл airline_ticket.h, содержащий объявления структур Time, Date и AirlineTicket, а также заготовка решения в виде cpp-файла update_field.cpp. Пришлите на проверку cpp-файл, который

* подключает заголовочный файл airline_ticket.h
* содержит макрос UPDATE_FIELD
* содержит определения операторов, необходимых для считывания классов Date и Time из потока istream и их использования в макросе ASSERT_EQUAL (формат ввода смотрите в юнит-тестах в файле update_field.cpp)

### Решение
 airlines/update_field.cpp

# Плохой макрос

Вам дан макрос, который распечатывает два переданных ему значения в переданный поток вывода. В реализации макроса есть недостаток, ограничивающий его применимость в реальных программах. Вам требуется найти и устранить недостаток.  

```cpp
#define PRINT_VALUES(out, x, y) out << (x) << endl; out << (y) << endl
```
### Решение
 bad_macros.cpp

# Макрос UNIQ_ID

Разработать макрос UNIQ_ID, который будет формировать идентификатор, уникальный в пределах данного cpp-файла. Например, следующий код должен компилироваться и работать:  

```cpp
int UNIQ_ID = 5;
string UNIQ_ID = "hello!";
```

В рамках данной задачи допускается, что код
```cpp
int UNIQ_ID = 5; string UNIQ_ID = "hello"; // оба определения на одной строке
```
не будет компилироваться.

### Решение
 uniq_id.cpp

# Таблица

Вам надо написать шаблонный класс Table для электронной таблицы. Для простоты будем считать, что все ячейки таблицы имеют один и тот же тип данных T. Таблица должна уметь менять свой размер по требованию пользователя. Вновь созданные ячейки должны заполняться значениями по умолчанию типа T.

Требования к классу такие:

    Класс должен называться Table.
* У класса должен быть шаблонный параметр T — тип элемента в ячейке.
* У класса должен быть конструктор, получающий на входе два числа типа size_t — количество строк и столбцов соответственно.
* У класса должны быть константная и неконстантная версии оператора [], возвращающего нечто такое, к чему снова можно было бы применить оператор []. То есть, должны работать конструкции вида cout << table[i][j];и table[i][j] = value;. Проверять корректность индексов при этом не нужно.
* У класса должна быть функция Resize, получающая на вход два параметра типа size_t и меняющая размер таблицы. Старые данные, умещающиеся в новый размер, должны при этом сохраниться.
* У класса должна быть константная функция Size, возвращающая pair<size_t, size_t> — размер таблицы (в том же порядке, в котором эти аргументы передавались в конструктор). При этом, если у таблицы Table один из размеров нулевой, то необходимо считать таковым и второй размер таблицы.

### Решение
 table.cpp

# Дек на основе двух векторов

Напишите шаблонный класс Deque, содержащий следующий набор методов:

* конструктор по умолчанию;
* константный метод Empty, возвращающий true, если дек не содержит ни одного элемента;
* константный метод Size, возвращающий количество элементов в деке;
* T& operator[](size_t index) и const T& operator[](size_t index) const;
* константный и неконстантный метод At(size_t index), генерирующий стандартное исключение out_of_range, если индекс больше или равен количеству элементов в деке;
* константные и неконстантные версии методов Front и Back, возвращающих ссылки на первый и последний элемент дека соответственно;
* методы PushFront и PushBack.

Неконстантные версии методов должны позволять изменять соответствующий элемент дека.

### Решение
 deque_with_double_vector.cpp

# Шаблон Paginator

В лекции мы разработали функцию Head, которая позволяет пройтись циклом for по началу контейнера. В этой задаче мы сделаем шаг вперёд и разработаем шаблон Paginator, который разбивает содержимое контейнера на несколько страниц. Классический пример, когда такое может пригодиться на практике, — это распределение списка мобильных приложений по экранам телефона. Допустим, у нас есть вектор всех приложений нашего телефона и на одном экране мы можем разместить 20 иконок приложений. Тогда распределить приложения по экранам мы можем вот таким кодом:

```cpp
vector<vector<Application>> DistributeAmongScreens(const vector<Application>& apps) {
  vector<vector<Application>> result;
  for (const auto& page : Paginate(apps, 20)) {
    result.push_back({page.begin(), page.end()});
  }
  // result[0] - все приложения, которые попадают на первый экран,
  // result[1] - все приложения, которые попадают на второй экран и т.д.
  return result;
}
```
Заметьте, наш код получился коротким и элегантным. Нам не пришлось писать какой-то отдельный код для обработки последнего экрана, который может содержать меньше 20 приложений.

Итак, разработайте шаблон класса Paginator со следующими свойствами:  
* он имеет один шаблонный параметр — тип итератора
* конструктор класса Paginator<Iterator> принимает три параметра: 
1. Iterator begin 
2. Iterator end — пара итераторов begin и end задают полуинтервал [begin; end), который мы будем нарезать на страницы 
3. size_t page_size — размер одной страницы
* по объектам класса Paginator<Iterator> можно проитерироваться с помощью цикла range-based for 
* класс Paginator<Iterator> имеет метод size_t size() const, который возвращает количество страниц, на которые был разбит переданный контейнер 
* сами страницы должны так же поддерживать итерацию с помощью range-based for и иметь метод size_t size() const, возвращающий количество объектов в этой странице 
* подробные примеры использования смотрите в юнит-тестах в шаблоне решения

Кроме того разработайте шаблон функции Paginate, которая принимает ссылку на контейнер и размер страницы, и возвращает объект класса Paginator<It>: 

```cpp
template <typename C> ??? Paginate(C& c, size_t page_size)
```

### Решение
 paginator.cpp

