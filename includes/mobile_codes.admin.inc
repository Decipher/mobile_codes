<?php
/**
 * @file
 */

/**
 *
 */
function mobile_codes_settings_form(&$form_state) {
  $form = array('#tree' => TRUE);

  $defaults = variable_get('mobile_codes_settings', array(
    'url' => array(
      'alias' => 'alias',
    ),
  ));

  $settings = array();
  drupal_alter('mobile_codes_settings', $settings);
  foreach ($settings as $type => $setting) {
    $form['settings'][$type] = array(
      '#type' => 'fieldset',
      '#title' => t('!type settings', array('!type' => strtoupper($type))),
    );

    foreach ($setting as $key => $values) {
      $form['settings'][$type][$key] = array(
        '#type' => 'checkbox',
        '#title' => $values['label'],
        '#description' => $values['description'],
        '#default_value' => isset($defaults[$type][$key]) ? $defaults[$type][$key] : FALSE,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

function mobile_codes_settings_form_submit($form, &$form_state) {
  drupal_set_message(t('Mobile Codes settings have been updated.'));
  variable_set('mobile_codes_settings', $form_state['values']['settings']);
}
