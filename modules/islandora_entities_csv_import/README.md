
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

Islandora Entities CSV Importer

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

STATUS
POSITION
EMAIL
BUILDING
ROOM_NUMBER
IDENTIFIER
TERM_OF_ADDRESS
GIVEN_NAME
FAMILY_NAME
FAX
PHONE
DISPLAY_NAME
DEPARTMENT
BUILDING
CAMPUS
NAME_DATE
STREET
CITY
STATE
COUNTRY
POSTCODE
START_DATE
END_DATE
ROOM_NUMBER
BUILDING
CAMPUS