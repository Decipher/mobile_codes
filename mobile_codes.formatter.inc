<?php


/**
 * @file
 */

function mobile_codes_field_formatter_info() {
  $formatters = array();

  module_load_include('admin.inc', 'mobile_codes');
  foreach (mobile_codes_get_presets() as $preset) {
    $formatters['mobile_codes_'. $preset->name .'_default'] = array(
      'label' => t('Mobile code: @preset image', array('@preset' => $preset->name)),
      'field types' => array('text')
    );
    $formatters['mobile_codes_'. $preset->name .'_path'] = array(
      'label' => t('Mobile code: @preset file path', array('@preset' => $preset->name)),
      'field types' => array('text')
    );
  }

  return $formatters;
}

function theme_mobile_codes_formatter($element) {
  preg_match('/^mobile_codes_(.*)_(.*)$/', $element['#formatter'], $matches);

  $arguments = array(
    'data' => 'text',
    'preset' => $matches[1]
  );

  switch ($matches[2]) {
    case 'path':
      $output = mobile_codes_generate($element['#item']['safe'], $arguments);
      break;

    default:
      $output = theme('mobilecode', $element['#item']['safe'], $arguments);
      break;
  }

  return $output;
}
