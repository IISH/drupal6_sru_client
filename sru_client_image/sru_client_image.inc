<?php
// $Id$

/**
 * SRU Asset Image Functions.
 */


/**
 * Creates a temporary image from a variable.
 *
 * The image is cropped to a square and then resized to the image size setting.
 *
 * @param $basename
 *   Name of the asset this image accompanies.
 * @param $data
 *   The raw image data.
 * @param $mimetype
 *   The MIME type of the image.
 * @return
 *   A file object with image info or FALSE on error.
 */
function sru_client_image_save_data($basename, $data, $mimetype) {
  global $user;

  // Gotta have a name to save to.
  $filepath = _sru_client_image_filename($basename, $mimetype, TRUE);
  if (!$filepath) {
    return FALSE;
  }

  // Save the data.
  $filepath = file_save_data($data, $filepath, FILE_EXISTS_RENAME);
  if (!$filepath) {
    return FALSE;
  }

  // Make sure it's a valid image.
  $image = image_get_info($filepath);
  if (!$image) {
    file_delete($filepath);
    return FALSE;
  }

  // Resize the image
  $size = variable_get('sru_client_image_size', 80);
  if (image_scale_and_crop($filepath, $filepath, $size, $size)) {
    // Changing the image dimensions will affect the file size. Clear out
    // PHP's cached value so we can find the new size.
    clearstatcache();
    $image = image_get_info($filepath);
  }

  // Store the file in the database so it can be removed by cron if it's not
  // used.
  $file = new stdClass();
  $file->filepath = $filepath;
  $file->filename = basename($file->filepath);
  $file->filemime = $mimetype;
  $file->filesize = $image['file_size'];
  $file->uid = $user->uid;
  $file->status = FILE_STATUS_TEMPORARY;
  $file->timestamp = time();

  drupal_write_record('files', $file);

  $file->pictype = $pictype;
  $file->height = $image['height'];
  $file->width = $image['width'];

  return $file;
}

/**
 * If the file is an image it will be resized to meet the image size
 * guidelines.
 *
 * @param $file
 *   A Drupal file object. This function may resize the file affecting its size.
 * @return
 *   An array. If the file is an image and did not meet the requirements, it
 *   will contain an error message.
 */
function sru_client_image_validate_size($file) {
  $errors = array();

  // Check first that the file is an image.
  if ($info = image_get_info($file->filepath)) {
    $size = variable_get('sru_client_image_size', 80);
    if ($info['width'] > $size || $info['height'] > $size) {
      // Try to resize the image to fit the dimensions.
      if (image_get_toolkit() && image_scale_and_crop($file->filepath, $file->filepath, $size, $size)) {
        // Clear the cached filesize and refresh the image information.
        clearstatcache();
        $info = image_get_info($file->filepath);
        $file->filesize = $info['file_size'];
      }
      else {
        $errors[] = t('The image is too large; the maximum dimensions are %dimensions pixels.', array('%dimensions' => $maximum_dimensions));
      }
    }
  }

  return $errors;
}


/**
 * Creates the image's filename in the form directory/prefix.ext
 *
 * @param $prefix
 *   The prefix of the filename, probably should be the nid.
 * @param $mimetype
 *   The image's mime type. jpeg, png and gif are the only formats allowed.
 * @param $in_tempdir
 *   Boolean indicating if the file be in the temp directory.
 * @return
 *   Full filepath or null in case of an error.
 */
function _sru_client_image_filename($prefix, $mimetype, $in_tempdir = FALSE) {
  $directory = $in_tempdir ? file_directory_temp() : audio_get_directory() . '/images';
  file_check_directory($directory, TRUE);

  switch ($mimetype) {
    case 'image/jpeg':
      $ext = '.jpg';
      break;
    case 'image/png':
      $ext = '.png';
      break;
    case 'image/gif':
      $ext = '.gif';
      break;
    default:
      // don't return a filename for any other extensions
      return;
  }

  // combine the path and file extension from the mimetype
  return $directory .'/'. $prefix . $ext;
}
