---
layout: post
title:  "IoT in the Box mit dem ESP8266"
date:   2016-07-20 08:00:36 +0200
categories: Projekte ESP8266
tags: ESP8266 IoT Temperatur WiFi
---


Ich hatte noch einen ESP8266 herumliegen, der seinen Einsatzzweck suchte. Also musste eine Projektidee her. Irgendwas mit IoT: immer gut. Akkubetrieben: sollte es schon sein. Telegram-Anbindung: immer doch! Also ab an die Planung.

<!--more-->

## Idee

Eine Art SmartButton, der auf Knopfdruck eine Nachricht an einen Nutzer sendet, ähnlich einer Klingel.

## Umsetzung
Die benötigten Materialien umfassen:

  - ESP8266 [ESP-01 Modul](http://www.banggood.com/Upgraded-Version-1M-Flash-ESP8266-ESP-01-WIFI-Transceiver-Wireless-Module-p-979509.html?p=U530099241512014110R)
  - 18650 Li-Ion Zelle aus einem alten Laptop Akku
  - [18650 Halter](http://www.banggood.com/5Pcs-DIY-Battery-Box-Holder-Case-For-18650-Rechargeable-Battery-p-965083.html?p=U530099241512014110R)
  - [Lithium Lade- und Schutzmodul](http://www.banggood.com/5Pcs-USB-Lithium-Battery-Charger-Module-With-Charging-And-Protection-p-943768.html?p=U530099241512014110R)
  - [3,3V Linearregler](http://www.banggood.com/5V-To-3_3V-DC-DC-Step-Down-Power-Supply-Buck-Module-AMS1117-800MA-p-933674.html?p=U530099241512014110R)
  - Knopf
  - Kartonschachtel


Der Grundaufbau musste natürlich erst einmal auf einem Breadboard getestet werden.


![Grober Test-Aufbau](/uploads/2016-07-20-iot-in-the-box-mit-dem-esp8266/Breadboard_bb-e1468979122227.png)

Der ESP bootet. Soweit so gut, nun zum spaßigen Teil...
## Programmierung

Ich lasse im Normalfall meinen [Code](https://github.com/LeoDJ/IoT-in-the-box) für sich sprechen, aber kurz zur Funktionsweise:

Der ESP ist als Client im lokalen WiFi-Netz angemeldet und kann per [ESP8266TelegramBOT](https://github.com/witnessmenow/ESP8266-TelegramBot) library [Telegram](https://telegram.org) Nachrichten senden und empfangen. Er prüft alle 15 Sekunden, ob er neue Nachrichten empfangen hat (z.B. `/status`, o.ä.) und reagiert auf diese. Auf Knopfdruck sendet er eine vordefinierte Nachricht an einen vordefinierten Telegram-Chat (egal ob Gruppe, oder Einzelperson). Wenn die Versorgungsspannung unter eine bestimmte Schwelle fällt wird auch eine Telegram-Nachricht versandt, damit der Akku rechtzeitig wieder aufgeladen werden kann.

![Deep-Sleep-Mod](https://tzapu.com/wp-content/uploads/2015/12/ESP8266-battery-deep-sleep-mod-esp01.jpg)

Wenn man die Funktionalität nun auf das Mindeste beschränken würde und nur aufwacht wenn der Knopf gedrückt wird, den ESP mit einer [Hardware-Modifikation](http://hackaday.com/2015/02/08/hack-allows-esp-01-to-go-to-deep-sleep/) versehen würde, damit er in den Deep Sleep wechseln kann und einen 3,3V Spannungsregler mit sehr niedrigem Ruhestrom verwenden würde (deutlich niedriger als die ca. 3mA des 1117), dann ist eine Akkulaufzeit von mehreren Monaten durchaus möglich.

Nachdem der Code nun auf dem Breadboard-Aufbau einwandfrei funktionierte, natürlich erst nach dem Fixen einiger Bugs, ging es nun darum, den Aufbau permanent zu machen.

## Hardware

Als Gehäuse dient eine alte Verpackungs-Schachtel für irgendwas Kleines.


![Innenleben von IoT in a Box](/uploads/2016-07-20-iot-in-the-box-mit-dem-esp8266/v1.1_inside.jpg)

Zuerst habe ich alles provisorisch eingepasst, danach die Aussparungen in die Schachtel geschnitten / gestochen und die Einzelteile verkabelt und verlötet. Zum Schluss habe ich noch alle Bauteile hochprofessionell mit Heißkleber fixiert.

Und somit war dieses Projekt auch vollendet.

Wie immer steht der Quellcode auf meinem [GitHub Account](https://github.com/LeoDJ) zur Verfügung.


![Vollendete IoT Box](/uploads/2016-07-20-iot-in-the-box-mit-dem-esp8266/v1.1_charging.jpg)

Edit: Hier geht es zu [Part 2](/2017/03/iot-in-the-box-v1-1)