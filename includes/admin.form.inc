<?php
/**
 * @file
 * Holds the administration form for Islandora Entities.
 */

/**
 * This is the administration form for islandora_entities.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_entities_settings($form, &$form_state) {

  $form['islandora_entities_query_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Entity searching Solr field.'),
    '#default_value' => variable_get(
      'islandora_entities_query_field',
      'eaccpf_name_complete_et'
    ),
    '#description' => t('Solr Field for entity searching.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_ingest_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest entities to.'),
    '#default_value' => variable_get(
      'islandora_entities_ingest_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules to link to provide links to the collection.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
