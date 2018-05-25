---
layout: post
title:  "IoT in the Box v1.1 - Jetzt mit Temperaturfühler!"
date:   2017-03-29 12:50:04 +0200
categories: IoT
redirect_from:
#  - 201x/x/
---

Hm, jetzt steht da so eine IoT Box mit Knopf hier rum und so wirklich nützlich ist sie jetzt auch nicht, da durch die bereits angesprochenen Einschränkungen nicht outdoor-tauglich. Also was damit machen? Richtig, upgraden!
<!--more-->

## Ziel des Upgrades
Es sollen die Temperaturen innerhalb meines Zimmers und außerhalb auf dem Balkon gemessen werden und die Daten der Einfachheit halber zu [Thingspeak](https://thingspeak.com/) zur Visualisierung geschickt werden.

So nun aber ab ans Projekt:
### Temperatursensoren
Ich hatte vor langer Zeit mal die [Dallas DS18B20 1-Wire Temperatursensoren](http://www.banggood.com/5Pcs-DS18B20-Temperature-Sensor-DALLAS-18B20-TO-92-Encapsulation-p-953365.html?p=U530099241512014110R) bestellt. Diese Sensoren sind echt klasse, sie haben

  - Einen Messbereich von -55°C bis +125°C
  - Die Möglichkeit, über die Datenleitung mit Strom versorgt zu werden und benötigen dadurch nur 2 Anschlusskabel
  - Man kann mehrere Sensoren an den gleichen Bus hängen und diese anhand der bereits einprogrammierten UID auseinander halten

### Hardwareerweiterung
Die Hardware aus [Version 1.0](/2016/07/iot-in-the-box-mit-dem-esp8266/) wurde nur minimal modifiziert. Ich habe eine Aussparung vorne in den Karton geschnitten und dahinter eine 2-polige Lüsterklemme geklebt.  Einen Pol habe ich direkt mit der Ground-Rail verbunden und den anderen mit dem letzten freien GPIO Pin.

Um die Sensoren über die Datenleitung mit Strom zu versorgen, muss man an diese noch einen Pullup-Widerstand anschließen. Für diesen ist ein Wert von 4,7 kΩ empfohlen.

![Innereien der IoT Box 1.1](/uploads/2017-03-29-iot-in-the-box-v1-1/v1.2_inside.jpg)

Es ist nicht so schön geworden, wie es sein könnte, aber solange es funktioniert bin ich zufrieden.

An die Lüsterklemme wurde nun ein Sensor für drinnen mit einem kurzen Kabel parallel zu einem 2-3m langen Kabel für den Außensensor angeschlossen.

Ich hatte zuerst bedenken, dass diese Kabellänge zu Störungen führen könnte, aber nach einigen Tests stellte sich heraus, dass der Sensor genau so zuverlässig arbeitet, wie der an dem kurzen Kabel.

Damit der Außensensor nicht so stark durch die Luftfeuchtigkeit in Mitleidenschaft gezogen wird, habe ich die Lüsterklemme, mit der er am Ende des Kabels befestigt ist, mit Heißkleber versiegelt.

![angeschlossene Sensoren](/uploads/2017-03-29-iot-in-the-box-v1-1/v1.2_sensors.jpg)

Der Außensensor hängt nun unter dem Dach vom Balkon und das Kabel führt durch mein Fenster zur IoT Box.
### Software
First things first, Link zum [Code auf Github](https://github.com/LeoDJ/IoT-in-the-box/blob/master/TempLogger/src/TempLogger.cpp).

Die Software besteht hauptsächlich aus dem Auslesen der Sensoren und Senden der Werte zu Thingspeak.

Der Code könnte etwas besser strukturiert sein, aber dazu hatte ich nach all den Monaten bei weitem keine Lust mehr, daher release ich ihn as-is.
### Fazit
Der Sensor sammelt nun seit September 2016 fleißig Daten und stellt diese auch auf der [Thingspeak Seite](https://thingspeak.com/channels/137258) schön dar. (Aktuell sind es ~72.000 Datenpunkte, Stand März 2017).

Da der Sensor sich leider auf dem Balkon, also nah am Haus, und auch noch auf der Südseite befindet, ist die Genauigkeit der Minimal-/Maximalwerte nicht so hoch. Denn im Sommer heizt sich die Luft unter dem Balkondach durch die Sonneneinstrahlung ordentlich auf und im Winter strahlen die Hauswände Wärme ab. Aber die durchschnittliche Temperatur ist im Großen und Ganzen okay.

Besonders nützlich sind die 2 Sensoren besonders im Sommer, dann kann man abends nämlich immer sehen, ab wann es draußen kälter ist, als drinnen und es sich lohnt, das Fenster aufzumachen.
