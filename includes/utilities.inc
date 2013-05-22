<?php
/**
 * @file
 * Holds helper functions for islandora_entities.
 */


/**
 * This function will add the entity content model to an object.
 *
 * Due to natural inheritance in the data model all entity type
 * objects will have the content model of entity as well as one
 * for their types.
 *
 * @param AbstractObject $fedora_object
 *   The object to add the relationship to.
 */
function islandora_entities_add_entity_content_model(AbstractObject $fedora_object) {
  $fedora_object->relationships->add(
    FEDORA_MODEL_URI,
    'hasModel',
    'islandora:entityCModel'
  );
}

/**
 * This function will run a query using Solr for the specified entity type.
 *
 * @param string $content_model
 *   The PID of the content model object representing they type of entity.
 * @param string $entities_query
 *   The value of the query to run for the Solr search.
 *
 * @return array
 *   The results of the query. Limited to PID, object label and EAC-CPF name.
 *   IslandoraSolrQueryProcessor->islandoraSolrResult
 */
function islandora_entities_solr_search_entities($content_model, $entities_query) {
  $results = array();

  $content_model_field = variable_get(
    'islandora_solr_content_model_field',
    'RELS_EXT_hasModel_uri_ms'
  );
  $entities_query_field = variable_get(
    'islandora_entities_query_field',
    'eaccpf_name_complete_et'
  );
  $object_label_field = variable_get(
    'islandora_solr_object_label_field',
    'fgs_label_s'
  );

  $query_processor = new IslandoraSolrQueryProcessor();
  $query_processor->solrQuery = format_string(
    '!entities_query_field:"!entities_query"',
    array(
      '!entities_query_field' => $entities_query_field,
      '!entities_query' => $entities_query,
    )
  );
  $query_processor->solrStart = 0;
  $query_processor->solrLimit = 10;
  $query_processor->solrParams = array(
    'fl' => "$entities_query_field, $object_label_field, PID",
    'fq' => format_string(
      '!content_model_field:"info:fedora/!content_model"',
      array(
        '!content_model_field' => $content_model_field,
        '!content_model' => $content_model,
      )
    ),
  );

  $query_processor->executeQuery(FALSE);
  $solr_results = $query_processor->islandoraSolrResult;
  return $solr_results;
}
