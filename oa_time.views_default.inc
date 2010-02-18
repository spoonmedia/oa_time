<?php // $Id$

function oa_time_views_default_views(){
$view = new view;
$view->name = 'time_tracker_total_duration';
$view->description = '';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'uid' => array(
    'label' => 'Time tracking user',
    'required' => 0,
    'id' => 'uid',
    'table' => 'time_entry',
    'field' => 'uid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'duration' => array(
    'label' => 'Total Duration',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'exclude' => 0,
    'set_precision' => FALSE,
    'precision' => 0,
    'decimal' => '.',
    'separator' => ',',
    'prefix' => '',
    'suffix' => ' minutes',
    'id' => 'duration',
    'table' => 'time_entry',
    'field' => 'duration',
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'casetracker_basic_case' => 'casetracker_basic_case',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
  'uid' => array(
    'operator' => '=',
    'value' => array(
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'uid_op',
      'identifier' => 'uid',
      'label' => 'User',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'uid',
    'table' => 'time_entry',
    'field' => 'uid',
    'relationship' => 'none',
  ),
  'timestamp' => array(
    'operator' => '>=',
    'value' => array(
      'type' => 'date',
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'timestamp_op',
      'identifier' => 'timestamp',
      'label' => 'Activity date: from',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'timestamp',
    'table' => 'time_entry',
    'field' => 'timestamp',
    'relationship' => 'none',
  ),
  'timestamp_1' => array(
    'operator' => '<=',
    'value' => array(
      'type' => 'date',
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'timestamp_1_op',
      'identifier' => 'timestamp_1',
      'label' => 'Activity date: to',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'timestamp_1',
    'table' => 'time_entry',
    'field' => 'timestamp',
    'relationship' => 'none',
  ),
  'pid' => array(
    'operator' => 'or',
    'value' => array(),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'pid_op',
      'identifier' => 'pid',
      'label' => 'Case Tracker: Project',
      'optional' => 1,
      'single' => 1,
      'remember' => 0,
      'reduce' => 0,
    ),
    'id' => 'pid',
    'table' => 'casetracker_case',
    'field' => 'pid',
    'relationship' => 'none',
    'reduce_duplicates' => 0,
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Time Tracker Report');
$handler->override_option('header_format', '5');
$handler->override_option('header_empty', 0);
$handler->override_option('footer_format', '5');
$handler->override_option('footer_empty', 0);
$handler->override_option('empty', 'No case found');
$handler->override_option('empty_format', '5');
$handler->override_option('items_per_page', 25);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'grid');
$handler->override_option('style_options', array(
  'grouping' => '',
  'columns' => '1',
  'alignment' => 'horizontal',
));
$translatables['time_tracker_total_duration'] = array(
  t('Defaults'),
  t('Time Tracker Report'),
  t('No case found'),
);

$views[$view->name] = $view;

$view = new view;
$view->name = 'time_tracker_report';
$view->description = '';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'uid' => array(
    'label' => 'Time tracking user',
    'required' => 0,
    'id' => 'uid',
    'table' => 'time_entry',
    'field' => 'uid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Title',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 1,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'pid' => array(
    'label' => 'Project',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 1,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'exclude' => 0,
    'id' => 'pid',
    'table' => 'casetracker_case',
    'field' => 'pid',
    'relationship' => 'none',
  ),
  'case_status_id' => array(
    'label' => 'Case status',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'exclude' => 0,
    'id' => 'case_status_id',
    'table' => 'casetracker_case',
    'field' => 'case_status_id',
    'relationship' => 'none',
  ),
  'duration' => array(
    'label' => 'Duration',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'set_precision' => FALSE,
    'precision' => 0,
    'decimal' => '.',
    'separator' => ',',
    'prefix' => '',
    'suffix' => ' minutes',
    'exclude' => 0,
    'id' => 'duration',
    'table' => 'time_entry',
    'field' => 'duration',
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'casetracker_basic_case' => 'casetracker_basic_case',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
  'uid' => array(
    'operator' => '=',
    'value' => array(
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'uid_op',
      'identifier' => 'uid',
      'label' => 'User',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'uid',
    'table' => 'time_entry',
    'field' => 'uid',
    'relationship' => 'none',
  ),
  'timestamp' => array(
    'operator' => '>=',
    'value' => array(
      'type' => 'date',
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'timestamp_op',
      'identifier' => 'timestamp',
      'label' => 'Activity date: from',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'timestamp',
    'table' => 'time_entry',
    'field' => 'timestamp',
    'relationship' => 'none',
  ),
  'timestamp_1' => array(
    'operator' => '<=',
    'value' => array(
      'type' => 'date',
      'value' => '',
      'min' => '',
      'max' => '',
    ),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'timestamp_1_op',
      'identifier' => 'timestamp_1',
      'label' => 'Activity date: to',
      'optional' => 1,
      'remember' => 0,
    ),
    'id' => 'timestamp_1',
    'table' => 'time_entry',
    'field' => 'timestamp',
    'relationship' => 'none',
  ),
  'pid' => array(
    'operator' => 'or',
    'value' => array(),
    'group' => '0',
    'exposed' => TRUE,
    'expose' => array(
      'use_operator' => 0,
      'operator' => 'pid_op',
      'identifier' => 'pid',
      'label' => 'Case Tracker: Project',
      'optional' => 1,
      'single' => 1,
      'remember' => 0,
      'reduce' => 0,
    ),
    'id' => 'pid',
    'table' => 'casetracker_case',
    'field' => 'pid',
    'relationship' => 'none',
    'reduce_duplicates' => 0,
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Time Tracker Report');
$handler->override_option('header_format', '5');
$handler->override_option('header_empty', 0);
$handler->override_option('empty', 'No case found');
$handler->override_option('empty_format', '5');
$handler->override_option('items_per_page', 25);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 1,
  'order' => 'asc',
  'columns' => array(
    'title' => 'title',
    'pid' => 'pid',
    'case_status_id' => 'case_status_id',
    'duration' => 'duration',
  ),
  'info' => array(
    'title' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'pid' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'case_status_id' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'duration' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  ),
  'default' => 'title',
));
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->override_option('path', 'oa_time/time_tracker');
$handler->override_option('menu', array(
  'type' => 'tab',
  'title' => 'Time Tracking',
  'description' => '',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
));
$translatables['time_tracker_report'] = array(
  t('Defaults'),
  t('No case found'),
  t('Time Tracker Report'),
  t('Page'),
);



$views[$view->name] = $view;

	return $views;

}
            
