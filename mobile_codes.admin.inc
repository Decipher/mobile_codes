<?php

// $Id$

/**
 * @file
 */

function mobile_codes_overview() {
  $header = array('Name', 'Description', array('data' => 'Operations', 'colspan' => 2));

  $presets = array();
  foreach (mobile_codes_get_presets() as $preset) {
    if ($preset->pid == '1') {
      array_unshift($presets, $preset);
    }

    else {
      $presets[] = $preset;
    }
  }

  foreach ($presets as $preset) {
    $rows[] = array(
      $preset->name,
      '',
      l(t('Edit'), 'admin/settings/mobile_codes/presets/'. $preset->pid .'/edit'),
      $preset->pid !== '1' ?
        l(t('Delete'), 'admin/settings/mobile_codes/presets/'. $preset->pid .'/delete')
        : ''
    );
  }

  return theme('table', $header, $rows);
}

function mobile_codes_get_presets() {
  static $presets = array();

  if (empty($presets)) {
    $result = db_query('SELECT * FROM {mobile_codes_presets} ORDER BY name');
    $presets = array();
    while ($preset = db_fetch_object($result)) {
      $preset->data = unserialize($preset->data);
      $presets[$preset->name] = $preset;
    }
  }

  return $presets;
}

/**
 * Mobile Codes presets form.
 */
function mobile_codes_presets_form(&$form_state) {
  $form = array(
    '#validate' => array('mobile_codes_presets_form_validate'),
    '#submit' => array('mobile_codes_presets_form_submit'),
    '#redirect' => 'admin/settings/mobile_codes',
  );

  // Preset settings
  $form['preset'] = array(
    '#type' => 'fieldset',
    '#title' => 'Preset settings',
  );

  $form['preset']['name'] = array(
    '#type' => 'textfield',
    '#title' => 'Name',
    '#required' => TRUE,
    '#default_value' => '',
    '#description' => t('Please only use alphanumeric characters, underscores (_), and hyphens (-) for Preset names') .'.',
  );

  // Mobile codes settings
  $form['mobile_codes'] = array(
    '#type' => 'fieldset',
    '#title' => 'Mobile Codes settings',
  );

  $form['mobile_codes']['type'] = array(
    '#type' => 'select',
    '#title' => t('Code type'),
    '#options' => array(
      'dm' => t('Datamatrix'),
      'qr' => t('QR Code'),
    ),
    '#default_value' => 'qr',
    '#description' => t('
      Set the default Mobile Code type - <a href="http://en.wikipedia.org/wiki/Datamatrix">Datamatrix</a> or <a href="http://en.wikipedia.org/wiki/QR_Code">QR Code</a>.
    '),
  );

  $form['mobile_codes']['data'] = array(
    '#type' => 'select',
    '#title' => t('Data type'),
    '#options' => array(
      'phone' => t('Phone Number'),
      'text' => t('Text'),
      'link' => t('URL'),
    ),
    '#default_value' => 'text',
    '#description' => t('Set the default Mobile Code data type.'),
  );

  $form['mobile_codes']['size'] = array(
    '#type' => 'select',
    '#title' => t('Mobile Code size'),
    '#options' => array(
      's' => t('Small'),
      'm' => t('Medium'),
      'l' => t('Large'),
    ),
    '#default_value' => 'm',
    '#description' => t('Set the default Mobile Code size.'),
  );

  $form['mobile_codes']['tinyurl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert URLs to TinyURLs'),
    '#default_value' => FALSE,
    '#description' => t('
      Set the default Mobile Code TinyURL behavior<br />
      <strong>Note:</strong> URLs over 60 characters will always get converted to TinyURLs.
    '),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Preset',
  );

  return $form;
}

function mobile_codes_presets_form_edit(&$form_state, $pid) {
  if (($preset = mobile_codes_load_preset($pid)) == FALSE) {
    drupal_set_message(t('Preset specified does not exist.'), 'warning');
    drupal_goto('admin/settings/mobile_codes');
  }

  $form = mobile_codes_presets_form($form_state);

  $form['preset']['name']['#default_value'] = $preset->name;
  $form['mobile_codes']['type']['#default_value'] = $preset->data['type'];
  $form['mobile_codes']['data']['#default_value'] = $preset->data['data'];
  $form['mobile_codes']['size']['#default_value'] = $preset->data['size'];
  $form['mobile_codes']['tinyurl']['#default_value'] = $preset->data['tinyurl'];

  // Prevent users from changing Default preset name.
  if ($preset->pid == '1') {
    $form['preset']['name'] += array(
      '#disabled' => TRUE,
      '#value' => $preset->name,
    );
  }

  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $pid,
  );

  return $form;
}

