<?php
// $Id$

/**
 * @file
 * Filter by whether or not an asset has a local thumbnail image.
 */
class sru_client_image_views_filter_image extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Has thumbnail image');
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "(SELECT COUNT(*) FROM {sru_client_image} si WHERE si.vid = $this->table_alias.$this->real_field) " . (empty($this->value) ? '=' : '<>') . " 0");
  }
}

