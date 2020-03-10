/*
 * Пример чтения текстовой переменной с сайта iocontrol.ru
 * на Arduino с Ethernet Shield'ом. Необходимо заполнить название
 * панели myPanelName и название переменной myVarName,
 * на название переменной созданной на сайте iocontrol.ru
 * Подробнее https://iocontrol.ru/blog/arduino-example-4
 */

#include <iocontrol.h>
#include <SPI.h>
#include <Ethernet.h>

// Название панели на сайте iocontrol.ru
const char* myPanelName = "название_панели";
// Название переменной строки на сайте iocontrol.ru
const char* myVarName = "название_переменной";

// Создаём объект клиента класса EthernetClient
EthernetClient client;
// Создаём объект iocontrol, передавая в конструктор название панели и клиента
iocontrol mypanel(myPanelName, client);

// MAC адреса Ethernet шилда. Должен быть уникальным в сети
byte mac[] = {
	0xFE, 0xED, 0xDE, 0xAD, 0xFA, 0xCC
};

//  Задаём статический IP-адрес на тот случай,
// если динамическое присвоение адреса даст сбой
// IPAddress ip(192, 168, 1, 31);
// IPAddress myDns(192, 168, 1, 1);


void setup()
{
	Serial.begin(9600);

	// Инициируем Ethernet Shield со статическим адресом
	// Ethernet.begin(mac, ip, myDns);

	// Инициируем Ethernet Shield с использованием DHCP
	Ethernet.begin(mac);

	// Вызываем функцию первого запроса к сервису
	mypanel.begin();
}

void loop()
{
	// Обновляем переменные в памяти и записываем
	// статус запроса в переменную
	int status = mypanel.readUpdate();

	// Если статус равен константе OK...
	if (status == OK) {

		// Записываем строку в объект
		String myString = mypanel.readString(myVarName);
		// Выводим значение в монитор последовательного порта
		Serial.println(myString);
	}
}
