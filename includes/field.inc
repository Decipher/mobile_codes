<?php
/**
 * @file
 * Content module integration.
 */

/**
 * Implements hook_field_formatter_info().
 */
function mobile_codes_field_formatter_info() {
  $formatters = array();
  $info = module_invoke_all('mobile_codes_field_formatter_info');

  $formatters['mobile_codes'] = array(
    'label' => t('Mobile code'),
    'field types' => array_keys($info),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_view().
 */
function mobile_codes_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  dpm($display['type']);
  return $element;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function mobile_codes_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  ctools_include('export');
  $presets = ctools_export_crud_load_all('mobile_codes_presets');
  foreach ($presets as &$preset) {
    if (isset($preset->disabled) && $preset->disabled) {
      unset($preset);
    }
  }

  $element['mobile_codes_preset'] = array(
    '#type' => 'select',
    '#title' => t('Mobile Codes preset'),
    '#options' => array(),
    '#default_value' => isset($instance['display'][$view_mode]['settings']['mobile_codes_preset']) ? $instance['display'][$view_mode]['settings']['mobile_codes_preset'] : current(array_keys($presets)),
  );
  foreach ($presets as $preset) {
    $element['mobile_codes_preset']['#options'][$preset->name] = $preset->name;
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function mobile_codes_field_formatter_settings_summary($field, $instance, $view_mode) {
  ctools_include('export');
  $presets = ctools_export_crud_load_all('mobile_codes_presets');
  foreach ($presets as &$preset) {
    if (isset($preset->disabled) && $preset->disabled) {
      unset($preset);
    }
  }

  $preset = isset($instance['display'][$view_mode]['settings']['mobile_codes_preset']) ? $instance['display'][$view_mode]['settings']['mobile_codes_preset'] : current(array_keys($presets));
  return t('Mobile Codes preset: !preset', array('!preset' => $preset));
}

/**
 *
 */
function mobile_codes_content_field_is_empty($element) {
  $field = content_fields($element['#field_name']);
  if (function_exists($function = "{$field['widget']['module']}_content_is_empty")) {
    return $function($element['#item'], $field);
  }
  return FALSE;
}
