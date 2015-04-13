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

  $form['islandora_entities_citation_base_query'] = array(
    '#type' => 'textarea',
    '#title' => t('Solr base query for citations.'),
    '#default_value' => variable_get(
      'islandora_entities_citation_base_query',
      '+RELS_EXT_hasModel_uri_mt:"ir:citationCModel"'),
    '#description' => t('Solr query for citation searching.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_thesis_base_query'] = array(
    '#type' => 'textarea',
    '#title' => t('Solr base query for theses.'),
    '#default_value' => variable_get(
      'islandora_entities_thesis_base_query',
      '+RELS_EXT_hasModel_uri_mt:"ir:thesisCModel"'),
    '#description' => t('Solr query for thesis searching.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_people_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest person entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_people_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_events_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest event entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_events_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_organizations_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest organization entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_organizations_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_places_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest place entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_places_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_title_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest title entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_title_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_department_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest department entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_department_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_disambiguated_fullname_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest disambiguated full name entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_disambiguated_fullname_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_family_collection'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection to ingest family name entities in.'),
    '#default_value' => variable_get(
      'islandora_entities_family_collection',
      'islandora:entity_collection'
    ),
    '#description' => t('Used by dependent modules provide links to the collection.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
