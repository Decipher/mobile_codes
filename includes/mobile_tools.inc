<?php
/**
 * @file
 * Mobile Tools module integration.
 */

/**
 * Implements hook_mobile_codes_form_alter_alter() on behalf of mobile_tools.module.
 */
function mobile_tools_mobile_codes_form_alter_alter($form, $form_state, $form_id) {
  if ($form_id == 'block_admin_configure' && $form['module']['#value'] == 'mobile_codes' && $form['delta']['#value'] == 'node_url') {
    $form['block_settings']['options']['#options']['mobile_tools'] = t('Use Mobile URL - !configure', array('!configure' => l('configure', 'admin/settings/mobile-tools')));
  }
}

/**
 * Implements hook_mobile_codes_block_node_url_text_alter() on behalf of mobile_tools.module.
 */
function mobile_tools_mobile_codes_block_node_url_text_alter($text, $options) {
  if ($options['mobile_tools']) {
    $text = mobile_tools_create_mobile_url($text);
  }
}
