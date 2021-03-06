<?php
/**
 * @file
 * System module integration.
 */

/**
 * Implements hook_menu().
 */
function mobile_codes_menu() {
  $items = array();
  drupal_alter('mobile_codes_menu', $items);
  return $items;
}

/**
 * Implements hook_theme().
 */
function mobile_codes_theme() {
  $items = array();
  drupal_alter('mobile_codes_theme', $items);
  return $items;
}

/**
 * Implements hook_form_alter().
 */
function mobile_codes_form_alter(&$form, &$form_state, $form_id) {
  drupal_alter('mobile_codes_form_alter', $form, $form_state, $form_id);
}
