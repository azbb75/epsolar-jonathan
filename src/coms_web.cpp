
#include "coms_web.h"
#include "coms_tracer.h"

const char *header = "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/xml\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Accept-Ranges: none\r\n"
    "Transfer-Encoding: chunked\r\n"
    "Connection: close\r\n"
    "\r\n";

AsyncWebServer server(80);
DNSServer dns;




uint32_t init_wifi_manager(){
  AsyncWiFiManager wifiManager(&server,&dns);
  //wifiManager.resetSettings();
  wifiManager.setBreakAfterConfig(true);
  digitalWrite(WIFI_LED,0);
  wifiManager.autoConnect("SOLAR");
  return 1;
}

uint32_t init_webserver(){
  server.on("/curr_data.xml", HTTP_GET, [](AsyncWebServerRequest *request){
      digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
      XML_curr_data(request);
    });
  server.on("/hist_data.xml", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
    XML_hist_data(request);
  });

  server.on("/gen_data.xml", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
    XML_gen_data(request);
  });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.onNotFound(notFound);
  server.begin();                  //Start server

  return 1;
}

void XML_hist_data(AsyncWebServerRequest *request)
{
  int* lambda_copy_ix = new int(index_counter+2);
  int* lambda_counter = new int(0); 
  int* lambda_state = new int(0); 
  AsyncWebServerResponse *response = request->beginChunkedResponse("text/xml",  [lambda_counter, lambda_state, lambda_copy_ix](uint8_t *buffer, size_t maxLen, size_t index) mutable -> size_t  {
    String temp = "";


    if(*lambda_state == XML_Done)
    {
    delete lambda_counter;
    delete lambda_state;
    delete lambda_copy_ix;
    return 0;
    }

    if(*lambda_state == XML_Body)
    {
      temp = "";
      for(uint32_t iteration = 0; iteration < 5 || temp.length() == 0; iteration++)
      {
        uint32_t index = (*lambda_copy_ix+*lambda_counter)%N_POINTS;
        if(p_data.valid[index])
        {
          temp.concat("<d_p t=\""+String(p_data.time[index])+"\">");

          temp.concat("<pv_p>");
          temp.concat(String(p_data.pv.power[index]));
          temp.concat("</pv_p>");

          temp.concat("<pv_c>");
          temp.concat(String(p_data.pv.current[index]));
          temp.concat("</pv_c>");

          temp.concat("<pv_v>");
          temp.concat(String(p_data.pv.voltage[index]));
          temp.concat("</pv_v>");

          temp.concat("<b_v>");
          temp.concat(String(p_data.bt.voltage[index]));
          temp.concat("</b_v>");

          temp.concat("<b_c>");
          temp.concat(String(p_data.bt.current[index]));
          temp.concat("</b_c>");


#ifdef USE_TRACER_2
          temp.concat("<pv_p_2>");
          temp.concat(String(p_data.pv.power_2[index]));
          temp.concat("</pv_p_2>");

          temp.concat("<pv_c_2>");
          temp.concat(String(p_data.pv.current_2[index]));
          temp.concat("</pv_c_2>");

          temp.concat("<pv_v_2>");
          temp.concat(String(p_data.pv.voltage_2[index]));
          temp.concat("</pv_v_2>");

          temp.concat("<b_v_2>");
          temp.concat(String(p_data.bt.voltage_2[index]));
          temp.concat("</b_v_2>");

          temp.concat("<b_c_2>");
          temp.concat(String(p_data.bt.current_2[index]));
          temp.concat("</b_c_2>");
#endif

          temp.concat("</d_p>");
        }

        if(*lambda_counter > N_POINTS-5)
        {
          *lambda_state = XML_Done;
          temp.concat("</p_data>");
          iteration = 5;

        }
        else
        {
          *lambda_counter = *lambda_counter + 1;
        }
      }
    }

    if(*lambda_state == XML_Preamble)
    {
      temp = "";
      temp.concat("<?xml version = \"1.0\" ?>");
      temp.concat("<p_data>");
      temp.concat("<curr_time>");
      temp.concat(String(millis()));
      temp.concat("</curr_time>");
      *lambda_state = XML_Body;
    }
    strncpy((char *)buffer, temp.c_str(), maxLen);
    return min(maxLen, temp.length());
  });
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}


void XML_curr_data(AsyncWebServerRequest *request)
{
  AsyncResponseStream *response = request->beginResponseStream("text/xml");
  response->addHeader("Access-Control-Allow-Origin", "*");
  uint16_t ix = index_counter;
  
  response->print("<?xml version = \"1.0\" ?>");
  response->print("<p_data>");

  if(p_data.valid[ix])
  {
    response->print("<d_p t=\""+String(p_data.time[ix])+"\">");
    
    response->print("<pv_v>");
    response->print(String(p_data.pv.voltage[ix]));
    response->print("</pv_v>");

    response->print("<pv_c>");
    response->print(String(p_data.pv.current[ix]));
    response->print("</pv_c>");
    
    response->print("<pv_p>");
    response->print(String(p_data.pv.power[ix]));
    response->print("</pv_p>");

    response->print("<b_c>");
    response->print(String(p_data.bt.current[ix]));
    response->print("</b_c>");

    response->print("<b_v>");
    response->print(String(p_data.bt.voltage[ix]));
    response->print("</b_v>");
#ifdef USE_TRACER_2
    response->print("<pv_v_2>");
    response->print(String(p_data.pv.voltage_2[ix]));
    response->print("</pv_v_2>");

    response->print("<pv_c_2>");
    response->print(String(p_data.pv.current_2[ix]));
    response->print("</pv_c_2>");
    
    response->print("<pv_p_2>");
    response->print(String(p_data.pv.power_2[ix]));
    response->print("</pv_p_2>");

    response->print("<b_c_2>");
    response->print(String(p_data.bt.current_2[ix]));
    response->print("</b_c_2>");

    response->print("<b_v_2>");
    response->print(String(p_data.bt.voltage_2[ix]));
    response->print("</b_v_2>");
#endif

    response->print("</d_p>");
  }
  response->print("</p_data>");

  request->send(response);
}

void XML_gen_data(AsyncWebServerRequest *request)
{

  AsyncResponseStream *response = request->beginResponseStream("text/xml");
  response->addHeader("Access-Control-Allow-Origin", "*");
  
  response->print("<?xml version = \"1.0\" ?>");
  response->print("<g_data>");

  response->print("<gt>");
  response->print(String(gen_data.genToday));
  response->print("</gt>");
  response->print("<gm>");
  response->print(String(gen_data.genMonth));
  response->print("</gm>");
  response->print("<gy>");
  response->print(String(gen_data.genYear));
  response->print("</gy>");
  response->print("<gtot>");
  response->print(String(gen_data.genTotal));
  response->print("</gtot>");

#ifdef USE_TRACER_2
  response->print("<gt_2>");
  response->print(String(gen_data.genToday_2));
  response->print("</gt_2>");
  response->print("<gm_2>");
  response->print(String(gen_data.genMonth_2));
  response->print("</gm_2>");
  response->print("<gy_2>");
  response->print(String(gen_data.genYear_2));
  response->print("</gy_2>");
  response->print("<gtot_2>");
  response->print(String(gen_data.genTotal_2));
  response->print("</gtot_2>");
#endif

  response->print("</g_data>");

  request->send(response);
}


void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}


