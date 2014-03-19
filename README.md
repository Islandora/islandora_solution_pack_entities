CONTENTS OF THIS FILE
---------------------
 * adding a test change
 * summary
 * configuration

SUMMARY
-------

This module is for adding support for entities (person, place, event,
organization) to Islandora.

CONFIGURATION
-------------

The Solr field for searching entities and the entity collection are
configurable at admin/islandora/entities.
Islandora Solr Metadata must be chosen as the default metadata display.
This can be set at admin/islandora/metadata.


Installation
------------

The autocomplete for the MADS forms requires solr values.
A standrad installation should include the transformations in
basic-solr-config - git@github.com:discoverygarden/basic-solr-config.git
The link to the MADS transformation in foxmlToSolr.xslt must be uncommented.
This will be either
  <xsl:include href="/usr/local/fedora/tomcat/webapps/fedoragsearch/WEB-INF/classes/fgsconfigFinal/index/FgsIndex/islandora_transforms/MADS_to_solr.xslt"/>
or
  <xsl:include href="/usr/local/fedora/tomcat/webapps/fedoragsearch/WEB-INF/classes/config/index/FgsIndex/islandora_transforms/MADS_to_solr.xslt"/>
depending on your installation.
