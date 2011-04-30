<?php
/**
 * @file
 * Image module integration.
 */

/**
 * Implements hook_mobile_codes_theme_alter() on behalf of image.module.
 */
function image_mobile_codes_theme_alter(&$items) {
  ctools_include('export');
  foreach (ctools_export_crud_load_all('mobile_codes_presets') as $preset) {
    if (isset($preset->disabled) && !$preset->disabled) {
      $items["mobile_codes_formatter_mobile_codes_image_{$preset->name}"] = array(
        'arguments' => array('element' => NULL),
        'function' => 'theme_mobile_codes_image_formatter',
        'file' => 'includes/image.inc',
      );
    }
  }
}

/**
 * Implements hook_mobile_codes_field_formatter_info_alter() on behalf of image.module.
 */
function image_mobile_codes_field_formatter_info_alter(&$formatters) {
  ctools_include('export');
  foreach (ctools_export_crud_load_all('mobile_codes_presets') as $preset) {
    if (isset($preset->disabled) && !$preset->disabled) {
      $formatters["mobile_codes_image_{$preset->name}"] = array(
        'label' => t('Mobile code: @preset', array('@preset' => $preset->name)),
        'field types' => array('image')
      );
    }
  }
}

function theme_mobile_codes_image_formatter($element) {
  if (!mobile_codes_content_field_is_empty($element)) {
    return theme('mobilecode', array('data' => url($element['#item']['filepath'], array('absolute' => TRUE)), 'attributes' => array('#preset' => drupal_substr($element['#formatter'], 23))));
  }
}
