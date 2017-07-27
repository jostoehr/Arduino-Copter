XBeeResponse response = XBeeResponse();

// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

void getRxPacket() {
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        xbee.getResponse().getRx16Response(rx16);
        option = rx16.getOption();
        data = rx16.getData();
      } else {
        xbee.getResponse().getRx64Response(rx64);
        option = rx64.getOption();
        data = rx64.getData();
      }
    } else {
      // not something we were expecting
    }
  } else if (xbee.getResponse().isError()) {
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());
  }
}
/*
if(getRxPacket()) {
      /*switch(data[0]) {
        case 'M':
          motorsOn = true;
          break;
        case 'm':
          motorsOn = false;
          setAllServo(0);
          break;
        default:
          if(motorsOn) {*/
            /*int x_joy1 = data[0]*256 + data[1];
            int speedDrone = map(x_joy1, 4, 1018, 1150, 2000);
            setAllServo(speedDrone);
          //}
      //}
    }
*/

