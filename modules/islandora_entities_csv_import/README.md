# Islandora Entities CSV Import [![Build Status](https://travis-ci.org/Islandora/islandora_solution_pack_entities.png?branch=7.x)](https://travis-ci.org/Islandora/islandora_solution_pack_entities)

## Introduction

This module is for adding person entities to Islandora using a .csv file. 

## Requirements

This module requires the following modules/libraries:
* [Islandora](https://github.com/islandora/islandora)
* [Islandora Basic Collection](https://github.com/Islandora/islandora_solution_pack_collection)
* [islandora_entities](https://github.com/Islandora/islandora_solution_pack_entities)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

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
