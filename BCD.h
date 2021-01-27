
/** Fonction de conversion decimal -> BCD */
byte decimal_to_bcd(byte decimal) 
{
  return (decimal / 10 * 16) + (decimal % 10);
}

/** Fonction de conversion BCD -> decimal */
byte bcd_to_decimal(byte bcd) 
{
  return (bcd / 16 * 10) + (bcd % 16); 
}

/** Fonction pour gerer erreur de mapping des tubes */
byte inverse_bcd (byte bcd) 
{
  return  (bcd % 16) * 16 + (bcd / 16);
}
