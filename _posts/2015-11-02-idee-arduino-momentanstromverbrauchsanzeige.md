---
layout: post
title:  "[Idee] Arduino Momentanstromverbrauchsanzeige"
date:   2015-11-02 16:40:14 +0100
categories: 
redirect_from:
#  - 201x/x/
---

Vor Kurzem hatte ich mich gefragt, wie viel Strom eigentlich im Moment insgesamt verbraucht wird.  Natürlich hätte ich zum Stromzähler rennen können und anhand der Drehgeschwindigkeit der Scheibe bestimmen können, wie viel Strom gerade verbraucht wird. Aber das kann ich ja nicht die ganze Zeit machen.

Daher die Idee, den Momentanverbrauch  mit einem Arduino auszulesen und an ein LC-Display zu senden.
### Das Ziel
Ziel ist es, im Wohnzimmer, oder an einer anderen, strategisch sinnvollen Position, ein LC-Display hängen zu haben, dass alle wichtigen Informationen anzeigt.

Was das Display anzeigen soll:

<!--more-->

  - Momentanverbrauch (in W / kW)
  - Grafische Darstellung des Momentanverbrauchs als Balken
  - 24h-Verbrauch (in kWh)
  - eventuelle Darstellung des 24h-Verbrauchs als Graph

### Das System
Sensor am Stromzähler -> Arduino -> NRF24L01 >>>> NRF24L01 -> Arduino -> LCD

![NRF24L01-Modul](/uploads/2015-11-02-idee-arduino-momentanstromverbrauchsanzeige/nrf24l01.jpg)

Damit die Informationen auch auf dem Display ankommen, müssen sie zuerst einmal durch einen Sensor am Stromzähler eingelesen werden. Die Sensordaten werden dann von einem Arduino ausgewertet und über ein NRF24L01-Funkmodul weitergesendet. Ein weiterer Arduino empfängt die Daten über ein NRF-Modul und zeigt diese dann auf einem LCD an.
### Der Sensor
![Ferraris-Zähler](/uploads/2015-11-02-idee-arduino-momentanstromverbrauchsanzeige/energiezaehler_kpl_01.jpg)

Hier wird das Ganze etwas problematisch. Denn um den Stromverbrauch mit einem alten Ferraris-Zähler (die mit Drehscheibe) zu messen, muss ich die rote Markierung auf der Scheibe digital erkennen können. Das geht nur durch irgendeine Art optische Erkennung.

Meine erste Idee war es, mit einer grünen LED und einem LDR erkennen zu können, ob sich unter dem Licht der LED gerade der silberne Teil der Scheibe, oder die rote Markierung befindet. Allerdings müsste die LED mit einer Linse auf einen Punkt der Scheibe fokussiert  werden, damit nicht zu viel Licht zum LDR zurückreflektiert wird. Man könnte die grüne LED auch durch eine grüne Laserdiode ersetzen, sofern diese in den beschränkten Platz des Schaltschranks passt.

Durch ähnliche Projekte auf [mikrocontroller.net](https://www.mikrocontroller.net/)  konnte ich mir noch einige weitere Anregungen einholen. Dort wurden Sensoren basierend auf Infrarotreflektionslichtschranken, Computermaussensoren, etc vorgeschlagen, die alle recht vielversprechend klingen.

Sofern der Sensor funktioniert, stellt der Rest des Systems keine große Schwierigkeit mehr da. Der Arduino am Zähler muss die Pulse, die er in x Zeitabständen bekommt in Watt(-stunden) umrechnen und diese Daten dann über die NRF-Module an den zweiten Arduino senden, der diese dann nur noch schön auf dem LCD anzeigen muss.


Bei Zeit werde ich die Theorie mit dem reflektierten grünen Licht testen und über die Ergebnisse berichten.