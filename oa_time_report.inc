<?php // $Id$

define('ROW_OPTION1' , 25); // default option
define('ROW_OPTION2', 50);
define('ROW_OPTION3', 100);

/* helper function */

function oa_time_get_pnid(){

	$pnid = 0;
	if(arg(0) == "node" && is_numeric(arg(1))){
        $pnid = arg(1);
        $node = node_load($pnid);
        if(!casetracker_is_project($node)){
             if(casetracker_is_case($node)){
                   $result = db_fetch_array(db_query("SELECT pid FROM casetracker_case WHERE nid = %d", $pnid));
                   $pnid = $result['pid'];
             }
        }
  	
    }
    return $pnid;
}
/**
 * Project time tracking form
 */
function oa_time_tracking_project_form($form_values)
{
  $default_row = ROW_OPTION1;
  $group = og_get_group_context();
  $sql = db_query("SELECT n.nid, n.title FROM node n, og_ancestry o 
		   WHERE o.group_nid = %d AND n.nid = o.nid AND n.type = 'casetracker_basic_project'", $group->nid);
  $project_options = array();
  
  // get list of current group's projects
  while($row = db_fetch_array($sql)){
  	$project_options[$row['nid']] = $row['title'];
  } 
 
  if($form_values['post'] != NULL){
  	$pnid = $form_values['post']['project'];
	$lines = $form_values['post']['lines'];

  } else{
	if($_GET['project'] != NULL) $pnid = $_GET['project'];
    else    $pnid = oa_time_get_pnid();
    
	if($_GET['lines'] != NULL) $lines = $_GET['lines'];
	else 	$lines = $default_row;
  }  
  
  $line_options = array();
  $line_options[ROW_OPTION1] = ROW_OPTION1;
  $line_options[ROW_OPTION2] = ROW_OPTION2;
  $line_options[ROW_OPTION3] = ROW_OPTION3;
 
  $form['#multistep'] = TRUE;
  $form['#redirect'] = FALSE;
  $form['#theme'] = 'oa_time_tracking_form';
  $form['#action'] = url($_GET['q']);
 
   $form['project'] = array(
      	'#title' => t('Project'),
      	'#type' => 'select',		
        '#value' => $pnid,      	
      	'#options' => $project_options,  
  );    
	
  $form['lines'] = array(
  	'#type' => 'select',
	'#title' => t('Rows per page'),
	'#options' => $line_options,
	'#value' => $lines,
  ); 

  $form['submit'] = array(
  	'#type' => 'submit',
	'#value' => t('Apply'), 
  ); 
  if($form_values['post'] != NULL){
  	$form['table'] = array( 
	'#type' => 'item',
	'#value' => _oa_time_tracking_project_overview($form_values['post']),
	);
  }else{
  	$form['table'] = array( 
	'#type' => 'item',
	'#value' => _oa_time_tracking_project_overview(),
	);
  } 
  
  return $form;
}


/**
 * Provide a default listing of time entries per project.
 */
function _oa_time_tracking_project_overview($form_values = NULL) {

  $default_row = ROW_OPTION1;

  $hdrs = array(
    array('data' => t('Case'), 'field' => 'title'), 
    array('data' => t('Status'), 'field' => 'status'), 
    array('data' => t('Hours'), 'field' => 'duration'), 
    array(),
  );

  $rows = array();
  
   if($form_values == NULL){
		
  	if($_GET['project'] != NULL) $pnid = $_GET['project'];	
	else	$pnid = oa_time_get_pnid();
  	
	if($_GET['lines'] != NULL) $lines = $_GET['lines'];
	else	$lines = $default_row;	
	
	
  }else{
  	$pnid = $form_values['project'];
	
	$lines = $form_values['lines'];	
  }

     
   $total_hours = db_fetch_array(db_query("SELECT SUM(te.duration) AS duration FROM casetracker_case c LEFT JOIN time_entry te ON c.nid = te.cid WHERE c.pid = " .$pnid)); 
   
   $sql = "SELECT n.nid, n.title AS title, cs.case_state_name AS status, SUM(te.duration)as duration 
	   FROM casetracker_case c LEFT JOIN time_entry te ON c.nid = te.cid,
	   node n,casetracker_case_states cs
	   WHERE c.pid = " .$pnid . " AND c.nid = n.nid AND c.case_status_id = cs.csid
	   GROUP BY c.nid" .tablesort_sql($hdrs);
   
   $countsql = "SELECT COUNT(*) FROM casetracker_case WHERE pid = " .$pnid; 
	 
   $caseinfo = pager_query($sql, $lines, 0, $countsql);     

   while ($row = db_fetch_array($caseinfo)) {
	$record  = array();	    
	$record[] = l($row['title'], 'node/'. $row['nid']);
	$record[] = t($row['status']);
	if(is_numeric($row['duration']))
		$record[] = number_format($row['duration'], 2);
	else
		$record[] = '0';
	    
	$rows[] = $record;
   }
      
   if ($rows){
       $node = node_load($pnid);
       $output = '<br><h2 class = node-title>'. l($node->title, 'node/'.$pnid) .'</h2>' ;
       $output .= t('<b>Total hours: ' .number_format($total_hours['duration'],2) .'</b><br><br>');
       $output .= theme('table', $hdrs, $rows);
       $output .= theme('pager', NULL, $lines, 0);
   }else{
       $output = '<br><div class = "view-empty">';
       $output .= '<p>No cases found </p>';
       $output .= '</div>';
   }
   
   return $output;
}

/**
 * User time tracking form
 */
function oa_time_tracking_user_form($form_values)
{
 
  $default_row = ROW_OPTION1;
  $group = og_get_group_context();
 
   
   if($form_values['post'] != NULL){
  	$user = $form_values['post']['user'];
	$from = $form_values['post']['from']['date'];
	$to = $form_values['post']['to']['date'];
	$lines = $form_values['post']['lines'];
	
  
  } else{
	if($_GET['user'] != NULL) $user = $_GET['user'];
    else    $user = 0;
    
	if($_GET['from']['date'] != NULL) $from = date('Y-m-d', strtotime($_GET['from']['date']));
    else    $from = '';
    
	if($_GET['to']['date'] != NULL) $to = date('Y-m-d', strtotime($_GET['to']['date']));
    else    $to = '';
	
	if($_GET['lines'] != NULL) $lines = $_GET['lines'];
	else 	$lines = $default_row;
  }  
   $line_options = array();
   $line_options[ROW_OPTION1] = ROW_OPTION1;
   $line_options[ROW_OPTION2] = ROW_OPTION2;
   $line_options[ROW_OPTION3] = ROW_OPTION3;
	
   //if current user has access to view time tracking report of other users
  if(user_access('view all users time tracking')){
  	$sql = db_query("SELECT u.uid, u.name AS name FROM users u ,og_uid g WHERE u.uid = g.uid AND g.nid = %d", $group->nid);
  	$user_options = array();
  	$user_options[0] = 'all';
    	while($row = db_fetch_array($sql)){
        	$user_options[$row['uid']] = $row['name'];
	}

	$form['user'] = array(
        '#title' => t('User'),
        '#type' => 'select',
        '#value' => $user,
        '#options' => $user_options,  
  	);
  }
 
  $form['#multistep'] = TRUE;
  $form['#redirect'] = FALSE;
  $form['#theme'] = 'oa_time_tracking_form';
  $form['#action'] = url($_GET['q']);
 
  if(module_exists('date')){
  	$form['from'] = array(
       '#type' => 'date_popup',
       '#title' => t('From date'),
       '#date_format' => 'm/d/Y',
       '#default_value' => $from,
		           
 	);
  	$form['to'] = array(
       '#type' => 'date_popup',
       '#title' => t('To date'),
       '#date_format' => 'm/d/Y',
       '#default_value' => $to,	
	
        ); 
  }
  else{
       $form['from'] = array(
       '#type' => 'textfield',
       '#title' => t('From'),
       '#size' => '10', 
	   '#value' => $from,  
       '#description' => t('Format: mm/dd/yyyy'),    
       );
       $form['to'] = array(
       '#type' => 'textfield',
       '#title' => t('To'),
       '#size' => '10',
	'#value' => $to,
       '#description' => t('Format: mm/dd/yyyy'),
       );
  }
  $form['lines'] = array(
  	'#type' => 'select',
	'#title' => t('Rows per page'),
	'#options' => $line_options,
	'#value' => $lines,
  ); 
  $form['submit'] = array(
  	'#type' => 'submit',
	'#value' => t('Apply'), 
  ); 
  if($form_values['post'] != NULL){
  	$form['table'] = array( 
	'#type' => 'item',
	'#value' => _oa_time_tracking_user_overview($form_values['post']),
	);
  }else{
  	$form['table'] = array( 
	'#type' => 'item',
	'#value' => _oa_time_tracking_user_overview(),
	);
  } 
  
  return $form;
}

function theme_oa_time_tracking_form($form){  
  
  $output = '';
  $header = array();
  $header[] = 'Report filter';
  
  $row = array();
  foreach (element_children($form) as $id) {
       if($id != 'submit' && $id != 'table'){
      		 $row[] = drupal_render($form[$id]);
       }    
  }
  
  $rows = array($row);
  
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form['submit']);    
  $output .= '<br>';
  $output .= drupal_render($form['table']);
    
return $output;

}

