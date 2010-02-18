<?php

class oa_time_views_handler_field_duration extends views_handler_field {
	function render($values){
		$value = $values->{$this->field_alias};
		$hours =floor($value / 60);
		$minutes = (int)($value) % 60;		
		$value = $hours .' hours ' .$minutes .' minutes';
		return check_plain($value);
	}
}