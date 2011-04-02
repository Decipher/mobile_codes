<?php
/**
 * @file
 * Block module integration.
 */

/**
 * Implements hook_mobile_codes_default_mobile_codes_preset_alter() on behalf of block.module.
 */
function block_mobile_codes_default_mobile_codes_preset_alter($export) {
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'block_node_url';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '180',
    'height' => '180',
    'output_encoding' => 'UTF-8',
  );

  $export['block_node_url'] = $preset;
}

/**
 * Implements hook_block().
 */
function mobile_codes_block($op = 'list', $delta = 0, $edit = array()) {
  switch ($op) {
    case 'list':
      $blocks = array();
      drupal_alter('mobile_codes_block', $blocks);
      return $blocks;

    case 'save':
      if (function_exists($function = "mobile_codes_block_{$delta}_{$op}")) {
        $function($edit);
      }
      break;

    default:
      if (function_exists($function = "mobile_codes_block_{$delta}_{$op}")) {
        return $function($edit);
      }
      return array();
  }
}

/**
 * Implements hook_mobile_codes_block_alter() on behalf of block.module.
 */
function block_mobile_codes_block_alter($blocks) {
  $blocks['node_url'] = array(
    'info' => t('Node URL'),
  );
}

/**
 *
 */
function mobile_codes_block_node_url_configure($edit) {
  $form = array();

  $form['preset'] = array(
    '#type' => 'select',
    '#title' => t('Mobile Codes preset'),
    '#options' => array(),
    '#default_value' => variable_get('mobile_codes_block_node_url_preset', 'block_node_url'),
  );
  ctools_include('export');
  foreach (ctools_export_crud_load_all('mobile_codes_presets') as $preset) {
    if (!$preset->disabled) {
      $form['preset']['#options'][$preset->name] = $preset->name;
    }
  }

  return $form;
}

/**
 *
 */
function mobile_codes_block_node_url_save($edit) {
  variable_set('mobile_codes_block_node_url_preset', $edit['preset']);
}

/**
 *
 */
function mobile_codes_block_node_url_view($edit) {
  if (arg(0) == 'node' && arg(1) != '' && arg(2) == '') {
    return array(
      'subject' => t('Node URL'),
      'content' => theme('mobilecode', url('node/' . arg(1), array('absolute' => TRUE, 'alias' => TRUE)), array('#preset' => variable_get('mobile_codes_block_node_url_preset', 'block_node_url')))
    );
  }
}
