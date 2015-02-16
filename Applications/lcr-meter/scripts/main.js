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

var connection = new WebSocket('ws://192.168.128.1:8080', 'redpitaya-data');
conn.binaryType = "arraybuffer";

conn.onopen = function() {
    conn.send(sigLen)
};