function mobile_codes_presets_form_validate($form, &$form_state) {
  $preset = mobile_codes_load_preset($form['preset']['name']['#value']);

  if ($preset !== FALSE) {
    if (!isset($form_state['values']['pid']) || $form_state['values']['pid'] != $preset->pid) {
      form_set_error(
        $form['preset']['name']['#name'],
        t('A preset named "%preset" already exists.', array('%preset' => $form['preset']['name']['#value']))
      );
    }
  }

  if (preg_match('/[^0-9a-zA-Z_\-]/', $form['preset']['name']['#value'])) {
    form_set_error(
      $form['preset']['name']['#name'],
      t('Please only use alphanumic characters, underscores (_), and hyphens (-) for preset names.')
    );
  }
}

function mobile_codes_presets_form_submit($form, &$form_state) {
  $data = serialize(
    array(
      'type' => $form_state['values']['type'],
      'data' => $form_state['values']['data'],
      'size' => $form_state['values']['size'],
      'tinyurl' => $form_state['values']['tinyurl'],
    )
  );

  _mobile_codes_flush_cache();

  if (!isset($form_state['values']['pid'])) {
    db_query(
      "INSERT INTO {mobile_codes_presets} (name, data) VALUES ('%s', '%s')",
      $form_state['values']['name'], $data
    );

    drupal_set_message(t('Preset created.'));
  }

  else {
    db_query(
      "UPDATE {mobile_codes_presets} set name = '%s', data = '%s' WHERE pid = %d",
      $form_state['values']['name'], $data, $form_state['values']['pid']
    );

    _mobile_codes_presets_flush($form_state['values']['pid']);
    drupal_set_message(t('Preset updated.'));
    drupal_goto('admin/settings/mobile_codes');
  }
}

function mobile_codes_presets_delete(&$form_state, $pid) {
  $preset = mobile_codes_load_preset($pid);

  $form['pid'] = array(
    '#type' => 'value',
    '#value' => $preset->pid
  );

  $form['name'] = array(
    '#type' => 'value',
    '#value' => $preset->name
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete the preset %name?', array('%name' => $preset->name)),
    'admin/settings/mobile_codes/presets/list',
    t('This action cannot be undone') .'.',
    t('Delete'),
    t('Cancel')
  );
}

function mobile_codes_presets_delete_submit($form, &$form_state) {
  _mobile_codes_preset_delete($form_state['values']['pid']);
  _mobile_codes_flush_cache();
  drupal_set_message(t('Deleted preset %name', array('%name' => $form_state['values']['name'])));
  drupal_goto('admin/settings/mobile_codes/presets/list');
}

function _mobile_codes_preset_delete($pid) {
  _mobile_codes_presets_flush($pid);
  return db_query('DELETE FROM {mobile_codes_presets} where pid = %d', $pid);
}

/**
 * Mobile Codes settings form.
 */
function mobile_codes_settings_form(&$form_state) {
  $form = array();

  $form['flush'] = array(
    '#type' => 'checkbox',
    '#title' => t('Flush on update') .'.',
    '#description' =>
      t('Flush cache mobile codes when their preset is updated') .'.<br />'.
      '<strong>'. t('Note') .':</strong>'. t('It is suggested to set this to off if you are using the Mobile Codes filter') .'.',
    '#default_value' => variable_get('mobile_codes_flush', 1),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function mobile_codes_settings_form_submit($form, &$form_state) {
  variable_set('mobile_codes_flush', $form_state['values']['flush']);
}

function _mobile_codes_flush_cache() {
  if (module_exists('content')) {
    cache_clear_all('*', 'cache_content', TRUE);
  }
}

function _mobile_codes_presets_flush($pid) {
  if (variable_get('mobile_codes_flush', 1) == 1) {
    drupal_set_message(t('Flushed Preset Images (ID: @pid)', array('@pid' => $pid)));

    $dir = realpath(file_directory_path() .'/mobile_codes/'. $pid);
    if (is_dir($dir)) {
      _mobile_codes_recursive_delete($dir);
    }

    db_query('DELETE FROM {mobile_codes} where pid = %d', $pid);
  }
}

/**
 * Recursively delete all files and folders in the specified filepath, then
 * delete the containing folder Note that this only deletes visible files with
 * write permission
 *
 * @param string $path
 *   An absolute filepath (relative to the filesystem) to delete
 */
function _mobile_codes_recursive_delete($path) {
  $listing = $path ."/*";

  foreach (glob($listing) as $file) {
    if (is_file($file) === TRUE) {
      @unlink($file);
    }
    elseif (is_dir($file) === TRUE) {
      _mobile_codes_recursive_delete($file);
      @rmdir($file);
    }
  }

  @rmdir($path);
}
