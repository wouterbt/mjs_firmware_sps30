Meet-je-stad Firmware met SPS30 fijnstofsensor (particulate matter)
===================================================================

Dit is aangepaste code van v4 van de [mjs_firmware](https://github.com/meetjestad/mjs_firmware), waarbij het uitlezen van de SPS30 fijnstofsensor over I2C is toegevoegd. Deze code gaat ervan uit dat de sensor direct op een 5V voeding is aangesloten, en zet de sensor na iedere meting in de slaapstand. Alleen de waarden voor PM2.5 en PM10 (in ug/m3) worden uitgelezen. De code gebruikt een zelfgeschreven library voor compactheid (`SPS30.h` en `SPS30.cpp`).

De nieuwste versie van de mjs\_firmware gebruikt ook de SPS30 sensor. Echter, die versie gaat ervan uit dat de voeding van de sensor aan en uit wordt gezet door de microcontroller. Dat is bij oude MJS-bordjes niet mogelijk. Daarom wordt in deze versie de sensor na iedere meting in de slaapstand gezet, en voorafgaand aan iedere meting weer gewekt.

Een ander verschil is dat de nieuwste versie van de mjs\_firmware _alle_ waarden uit de sensor doorgeeft via LoRa.

Voor het uploaden van de software naar het Meet-je-stad-bordje is een [seriële programmer](https://github.com/meetjestad/mjs_programmer) nodig. Je kan voor het uploaden van de software ook een Arduino gebruiken als je die toevallig al hebt. Zet de power-jumper op "PRG" en sluit de programmer-pinnetjes als volgt aan: 
Vin → 5V op de Arduino  
GND → GND op de Arduino  
RxD → Digitaal 0 (RX) op de Arduino  
TxD → Digitaal 1 (TX) op de Arduino

Sluit dan op je Arduino RESET aan op GND. Daarmee wordt de chip op de Arduino uitgeschakeld en wordt de communicatie doorgestuurd naar het MjS-bordje. Installeer in de Arduino IDE de software zoals aangegeven in de [handleiding](https://github.com/meetjestad/mjs_firmware#basic-usage). Als je software wil uploaden naar het MjS-bordje, kies dan Tools / Board / MJS Meetstation. Maak dan verbinding tussen de RESET-pinnetjes van het bordje. Druk dan op de Upload-knop in de Arduino-IDE. Op het moment dat er "uploading" komt te staan, maak dan de verbinding los van de RESET-pinnetjes. De software wordt dan op de MjS-microcontroller gezet i.p.v. op de Arduino.