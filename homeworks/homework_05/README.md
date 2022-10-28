# Сервис url-shortener 

Сервис предоставляет пользователям возможность делать короткие ссылки. Переходя по короткой ссылке, созданной в сервисе, браузер перенаправляется на оригинальный адрес.

## Запуск приложения
1. Запустите сервис командой `make docker-start-service-debug`
2. Отправьте запрос на сокращение ссылки с помощью утилиты командной строки curl. 
```
curl -X POST localhost:8080/v1/make-shorter \
  -d '{
    "url": "https://ya.ru"
  }'
```
В ответ придет примерно такой JSON: 
```
{
	"short_url": "http://localhost:8080/some-id"
}
```
Где `short_url` - адрес, переход по которому, осуществит перенаправление запроса на оригинальный адрес.
3. Откройте короткий URL `http://localhost:8080/some-id` в браузере и запрос будет перенаправлен на оригинальный URL.

## Задание

На лекции мы проследили за процессом, как разрабатывать новые крутые продуктовые фичи в нашем сервисе Такси. Давайте реализуем что-то похожее на небольшом проекте `url-shortener`. Он всего лишь умеет укорачивать урлы и дает немного управления над созданными редиректами (можно посмотреть статистику использования и удалить ссылку).

Представьте, что нам необходимо вывести наш сервис `url-shortener` на новый качественный уровень на рынке подобных систем. Надо завоевать долю на рынке и нарастить количество активных пользователей с X до Y %. Это стратегическая цель. Но как ее достичь?

Дальше задание разделяется на 2 пути: вы можете взять описанную ниже фичу либо придумать свою крутую. Главное — реализовать в коде и показать путь фичи от идеи до воплощения. Если пойдете по второму пути, то все равно нужно реализовать в коде предложенную фичу, чтобы наши автотесты проверили ваш код.

В требованиях к заданию есть творческая составляющая — нужно будет написать отчет в формате md. Если идете путем своей фичи - описываете в этой части свою фичу, если нет — то нашу. Подробности ниже.

### Давайте сначала присмотримся к фиче, предложенной нами

Кто-то проанализировал рынок за вас и решил, что киллер-фичей, которую так необходимо реализовать во что бы то ни стало, является "VIP ссылки"!

Что это? Всё просто. Вы помните, что `UrlShortener` возвращает произвольную комбинацию символов в укороченном URL. А в VIP ссылках, это не так: пользователь сам указывает, какой будет его короткая ссылка, конечно, только если заданная им комбинация символов свободна.

Формальное описание интерфейса на OpenAPI 3.0 тут [openapi.yaml](openapi.yaml)

А ниже для общего представления неформальное описание.

make_shorter на входе получает:
```
url = "user-defined-long-url"
optional vip_key = "user-defined-symbols"
optional time_to_live = 1
optional time_to_live_unit = SECONDS, MINUTES, HOURS, DAYS
```

Максимальный TimeToLive не должен превышать 2 дней (иначе красивые vip ссылки закончатся).

В ответ на операцию приходит
```
short_url = "example.com/xyz" - короткая ссылка
```

Ну или ошибка 400, если есть какие-то проблемы с входными параметрами, например, если `vip_key` уже занят, отсутствует `url` или переданы невалидные значения для TTL.

### А что если у меня своя классная идея?
Все просто - опиши ее и реализуй, а потом презентуй в коротком (до 2 минут) видео ролике - загрузи видео на любой открытый видеохостинг - ютуб, например. В ролике необходимо показать функциональность твоей фичи. Не забудь реализовать базовую фичу "vip ссылки", она будет проверена автоматически.

### Требования к результату домашней работы

0. Форкнуть (fork) данный репозиторий с заданием в свой репозиторий;
1. Необходимо описать идею (vip ссылки или свою) в 1-2 предложениях;
2. Сформулировать продуктовые гипотезы - 1-2 штуки в формате, как было на лекции;
3. Оценить примерные трудозатраты (попробуй аргументировать оценку, например, требуемым количеством новых классов, объемом кода);
4. Придумать, можно ли сделать MVP, если да, то как он будет выглядеть и сколько это займет времени;
5. Проработать архитектуру и описать ее в тексте (в качестве формального описания подойдут openapi описание, диаграммы классов, компонентные диаграммы - в зависимости от того, что лучше отразит суть изменений и, что по вашему мнению будет понятнее проверяющему);
6. Реализовать полное решение идеи в коде. Если пошли по пути разработки своей супер-идеи, то не забудьте реализовать vip ссылки;
7. Добиться чтобы все предоставленные в исходном репозитории тесты на vip ссылки проходили успешно, внося правки в код сервиса, а не тестов :) ;
8. Придумать AB-тест - какие выборки пользователей будут в эксперименте? Какие параметры фичи будем проверять в каждой выборке?
9. Выбрать и описать набор наблюдаемых продуктовых метрик, по которым можно сделать вывод, что фича "взлетела". Какие значения метрик ожидаем увидеть?
10. Сделать отчет в файле README.md (имеющийся удалить, свой добавить) в своем репозитории с ответами на эти вопросы.

Если идешь путем разработки своей фичи, то отчет пиши про неё. Если реализуешь только vip ссылки, то отчет по ней.

Если что-то непонятно, смело задавай вопросы своему ментору.

## Работа с приложением

### Требования

Необходимо, чтобы были установлены следующие компоненты:

- `Docker` и `docker-compose`
- `Python`

### Установка

1. Склонируйте репозиторий `git clone your-service-repo && cd your-service-repo`
2. Обновите сабмодули `git submodule update --init`
3. Запустите сборку 
- В docker контейнере `make docker-build-debug` (рекомендуется)
- Локально `make build-debug` (не рекомендуется)

### Запуск

- Запуск приложения в docker контейнере (рекомендуется):
```commandline
make docker-start-service-debug
```

- Запуск приложения локально (не рекомендуется):
```commandline
make service-start-debug
```

### Тестирование

- Запуск тестов в docker контейнере (рекомендуется):
```commandline
make docker-test-debug
```

- Запуск тестов локально (не рекомендуется):
```commandline
make test-debug
```

### Запуск форматирования кода
```commandline
make format
```

### Попробнее про фреймворк userver

- Документация
https://userver.tech/index.html

- Исходный код 
https://github.com/userver-framework/userver

- Шаблон сервиса 
https://github.com/userver-framework/service_template

- Шаблон сервиса с базой 
https://github.com/userver-framework/pg_service_template

### Работа со временем

При работе используйте `userver::utils::datetime::Now` из `<userver/utils/datetime.hpp>`. Если спользовать просто `chrono`, то не будет работать `mocked_time` в тестах