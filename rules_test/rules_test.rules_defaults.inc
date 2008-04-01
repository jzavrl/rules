<?php
// $Id$
/**
 * @file Rules default rules - this rules are used by the tests
 */


function rules_test_rules_defaults() {
  $rules = array();

  $rules['rules_test_1'] = array(
    '#type' => 'rule',
    '#name' => 'rules_test_1',
    '#label' => t('Test altering arguments by reference'),
    '#set' => 'rules_test_1',
    '#active' => TRUE,
  );
  $condition1 = rules_use_condition('rules_condition_alter_arg', array(
    '#argument map' => array('rules_test' => 'rules_test'),
    '#weight' => -1,
  ));
  $condition2 = rules_use_condition('rules_condition_check_for_altered_arg', array(
    '#argument map' => array('rules_test' => 'rules_test'),
  ));
  $conditions = rules_configure('AND', $condition1, $condition2);
  $action = rules_use_action('rules_log_msg', array(
    '#settings' => array(
      'msg' => 'Rules Test 1 - Success!',
    )
  ));
  $rules['rules_test_1'] = rules_configure($rules['rules_test_1'], $conditions, $action);

  
  $rules['rules_test_2_1'] = array(
    '#type' => 'rule',
    '#name' => 'rules_test_2_1',
    '#label' => t('Test changing arguments per action'),
    '#set' => 'rules_test_2',
    '#active' => TRUE,
    '#weight' => -1,
  );
  $action = rules_use_action('rules_change_arg', array(
    '#argument map' => array('rules_test' => 'rules_test'),
  ));
  $rules['rules_test_2_1'] = rules_configure($rules['rules_test_2_1'], $action);

  $rules['rules_test_2_2'] = array(
    '#type' => 'rule',
    '#name' => 'rules_test_2_2',
    '#label' => t('Test changing arguments per action - check'),
    '#set' => 'rules_test_2',
    '#active' => TRUE,
  );
  $condition = rules_use_condition('rules_condition_check_for_altered_arg', array(
    '#argument map' => array('rules_test' => 'rules_test'),
  ));
  $action = rules_use_action('rules_log_msg', array(
    '#settings' => array(
      'msg' => 'Rules Test 2 - Success!',
    )
  ));
  $rules['rules_test_2_2'] = rules_configure($rules['rules_test_2_2'], $condition, $action);
  
  
  $rules['rules_test_4_1'] = array(
    '#type' => 'rule',
    '#name' => 'rules_test_4_1',
    '#label' => t('Test changing arguments per action'),
    '#set' => 'rules_test_4',
    '#active' => TRUE,
  );
  $condition = rules_use_condition('rules_condition_check_for_altered_arg', array(
    '#argument map' => array('rules_test_2' => 'rules_test'),
  ));
  $action = rules_use_action('rules_log_msg', array(
    '#settings' => array(
      'msg' => 'Rules Test 4 - Success!',
    )
  ));
  $rules['rules_test_4_1'] = rules_configure($rules['rules_test_4_1'], $condition, $action);
  

  return array(
    'rules' => $rules,
    'rule_sets' => array(
      'rules_test_1' => array(
        'label' => 'Rule Testing 1',
        'arguments' => array('rules_test' => array('entity' => 'rules_test', 'label' => 'node')),
       ),
      'rules_test_2' => array(
        'label' => 'Rule Testing 2',
        'arguments' => array('rules_test' => array('entity' => 'rules_test', 'label' => 'node')),
       ),
      'rules_test_4' => array(
        'label' => 'Rule Testing 4',
        'arguments' => array(
          'rules_test_1' => array('entity' => 'rules_test', 'label' => 'node'),
          'rules_test_2' => array('entity' => 'rules_test', 'label' => 'node', 'handler' => 'rules_test_4_load_entity'),
         ),
       ),
    ),
  );
}

