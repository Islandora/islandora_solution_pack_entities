<?php

/**
 * @file
 * Handles the entity creation from csv import.
 */

/**
 * The form for uploading csv.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_entities_import_form(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_entities_csv_import', 'includes/utilities');
  $extensions = array('txt csv');
  $upload_size = min((int) ini_get('post_max_size'), (int) ini_get('upload_max_filesize'));
  $form['file'] = array(
    '#title' => t('Upload csv'),
    '#type' => 'managed_file',
    '#description' => t('Select a file to upload.<br/>Files must be less than <strong>@size MB.</strong><br/>Allowed file types: <strong>@ext.</strong>', array('@size' => $upload_size, '@ext' => $extensions[0])),
    '#upload_location' => 'temporary://',
    '#required' => TRUE,
    '#upload_validators' => array(
      'file_validate_extensions' => $extensions,
      'file_validate_size' => array($upload_size * 1024 * 1024),
    ),
  );
  $form['collection'] = array(
    '#title' => t('Select collection to hold created entities'),
    '#type' => 'textfield',
    '#size' => 40,
    '#description' => t('Enter collection name or PID'),
    '#autocomplete_path' => 'import_entity_csv/autocomplete',
    '#required' => TRUE,
    '#element_validate' => array('islandora_entities_csv_import_validate_collection'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Upload CSV'),
  );
  return $form;
}

/**
 * Processes uploaded csv.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function islandora_entities_import_form_submit(array $form, array &$form_state) {
  module_load_include('inc', 'islandora_entities_csv_import', 'includes/utilities');
  $file = file_load($form_state['values']['file']);
  $collection_pid = $form_state['values']['collection'];
  // CSV importer is limited to Islandora Person Content Model.
  $cmodel = 'islandora:personCModel';
  $namespace = 'islandora';
  $collection_info = islandora_entities_import_get_collection_info($collection_pid);
  if ($collection_info && $collection_info['pid'] && $collection_info['cmodels'] && isset($collection_info['cmodels'][$cmodel])) {
    $namespace = $collection_info['cmodels'][$cmodel]['namespace'];
    islandora_entities_import_csv_batch(drupal_realpath($file->uri), $collection_pid, $namespace);
  }
  else {
    form_set_error('collection', t('Something is wrong with the specified collection.'));
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Validates the collection Drupal Form Element.
 *
 * Ensures that the object exists, is a collection and has the correct policy.
 *
 * @param array $element
 *   The collection Drupal Form Element.
 * @param array $form_state
 *   The Drupal Form State.
 */
function islandora_entities_csv_import_validate_collection(array $element, array &$form_state) {
  module_load_include('inc', 'islandora_entities_csv_import', 'includes/utilities');
  $collection_pid = $form_state['values']['collection'];
  $collection_info = islandora_entities_import_get_collection_info($collection_pid);
  if ($collection_info) {
    if (!$collection_info['pid']) {
      form_set_error('collection', t('"@collection" is not a collection object.', array('@collection' => $collection_pid)));
    }
    elseif ($collection_info['cmodels']) {
      // CSV importer is limited to Islandora Person Content Model.
      $cmodel = 'islandora:personCModel';
      if (!isset($collection_info['cmodels'][$cmodel])) {
        form_set_error('collection', t('"@collection" is not set up to hold "@cmodel" objects.', array(
          '@collection' => $collection_pid,
          '@cmodel' => $cmodel,
        )));
      }
    }
    else {
      // This should never happen.
      form_set_error('collection', t('"@collection" does not have a COLLECTION_POLICY.', array('@collection' => $collection_pid)));
    }
  }
  else {
    form_set_error('collection', t('The collection "@collection" does not exist.', array('@collection' => $collection_pid)));
  }
}
