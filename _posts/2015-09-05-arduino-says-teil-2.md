---
layout: post
title:  "Arduino Says (Teil 2)"
date:   2015-09-05 17:25:44 +0200
categories: Projekte Arduino ATTiny
tags: Arduino ATTiny Code Elektronik Programmieren Projekt
---

![Code Ausschnitt](/uploads/2015-09-05-ATTiny-says-code1.png)

Wie versprochen jetzt der zweite Teil von Arduino Says: Software

Für alle die nicht lesen wollen, hier direkt der [Code](https://github.com/LeoDJ/ATTiny-Says/blob/master/ATTiny_says/ATTiny_says.ino).
### Funktionsprinzip
Der Spielablauf von Simon besteht darin, dass der Spieler eine zufällige Sequenz an aufleuchtenden LEDs mit den Knöpfen nachmachen muss. Hat er dies geschafft, wird die Sequenz um einen Schritt erweitert. Das geht so lang, bis der Spieler sich verklickt (oder die maximale Sequenzlänge erreicht wird, wobei Ersteres sehr viel wahrscheinlicher ist).

(Zum selbst ausprobieren: [http://www.freesimon.org/](http://www.freesimon.org/) (mein Highscore: 17))
### Code
Nach einigem Herumgebastel war die erste Version des Programmcodes auch soweit fertig und bereit geflasht zu werden. Doch wie bekommt man den Code jetzt auf den ATTiny? Der hat ja schließlich keinen USB-Anschluss...

<!--more-->

Da ich keinen USB-ISP-Programmer besitze, musste eben ein Arduino Nano mit dem ArduinoISP-Sktech als Programmer herhalten.

Die erste Version funktionierte natürlich nicht wie gedacht und brauchte noch einige Optimierungen (laut Dropbox genau genommen 31). Und für jede einzelne Änderung des Codes musste ich den ATTiny vom einen Teil des Breadboards auf den anderen stecken und wieder zurück, nur um zu sehen, dass es immer noch nicht richtig funktioniert :P
### Funktionsumfang
Nach noch mehr Herumgebastel ist nun Version 0.1 des Programmcodes soweit fertig.

Es kann:

  - Simon says bis zu einer Sequenzlänge von 32 (ist anscheinend das offizielle Maximum, wie [hier](https://youtu.be/F3LjJITuheM?t=2m29s) zu sehen (wäre aber auf über 400 erweiterbar, bis der RAM des ATTiny (512 Byte) eben belegt ist)
  - Tastentöne
  - Kleine Animationen (einmal blinken = Spielstart, zweimal blinken = verloren)

Es soll noch können:

  - Gescheite Animationen für Spielstart, Spielende und Schlafmodus
  - Schlafmodus, damit man keinen Power-Schalter braucht und man das Spiel mit einem beliebigen Tastendruck wecken kann.
  - (Mute-Schalter vor dem Buzzer im endgültigen Layout)


Layout und Code finden sich auch im [Github Repo](https://github.com/LeoDJ/ATTiny-Says)