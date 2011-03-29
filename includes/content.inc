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
  drupal_alter('mobile_codes_field_formatter_info', $formatters);
  return $formatters;
}
