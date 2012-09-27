<?php
// $Id$

/**
 * Show an asset's local thumbnail image filename
 */
class sru_client_image_views_handler_image_path extends views_handler_field {

  function render($values) {
    if (!empty($values->{$this->aliases['nid']}) && !empty($values->{$this->aliases['fid']})) {
      $file = db_fetch_object(db_query("SELECT * FROM {files} WHERE fid=%d", $values->{$this->aliases['fid']}));
      if (isset($file->filepath) && file_exists($file->filepath)) {
        return $file->filepath;
      }
    }
  }
}
