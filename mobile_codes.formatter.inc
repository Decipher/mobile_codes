<?php

// $Id$

/**
 * @file
 */

function mobile_codes_field_formatter_info() {
  $formatters = array();

  module_load_include('admin.inc', 'mobile_codes');
  foreach (mobile_codes_get_presets() as $preset) {
    $formatters['mobile_codes_'. $preset->name] = array(
      'label' => t('Mobile code') .': '. $preset->name,
      'field types' => array('text')
    );
  }

  return $formatters;
}

function theme_mobile_codes_formatter($element) {
  return theme('mobilecode', $element['#item']['safe'], array(
    'data' => 'text',
    'preset' => drupal_substr($element['#formatter'], 13),
  ));
}
