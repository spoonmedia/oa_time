// $Id$

if(Drupal.jsEnabled){
	var start_time;
	var elapsed_time;
	var t;
	$(document).ready(function() {
		var block = $('#oa_time_counter_block');
		
		block.append('<div id = "tc_block_content"></div>');
		block.append('<div id = "tc_buttons" style="text-align:center;"><br></div>');		
		$('#tc_buttons').append('<a href="#right" class="button" id="start_button">Start</a> &nbsp');
		$('#tc_buttons').append('<a href="#right" class="button" id="stop_button">Stop</a>');
		
		var content = $('#tc_block_content');
		var table = '<table>\
				<tbody>\
				<tr>\
					<td rowspan = "3" style = "vertical-align:middle;">\
						<div id = "block_clock" style="text-align:center; font-size:xx-large;">\
							00:00:00\
						</div>\
					</td>\
					<td><label>Start time : </label></td>\
					<td><div id = "start_time">00:00:00</div> </td>\
				</tr>\
				<tr>\
					<td><label>End time: </label></td>\
					<td><div id = "end_time">00:00:00</div></td>\
				</tr>\
				<tr>\
					<td><label>Elapsed time: </label></td>\
					<td><div id = "elapsed_time">00.00 hours</div></td>\
				</tr>\
				</tbody>\
				</table>';
		
		content.append(table);


		var start = $('#start_button');
		start.click(function()
				{
				
				
				var d = new Date();
				start_time = d;
				elapsed_time = 0;
				$('#start_time').html(start_time.toLocaleTimeString());
				$('#end_time').html('00:00:00');
				$('#elapsed_time').html('00.00 hours');
				timer();
											
				});
		
		var stop = $('#stop_button');
                stop.click(function()
                                {
				clearTimeout(t);
                var end_time = new Date(start_time.getTime() + elapsed_time);                           
				var elapsed = elapsed_time/3600000;  
				
				elapsed = new Number(elapsed);
				
                               								 
                $('#end_time').html(end_time.toLocaleTimeString());
				$('#elapsed_time').html(formatTime(elapsed.toFixed(2)) + ' hours');
				$('#edit-casetracker-duration').val(elapsed.toFixed(2));
				
                });
		
		 

	});
	// adding zero in front of number less than 10         
	function formatTime(i){
		if (i<10)  i="0" + i;
  		return i;
	}
	
	// displaying elapsed time
	function timer(){
		//in milliseconds
		elapsed_time += 1000;                  
            
        elapsed_hours = Math.floor(elapsed_time /3600000);
        var elapsed = elapsed_time % 3600000;
        elapsed_minutes = Math.floor(elapsed / 60000);
        elapsed = elapsed % 60000;
        elapsed_seconds = Math.floor(elapsed / 1000);
                                                                 
        $('#block_clock').html(formatTime(elapsed_hours) + ':' + formatTime(elapsed_minutes) + ':' + formatTime(elapsed_seconds));	
		
		// timer() function runs every 1 second
		t = setTimeout('timer()', 1000);	
	}
}