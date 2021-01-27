
//byte isBandLimitReached = 0;

//boolean stereo ;

int32_t currFreq = 969 ;  

int32_t FREQ;

float defaultStations[24] = { 88.2, 88.7, 89.9, 90.7, 91.1, 91.7,  92.9, 93.7, 94.2, 94.8,95.3, 
95.7, 96.9, 99.2, 100.5, 100.9, 101.5, 102.3, 103.3, 104.1, 105.1, 105.5, 105.9, 107.1};

float stations[24] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
0.0,0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,};

byte stationIndex = 0;

// EEPROM (SAVE frequency and Index station)
int address = 1;
int addressStationIndex = 100;

TEA5767N radio = TEA5767N();

// -------------------------------------------------------------------

void radioStart() 
{
    radio.mute();
    radio.selectFrequency(currFreq / 10.0 ); // INT to FLOAT
   // Serial.println(currFreq /10, 1 );
   // Serial.println(currFreq / 10.0 , 1);
    radio.turnTheSoundBackOn();
}
// -------------------------------------------------------------------

void loadStations(int i) 
{
        stations[i] = defaultStations[i];
        currFreq = stations[i] *10;
        radioStart();
        EEPROM.put(address, currFreq);
        EEPROM.put(addressStationIndex, i);
        FREQ= currFreq;
        updateDisplay(FREQ);
} 


