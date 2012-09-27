<?php
// $Id$
/**
 * @file
 *  SRU Client image views include.
 */

/**
 * Implementation of hook_views_data().
 *
 * @return array
 *   Array containing extra field and filter information for the asset images.
 */
function sru_client_image_views_data() {

  // Basic table information.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['sru_client_image']['table']['group'] = t('Asset');

  // For other base tables, explain how we join
  $data['sru_client_image']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'files' => array(
      'left_field' => 'fid',
      'field' => 'fid',
    ),
  );

  // Fields
  $data['sru_client_image']['image'] = array(
    'title' => t('Thumbnail image'),
    'help' => t('This will display a local thumbnail image.'),
    'real field' => 'vid',
    'field' => array(
      'handler' => 'sru_client_image_views_handler_image',
      'additional fields' => array('nid', 'fid'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'sru_client_image_views_filter_image',
      'title' => t('Has thumbnail image'),
      'type' => 'yes-no',
      'help' => t('Only display assets with thumbnail image.'),
    ),
  );

  $data['sru_client_image']['image_path'] = array(
    'title' => t('Thumbnail image path'),
    'help' => t('The path to the local thumbnail image.'),
    'real field' => 'fid',
    'field' => array(
      'handler' => 'sru_client_image_views_handler_image_path',
      'additional fields' => array('nid', 'fid'),
    ),
  );

  return $data;
}


/**
 * Implementation of hook_views_handlers()
 */
function sru_client_image_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'sru_client_image'),
    ),
    'handlers' => array(
      // field handlers
      'sru_client_image_views_handler_image' => array(
        'parent' => 'views_handler_field',
      ),
      'sru_client_image_views_handler_image_path' => array(
        'parent' => 'views_handler_field',
      ),
      'sru_client_image_views_filter_image' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}

