/**
* Author: 1NFuSeD <luka.golinar@redpitaya.com>
*/


//settings which can be modified

var app_id = 'lcr_meter';  
var root_url = '192.168.1.100';
var root_port = '';
//var root_url = 'http://10.0.1.221';      // Test local
//var root_url = 'http://192.168.53.133';  // Test remote and local
//var root_url = 'http://192.168.1.100';   // Default RedPitaya IP
var start_app_url = root_url + '/bazaar?start=' + app_id;
var stop_app_url = root_url + '/bazaar?stop=';
var get_url = root_url + '/data';
var post_url = root_url + '/data';

var plot_options = {
	colors: ['#3276B1'], //Channel 1, Channel 2 - Reference channel
	lines: { lineWidth: 1 },
	selectin: { mode: 'xy' },
	zoom: { interactive: true, trigger: null },
	xaxis: { min: 0, max: 10 },
    grid: { borderWidth: 0 },
    legend: { noColumns: 2, margin: [0, 0], backgroundColor: 'transparent' },
    touch: { autoWidth: false, autoHeight: false }
}

// Settings which should not be modified
  
  var update_timer = null;
  var zoompan_timer = null;
  var downloading = false;
  var sending = false;
  var send_que = false;
  var use_long_timeout = false;
  var trig_dragging = false;
  var touch_last_y = 0;
  var user_editing = false;
  var app_started = false;
  var last_get_failed = false;
  var refresh_counter = 0;
  var autorun = 1;
  var datasets = [];
  var plot = null;
  var params = {
    original: null,
    local: null
  };
  
  // Default parameters - posted after server side app is started 
  var def_params = {
    en_avg_at_dec: 0
  }; 





