---
layout: post
title:  "Addressable LED Comparison"
categories: Projekte LED
tags: WS2812 APA102 Addressable-LED
excerpt_separator: <!--more-->  # for some reason it's needed here but works elsewhere without?
---

A while ago I started collecting details of different addressable LED types. This list is by no means complete, nor 100% correct, but I never found a similar comparison overview elsewhere:

<!--more-->

| LED             | PWM Frequency                      | ct/LED[^1] | All-white current | Quiescent Current | Colors | Voltage  | Notes                                                                                                                                                         | Datasheet                                                                                                                                                                                 |
|-----------------|------------------------------------|------------|-------------------|-------------------|--------|----------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| WS2811          | 400 Hz                             | 3          |                   | ~1 mA             | RGB    | 12 V[^2] |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/WS2811.pdf)                                                                                                                          |
| WS2812B         | 430 Hz                             | 5          |                   | 0.6 mA            | RGB    | 5 V      |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/WS2812B.pdf)                                                                                                                         |
| WS2812C         | 2 kHz                              |            | 5 mA              | 0.3 mA            | RGB    | 5 V      |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/WS2812C.pdf)                                                                                                                         |
| WS2813          | 2 kHz                              | 8.5        |                   |                   | RGB    | 5 V      | - Backup data pin <br>- Integrated capacitor                                                                                                                  | [PDF](/uploads/2022-05-29-addressable-led-comparison/WS2813.pdf)                                                                                                                          |
| WS2815          | 2 kHz                              | 7.5        |                   |                   | RGB    | 12 V     | - Backup data pin <br>- Directly 12V compatible, although [inefficiently](https://twitter.com/_LeoDJ/status/1146876845197090823)                              | [PDF](/uploads/2022-05-29-addressable-led-comparison/WS2815.pdf)                                                                                                                          |
| WS2816B         | 10 kHz                             |            |                   | 0.7 mA            | RGB    | 5V       | - Backup data pin <br>- 16 bit resolution per color <br>- Additional 4 bit gamma <br>- Only available in small SMD packages and no strips currently available | [PDF (English, auto translated)](/uploads/2022-05-29-addressable-led-comparison/WS2816B-2020_en.pdf) <br>[PDF (Chinese)](/uploads/2022-05-29-addressable-led-comparison/WS2816B-2020.pdf) |
| SK6812          | 1.1 kHz                            |            |                   | 1 mA              | RGB    | 5 V      |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/SK6812_RGB.pdf)                                                                                                                      |
| SK6812RGBW      | 1.1 kHz                            | 9.5        |                   | 1 mA              | RGBW   | 5 V      |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/SK6812_RGBW.pdf)                                                                                                                     |
| SK6812WWA       | 1.1 kHz                            |            |                   | 1 mA              | W/WW/A | 5 V      |                                                                                                                                                               | [PDF](/uploads/2022-05-29-addressable-led-comparison/SK6812_WWA.pdf)                                                                                                                      |
| APA102          | 19.2 kHz (RGB) <br>580 Hz (global) | 10.5       | 24.5 mA           | 1 mA              | RGB    | 5 V      | - SPI protocol <br>- [Protocol Quirks](https://cpldcpu.wordpress.com/2014/11/30/understanding-the-apa102-superled/)                                           | [PDF](/uploads/2022-05-29-addressable-led-comparison/APA102.pdf)                                                                                                                          |
| SK9822          | 4.7 kHz (RGB) <br>CC (global)      | 11.5       | 20 mA             | 1 mA              | RGB    | 5 V      | - Constant current global brightness <br>- [APA102 Comparison](https://cpldcpu.wordpress.com/2016/12/13/sk9822-a-clone-of-the-apa102/)                        | [PDF](/uploads/2022-05-29-addressable-led-comparison/SK9822.pdf)                                                                                                                          |
| APA107          | 9 kHz                              |            |                   |                   | RGB    | 5V       | - APA102 SPI protocol <br>- Constant current global brightness (probably)                                                                                                                                            | [PDF]([PDF](/uploads/2022-05-29-addressable-led-comparison/APA107.pdf))                                                                                                                   |
| HD107S / NS107S | 27 kHz                             |            |                   | 1 mA              | RGB    | 5V       | - APA102 SPI protocol <br>- Constant current global brightness (probably)                                                                                     | [PDF](/uploads/2022-05-29-addressable-led-comparison/NS107S.pdf)                                                                                                                          |
| HD108 / NS108   | 27 kHz                             |            |                   | 0 mA?             | RGB    | 5V       | - SPI protocol <br>- 16 bit color + 5 bit CC per color                                                                                                        | [PDF](/uploads/2022-05-29-addressable-led-comparison/NS108.pdf)                                                                                                                           |



If you want to expand or correct this list, please send a [pull request or issue](https://github.com/LeoDJ/Blog/blob/master/_posts/2022-05-29-addressable-led-comparison.md).

## Other niche LED types
* UCS2904
  * Like WS2811 IC, but RGBW and for higher voltages out of the box
  * Probably SK6812 RGBW protocol
* BS0815 / LC8808 / GS8205
  * Like WS2815 (12V), but 12 bit PWM with internal gamma table (still 8 bit data)
  * 8 kHz RGB PWM
  * Internal test patterns
  * [LC8808 PDF](http://addressable-led.com/UploadFile/upi/file/20190318/LC8808-LED.pdf)
  * [GS8205 PDF](https://www.ledlightinghut.com/files/GS8208.pdf)


[^1]: Rough estimation based on prices of 5m 60 LEDs/m IP20 strip on AliExpress
[^2]: When used in 12V-strip configuration (3 LEDs per IC), only addressable in groups of 3 LEDs

<style type="text/css">
    /* Expand table completely, users now might have to scroll horizontally, but the table isn't completely cramped that way */
    table {
        width: max-content;
    }
</style>