/**
 * Provide a default listing of time entries per user.
 */
function _oa_time_tracking_user_overview($form_values = NULL) {

  $default_row = ROW_OPTION1;
  
  if($form_values == NULL){
		
  	if($_GET['user'] != NULL) $uid = $_GET['user'];	
	else{
		if(user_access('view all users time tracking'))
			$uid = 0;
		else
			$uid = $GLOBALS['user']->uid;
	}
  	if($_GET['from']['date'] != NULL) $from = strtotime($_GET['from']['date']);
        else    $from = 0;
  	if($_GET['to']['date'] != NULL) $to = strtotime($_GET['to']['date']);
        else    $to = time();
	if($_GET['lines'] != NULL) $lines = $_GET['lines'];
	else	$lines = $default_row;	
	
	
  }else{
	if($form_values['user'] != NULL)
  		$uid = $form_values['user'];
	else $uid = $GLOBALS['user']->uid;

	$from = strtotime($form_values['from']['date']);
        if(!$from) $from = 0;

  	$to = strtotime($form_values['to']['date']. ' +1 day');
        if(!$to) $to = time();
	
	$lines = $form_values['lines'];	
  }
    
  $hdrs = array(
    array('data' => t('Case'), 'field' => 'title'), 
	array('data' => t('Project'), 'field' => 'ptitle'),
	array('data' => t('Case status'), 'field' => 'status'),    
    array('data' => t('Hours'), 'field' => 'duration'),     	
  );
  if($uid != 0)
  	$user_filter = " te.uid = " .$uid ." AND";
  else
	$user_filter = "";

  $date_filter = " AND te.timestamp BETWEEN " .$from ." AND " .$to; 
  $rows = array();
 
  $group = og_get_group_context();

  $total_hours = db_fetch_array(db_query("SELECT SUM(te.duration) AS duration FROM time_entry te , og_ancestry o WHERE" 
		.$user_filter ." o.nid = te.cid AND o.group_nid = " .$group->nid ." AND te.timestamp BETWEEN " .$from ." AND " .$to )); 

  $sql = "SELECT n.nid AS nid, pj.nid AS pnid, n.title AS title, pj.title AS ptitle,
	     cs.case_state_name as status , sum(te.duration) AS duration 
		 FROM time_entry te, node n, node pj, casetracker_case c, casetracker_case_states cs, og_ancestry o WHERE"
		 .$user_filter ." n.nid = te.cid AND c.nid = n.nid AND c.pid = pj.nid 
		 AND c.case_status_id = cs.csid AND c.nid = o.nid AND o.group_nid = ".$group->nid .$date_filter  
		 ." GROUP BY te.cid"  .tablesort_sql($hdrs);
	
	  $countsql = "SELECT COUNT(DISTINCT(te.cid)) FROM time_entry te, og_ancestry o WHERE" .$user_filter 
			." o.nid = te.cid AND o.group_nid = " .$group->nid ." AND te.timestamp BETWEEN " .$from ." AND " .$to ;     
	    
 	
	$caseinfo = pager_query($sql, $lines, 0, $countsql);
	  
	while ($row = db_fetch_array($caseinfo)) {
	   if($row['duration'] > 0){
	    $record  = array();
	    
	    $record[] = l($row['title'], 'node/'. $row['nid']);
	    $record[] = l($row['ptitle'], 'node/' .$row['pnid']);
	    $record[] = t($row['status']);
	   
	    if(is_numeric($row['duration'])){
			$record[] = number_format($row['duration'], 2);
			
	    }
	    else
			$record[] = '0';

	    $rows[] = $record;
	   }
	  }	
    
	if ($rows){
	      
	    $user = user_load($uid);
	 
	    if($user->name == NULL)
			$output .= '<br><h2 class = node-title>'. t('All users') .'</h2>' ;
	    else 	    
	    	$output .= '<br><h2 class = node-title>'. l($user->name, 'user/'.$uid) .'</h2>' ;
            
	    $output .= t('<b>Total hours: ' . number_format($total_hours['duration'], 2) .'</b><br><br>');
	    $output .= theme('table', $hdrs, $rows);
	    $output .= theme('pager', NULL, $lines, 0);
	    
	}else{
	    $output .= '<br><br><div class = "view-empty">';
	    $output .= '<p> No cases found </p>';
	    $output .= '</div>';
	}	
	return $output;
}
