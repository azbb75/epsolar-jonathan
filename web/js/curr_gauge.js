var g_power, g_current, g_voltage, g_bvoltage, g_bcurrent;

//On Page load show graphs
$( window ).on('load', function() {
	g_current = new JustGage({
  		id: "g_current",
  		min: 0,
      	max: 10,
		decimals: 1,
		gaugeWidthScale: 0.8,
		titleFontColor: "white",
		valueFontColor: "white",
		label: "PV Current",
		shadowOpacity: 0,
		shadowSize: 0,
		shadowVerticalOffset: 0,
		customSectors: [{color : "green", lo : 0, hi : 10}],
		counter: true
	})

	g_bcurrent = new JustGage({
		id: "g_bcurrent",
		min: 0,
		max: 31,
		decimals: 1,
		gaugeWidthScale: 0.8,
		titleFontColor: "white",
		valueFontColor: "white",
		label: "Battery Current",
		shadowOpacity: 0,
		shadowSize: 0,
		shadowVerticalOffset: 0,
		customSectors: [{color : "lime", lo : 0, hi : 40}],
		counter: true
	})

	g_power = new JustGage({
		id: "g_power",
		min: 0,
		max: 410,
		decimals: 1,
		gaugeWidthScale: 0.8,
		titleFontColor: "white",
		valueFontColor: "white",
		label: "PV Power",
		shadowOpacity: 0,
		shadowSize: 0,
		shadowVerticalOffset: 0,
		customSectors: [{color : "yellow", lo : 0, hi : 400}],
		counter: true
	})

	g_voltage = new JustGage({
		id: "g_voltage",
		min: 0,
		max: 68,
		decimals: 1,
		gaugeWidthScale: 0.8,
		titleFontColor: "white",
		valueFontColor: "white",
		label: "PV Voltage",
		shadowOpacity: 0,
		shadowSize: 0,
		shadowVerticalOffset: 0,
		customSectors: [{color : "aqua", lo : 0, hi : 60}],
		counter: true
	})

	g_bvoltage = new JustGage({
		id: "g_bvoltage",
		min: 0,
		max: 16,
		decimals: 1,
		gaugeWidthScale: 0.8,
		titleFontColor: "white",
		valueFontColor: "white",
		label: "Battery Voltage",
		shadowOpacity: 0,
		shadowSize: 0,
		shadowVerticalOffset: 0,
		customSectors: [{color : "red", lo : 0, hi : 15}],
		counter: true
	})
});