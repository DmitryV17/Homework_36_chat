# Homework_36_chat
В общем, этот чат не совсем рабочий, все что работает это интерфейс и подключение к базе данных mysql.
Причем последнее у меня работает так же  не без проблем, при подключении библиотеки мне приходится вручную переписывать файл.pro
меняя текст в конце на ткой:

win32: LIBS += -L'C:/Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += 'C:/Program Files/MySQL/MySQL Server 8.0/include'
Иначе Qt не видит mysql.h

Самое большее что я смог добиться в графическом варианте своего чата так это подключение к базе данных. 
Как приделать оствльные функции из консольного варианта своего проекта я так и не понял. 
В папке ConsoleVersion оставил и свои консольные варианты чатов, в которых функционал работает  полностью, проблемы у меня именно 
с переводом функций на графический вариант чата. 
А именно:
1. Не отправляется запрос на проверку логина и пароля, вводимых пользователем в line edit. Сам ввод возможен, однако какие то проблемы 
происходят при обработке запроса к бд, причем из-за каких то последних измененийй чат при такой процедуре стал вылетать. 
В базе данных такой запрос работает, вохможно проблемы возникают когда я перевожу передаваемые переменные 
их QString в std::string.
2. Вывод списка пользователей или  сообщений, в общем получение данных из самой базы данных у меня так же вызвалр проблемы. 
Я не понимаю как можно вывести массив информации на view list, пробовал разные способы и даже пытался передать информацию в вектор, однако 
так и не смог вывести текст. 
3. Возвращаясь к проблемам с подключением, я нашел статью на хабре: https://habr.com/ru/articles/51650/ где указывается очень простой способ привязки
Qt к базам данных, однако этот способ у меня не работает 
При попытке решения проблемы по этому видео - https://youtu.be/qVdhPUI1Fio?si=HuxLNi3xNCl47dTJ  выяснил что у меня нету драйверов на базы данных. 
Установка MySql Коннектора не помогла, поскольку в папке с ним, если следовать видеоинструкции, просто нету файла libmysql.lib 
Поэтому метод с хабра я использовать не могу при работ со своими версиями mysql и Qy/
   Собственно поскольку я не могу ни задавать запросы в базу данных не получать ответы, в проекте нет реализации  остальных функций, 
они требуют такого же функционала. Весь функционал остался в консольных вариантах моего чата. 

