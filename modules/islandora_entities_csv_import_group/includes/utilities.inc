<?php

/**
 * @file
 * Creates Islandora Entity Objects from CSV.
 */

/**
 * Created Entities from supplied csv file.
 *
 * @param url $path
 *   Path to file
 * @param string $collection_pid
 *   PID of collection where created objects are to be stored.
 */
function islandora_entities_import_csv_group_batch($path, $collection_pid) {
  $scholars = islandora_entities_read_csv($path);
  $batch = array(
    'title' => t("Creating Organization Objects"),
    'progress_message' => t('Adding @current organizations out of @total.'),
    'operations' => array(),
    'file' => drupal_get_path('module', 'islandora_entities_csv_import_group') . '/includes/utilities.inc',
  );
  foreach ($scholars as $scholar) {
    $batch['operations'][] = array(
      'islandora_entities_build_group_object',
      array($scholar, $collection_pid),
    );
  }
  batch_set($batch);
}

/**
 * Creates associative array representing scholar data.
 *
 * @param url $path
 *   Path to CSV file
 *
 * @return array
 *   array of associative arrays containing header => value pairs
 */
function islandora_entities_read_csv($path) {
  ini_set("auto_detect_line_endings", "1");
  $scholars = array();
  if (($handle = fopen($path, "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 0, ",")) !== FALSE) {
      if (!isset($header)) {
        $header = $data;
        continue;
      }
      for ($counter = 0; $counter < count($data); $counter++) {
        $scholar[$header[$counter]] = $data[$counter];
      }
      $scholars[] = $scholar;
    }
    fclose($handle);
  }
  return $scholars;
}

/**
 * Builds scholar objects.
 *
 * @param array $scholar
 *   Header => value pairs representing date to be converted to MADS record
 * @param string $collection_pid
 *   PID of collection to hold new objects.
 */
function islandora_entities_build_group_object($scholar, $collection_pid) {

  $mads = islandora_entities_build_mads($scholar);
  $tuque = new IslandoraTuque();
  $repository = $tuque->repository;
  $fedora_object = $repository->constructObject('islandora');
  $fedora_object->label = isset($scholar['GROUP_NAME']) ? $scholar['GROUP_NAME'] : 'Member';
  $fedora_object->owner = 'admin';
  $datastream = $fedora_object->constructDatastream('MADS', 'M');
  $datastream->label = 'MADS';
  $datastream->mimetype = 'text/xml';
  $datastream->content = $mads;
  $fedora_object->ingestDatastream($datastream);
  $fedora_object->relationships->add(FEDORA_MODEL_URI, 'hasModel', 'islandora:organizationCModel');
  $fedora_object->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOfCollection', $collection_pid);
  $new_fedora_object = islandora_add_object($fedora_object);
}

/**
 * Builds MADS stream from Scholar data.
 *
 * @param array $scholar
 *   Associative array of header => value pairs
 *
 * @return xml
 *   MADS xml representing individual scholar
 */
function islandora_entities_build_mads($scholar) {
  $dom = new DomDocument('1.0', 'UTF-8');
  $dom->preserveWhiteSpace = FALSE;
  $dom->formatOutput = TRUE;
  $mads_uri = "http://www.loc.gov/mads/v2";
  $root = $dom->createElement('mads');
  $dom->appendChild($root);

  $ns_mads = $dom->createAttribute('xmlns');
  $root->appendChild($ns_mads);
  $value = $dom->createTextNode($mads_uri);
  $ns_mads->appendChild($value);

  $ns_mads_qualified = $dom->createAttribute('xmlns:mads');
  $root->appendChild($ns_mads_qualified);
  $value = $dom->createTextNode($mads_uri);
  $ns_mads_qualified->appendChild($value);

  $xsi = $dom->createAttribute('xmlns:xsi');
  $root->appendChild($xsi);
  $value = $dom->createTextNode("http://www.w3.org/2001/XMLSchema-instance");
  $xsi->appendChild($value);

  $xlink = $dom->createAttribute('xmlns:xlink');
  $root->appendChild($xlink);
  $value = $dom->createTextNode("http://www.w3.org/1999/xlink");
  $xlink->appendChild($value);

  islandora_entities_add_authority($dom, $scholar);

  if (isset($scholar['IDENTIFIER'])) {
    $identifier = islandora_entities_attach_element($dom, "identifier", $root, $scholar['IDENTIFIER']);
    $identifier->setAttribute('type', 'u1');
  }
  if (isset($scholar['STATUS'])) {
    $status = islandora_entities_attach_element($dom, 'note', $root, $scholar['STATUS']);
    $status->setAttribute('type', 'status');
  }
  return $dom->saveXML();
}

/**
 * Adds authority.
 *
 * @param DomDocument $dom
 *   Document holding MADS data
 * @param array $scholar
 *   Associative array of header => value pairs
 */
function islandora_entities_add_authority($dom, $scholar) {
  $name = array();
  $nameparts = array(
    'GROUP_NAME',
  );
  foreach ($nameparts as $namepart) {
    if (isset($scholar[$namepart])) {
      $name[$namepart] = $scholar[$namepart];
    }
  }
  if (count($name) == 0) {
    return;
  }
  $root = $dom->documentElement;
  $authority = islandora_entities_attach_element($dom, "authority", $root);
  $name_node = islandora_entities_attach_element($dom, 'name', $authority);
  $name_node->setAttribute('type', 'corporate');
  if (isset($name['GROUP_NAME'])) {
    $name_part = islandora_entities_attach_element($dom, 'namePart', $name_node, $name['GROUP_NAME']);
  }

}

/**
 * Creates, populates and attaches new node to Dom object.
 *
 * @param DOMDocument $dom
 *   MADS DOMDocument
 * @param string $element_name
 *   Name of element to be attached
 * @param DOMElement $parent_node
 *   Node to which new element will be attached
 * @param string $content
 *   Optional content for created node
 *
 * @return DOMElement
 *   Created node
 */
function islandora_entities_attach_element($dom, $element_name, $parent_node, $content = NULL) {
  if ($content) {
    $elements = explode('~', htmlspecialchars(str_replace('||', ',', $content)));
    foreach ($elements as $element_content) {
      $node = $dom->createElement($element_name, trim($element_content));
      $parent_node->appendChild($node);
    }
  }
  else {
    $node = $dom->createElement($element_name);
    $parent_node->appendChild($node);
  }
  return $node;
}


