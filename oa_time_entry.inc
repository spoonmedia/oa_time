<?php // $Id

class time_entry {
  var $teid; // time entry id
  var $uid; // user id
  var $cid; // case id
  var $note;
  var $timestamp;
  var $duration;
  
  function __construct($row = NULL) {
    $row = (object) $row;
    
    foreach (array_keys((array) $this) as $var) {
      $func = 'set_'. $var;
      if (method_exists($this, $func)) {
        if ($row && isset($row->$var)) {
          $this->$func($row->$var);
        }
        else {
          $this->$func();
        }
      }
      else {
        $this->$var = $row->$var;
      }
    }
  }

  function handler() {
    return get_class($this);
  }

  function form() {
    $user = $this->user();
    $form = array();
    $form['teid'] = array();	
    $form['cid'] = array();
    $form['uid'] = array();
    $form['timestamp'] = array();
    $form['note'] = array();
    $form['duration'] = array();
    $form['submit'] = array();
    return $form;
  }

  function validate() {
    return oa_time_access();
  }

  function save($values=NULL) {
    if ($values) $this->__construct($values);
    $update = db_fetch_array(db_query("SELECT * FROM time_entry WHERE teid = %d", $this->teid));
     if(isset($update['teid'])) $update = 'teid';
     else $update = NULL;   
     drupal_write_record('time_entry', $this, $update);
  }  

  function set_uid($uid = NULL) {
    if (!$uid) {
      global $user;
      $uid = $user->uid;
    }
    elseif (!is_numeric($uid)) {
      $user = user_load(array('name' => $uid));
      $uid = $user->uid;
    }
    $this->uid = $uid;
  }

  function user() {
    if ($this->uid) return user_load($this->uid);
  }

  function set_cid($cid = NULL) {
    $this->cid = $cid;
  }

  function caseload() {
    if ($this->cid) return node_load($this->cid);
  }    
  
  function set_teid($teid = NULL) {
    $this->teid = $teid;
  }

  function comment() {
    if ($this->teid) return comment_load($this->teid);
  }
  
  function set_note($note = NULL) {
    $this->note = filter_xss($note);
  }

  function note($format = NULL) {
    return filter_xss($this->note);
  }

  function set_timestamp($timestamp = NULL) {
    if ($timestamp) {
      if (is_numeric($timestamp)) {
        $this->timestamp = $timestamp;
      }
      else {
        $this->timestamp = strtotime($timestamp);
      }
    }
    else {
      $this->timestamp = time();
    }
  }

  function timestamp($format = NULL) {
    if (!$this->timestamp) $this->timestamp = time();
    return date('m/d/Y', $this->timestamp);    
  }

  function set_duration($duration = NULL) {
    if ($duration) $this->duration = (float) $duration;
  }

  function duration($format = NULL) {
    return $this->duration;
  }  
  
}
