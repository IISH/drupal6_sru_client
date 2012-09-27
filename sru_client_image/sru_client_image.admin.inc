<?php
// $Id$
/**
 * @file
 *  Configure general settings for SRU Client Image.
 */

/**
 * Module's settings form.
 */
function sru_client_image_admin_settings() {
  $form['sru_client_image_size'] = array(
    '#type' => 'select',
    '#title' => t('Image size'),
    '#default_value' => variable_get('sru_client_image_size', '260x260'),
    '#options' => array(
      '260x260' => '260 X 260',
      '180x180' => '180 X 180',
      '120x120' => '120 X 120',
      '80x80'  => '80 X 80',
    ),
    '#description' => t('The size (in pixels) to display the thumbnail version of asset images. Default is <em>260 X 260</em>.'),
  );
  $form['sru_client_image_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Image directory'),
    '#default_value' => variable_get('sru_client_image_directory', 'images'),
    '#description' => t('The subdirectory within the files directory the thumbnails will be stored in.'),
  );
  return system_settings_form($form);
}

