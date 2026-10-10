
setInterval(function() {
	  GetCurrData();
  }, 2000);

setInterval(function() {
    GetGenData();
  }, 1000*60*5);
  
setInterval(function() {
  GetHistData();
}, 1000*60*3);

var server_URL = ""

function GetHistData() {
  $.ajax({url: server_URL + "/hist_data.xml", success: function(responseXML){
      var dataPoints = responseXML.getElementsByTagName("d_p");
      var currTime = responseXML.getElementsByTagName("curr_time")[0].childNodes[0].nodeValue;
      
      chart_pv_voltage_buff.length = 0;
      chart_pv_power_buff.length = 0;
      chart_pv_current_buff.length = 0;
      chart_b_current_buff.length = 0;
      chart_b_voltage_buff.length = 0;
      timeStamp.length = 0;
      
      for (let item of dataPoints){

        chart_pv_power_buff.push(item.getElementsByTagName("pv_p")[0].childNodes[0].nodeValue);
        chart_pv_voltage_buff.push(item.getElementsByTagName("pv_v")[0].childNodes[0].nodeValue);
        chart_b_current_buff.push(item.getElementsByTagName("b_c")[0].childNodes[0].nodeValue);
        chart_pv_current_buff.push(item.getElementsByTagName("pv_c")[0].childNodes[0].nodeValue);
        chart_b_voltage_buff.push(item.getElementsByTagName("b_v")[0].childNodes[0].nodeValue);

        timeStamp.push(moment().subtract((currTime - item.attributes[0].value), 'milliseconds'));
      }
      window.myLine.update(0)
      console.log("Chart refreshed!")
    }
  });
}

function GetCurrData() {
  $.ajax({url: server_URL + "/curr_data.xml", success: function(responseXML){
    g_power.refresh(responseXML.getElementsByTagName("pv_p")[0].childNodes[0].nodeValue);
    g_voltage.refresh(responseXML.getElementsByTagName("pv_v")[0].childNodes[0].nodeValue);
    g_bvoltage.refresh(responseXML.getElementsByTagName("b_v")[0].childNodes[0].nodeValue);
    g_current.refresh(responseXML.getElementsByTagName("pv_c")[0].childNodes[0].nodeValue);
    g_bcurrent.refresh(responseXML.getElementsByTagName("b_c")[0].childNodes[0].nodeValue);
    console.log("Gauges refreshed!")
  }});
}

function GetGenData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      $("#gen_today").text(this.responseXML.getElementsByTagName("gt")[0].childNodes[0].nodeValue + " kWh")
      $("#gen_month").text(this.responseXML.getElementsByTagName("gm")[0].childNodes[0].nodeValue + " kWh")
      $("#gen_year").text(Math.trunc(this.responseXML.getElementsByTagName("gy")[0].childNodes[0].nodeValue) + " kWh")
      $("#gen_total").text(Math.trunc(this.responseXML.getElementsByTagName("gtot")[0].childNodes[0].nodeValue) + " kWh")
      console.log("Table refreshed!");
    }
  };
  xhttp.open("GET", server_URL + "/gen_data.xml", true);
  xhttp.send();
}

$( window ).on('load', function() {
  GetHistData();
  GetGenData();
});
  