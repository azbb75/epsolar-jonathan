#ifndef COMS_TRACER_H
#define COMS_TRACER_H

#include <Arduino.h>
#include <ModbusMaster.h>

#define N_POINTS 360
#ifdef HARDWARE_V2
#define COM_LED D4
#elif HARDWARE_V1
#define COM_LED D1
#endif
#define LED 2  //On board LED


#define RS485_PERIOD_MS 200

// fancy math to find out how often to sample chart
#define DIVIDER_HIST ((24*60*1000)/N_POINTS/(RS485_PERIOD_MS))*60

//#define USE_TRACER_2


struct pvData{
  float voltage[N_POINTS];
  float current[N_POINTS];
  float power[N_POINTS];
#ifdef USE_TRACER_2
  float voltage_2[N_POINTS];
  float current_2[N_POINTS];
  float power_2[N_POINTS];
#endif
};
struct btData{
  float current[N_POINTS];
  float voltage[N_POINTS];
  float temp[N_POINTS];
#ifdef USE_TRACER_2
  float current_2[N_POINTS];
  float voltage_2[N_POINTS];
  float temp_2[N_POINTS];
#endif
};
struct powerData{
  pvData pv;
  btData bt;
  unsigned long time[N_POINTS];
  bool valid[N_POINTS] = {};
};

struct genData{
  float genToday;
  float genMonth;
  float genYear;
  float genTotal;

#ifdef USE_TRACER_2
  float genToday_2;
  float genMonth_2;
  float genYear_2;
  float genTotal_2;
#endif
};

extern uint16_t index_counter;
extern uint16_t count;
extern struct powerData p_data;
extern struct genData gen_data;


bool read_register_3100();
bool read_register_3300();
void read_from_tracer();

struct powerData get_p_data();
struct genData get_gen_data();

#endif

