## Simple docker

## Part 1. Готовый докер

- Возьми официальный докер-образ с nginx и выкачай его при помощи docker pull.

![alt text](pictures/1-1.png)

- Проверь наличие докер-образа через docker images.

![alt text](pictures/1-2.png)

- Запусти докер-образ через docker run -d [image_id|repository].

![alt text](pictures/1-3.png)

- Проверь, что образ запустился через docker ps.

![alt text](pictures/1-4.png)

- Посмотри информацию о контейнере через docker inspect [container_id|container_name].

![alt text](pictures/1-5.png)

- По выводу команды определи и помести в отчёт размер контейнера, список замапленных портов и ip контейнера.

- Размер - "Size": 72195292
- список замапленных портов:

![alt text](pictures/1-6.png)

- IP-адрес:

![alt text](pictures/1-7.png)

- Останови докер контейнер через docker stop [container_id|container_name].
- Проверь, что контейнер остановился через docker ps.

![alt text](pictures/1-8.png)

- Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду run.

![alt text](pictures/1-9.png)

- Проверь, что в браузере по адресу localhost:80 доступна стартовая страница nginx.

![alt text](pictures/1-10.png)

- Перезапусти докер контейнер через docker restart [container_id|container_name].
- Проверь любым способом, что контейнер запустился.

![alt text](pictures/1-11.png)

## Part 2. Операции с контейнером

- Прочитай конфигурационный файл nginx.conf внутри докер контейнера через команду exec.

- Включаем bash:

![alt text](pictures/2-1.png)

- Читаем:

![alt text](pictures/2-2.png)

- Создай на локальной машине файл nginx.conf.
- lev@lev-kubuntu:~/code/school21/DO5_SimpleDocker-1/src/part2$ touch nginx.conf

- Настрой в нем по пути /status отдачу страницы статуса сервера nginx.

![alt text](pictures/2-3.png)

- Скопируй созданный файл nginx.conf внутрь докер-образа через команду docker cp.

![alt text](pictures/2-4.png)

- Перезапусти nginx внутри докер-образа через команду exec.
- docker exec f3e6b74dc09e nginx -s reload

- Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

![alt text](pictures/2-5.png)

- Экспортируй контейнер в файл container.tar через команду export.

![alt text](pictures/2-6.png)

- Останови контейнер.

![alt text](pictures/2-7.png)

- Удали образ через docker rmi [image_id|repository], не удаляя перед этим контейнеры.

![alt text](pictures/2-8.png)

- Удали остановленный контейнер.
- На скриншоте сверху была надпись: image is being used by stopped container 7015c2f0e5d3. Значит, искомый контейнер - 7015c2f0e5d3.
- docker rm 7015c2f0e5d3

- Импортируй контейнер обратно через команду import.

![alt text](pictures/2-9.png)

- Запусти импортированный контейнер.

- docker run -d -p 80:80 -p 443:443 my_nginx nginx

- Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.

![alt text](pictures/2-10.png)

## Part 3. Мини веб-сервер

- Программа написана в папке сервер.
- Для дальнейшей работы нужно установить в контейнере с nginx необходимые программы.
- apt-get update && apt-get install -y libfcgi-dev gcc spawn-fcgi
- После этого нужно перекинуть скомпилированный сервер (или скомпилировать его в контейнере) в директорию home, а также скинуть файл с конфигурацией nginx в /etc/nginx/
- В контейнере: root@c494ccb3603b:/home# spawn-fcgi -p 8080 -n server
- Перенаправление с 81 порта на 80 также осуществляется.

## Part 4. Свой докер

- sudo docker build -t liquorib:s21 .
- sudo docker images
- если есть проблемы со стартом из-за занятости порта, то смотрим приложения, занимающие его: sudo lsof -i:80
- sudo fuser -k 80/tcp - убиваем их процессы
- sudo docker run -it -p 80:81 -v "$(pwd)/nginx.conf:/etc/nginx/nginx.conf" -d liquorib:s21

## Part 5. Dockle

- Установка Dockle - скрипт в папке.
- Вывод после команды sudo dockle -ak NGINX_GPGKEY -i CIS-DI-0010 liquorib:s21 - чтобы проигнорировать false positive от докла насчет nginx

![alt text](pictures/5-1.png)

- Вывод после внесения изменений:

![alt text](pictures/5-2.png)

- Оставшиеся уведомления не являются ошибками(FATAL) и предупреждениями(WARN).

## Part 6. Базовый Docker Compose

- sudo docker stop $(sudo docker ps -aq) - остановить все контейнеры
- sudo docker compose up
- sudo docker rm -f $(sudo docker ps -a -q) - удалить все контейнеры
- sudo docker image remove -f $(sudo docker images -a -q) - удалить все образы