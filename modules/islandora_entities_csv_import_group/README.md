
ISLANDORA ENTITIES CSV IMPORT
==================

CONTENTS OF THIS FILE
---------------------

 * summary
 * requirements
 * installation
 * configuration


SUMMARY
-------

Islandora Entities CSV Importer - adapted for group (corporate body) authority entities by Rosiel

Made for ingesting objects described by CSV

REQUIREMENTS
------------

The following Drupal modules are required:
 * islandora
 * islandora_entities

INSTALLATION
------------

Enable the module.

CONFIGURATION
-------------
CSV's must be properly prepared.  Any comma within a field must be replaced with
a double pipe ie - 'Nursing, Department of' must be replaced with
'Nursing|| Department of'

If multiple arguments are supplied within a single column, they must be
separated with a ~  ie meat~cheese~pickles
If a column in a CSV is to be processed it must have a header from the following
list.

GROUP_NAME

