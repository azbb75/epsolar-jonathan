var chart_pv_power_buff = [];
var chart_b_voltage_buff = [];
var chart_b_current_buff = [];
var chart_pv_current_buff = [];
var chart_pv_voltage_buff = [];
var timeStamp = [];

var con = {
    type: 'line',
    data: {
        labels: timeStamp, //Bottom Labeling
        datasets: [{
            label: "PV Watts",
            yAxisID: 'p',
            fill: false,  //Try with true
            backgroundColor: 'yellow', //Dot marker color
            borderColor: 'yellow', //Graph Line Color
            borderWidth: 1,
            data: chart_pv_power_buff,
            pointRadius: 0,
            pointHoverRadius: 0,
            cubicInterpolationMode: 'monotone'
        },
        {
            label: "PV Voltage",
            yAxisID: 'v',
            fill: false,  //Try with true
            backgroundColor: 'aqua', //Dot marker color
            borderColor: 'aqua', //Graph Line Color
            borderWidth: 1,
            data: chart_pv_voltage_buff,
            pointRadius: 0,
            pointHoverRadius: 0,
            cubicInterpolationMode: 'monotone'
        },
        {
            label: "Batt Voltage",
            yAxisID: 'bv',
            fill: false,  //Try with true
            backgroundColor: 'red', //Dot marker color
            borderColor: 'red', //Graph Line Color
            borderWidth: 1,
            data: chart_b_voltage_buff,
            pointRadius: 0,
            pointHoverRadius: 0,
            cubicInterpolationMode: 'monotone'
        }],
    },
    options: {
        responsive: true,
        legend: {
            //display: false
         },
        title: {
                display: true,
                text: "Last 24 Hours"
            },
        maintainAspectRatio: false,
        elements: {
        line: {
                tension: 0 //Smoothening (Curved) of data lines
            }
        },
        scales: {
            yAxes: [{
                id: 'p',
                ticks: {
                    beginAtZero:true,
                    max: 400,
                    min: 0,
                    fontColor: "yellow"
                },
                gridLines: {
                  display: true,
                  color: "#262626"
                }
            },
            {
                id: 'v',
                ticks: {
                    beginAtZero:true,
                    max: 80,
                    min: 0,
                    fontColor: "aqua"
                },
                gridLines: {
                    display: true,
                    color: "#262626"
                }
            },
            {
                id: 'bv',
                ticks: {
                    beginAtZero:true,
                    max: 16,
                    min: 0,
                    fontColor: "red"
                },
                gridLines: {
                    display: true,
                    color: "#262626"
                }
            }],
            xAxes: [{
                type: 'time',
                time: {
                    unit: 'hour'
                },
                ticks: {
                    autoSkip:true,
                    maxTicksLimit: 12
                },
                gridLines: {
                    display: true,
                    color: "#262626"
                }
            }]
        }
    }
}

//On Page load show graphs
$( window ).on('load', function() {
    var ctx = document.getElementById('canvas').getContext('2d');
    window.myLine = new Chart(ctx, con);
    });