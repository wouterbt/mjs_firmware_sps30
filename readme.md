Meet-je-stad Firmware met SPS30 fijnstofsensor (particulate matter)
===================================================================

Dit is aangepaste code van v4 van de [mjs_firmware](https://github.com/meetjestad/mjs_firmware), waarbij het uitlezen van de SPS30 fijnstofsensor over I2C is toegevoegd. Deze code gaat ervan uit dat de sensor direct op een 5V voeding is aangesloten, en zet de sensor na iedere meting in de slaapstand. Alleen de waarden voor PM2.5 en PM10 (in ug/m3) worden uitgelezen. De code gebruikt een zelfgeschreven library `SPS30.h` voor compactheid.

De nieuwste versie van de mjs\_firmware gebruikt ook de SPS30 sensor. Echter, die versie gaat ervan uit dat de voeding van de sensor aan en uit wordt gezet door de microcontroller. Dat is bij oude MJS-bordjes niet mogelijk. Daarom wordt in deze versie de sensor na iedere meting in de slaapstand gezet, en voorafgaand aan iedere meting weer gewekt.

Een ander verschil is dat de nieuwste versie van de mjs\_firmware _alle_ waarden uit de sensor doorgeeft via LoRa. 