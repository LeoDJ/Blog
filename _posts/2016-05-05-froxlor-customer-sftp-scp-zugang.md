---
layout: post
title:  "Froxlor Customer SFTP/SCP Zugang"
date:   2016-05-05 03:09:41 +0200
categories: Linux
tags: Froxlor libnss-mysql SCP SFTP
---

![SFTP Logo](/uploads/2016-05-05-sftp.png)
Da ich mich enorm daran störte, dass ich nicht einfach per SFTP (über WinSCP) Dateien auf meine share-Subdomain hochladen konnte, wollte ich dies endlich einmal ändern.

[Hier](froxlor-customer-sftp-scp-zugang/#sfs) geht es direkt zur Schritt-für-Schritt Anleitung

<!--more-->

Für meine Webserver-Konfiguration kommt [froxlor](https://www.froxlor.org/) zum Einsatz. Dieses Management Interface bietet unter anderem die Möglichkeit, einzelne Customer zu erstellen, denen dann Subdomains zugewiesen werden können. Ich für meinen Teil habe für jede Domain einen einzelnen Customer, um diese schön zu trennen.

Nach vielem Herumprobieren bin ich auf eine akzeptable Lösung gekommen, damit sich der Benutzer über SFTP einloggen kann und auf sein Verzeichnis, aber nicht auf andere Verzeichnisse zugreifen kann.

Für jeden froxlor-Customer wird standardmäßig ein "virtueller" Linux-Benutzer angelegt. Mit diesem kann man allerdings in der Standard-Konfiguration nicht viel anfangen. Damit man diese Benutzer z.B. zum Einloggen benutzen kann, muss man im froxlor-Interface erst einmal libnss-mysql aktivieren. (System &gt; Configuration &gt; $Distro &gt; Other (System) &gt; libnss-mysql)

Nachdem dies eingerichtet wurde, sind die froxlor-Customer normale Linux-Benutzer, allerdings können diese sich standardmäßig nicht über SSH einloggen, da bei diesen die `/bin/false`-Shell eingestellt ist, was sie aber auch nicht können müssen.

Damit der SFTP-Benutzer nicht auf andere Ordner zugreifen darf, muss er in einem Chroot-Jail eingesperrt werden. Dazu muss aber jeder Ordner bis zum jail-Ordner von Root besessen werden. Standardmäßig befinden sich die Customer-Ordner aber in einem Unterordner im froxlor-Ordner. Dieser darf aber nicht von Root besessen werden, da sonst froxlor nicht mehr in den Ordner schreiben darf, was es aber weiterhin können muss.  
Also wird der Customer-Ordner in einen separaten Ordner (in einem von Root besessenen Ordner) gemountet.

<h3 id="sfs">Disclaimer</h3>

Die Ausführung der folgenden Befehle geschieht auf eigene Gefahr. Für zerschossenen Server-Konfigurationen o.ä. übernehme ich keinerlei Haftung.

### Schritt-für-Schritt

Also ergibt sich folgender Schritt-für-Schritt-Ablauf:

#### Einmalige Schritte

  1. libnss-mysql in froxlor aktivieren  
     (System &gt; Configuration &gt; $Distro &gt; Other (System) &gt; libnss-mysql)
  1. `sudo groupadd sftpUser`
  1. `sudo mkdir /home/sftpUsers`
  1. folgende Zeilen in `/etc/ssh/sshd_config` einfügen:
    
    Match Group sftpUser
    ChrootDirectory /home/sftpUsers/%u
    ForceCommand internal-sftp

  1. `sudo systemctl restart sshd`

#### Schritte pro Benutzer
Diese Schritte muss man jeweils für jeden Benutzer ausführen, dem man SFTP-Zugang gewähren möchte.

ACHTUNG! Unbedingt bei jedem Befehl $U durch den entsprechenden Customer-Username ersetzen (z.B. `share`)

  1. [optional] Froxlor Customer anlegen (es kann auch ein bereits Bestehender benutzt werden)
  1. `sudo usermod -aG sftpUser $U`
  1. `sudo mkdir /home/sftpUsers/$U`
  1. `sudo mkdir /home/sftpUsers/$U/html`
  1. `sudo chown $U:$U/home/sftpUsers/$U/html`
  1. `sudo mount --bind /var/customers/webs/$U /home/sftpUsers/$U/html`
  1. `sudo -i`
  1. `echo '/var/customers/webs/$U /home/sftpUsers/$U/html    none  bind' &gt;&gt; /etc/fstab`
  1. `exit`
  1. `sudo nscd --invalidate=passwd`


Nun sollte man sich über SFTP/SCP mit den froxlor-Zugangsdaten des jeweiligen Customers einloggen können und lediglich einen html-Ordner sehen. Durch diesen kann man auf den Document-Root des Customers zugreifen, also z.B. eine neue index.html hochladen.

