<?php // $Id$

/**
 * Implementation of hook_views_data()
 */

function oa_time_views_data(){
	$data = array();
 	
	$data['time_entry']['table']['group'] = t('Open Atrium Time Tracking');
	
 	// Joins.
 	$data['time_entry']['table']['join'] = array(
 		'node' => array(
 		'left_field' => 'nid',
 		'field' => 'cid',
 		),
 	);

 	// Fields.
 	$data['time_entry']['timestamp'] = array(
 		'title' => t('Activity date'),
 		'help' => t('Date the time was entered.'),
 		'field' => array(
 			'handler' => 'views_handler_field_date',
 			'click sortable' => TRUE,
 		),
 		'sort' => array(
 			'handler' => 'views_handler_sort_date',
 		),
 		'filter' => array(
 			'handler' => 'views_handler_filter_date',
 		),
 		'argument' => array(
 			'handler' => 'views_handler_argument_date',
 		),
 	); 	
 	 	
 	$data['time_entry']['duration'] = array(
 		'title' => t('Duration'),
 		'help' => t('Time spent during a time entry.'),
 		'field' => array(
 			'handler' => 'oa_time_views_handler_field_duration',
 			'click sortable' => TRUE,
 		),
 		'sort' => array(
 			'handler' => 'views_handler_sort_numeric',
 		),
 		'filter' => array(
 			'handler' => 'views_handler_filter_numeric',
 		),
 		'argument' => array(
 			'handler' => 'views_handler_argument_numeric',
 		),
 	);

 	$data['time_entry']['uid'] = array(
 		'title' => t('User'),
 		'help' => t('The user that entered time.'),
 		'field' => array(
                        'handler' => 'views_handler_field_numeric',
                        'click sortable' => TRUE,
                ),
                'sort' => array(
                        'handler' => 'views_handler_sort_numeric',
                ),
                'filter' => array(
                        'handler' => 'views_handler_filter_numeric',
                ),
                'argument' => array(
                        'handler' => 'views_handler_argument_numeric',
                ),
		'relationship' => array(
 			'base' => 'users',
 			'field' => 'uid',
 			'handler' => 'views_handler_relationship',
 			'label' => t('Time tracking user'),
 		),
 	);
	
	$data['time_entry']['cid'] = array(
 		'title' => t('Case'),
 		'help' => t('The case related to the time entry.'),
 		'field' => array(
                        'handler' => 'views_handler_field_numeric',
                        'click sortable' => TRUE,
                ),
                'sort' => array(
                        'handler' => 'views_handler_sort_numeric',
                ),
                'filter' => array(
                        'handler' => 'views_handler_filter_numeric',
                ),
                'argument' => array(
                        'handler' => 'views_handler_argument_numeric',
                ),
 	);
 	
 	$data['time_entry']['teid'] = array(
 		'title' => t('Comment'),
 		'help' => t('The comment related to the time entry.'),
 		'field' => array(
                        'handler' => 'views_handler_field_numeric',
                        'click sortable' => TRUE,
                ),
                'sort' => array(
                        'handler' => 'views_handler_sort_numeric',
                ),
                'filter' => array(
                        'handler' => 'views_handler_filter_numeric',
                ),
                'argument' => array(
                        'handler' => 'views_handler_argument_numeric',
                ),
		'relationship' => array(
                        'base' => 'comments',
                        'field' => 'cid',
                        'handler' => 'views_handler_relationship',
                        'label' => t('Time tracking comment'),
                ),
 	);
 	
 	$data['time_entry']['note'] = array(
 		'title' => t('Note'),
 		'help' => t('Notes or details on the time tracking activity.'),
 		'field' => array(
 			'handler' => 'views_handler_field',
 		),
 		'sort' => array(
 			'handler' => 'views_handler_sort',
 		),
 	);
 	 	
	
 	return $data; 
}

function oa_time_views_query_alter(&$view, &$query){
	if($view->name == 'time_tracker_report'){
	    $query->clear_fields();
            $query->add_field('node','nid');
            $query->add_field('node','title');
	    $query->add_field('casetracker_case','pid');
            $query->add_field('casetracker_case','case_status_id');
            $query->add_field(NULL, 'FLOOR(SUM(duration))', 'time_entry_duration', array('aggregate' => TRUE));
            $query->queue_table('og_ancestry');
	    global $user;
            $group_query = "SELECT node.nid AS nid FROM node node  LEFT JOIN og_uid og_uid ON node.nid = og_uid.nid WHERE og_uid.uid = " . $user->uid;
	    $query->add_where('AND', 'og_ancestry.group_nid IN (%s)', $group_query);
	    $query->add_groupby('time_entry.cid');        
	    
		foreach($query->where[0]['clauses'] as $i=>$clause){
			if($clause == 'time_entry.timestamp <= %s')
				$query->where[0]['args'][$i] += 86400; // add 1 day in seconds
		}
	}
	else if($view->name == 'time_tracker_total_duration'){
            $query->clear_fields();
            $query->add_field(NULL, 'FLOOR(SUM(duration))', 'time_entry_duration');
            $query->queue_table('og_ancestry');
            global $user;
            $group_query = "SELECT node.nid AS nid FROM node node  LEFT JOIN og_uid og_uid ON node.nid = og_uid.nid WHERE og_uid.uid = " . $user->uid;
            $query->add_where('AND', 'og_ancestry.group_nid IN (%s)', $group_query);

                foreach($query->where[0]['clauses'] as $i=>$clause){
                        if($clause == 'time_entry.timestamp <= %s')
                                $query->where[0]['args'][$i] += 86400; // add 1 day in seconds
                }
     
        }

}

function oa_time_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'oa_time'),
    ),
    'handlers' => array(
      // ---------- Fields ----------
      'oa_time_views_handler_field_duration' => array(
        'parent' => 'views_handler_field',
      ),
      
	),
  );
}


