// Check UID
boolean checkUID ( byte c1[], byte c2[] ) {
  boolean match = false;          // initialize card match to false
  if ( c1[0] != 0 )      // Make sure there is something in the array first
    match = true;       // Assume they match at first
  for ( uint8_t k = 0; k < __CARD_LENGTH; k++ ) {   // Loop
    if ( c1[k] != c2[k] )     // IF c1 != c2 then set match = false, one fails, all fail
      match = false;
  }
  return match;      // Return

}
