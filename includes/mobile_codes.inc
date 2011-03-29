<?php
/**
 * @file
 * Mobile Codes module integration.
 */

/**
 * Implements hook_default_mobile_codes_preset().
 */
function mobile_codes_default_mobile_codes_preset() {
  $export = array();
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'large';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '400',
    'height' => '400',
    'output_encoding' => 'UTF-8',
  );

  $export['large'] = $preset;
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'medium';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '250',
    'height' => '250',
    'output_encoding' => 'UTF-8',
  );

  $export['medium'] = $preset;
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'small';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '150',
    'height' => '150',
    'output_encoding' => 'UTF-8',
  );

  $export['small'] = $preset;
  return $export;
}

/**
 * Implements hook_default_mobile_codes_provider().
 */
function mobile_codes_default_mobile_codes_provider() {
  $export = array();
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'google';
  $provider->url = 'https://chart.googleapis.com/chart?chs=[width]x[height]&cht=qr&chl=[data]&choe=[output_encoding]';
  $provider->parameters = array(
    'width' => array(
      'token' => 'width',
      'type' => 'text',
      'value' => '150',
    ),
    'height' => array(
      'token' => 'height',
      'type' => 'text',
      'value' => '150',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'output_encoding' => array(
      'token' => 'output_encoding',
      'type' => 'select',
      'value' => 'UTF-8
Shift_JIS
ISO-8859-1',
    ),
  );

  $export['google'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'kaywa_dm';
  $provider->url = 'http://datamatrix.kaywa.com/img.php?s=[size]&d=[data]';
  $provider->parameters = array(
    'size' => array(
      'token' => 'size',
      'type' => 'select',
      'value' => '5|Small
6|Medium
8|Large
12|Extra Large',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
  );

  $export['kaywa_dm'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'kaywa_qr';
  $provider->url = 'http://qrcode.kaywa.com/img.php?s=[size]&d=[data]';
  $provider->parameters = array(
    'size' => array(
      'token' => 'size',
      'type' => 'select',
      'value' => '5|Small
6|Medium
8|Large
12|Extra Large',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
  );

  $export['kaywa_qr'] = $provider;
  $provider = new stdClass;
  $provider->disabled = TRUE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'nokia_qr';
  $provider->url = 'http://mobilecodes.nokia.com/qr?DATA=[data]&MODULE_SIZE=[size]&name=[name]&MARGIN=[margin]&ENCODING=BYTE&type=[type]&a=create';
  $provider->parameters = array(
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'size' => array(
      'token' => 'size',
      'type' => 'text',
    ),
    'name' => array(
      'token' => 'name',
      'type' => 'text',
    ),
    'margin' => array(
      'token' => 'margin',
      'type' => 'text',
    ),
    'type' => array(
      'token' => 'type',
      'type' => 'select',
      'value' => 'vcard',
    ),
  );

  $export['nokia_qr'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'qrstuff';
  $provider->url = 'http://www.qrstuff.com/generate.generate?type=[type]&text=[data]&foreground_color=[color]';
  $provider->parameters = array(
    'type' => array(
      'token' => 'type',
      'type' => 'select',
      'value' => 'TEXT|Text
URL|Website URL',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'color' => array(
      'token' => 'color',
      'type' => 'text',
      'value' => '000000',
    ),
  );

  $export['qrstuff'] = $provider;

  return $export;
}
