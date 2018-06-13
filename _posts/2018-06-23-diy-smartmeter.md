---
layout: post
title:  "DIY SmartMeter"
date:   2020-06-23 12:00:00 +0200
categories: Projekte Arduino
tags: Arduino NRF24L01 Stromzähler
---

Wie bereits vor Jahren mal [als Idee festgehalten](/2015/11/idee-arduino-momentanstromverbrauchsanzeige/) kam ich nun endlich dazu die Idee mit dem DIY SmartMeter umzusetzen.

Wie bereits im letzten Artikel angesprochen, bin ich aktuell daran das mySensors Netzwerk bei mir zuhause zu erweitern.

Nun ist den Stromzähler daran anzubinden der nächste logische Schritt, da mich die Stromverbrauchswerte schon immer interessiert haben.

<!--more-->

# Hardware
Bei diesem Projekt galt für mich nach dem eher hardwarelastigen letzten Projekt, der PDBox, ganz klar "Software first".

Natürlich benötige ich trotzdem hardwareseitig einen Testaufbau. Hier daher ganz klassisch als Breadboard-Aufbau gelöst.

## Komponenten

  - [Arduino Nano](https://www.banggood.com/ATmega328P-Arduino-Compatible-Nano-V3-Improved-Version-No-Cable-p-959231.html?p=U530099241512014110R)
  - [NRF24L01+](https://www.banggood.com/3Pcs-NRF24L01-SI24R1-2_4G-Wireless-Power-Enhanced-Communication-Receiver-Module-p-1057155.html?p=U530099241512014110R)
  - [Spannungswandler 5V->3,3V](https://www.banggood.com/5Pcs-5V-To-3_3V-DC-DC-AMS1117-800MA-Step-Down-Power-Supply-Buck-Module-p-944686.html?p=U530099241512014110R)
  - [CNY70 IR-Reflexkoppler](https://www.reichelt.de/index.html?ARTICLE=6683)


## Reflexkoppler
![CNY70 Sensor](/uploads/2018-06-23-diy-smartmeter/CNY70.jpg)

Der CNY70 ist ein Infrarotreflexkoppler. Das bedeutet, dass er ähnlich wie ein Optokoppler aus einer Infrarot Leuchtdiode und einem Fototransistor besteht.

Während bei einem Optokoppler die beiden Komponenten jedoch im Gehäuse aufeinander zeigend verbaut sind, zeigen diese bei einem Reflexkoppler aus dem Gehäuse nach außen.

Das von der Leuchtdiode abgestrahlte Licht wird von der Oberfläche reflektiert und fällt zurück in den Fototransistor der dann abhängig von der Lichtstärke einen gewissen Strom fließen lässt. Dieser Strom kann man dann über einen Widerstand mithilfe des Analog-Digital-Wandlers eines Mikrocontrollers messen.

![CNY70 schematisch](/uploads/2018-06-23-diy-smartmeter/CNY70_schematically.png)
### CNY70 Adapterplatine
Der hier verwendete CNY70 benötigt noch zwei zusätzliche Widerstände, die ich zusammen mit dem Sensor auf eine eigen kleine Adapterplatine gelötet habe. Normalerweise hätte ich den CNY70 einfach mit Jumper Kabeln verbunden und die Widerstände erst auf dem Breadboard verbaut. Allerdings sind die Beinchen am Sensor wohl ein bisschen dünner als normale Dupont Pins und deshalb haben die Kabel nicht gehalten.

<!-- [gallery type="rectangular" ids="2093,2103"] -->
![](/uploads/2018-06-23-diy-smartmeter/CNY70_breakout_board.jpg)
![](/uploads/2018-06-23-diy-smartmeter/CNY70_breakout_schematic.png)

## Testaufbau
Für den Testaufbau habe ich dann einfach den Sensor mit Klebeband an den Stromzähler geklebt und das Breadboard in den Zählerschrank gelegt. Versorgt wird der Arduino einfach mit einem USB-Netzteil.

![Testaufbau](/uploads/2018-06-23-diy-smartmeter/test_setup.jpg)

# Software
Da nun die Hardware grundsätzlich erst mal steht kann ich mit dem spaßigen Teil beginnen.

## Sensor auslesen
Die erste Hürde, an der ich vor ca. zwei Jahren gescheitert bin war, dass man mit dem Reflexkoppler ja diesen kleinen roten Strich auf der Zählscheibe erkennen muss. Wenn sich dieser am Sensor vorbei dreht, bewirkt er allerdings nur eine relativ geringe Änderung der reflektierten Lichtstärke, da sich der CNY70 nicht wirklich gut fokussieren lässt.

Als Größenordnung der geringen Änderung mal so viel: Beim Arduino tritt eine Änderung des gemessenen Analogwerts bei Erkennung des roten Strichs um ca. 5 Werte (von 1023) auf, während bei Ruhezustand bereits durch das Rauschen des Analog-Digital-Wandlers (ADC) der Wert schon um ca. 3 Werte schwankt.

Ein so geringes Signal müssten man nun entweder verstärken, oder man filtert das ADC-Rauschen mithilfe von Software aus dem Signal heraus. Letzteres ist der Weg, den ich gewählt habe, da eine Verstärkung auf der analogen Seite für mich deutlich komplexer ist und den Messbereich des Sensors einschränkt.

### Filterung
Als Filterung nutze ich hier ein gleitenden Mittelwert. Bei diesem merkt der Mikrocontroller sich die letzten x gemessenen Werte und nimmt davon den Durchschnitt. Wird ein neuer Wert gemessen wird der älteste Wert verworfen. Durch diesen Filter beschränken sich die Schwankungen dann nur noch auf ungefähr einen halben Wert.

Den Messintervall habe ich mal auf 5 Millisekunden festgelegt. Damit sieht man ganz gute Kanten in den Werten und hat eine gute Reaktionszeit auf die rote Markierung.

### Kalibrierung
Nun ist es allerdings so, dass der Fototransistor nicht nur auf das Infrarotlicht von der Leuchtdiode reagiert, sondern auch auf anderes einfallendes Licht. Um den Sensor nicht jedes Mal manuell auf die Lichtverhältnisse im Zählerschrank kalibrieren zu müssen, habe ich hier erneut eine Filterung eingebaut. Dafür kommt ein sogenannter "exponentiell gewichteter gleitender Mittelwert" (EWMA) zum Einsatz.

Das hört sich jetzt sehr kompliziert an, heißt aber insgesamt eigentlich nur, dass der neu eingelesene Wert in einem Verhältnis zu dem bereits vorhandenen Durchschnittswert verrechnet wird. Das spart einiges an Arbeitsspeicher, da im Prinzip nur der aktuelle Durchschnittswert im Speicher gehalten werden muss.

Wird ein neuer Wert eingelesen, so wird von dem Durchschnittswert bspw. ein Hundertstel entfernt und der neue Wert geteilt durch hundert dazuaddiert.

Somit wird immer errechnet, was der aktuelle Helligkeitswert ohne rote Markierung ist, damit die Differenz akkurat ermittelt werden kann.

### Sensorwerte
Im folgenden Screenshot sieht man nun die rohen Sensorwerte beim Vorbeidrehen der roten Markierung.

![Sensorwerte bei roter Markierung](/uploads/2018-06-23-diy-smartmeter/pulse.jpg)

Die rote Linie ist der gleitende Mittelwert der Sensorfilterung, dort sieht man sehr gut, dass ein klarer Helligkeitsabfall auftritt, der recht gut in Software erkannt werden kann.

Die grüne Linie ist der EWMA von der automatischen Kalibrierung, man sieht sehr gut, dass er sich immer sehr langsam dem aktuellen Wert annähert und immer maximal einen Wert vom gefilterten Eingangssignal abweicht.

Die blaue Linie ist ein Vergleichswert, was passieren würde, wenn man die kurzzeitige Filterung mit einem EWMA vornehmen würde. Die abfallende Kante ist mir hier nicht eindeutig genug, weshalb ich den gleitenden Mittelwert (rot) bevorzuge.

Die ungefilterten Sensorwerte sind in diesem Diagramm nicht gezeigt, da man sonst die gefilterten Linien gar nicht mehr erkennen würde.

## Momentanverbrauch
Da nun eine Umdrehung der Zählerscheibe sehr gut gemessen werden kann geht es nun damit weiter, was man mit diesen Daten anfangen kann.

Auf dem Stromzähler steht immer, wie viele Umdrehungen pro gemessener Kilowattstunde anfallen. In meinem Fall sind es 375U/kWh. Das heißt man kann durch Zählen der Umdrehungen den Verbrauch in kWh erfassen und quasi den Zählerstand digital vorhalten, sofern der Sensor akkurat jede Umdrehung erkennt und keinen Ausfall erleidet.

Allerdings kann man zusätzlich auch die Zeit einer Umdrehung messen. Dadurch lässt sich dann nämlich der aktuelle Verbrauch in Watt berechnen. Dazu kann man einfach folgende Formel anwenden:

$$
Watt=\frac{3600}{Intervall\ *\ \frac{375\ U/kWh}{1000}}
$$

<script src="/assets/js/MathJax/MathJax.js?config=TeX-MML-AM_CHTML"></script>
