<?php
// $Id$
/**
 * Copyright (c) 2009 Madcap BV (http://www.madcap.nl)
 * All rights reserved.
 *
 * Permission is granted for use, copying, modification, distribution,
 * and distribution of modified versions of this work as long as the
 * above copyright notice is included.
 *
 * Copyright (c) 2010 IISG (http://www.iisg.nl)
 *
 * @file
 *  SRU Client views include.
 */

/**
 * Implementation of hook_views_data().
 *
 * @return array
 *   Array containing extra field and filter information for the asset content-type.
 */
function sru_client_views_data() {

  $data = array();
  $data['sru_client_asset']['table']['group'] = t('Asset');
  $data['sru_client_asset']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Asset'),
  );

  $data['sru_client_asset']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );

 // Nid
  $data['sru_client_asset']['nid'] = array(
    'title' => t('Asset'),
    'help' => t('Asset'),
    'relationship' => array(
      'base' => 'node',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Asset node'),
    ),
  );

  // Identifier.
  $data['sru_client_asset']['identifier'] = array(
    'title' => t('identifier'),
    'help' => t('identifier'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Source.
  $data['sru_client_asset']['source'] = array(
    'title' => t('Source'),
    'help' => t('Source'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  return $data;
}


