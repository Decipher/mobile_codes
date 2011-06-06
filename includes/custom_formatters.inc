<?php
/**
 * @file
 * Custom Formatters module integration.
 */

/**
 * Implements hook_custom_formatters_defaults().
 */
function mobile_codes_custom_formatters_defaults() {
  $formatters = array();

  $formatter = new stdClass;
  $formatter->disabled = TRUE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'example_php_mobile_codes';
  $formatter->label = 'Example: Mobile Codes (PHP)';
  $formatter->description = 'A PHP example formatter; Mobile Codes module.';
  $formatter->mode = 'php';
  $formatter->field_types = 'text';
  $formatter->code = '/**
 * This is an example Advanced Custom Formatter to demonstrate how to output various items as a Mobile Code.
 */
$preset = \'medium\';

/**
 * If Devel module is present (recommended), display the contents of the $element variable to help with construction of the formatter.
 */
if (module_exists(\'devel\')) {
  dpm($variables);
}

/**
 * Render Node URL as a Mobile Code.
 */
/* -- Delete this line if you want to use this code -- /
$node = $variables[\'#object\'];
$url = url("node/{$node->nid}", array(\'absolute\' => TRUE, \'alias\' => TRUE));
return theme(\'mobilecode\', array(\'data\' => $url, \'attributes\' => array(\'#preset\' => $preset)));
// */

/**
 * Render Node URL as the path to a Mobile Code.
 */
/* -- Delete this line if you want to use this code -- /
$node = $variables[\'#object\'];
$url = url("node/{$node->nid}", array(\'absolute\' => TRUE, \'alias\' => TRUE));
$request = mobile_codes_process_url($url, array(\'#preset\' => $preset));
return mobile_codes_generate($request);
// */

/**
 * Render Node author as a vCard Mobile Code (requires vCard module).
 */
/* -- Delete this line if you want to use this code -- /
if (module_exists(\'vcard\')) {
  $node = $variables[\'#object\'];
  $account = user_load($node->uid);
  $vcard = vcard_get($account);
  $vcard_text = $vcard->fetch();
  return theme(\'mobilecode\', array(\'data\' => $vcard_text, \'attributes\' => array(\'#preset\' => $preset)));
}
// */';
  $formatters['example_php_mobile_codes'] = $formatter;

  return $formatters;
}
