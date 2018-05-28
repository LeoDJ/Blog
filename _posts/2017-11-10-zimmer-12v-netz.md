---
layout: post
title:  "Zimmer 12V Netz"
date:   2017-11-10 20:00:00 +0100
categories: Idee
tags: 12V Arduino LED Strom XT60
---

## Idee
Vor einiger Zeit fiel mir auf, wie viele Geräte ich im Zimmer rumstehen habe, die mit 12V versorgt werden. Z.B. Modellbauladegerät, Lüfter, LED Beleuchtung, etc. Natürlich hat auch jedes dieser Geräte jeweils ein eigenes Netzteil, was einerseits dafür sorgt, dass viele Steckdosen der Mehrfachsteckdosen dadurch eingenommen werden und andererseits, dass diese Netzteile auch während das Gerät ausgeschaltet ist ein klein wenig Strom verbrauchen. Daher die Idee: warum nicht einfach die 12V zentral umwandeln?

<!--more-->

Die generelle Notwendigkeit für 230V Wechselspannung im Haus ist natürlich nachvollziehbar. Wechselspannung kann man leicht und mit (verhältnismäßig) wenigen Verlusten transformieren und die hohe Spannung innerhalb eines Hauses bzw. Wohnblocks hält die Leitungsverluste relativ gering.

Innerhalb eines Zimmers sind diese Eigenschaften jedoch nicht notwendig. Viele Geräte benötigen dieselbe Spannung und die Leitungslänge beschränkt sich auf wenige Meter, was bei moderaten Strömen die Verluste gering hält.

## Bauteile
Als zentrales Netzteil soll ein altes Computer-ATX-Netzteil herhalten, da die Meisten sehr leistungsstark sind. Sie können über 20 Ampere bei 12V bereitstellen und da ich noch einige alte herumliegen habe, muss ich nicht extra eins kaufen.

Da alle LED Streifen und das Modellbauladegerät doch einige Ampere ziehen können entschied ich mich ein Kabel mit großem Querschnitt zuzulegen. Die Wahl fiel auf eine 30m Rolle 2x4mm² Lautsprecherkabel.
Das besteht zwar nur aus verkupfertem Aluminium als Leiter, bietet aber den selben Leitungswiderstand wie 2,5mm² Vollkupfer für deutlich weniger Geld.

Da ich das System so modular wie möglich halten möchte werden die Kabelstrecken an den Enden jeweils mit XT60-Verbindungen ausgestattet.

Geplant sind aktuell zwei Versorgungspunkte, an denen jeweils eine Art "XT60-Mehrfachsteckdose" angebracht werden soll. Die Idee hier ist, diese in Aufputz-Abzweigdose einzubauen.
An diese werden dann mit Adapterkabeln die Verbraucher angeschlossen.

## Verbraucher
Wie oben bereits kurz aufgezählt hier noch eine ausführlichere Beschreibung der Verbraucher, die an das 12V System angeschlossen werden sollen:

In meinem Zimmer befinden sich diverse LED Streifen zur Beleuchtung.
Über der Couch befindet sich ein RGB-LED-Streifen mit Fernbedienung zur Szenenbeleuchtung.
Über dem "Werkbrett" im Regal kleben 3 parallele Streifen weißer LED-Streifen als Arbeitsbeleuchtung (der macht sehr schön weiches Licht).
Geplant ist auch noch weitere RGB-LED-Streifen in den Schattenfugen an der Decke anzubringen.

Da meine Heizung sich hinter meinem Schreibtisch, unter dem Fenstersims, hinter den Monitoren befindet staut sich im Winter dort oft die Wärme, die so schlecht an das Zimmer abgegeben werden kann. Deshalb habe ich dort einen temporären, alten PC-Lüfter installiert, der die Luft unter dem Fenstersims herauspustet.

Außerdem befindet sich auf dem Werkbrett ein Buck-Boost-Modul als "Labornetzteil" für kleinere Testaufbauten.

Da ich in meiner Freizeit aktiv Quadcopter fliege müssen auch die Akkus entsprechend oft geladen werden. Das Ladegerät wird direkt mit 12V versorgt, und kann mit bis zu 80W laden. Verluste eingerechnet ergibt sich ein Stromfluss zwischen 7-8A bei 12V.

Als weitere Überlegung steht im Raum, auch den 3D Drucker über das 12V Netz zu versorgen. Der Vorteil wäre, dass nicht mehr das beigelegte Netzteil von fraglicher Qualität und Sicherheit genutzt werden müsste. Allerdings kann der Drucker durch das beheizte Bett bis zu 250W verbrauchen. Bei 12V wären das über 20A, wo es wiederum mit dem ATX-Netzteil knapp wird, sofern ich das Ladegerät gleichzeitig betreiben möchte.
Außerdem entsteht bei diesen Strömen doch ein gewisser Leitungsverlust, der auch noch mit dem dicken Kabel merkbar ist.

<!-- [caption id="attachment_2019" align="alignnone" width="1838"]<a href="https://gingerlabs.de/?attachment_id=2019" rel="attachment wp-att-2019"><img class="wp-image-2019 size-full" src="https://gingerlabs.de/wp-content/uploads/2017/11/Zimmer-12V-Bus-Skizze.png" alt="12V Bus Skizze" width="1838" height="858" /></a> Skizze des Aufbaus[/caption] -->
![](/uploads/2017-11-10-zimmer-12v-netz/Zimmer-12V-Bus-Skizze.png)

## Erweiterungsideen
Anstatt des ATX Netzteils könnte man auf ein Server-Netzteil ausweichen, von denen ich auch noch ein Paar da habe. Allerdings sind deren Lüfter auch auf niedrigster Stufe noch recht laut.

Man könnte das 12V Netz zu einem späteren Zeitpunkt perfekt an ein Solarsystem auf 12V Basis koppeln, das sich hauptsächlich aus den per Solar geladenen Akkus versorgt und bei zu geringer Spannung der Akkus ein Netzteil/Ladegerät zuschaltet.

Die passiven XT60-Verteiler könnten mit Arduino, Knöpfen und MOSFETs um schaltbare Ausgänge erweitert werden. Und als weiteren Gedanken eventuell auch an ein Home-Automation System angebunden werden.
Diese Erweiterung befindet sich aktuell bereits in Planung.

## Fazit
Ein 12V-Netz aufzubauen würde sich für die Anzahl der Verbraucher definitiv Lohnen und der Aufwand von Kabel verlegen und Verteilerdosen bauen hält sich auch in Grenzen.

Aktuell habe ich bereits Stecker, Kabel und Netzteil da und arbeite schon an den Verteilerdosen.