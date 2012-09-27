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
 *  SRU Client js file.
 */

$('document').ready(function() {
  $('table.collection-search input[type=checkbox].search-result-select-all').click(function(){
    if ($(this).attr('checked')) {
	  $('table.collection-search tr td input[type=checkbox]:not(:disabled)').attr('checked', 'checked');
    }
    else {
      $('table.collection-search tr td input[type=checkbox]:not(:disabled)').removeAttr('checked');
    }
  });
});
