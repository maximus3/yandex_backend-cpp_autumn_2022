FROM registry.yandex-academy.ru/school/2022-09/backend/cpp/homeworks/hw2_search/fruits/service-base:latest

RUN mkdir /$app/solution

ADD src /$app
ADD solution /$app/solution

CMD python manage.py migrate
CMD python manage.py runserver 0.0.0.0:8000
