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
      $type_mappings[$type],
      $query_parameters['entities_query']
    );
  }

  // Format the results for the CWRCwriter.
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

  drupal_json_output($results);
}
