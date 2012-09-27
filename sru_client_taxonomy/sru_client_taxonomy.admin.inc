<?php
// $Id$
/**
 * @file
 *  Configure general settings for SRU Client Taxonomy.
 */

/**
 * Module's settings form.
 */
function sru_client_taxonomy_admin_settings() {

  if (!count($modules = module_implements('sru_info'))) {
    drupal_set_message(t('Please define one or more XML standards.'), 'error');
    return;
  }

  foreach ($modules as $module) {
    // Call hook_sru_extract_fields() with an empty record to just collect the field names.
    $field_names = array_keys(module_invoke($module, 'sru_extract_fields', array()));
    $info = module_invoke($module, 'sru_info');

    $name_options = drupal_map_assoc($field_names);
    if ($name_options) {
      $form['sru_client_taxonomy_field_'. $module] = array(
        '#type' => 'select',
        '#title' => t('Keywords field for %name', array('%name' => $info['name'])),
        '#default_value' => variable_get('sru_client_taxonomy_field_'. $module, ''),
        '#options' => $name_options,
        '#description' => t('The asset field containing keywords.'),
      );
    } 
    else {
      drupal_set_message(t('No asset fields are available.'), 'error');
    }
  }

  $vocabularies = taxonomy_get_vocabularies('sru_client_asset');
  foreach ($vocabularies as $vocabulary) {
    if ($vocabulary->tags) {
      $vocab_options[$vocabulary->vid] = $vocabulary->name;
    }
  }
  if ($vocab_options) {
    $form['sru_client_taxonomy_vocabulary'] = array(
      '#type' => 'select',
      '#title' => t('Vocabulary'),
      '#default_value' => variable_get('sru_client_taxonomy_vocabulary', ''),
      '#options' => $vocab_options,
      '#description' => t('The vocabulary to store keywords in. This should be a free tagging vocabulary.'),
    );
  } 
  else {
    $asset_type = check_plain(node_get_types('name', 'sru_client_asset'));
    drupal_set_message(t('Please enable one or more free tagging vocabularies for content type %asset_type.', array('%asset_type' => $asset_type)), 'error');
    return;
  }

  return system_settings_form($form);
}



