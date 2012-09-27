<?php
// $Id$

/**
 * @file
 * Show an asset's local thumbnail image.
 *
 * If imagecache is available a preset may be chosen.
 */
class sru_client_image_views_handler_image extends views_handler_field {

  /**
   * Define default values for options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['image_size'] = array('default' => 'default');
    return $options;
  }

  /**
   * Extend the field's basic options with more image specific options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Default is the local copy.
    $sizes = array('default' => 'default');
    // Add imagecache presets.
    if ((module_exists('imagecache')) && ($presets = imagecache_presets())) {
      foreach ($presets as $preset) {
        $sizes[$preset['presetname']] = $preset['presetname'];
      }
    }
    $form['image_size'] = array(
      '#type' => 'select',
      '#title' => t('Image size to show'),
      '#options' => $sizes,
      '#default_value' => $this->options['image_size'],
      '#description' => t('Pick an image size to display.'),
    );
  }

  function render($values) {
    if (!empty($values->{$this->aliases['nid']}) && !empty($values->{$this->aliases['fid']})) {
      $file = db_fetch_object(db_query("SELECT * FROM {files} WHERE fid=%d", $values->{$this->aliases['fid']}));
      $image_size = $this->options['image_size'];
      if (isset($file->filepath) && file_exists($file->filepath)) {
        if ($image_size == 'default') {
          return  theme('sru_client_image', $file);
        } 
        else {
          return theme('imagecache', $image_size, $file->filepath);
        }
      }
    }
  }
}
