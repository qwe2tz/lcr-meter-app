/**
* Author: 1NFuSeD <luka.golinar@redpitaya.com>
*/

//Global variables
var sig_len = 0;


//On page load function

$(function() { 
    
    // Show different buttons on touch screens    
    if(window.ontouchstart === undefined) {
      $('.btn-lg').removeClass('btn-lg');
      $('#accordion .btn, .modal .btn').addClass('btn-sm');
      $('#btn_zoompan').remove();
      $('#btn_zoomin, #btn_zoomout, #btn_pan').show();
    }
    else {
      update_interval = update_interval_mobdev;
      $('#btn_zoomin, #btn_zoomout, #btn_pan').remove();
      $('#btn_zoompan').show();
    }
    
    // Add application ID in the message from modal popup
    $('.app-id').text(app_id);
    
    // Disable all controls until the params state is loaded for the first time 
    $('input, select, button', '.container').prop('disabled', false);   
});

//Web socket connection
var connection = new WebSocket('ws://' + root_url + root_port, 'redpitaya-data');
connection.binaryType = "arraybuffer";

//temp var
var dummy_data = [];

//Init plot function
$(function init_plot(){
	var plot_holder = $('#plot_holder');

	plot = $.plot(plot_holder, 
      [dummy_data],
      plot_options
    );
});

connection.onopen = function() {
    connection.send(sigLen)
};