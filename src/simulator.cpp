#include "simulator.h"



void simulate_data()
{
  digitalWrite(COM_LED, 1);
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

  p_data.time[index_counter] = millis();
  
  p_data.pv.voltage[index_counter] = float(500+random(-20, 20))/10;
  p_data.pv.current[index_counter] = float(70+random(-30,30))/10;
  p_data.pv.power[index_counter] = float(350+random(-50,50))/10;
  p_data.bt.voltage[index_counter] = float(130+random(-10,10))/10;
  p_data.bt.current[index_counter] = float(250+random(-50,50))/10;

  gen_data.genToday = float(10+random(0, 20))/10;
  gen_data.genMonth = float(100+random(0, 20))/10;
  gen_data.genYear = float(1000+random(0, 20))/10;
  gen_data.genTotal = float(10000+random(0, 20))/10;






#ifdef USE_TRACER_2
  p_data.pv.voltage_2[index_counter] = float(500+random(-20, 20))/10;
  p_data.pv.current_2[index_counter] = float(70+random(-30,30))/10;
  p_data.pv.power_2[index_counter] = float(350+random(-50,50))/10;
  p_data.bt.voltage_2[index_counter] = float(130+random(-10,10))/10;
  p_data.bt.current_2[index_counter] = float(250+random(-50,50))/10;

  gen_data.genToday_2 = float(10+random(0, 20))/10;
  gen_data.genMonth_2 = float(100+random(0, 20))/10;
  gen_data.genYear_2 = float(1000+random(0, 20))/10;
  gen_data.genTotal_2 = float(10000+random(0, 20))/10;

#endif

  p_data.valid[(index_counter+1)%N_POINTS] = false;
  p_data.valid[(index_counter+2)%N_POINTS] = false;
  p_data.valid[(index_counter+3)%N_POINTS] = false;
  p_data.valid[(index_counter+4)%N_POINTS] = false;
  p_data.valid[index_counter] = true;
  digitalWrite(COM_LED, 0);

}