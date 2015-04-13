<?php

/**
 * @file
 * Holds the ajax callbacks for the islandora_entities.
 */

/**
 * A JSON callback that will return the results of a query on entities in Solr.
 *
 * Uses $_get['entities_query'].
 *
 * @param string $type
 *   A string mapped to content model that defines the entity sub-type to
 *   limit the search to.
 */
function islandora_entities_query_entities_callback($type) {
  module_load_include('inc', 'islandora_entities', 'includes/utilities');
  $query_parameters = drupal_get_query_parameters();
  $results = array();

  $type_mappings = array(
    'Tag Place' => ISLANDORA_ENTITIES_PLACE_CONTENT_MODEL,
    'Tag Person' => ISLANDORA_ENTITIES_PERSON_CONTENT_MODEL,
    'Tag Event' => ISLANDORA_ENTITIES_EVENT_CONTENT_MODEL,
    'Tag Organization' => ISLANDORA_ENTITIES_ORGANIZATION_CONTENT_MODEL,
  );

  $solr_results = array();
  if (isset($query_parameters['entities_query'])) {
    $solr_results = islandora_entities_solr_search_entities(
        $type_mappings[$type], $query_parameters['entities_query']
    );
  }

  // Format the results for the CWRCwriter.
  if (isset($solr_results['response']['objects'])) {
    foreach ($solr_results['response']['objects'] as $object_response) {
      $pid = $object_response['PID'];
      $results[] = array(
        'identifier' => $object_response['object_label'],
        // @XXX What's the target attribute? Ask Alan.
        'Object' => l($pid, "islandora/object/$pid", array(
          'attributes' => array('target' => '_blank'),
        )),
      );
    }
  }

  drupal_json_output($results);
}

/**
 * Returns array of items to autocomplete forms.
 *
 * @param string $type
 *   Selects eithe Scholar or Department
 *
 * @return array
 *   array of all candidates
 */
function islandora_entities_autocomplete($type) {

  $mappings = array(
    'scholar' => array(
      'cmodel' => 'islandora:personCModel',
      'title' => variable_get('islandora_entities_scholar_title_solr_field', 'MADS_title_mt'),
    ),
    'department' => array(
      'cmodel' => 'islandora:organizationCModel',
      'title' => variable_get('islandora_entities_department_solr_field', 'MADS_department_mt'),
    ),
    'disambiguated' => array(
      'cmodel' => 'islandora:personCModel',
      'title' => variable_get('islandora_entities_disambiguated_solr_field', 'MADS_disambiguated_fullname_mt'),
    ),
    'last_name' => array(
      'cmodel' => 'islandora:personCModel',
      'title' => variable_get('islandora_entities_last_name_solr_field', 'MADS_family_mt'),
    ),
  );
  $qualifier = $mappings[$type]['title'] . ':*';
  $path = request_path();
  if ($path) {
    $path_array = explode('/', $path);
    $stub = end($path_array);
    $qualifier = $mappings[$type]['title'] . ':' . $stub . '*';
  }
  $params = array(
    'fl' => array($mappings[$type]['title'], 'PID'),
  );
  $query = "$qualifier AND " . 'RELS_EXT_hasModel_uri_mt:"' . $mappings[$type]['cmodel'] . '"';
  $url = parse_url(variable_get('islandora_solr_url', 'localhost:8080/solr'));
  $solr = new Apache_Solr_Service($url['host'], $url['port'], $url['path'] . '/');
  $solr->setCreateDocuments(FALSE);
  try {
    $results = $solr->search($query, 0, 1000, $params);
    $json = json_decode($results->getRawResponse(), TRUE);
  }
  catch (Exception $e) {
    watchdog_exception('Islandora Entities', $e, 'Got an exception while searching entities for callback.', array(), WATCHDOG_ERROR);
  }
  $list = array();
  foreach ($json['response']['docs'] as $choice) {
    if (isset($choice[$mappings[$type]['title']])) {
      $list[$choice[$mappings[$type]['title']][0]] = $choice[$mappings[$type]['title']][0];
    }
  }

  drupal_json_output($list);
}
