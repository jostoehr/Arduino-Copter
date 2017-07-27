boolean checkSuccessResponse() {
  // after sending a tx request, we expect a status response
  // wait up to 5 seconds for the status response
  if (xbee.readPacket(5000)) {
    // got a response!
    // should be a znet tx status              
    if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
       xbee.getResponse().getTxStatusResponse(txStatus);
       // get the delivery status, the fifth byte
       if (txStatus.getStatus() == SUCCESS) {
          // success.  time to celebrate
          return true;
       } else {
          // the remote XBee did not receive our packet. is it powered on?
          return false;
       }
    }      
  } else if (xbee.getResponse().isError()) {
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());
    return false;
  } else {
    // local XBee did not provide a timely TX Status Response.  Radio is not configured properly or connected
    return false;
  }
  return false;
}

