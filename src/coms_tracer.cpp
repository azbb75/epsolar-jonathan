#include "coms_tracer.h"


ModbusMaster tracer;

uint16_t count = DIVIDER_HIST;

volatile bool rs485Busy = false;
uint16_t index_counter = 0;
struct powerData p_data;
struct genData gen_data;


void reset_modbus()
{
    //this is needed when modbus coms break down
    Serial.end();
    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    digitalWrite(1, HIGH);
    digitalWrite(3, HIGH);
    delay(50);
    Serial.begin(115200);
}

bool read_register_3100() {
  tracer.begin(1, Serial);
  uint8_t result = tracer.readInputRegisters(0x3100, 7);
  if (result != tracer.ku8MBSuccess) 
  {
    return false;
  } 
  p_data.pv.voltage[index_counter] = (long)tracer.getResponseBuffer(0x00) / 100.0f;
  p_data.pv.current[index_counter] = (long)tracer.getResponseBuffer(0x01) / 100.0f;
  p_data.pv.power[index_counter] = ((long)tracer.getResponseBuffer(0x03) << 16 | tracer.getResponseBuffer(0x02)) / 100.0f;
  p_data.bt.voltage[index_counter] = tracer.getResponseBuffer(0x04) / 100.0f;
  p_data.bt.current[index_counter] = (long)tracer.getResponseBuffer(0x05) / 100.0f;
  p_data.bt.temp[index_counter] = tracer.getResponseBuffer(0x11) / 100.0f;
  tracer.clearResponseBuffer();

#ifdef USE_TRACER_2
  tracer.begin(2, Serial);
  digitalWrite(COM_LED, 1);
  result = tracer.readInputRegisters(0x3100, 7);
  digitalWrite(COM_LED, 0);
  if (result != tracer.ku8MBSuccess) 
  {
    return false;
  } 
  p_data.pv.voltage_2[index_counter] = (long)tracer.getResponseBuffer(0x00) / 100.0f;
  p_data.pv.current_2[index_counter] = (long)tracer.getResponseBuffer(0x01) / 100.0f;
  p_data.pv.power_2[index_counter] = ((long)tracer.getResponseBuffer(0x03) << 16 | tracer.getResponseBuffer(0x02)) / 100.0f;
  p_data.bt.voltage_2[index_counter] = tracer.getResponseBuffer(0x04) / 100.0f;
  p_data.bt.current_2[index_counter] = (long)tracer.getResponseBuffer(0x05) / 100.0f;
  p_data.bt.temp_2[index_counter] = tracer.getResponseBuffer(0x11) / 100.0f;
  
#endif
  tracer.clearResponseBuffer();
  
  return true;
}


bool read_register_3300() {
  tracer.begin(1, Serial);
  uint8_t result = tracer.readInputRegisters(0x3300, 0x13);
  if (result != tracer.ku8MBSuccess) 
  {
    return false;
  } 

  gen_data.genToday = ((long)tracer.getResponseBuffer(0x0D) << 16 | tracer.getResponseBuffer(0x0C)) / 100.0f;
  gen_data.genMonth = ((long)tracer.getResponseBuffer(0x0F) << 16 | tracer.getResponseBuffer(0x0E)) / 100.0f;
  gen_data.genYear = ((long)tracer.getResponseBuffer(0x11) << 16 | tracer.getResponseBuffer(0x10)) / 100.0f;
  gen_data.genTotal = ((long)tracer.getResponseBuffer(0x13) << 16 | tracer.getResponseBuffer(0x12)) / 100.0f;
  tracer.clearResponseBuffer();

#ifdef USE_TRACER_2
  tracer.begin(2, Serial);
  digitalWrite(COM_LED, 1);
  result = tracer.readInputRegisters(0x3300, 0x13);
  digitalWrite(COM_LED, 0);
  if (result != tracer.ku8MBSuccess) 
  {
    return false;
  } 

  gen_data.genToday_2 = ((long)tracer.getResponseBuffer(0x0D) << 16 | tracer.getResponseBuffer(0x0C)) / 100.0f;
  gen_data.genMonth_2 = ((long)tracer.getResponseBuffer(0x0F) << 16 | tracer.getResponseBuffer(0x0E)) / 100.0f;
  gen_data.genYear_2 = ((long)tracer.getResponseBuffer(0x11) << 16 | tracer.getResponseBuffer(0x10)) / 100.0f;
  gen_data.genTotal_2 = ((long)tracer.getResponseBuffer(0x13) << 16 | tracer.getResponseBuffer(0x12)) / 100.0f;
  tracer.clearResponseBuffer();

#endif

  return true;
}

void read_from_tracer()
{

  if(!read_register_3300())
  {
    //failed to read. Exit
    Serial.println("Could not read Register 3300, trying modbus reset...");
    reset_modbus();
    digitalWrite(COM_LED, LOW);
    return;
  }
  if(!read_register_3100())
  {
    //failed to read. Exit
    Serial.println("Could not read Register 3100, trying modbus reset...");
    reset_modbus();
    digitalWrite(COM_LED, LOW);
    return;
  }
  p_data.time[index_counter] = millis();
  p_data.valid[index_counter] = true;


  count++;
  if(count >= DIVIDER_HIST){
    //read success. Increment array index.

    index_counter++;
    count = 0;
  }

  if(index_counter >= N_POINTS)
  {
    index_counter = 0;
  }


  digitalWrite(COM_LED,!digitalRead(COM_LED));
}

uint16_t get_index_counter(){
    return index_counter;
}



