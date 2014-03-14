<?php

/**
 * @file
 * Theme hooks.
 */

/**
 * Implements hook_preprocess().
 */
function islandora_entities_preprocess_islandora_person(array &$variables) {
  module_load_include('inc', 'islandora_entities', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/metadata');
  $biography = "";
  $object = $variables['object'];
  $pid = $object->id;

  if ($object['MADS']) {
    $mads = $object['MADS']->content;
    $simplexml = simplexml_load_string($mads);
    $notes = $simplexml->note;
    foreach ($notes as $note) {
      if ($note['type'] == 'history') {
        $biography = (string) $note;
        $variables['biography'] = str_replace("\n", "<br />", $biography);
      }
    }
    $variables['title'] = (string) $simplexml->authority->titleInfo->title;
    $activities = $simplexml->fieldOfActivity;
    foreach ($activities as $activity) {
      if ((string) $activity) {
        $fields_of_activity[] = (string) $activity;
      }
    }
    if (isset($fields_of_activity)) {
      $list_variables = array(
        'items' => $fields_of_activity,
        'title' => t('Research Interests'),
        'type' => 'ul',
        'attributes' => array('class' => 'research_interests'),
      );
      $variables['activities'] = theme_item_list($list_variables);
    }
    $depts = $simplexml->affiliation->organization;
    $colleages = array();
    foreach ($depts as $dept) {
      if ((string) $dept) {
        $colleages[(string) $dept] = islandora_entities_get_dept_members((string) $dept, $object->id);
      }
    }
    if (isset($colleages)) {
      foreach ($colleages as $dept => $members) {
        $list_variables = array(
          'items' => $members,
          'title' => t('Other Scholars in @dept', array('@dept' => $dept)),
          'type' => 'ul',
          'attributes' => array('class' => 'fellow_scholars'),
        );
        $variables['fellow_scholars'][] = theme_item_list($list_variables);
      }
    }
    $identifiers = $simplexml->identifier;
    foreach ($identifiers as $identifier) {
      if ($identifier['type'] == 'u1') {
        $themed_links = islandora_entities_get_related((string) $identifier, $variables['title'], 'citations');
      }
    }
    if (count($themed_links)) {
      $variables['recent_citations'] = $themed_links;
    }
  }
  if ($object["TN"]) {
    $variables['tn'] = "/islandora/object/$pid/datastream/TN/view";
  }
  $variables['metadata'] = islandora_retrieve_metadata_markup($object, TRUE);
}

/**
 * Gets all members of department.
 *
 * @param string $dept
 *   Department being queried
 * @param string $pid
 *   Object pid, results will be excluded
 *
 * @return array
 *   Department members
 */
function islandora_entities_get_dept_members($dept, $pid) {
  $params = array(
    'fl' => array('MADS_title_ms', 'PID'),
  );
  $query = "MADS_organization_ms:\"$dept\" AND -PID:\"$pid\"";
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
  $colleages = array();
  foreach ($json['response']['docs'] as $choice) {
    if (isset($choice['MADS_title_ms'])) {
      foreach ($choice['MADS_title_ms'] as $candidate) {
        $colleages[] = $candidate;
      }
    }
  }
  return $colleages;
}

/**
 * Implements hook_preprocess().
 */
function islandora_entities_preprocess_islandora_dept(array &$variables) {
  module_load_include('inc', 'islandora', 'includes/metadata');
  $object = $variables['object'];
  $variables['metadata'] = islandora_retrieve_metadata_markup($object, TRUE);
}
