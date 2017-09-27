<?php
/*
 +--------------------------------------------------------------------+
 | CiviCRM version 4.7                                                |
 +--------------------------------------------------------------------+
 | This file is a part of CiviCRM.                                    |
 |                                                                    |
 | CiviCRM is free software; you can copy, modify, and distribute it  |
 | under the terms of the GNU Affero General Public License           |
 | Version 3, 19 November 2007 and the CiviCRM Licensing Exception.   |
 |                                                                    |
 | CiviCRM is distributed in the hope that it will be useful, but     |
 | WITHOUT ANY WARRANTY; without even the implied warranty of         |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.               |
 | See the GNU Affero General Public License for more details.        |
 |                                                                    |
 | You should have received a copy of the GNU Affero General Public   |
 | License and the CiviCRM Licensing Exception along                  |
 | with this program; if not, contact CiviCRM LLC                     |
 | at info[AT]civicrm[DOT]org. If you have questions about the        |
 | GNU Affero General Public License or the licensing of CiviCRM,     |
 | see the CiviCRM license FAQ at http://civicrm.org/licensing        |
 +--------------------------------------------------------------------+
*/


/*
 * Heavily based on anonymous code contribution. No claim.
 * CiviCRM Views Integration
 *
 * Filters Contact reference, and is configured using the labels from the database
 *
 */
class civicrm_handler_filter_contact_ref extends views_handler_filter_string {
  function construct() {
    parent::construct();
    if (!civicrm_initialize()) {
      return;
    }
  }
  function op_equal($field) {
    $this->filterContactRef($field);
  }
  function op_contains($field) {
    $this->filterContactRef($field);
  }

  public function filterContactRef($field) {
    $contact = civicrm_api3('Contact', 'get', array(
      'return' => array("id"),
      'sort_name' => $this->value,
      'options' => array('limit' => 0),
    ));
    if (!empty($contact['values'])) {
      $ids = CRM_Utils_Array::collect('id', $contact['values']);
      $this->query->add_where($this->options['group'], $field, $ids, 'IN');
    }
  }
}


