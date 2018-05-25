---
layout: post
title:  "Screencloud unter Ubuntu 16.04 installieren"
date:   2016-07-15 01:58:29 +0200
categories: 
redirect_from:
#  - 201x/x/
---
<!-- ![Screencloud Logo](/wp-content/uploads/2016/07/b925d8ad974fc5e30901dfcf78ca14e8_400x400-e1468541679837.png) -->

Da ich gerade testweise einer Linux Distribution (Kubuntu 16.04) erneut eine Chance gebe, bei mir als Produktivsystem eingesetzt zu werden (sowohl Desktop als auch Laptop), bin ich vor kurzem auf die erste größere Hürde gestoßen. Und zwar war es mir aufgrund der fehlenden `libqtmultimediakit` Bibliothek nicht möglich, die screencloud .deb zu installieren.

Kurz und knapp habe ich folgende Schritte befolgt, um screencloud trotzdem zu installieren:
<!--more-->

  - [Diese libqtmultimediakit .deb](http://de.archive.ubuntu.com/ubuntu/pool/universe/q/qtmobility/libqtmultimediakit1_1.2.0-1ubuntu2_amd64.deb) herunterladen und installieren
  - `sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/olav-st/xUbuntu_15.10/ /' >> /etc/apt/sources.list.d/screencloud.list"`
  - `sudo apt update`
  - `sudo apt install screencloud`


Nun hatte ich aber immer noch folgenden Fehler beim Starten von screencloud mit SFTP Plugin:
`ImportError: No module named Crypto.PublicKey`

Das konnte durch ein einfaches `sudo pip install crypto pycrypto` behoben werden.

Ich nutze das SFTP Plugin, um Bilder automatisch auf meinen vServer hochladen zu lassen und den Link in die Zwischenablage zu bekommen (macht das Teilen von Bildern über nur-Text-Chat deutlich einfacher).
Hier sind meine Einstellungen:

![Einstellungen des SFTP-Plugins](https://share.gingerlabs.de/screen_2016-07-15_01-55-14_f0HvPttW.png)

Der Name `screen_%Y-%m-%d_%H-%M-%S_{rnd_s}` sorgt dafür, dass der Dateiname gemäß dem gegebenen Muster erzeugt wird (Beispiel in der letzten Zeile des Screenshots.



Erhaltene Fehlermeldungen mit anderen Installationsmethoden:


  - `/opt/screencloud/screencloud: error while loading shared libraries: libquazip.so.0: cannot open shared object file: No such file or directory`
  - ```The following packages have unmet dependencies:  
screencloud : Depends: libqtmultimediakit1 but it is not installable  
E: Unable to correct problems, you have held broken packages.```
