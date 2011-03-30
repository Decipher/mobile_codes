<?php
/**
 * @file
 * Shorten module integration.
 */

/**
 * Implements hook_mobile_codes_form_alter_alter() on behalf of shorten.module.
 */
function shorten_mobile_codes_form_alter_alter($form, $form_state, $form_id) {
  if ($form_id == 'block_admin_configure' && $form['module']['#value'] == 'mobile_codes' && $form['delta']['#value'] == 'node_url') {
    $form['block_settings']['options']['#options']['shorten'] = t('Shorten URL - !configure', array('!configure' => l('configure', 'admin/settings/shorten')));
  }
}

/**
 * Implements hook_mobile_codes_block_node_url_text_alter() on behalf of shorten.module.
 */
function shorten_mobile_codes_block_node_url_text_alter($text, $options) {
  if ($options['shorten']) {
    $text = shorten_url($text);
  }
}
