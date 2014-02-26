<?php
/**
 * @file
 * Creates Citations tab..
 */

/**
 * Creates themed list of scholar's citations.
 *
 * @param AbstractObject $object
 *   Object representing scholar
 *
 * @return html
 *   themed list of citations
 */
function islandora_entities_create_citation_tab(AbstractObject $object) {
  module_load_include('inc', 'islandora_entities', 'includes/utilities');
  if ($object['MADS']) {
    $mads = $object['MADS']->content;
    $simplexml = simplexml_load_string($mads);
    $identifiers = $simplexml->identifier;
    foreach ($identifiers as $identifier) {
      if ($identifier['type'] == 'u1') {
        return islandora_entities_get_related_citations((string) $identifier, (string) $simplexml->authority->titleInfo->title);
      }
    }
  }
}
