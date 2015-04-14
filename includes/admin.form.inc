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

  $form['islandora_entities_scholar_title_solr_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr field for scholar title.'),
    '#default_value' => variable_get(
      'islandora_entities_scholar_title_solr_field',
      'MADS_title_mt'
    ),
    '#description' => t('Solr field for autocompletion.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_department_solr_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr field for department.'),
    '#default_value' => variable_get(
      'islandora_entities_department_solr_field',
      'MADS_department_mt'
    ),
    '#description' => t('Solr field for autocompletion.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_disambiguated_solr_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr field for disambiguated full name.'),
    '#default_value' => variable_get(
      'islandora_entities_disambiguated_solr_field',
      'MADS_disambiguated_fullname_mt'
    ),
    '#description' => t('Solr field for autocompletion.'),
    '#required' => TRUE,
  );

  $form['islandora_entities_last_name_solr_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr field for last name.'),
    '#default_value' => variable_get(
      'islandora_entities_last_name_solr_field',
      'MADS_family_mt'
    ),
    '#description' => t('Solr field for autocompletion.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
