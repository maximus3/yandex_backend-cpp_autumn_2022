# Домашка по НТ для Школы Бекенд Разработки
  * Приложение в виде Docker-контейнера собирано и залито на https://hub.docker.com/r/shbr2022/sorting
    * в приложении реализованно 2 типа сортировок: пузырьковая (/bubble) и сортировка слиянием(/merge)
    * на вход подается Post-запрос с телом в виде json-ки, внутри которой список int-ов, который нужно отсортировать. Пример тела запроса ``{"numbers": [10, 8, 7, 13, 25, 64, 85, 91, 70]}``
    * на выходе отдается http_200 с отсортированной json-кой
  * /test-data - примеры запросов к сервису
  * HomeWork.md - инструкция к домашнему заданию