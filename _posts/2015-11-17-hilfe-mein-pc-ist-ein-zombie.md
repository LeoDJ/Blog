---
layout: post
title:  "Hilfe, mein PC ist ein Zombie!"
date:   2015-11-17 18:18:27 +0100
categories: Allgemein Windoof
tags: 
  - Lösung
  - Problem
  - waketimer
  - Windoof
  - Windows
  - Windows 10
---


Einige kennen das vermutlich auch. Man ist für eine kurze Weile weg vom PC und schickt den Rechner deshalb in den Standby. Als man jedoch wiederkommt ist er wieder an!? Gruselig.

In den meisten Fällen lässt sich das Problem recht schnell auf die Maus o.ä. zurückführen, die sich einbildet, sie hätte sich noch einen Mikrometer bewegt und dadurch den PC wieder aufweckt. Dabei wiederum lässt sich der Täter im Normalfall durch ein einfaches `powercfg -lastwake `in der Windows Konsole aufspüren.

In meinem Fall war das jedoch etwas anderes, denn `powercfg -lastwake` liefert mir kein einziges Gerät zurück, das den PC aufgeweckt haben sollte. Auch im Gerätemanager ist die "Aufweckfähigkeit" jedes Gerätes unterbunden und zur Sicherheit dürfen auch die Waketimer den PC nicht aufwecken.

An diesem Punkt konnte mir selbst Google nicht mehr weiterhelfen. Denn schließlich hatte ich schon alles getan, um unerwünschtes Aufwecken zu unterbinden. Sogar den Waketimern hatte ich ihre Weckfähigkeit entzogen

Denkste! Aus reiner Neugierde führte ich auch noch den Befehl
`powercfg -waketimers` aus. Und siehe da: es war tatsächlich ein Waketimer aktiv!
`Der von [SERVICE] \Device\HarddiskVolume2\Windows\System32\svchost.exe (SystemEventsBroker) gesetzte Zeitgeber läuft um $in5min am $heute ab.
Ursache: Die geplante Aufgabe "NT TASK\Microsoft\Windows\UpdateOrchestrator\Reboot" wird ausgeführt. Hierzu muss der Computer reaktiviert werden.`

Aha! Der Computer muss dazu also reaktiviert werden... Komisch, da ich in den Energieeinstellungen den Waketimern doch eigentlich verboten hatte, den PC aufzuwecken. Ein kurzer Check bestätigt mir, Waketimer dürfen laut Einstellung den PC immer noch nicht aufwecken. Trotzdem hat es dieser getan. :o

An diesem Punkt sollte man wohl erwähnen, dass dieses Problem früher so nicht aufgetreten ist und erst seit der Installation von Windows 10 auftrat... Oh, hm, da hat einer bei Microschrott wohl wieder geschlampt und es geschafft, die Waketimer-Einstellung komplett zu ignorieren. (Ich frage mich echt warum ich immer noch bei denen bin... Achja, stimmt. Spiele.)

Also rein in die Aufgabenplanung und durchs Seitenmenü gehangelt (Microsoft > Windows > UpdateOrchestrator > Reboot => Eigenschaften > Bedingungen) und ein erneuter Aha-Moment: Da ist ja der fiese kleine Haken.


![Da haben wir den Lümmel!](/uploads/2015-11-17-Reaktivieren.png)

Tja, seitdem der Haken draußen ist, hatte ich keinerlei Probleme mit dem zombieartigen Aufwachen meines PCs mehr. :)

Fazit: Windoof ist und bleibt eben immer noch eins: doof!