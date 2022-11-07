
## Задание

В качестве приложения возьмем сервис ((https://git.yandex-academy.ru/school/2022-09/backend/cpp/homeworks/ya-bookmarker bookmarker)) из ДЗ по тестированию.

Необходимо выполнить два вида профилирования:

* по процессору
* по памяти


### По процессору 

1. Необходимо запустить приложение

2. Определить ID процесса с помощью команды

```
ps -ef
```

3. Запустить профилирование

```
perf record -g --call-graph dwarf,32000 -p <pid> sleep 10
```

4. В это время время подергать ручки приложения с помощью curl, например

```
curl -XPOST "htpp://localhost:8080/register" -F "email=me@ya.ru" -F "password=pswd"
```

5. Получить флеймграф 

```
git clone https://github.com/brendangregg/FlameGraph

perf script | ~/FlameGraph/stackcollapse-perf.pl | ~/FlameGraph/flamegraph.pl > flame.svg
```

### По памяти

1. Установить настройки профилирования в переменную окружения

```
export MALLOC_CONF="prof:true,prof_active:false,,prof_prefix:/tmp/jeprof-hello"
```

2. Начать профилирование

```
curl -X POST localhost:8086/service/jemalloc/prof/enable
```

3. В это время время подергать ручки приложения с помощью curl, например

```
curl -XPOST "htpp://localhost:8080/register" -F "email=me@ya.ru" -F "password=pswd"
```

4. Сделать dump
```
curl -X POST localhost:8086 /service/jemalloc/prof/dump
```

5. Завершить профилирование

```
curl -X POST localhost:8086 /service/jemalloc/prof/disable
```

6. Экспортировать отчет в PDF

```
jeprof --show_bytes --pdf ./service_template /tmp/jeprof.5503.1.m1.heap> prof.pdf
```

### Результат выполнения


По результатам составить отчет о шагах, которые были выполнены в процессе профилирования, приложить результаты и сделать выводы.


