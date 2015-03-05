
# Islandora Example Module 

## Introduction

This module is for adding support for entities (person, place, event,
organization) to Islandora.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)
* Any
* Additional
* Requirements

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

The autocomplete for the MADS forms requires solr values. A standard installation should include the transformations in
[basic-solr-config](https://github.com/discoverygarden/basic-solr-config) (exampbe config from [discoverygarden](https://github.com/discoverygarden))

The link to the MADS transformation in foxmlToSolr.xslt must be uncommented. This will be either
  <xsl:include href="/usr/local/fedora/tomcat/webapps/fedoragsearch/WEB-INF/classes/fgsconfigFinal/index/FgsIndex/islandora_transforms/MADS_to_solr.xslt"/>
or
  <xsl:include href="/usr/local/fedora/tomcat/webapps/fedoragsearch/WEB-INF/classes/config/index/FgsIndex/islandora_transforms/MADS_to_solr.xslt"/>
depending on your installation.

## Configuration

The Solr field for searching entities and the entity collection are configurable at Administration » Islandora » Solution pack configuration » Entities  (admin/islandora/solution_pack_config/entities).

Islandora Solr Metadata must be chosen as the default metadata display. This can be set at Administration » Islandora » Metadata Display (admin/islandora/metadata).

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)


## Maintainers/Sponsors

Current maintainers:

* [Alan Stanley](https://github.com/ajstanley)

## Development

If you would like to contribute to this module, please check out our helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the Islandora.ca site.


## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)


 
