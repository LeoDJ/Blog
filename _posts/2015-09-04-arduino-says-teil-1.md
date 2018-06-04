---
layout: post
title:  "Arduino Says (Teil 1)"
date:   2015-09-04 23:52:39 +0200
categories: Projekte Arduino ATTiny
tags: Arduino ATTiny Elektronik Projekt Schaltplan Target
---

![Original Simon Spiel](https://upload.wikimedia.org/wikipedia/commons/9/99/OriginalSimon.jpg)

Einige kennen eventuell noch das Denkspiel [Simon](https://en.wikipedia.org/wiki/Simon_(game)).

Ich dachte mir: so ein einfaches Spiel müsste sich doch sehr einfach mit einem Arduino nachbauen lassen. Es besteht ja schließlich nur aus 4 Tastern, 4 LEDs und einem Buzzer.

Aber wieso ein Arduino für so ein einfaches Spiel vergeuden? Ein ATTiny85 tut's doch auch und ist obendrein noch günstiger.

<!--more-->

Nur ein kleines Problem: Der ATTiny hat nur 5 I/O Pins, obwohl ich für das Spiel eigentlich 9 bräuchte...

Moment, sagte ich neun? Fünf reichen doch vollkommen aus! An einen I/O-Pin kann man einen Taster und eine LED gleichzeitig anschließen, sofern man weiß wie.

Die LED ist mit dem Plus-Beinchen über einen Widerstand direkt mit V<sub>CC</sub> verbunden und der Taster hängt an GND. Das Minus-Beinchen der LED und das andere Beinchen des Tasters sind nun verbunden, was wiederum dafür sorgt, dass die LED leuchtet, sobald man den Taster drückt. An diesem Verbindungspunkt wird nun ein I/O-Pin des ATTinys angeschlossen, sodass der ATTiny sowohl den Status des Tasters abfragen, als auch die LED leuchten lassen kann.

Der letzt I/O-Pin geht nun noch für den Buzzer drauf. Man will ja schließlich auch was hören. ;)

Mit diesem Wissen und dem gratis Elektronik CAD - Programm [Target 3001!](http://server.ibfriedrich.com/wiki/ibfwikide/index.php?title=Hauptseite) machte ich mich nun an den Schaltplan

![ATTiny says - Schaltplan](/uploads/2015-09-04-ATTiny-says-Schaltplan.jpg)