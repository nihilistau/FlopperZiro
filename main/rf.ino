void rf() {
  type = 4;
  switch (sceltaSubMenu) {
    case 0:
      subMenuDisplay();
      break;
    case 1:
      scanRf();
      break;
    case 2:
      sdMenuDisplay(4);
      break;
  }
}

//+=============================================================================
// Display RF
//
void scanRf() {
  if (scanning == 1) {
    graficascan();
    if (mySwitch.available()) {
      Serial.print("Received ");
      Serial.println(mySwitch.getReceivedValue());
      Serial.print(mySwitch.getReceivedBitlength());
      Serial.println("bit ");
      Serial.print("Protocol: ");
      Serial.println(mySwitch.getReceivedProtocol());
      rfvalue = mySwitch.getReceivedValue();
      rfbit = mySwitch.getReceivedBitlength();
      rfprotocol = mySwitch.getReceivedProtocol();
      mySwitch.resetAvailable();
      scanning = 0;
    }
  } else {
    scanbase();
    display.setCursor(25, 25);
    display.println("Value " + String(rfvalue));
    display.setCursor(20, 35);
    display.println("Bit " + String(rfbit));
    display.setCursor(60, 35);
    display.println("Protocol " + String(rfprotocol));
  }
  battery();
  checkModuleButton(4);
}

void emulateRf() {
  scanbase();
  display.setCursor(33, 30);
  display.println("Sending...");
  battery();
  mySwitch.send(rfvalue, rfbit);
  delay(2000);
}

void saveRf() {
  scanbase();
  if (scanning == 0) {
    if (sdbegin) {
      display.setCursor(33, 30);
      display.println("Saving...");
      for (int i = 0; i < 100; i++) {

        String title;
        if (i < 10 && i >= 0) {
          title = "/rf/rf_0" + String(i);
          title = title + ".txt";
        } else {
          title = "/rf/rf_" + String(i);
          title = title + ".txt";
        }

        if (SD.exists(title)) {
          //display.setCursor(33, 30);
          //display.println("Già esistente");
        }else {
          file = SD.open(title, FILE_WRITE);
          file.println(rfvalue);
          file.println(rfbit);
          file.println(rfprotocol);
          file.close();
          break;
        }
      }
    } else {
      display.setCursor(33, 30);
      display.println("SD Error...");
    }
  } else {
    display.setCursor(30, 30);
    display.println("Nothing to send");
  }
  battery();
  delay(2000);
}
