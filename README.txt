// $Id$

= SRU Client =

A module to query an SRU webservice (http://www.oclc.org/research/activities/srw). Information about remote objects may be stored as nodes of type "asset" in Drupal.


= Requirements =

Views.


= Installation =

To install, place the entire sru_client folder into your modules directory.
Go to Administer -> Site building -> Modules and enable the SRU Client module and one or more of its submodules:

XML modules are needed to read data from the SRU webservice:

- sru_client_dc - read Dublin Core SRU output
- sru_client_marc - read MARC 21 SRU output

The SRU Client module saves basic information about remote objects in asset nodes. Extensions allow you to store additional data:

- sru_client_image - if a remote object contains an image, create and store a local thumbnail copy
- sru_client_termcopy - copy all terms from a collection to its assets
- sru_client_taxonomy - copy terms from a configurable field of a remote object to its asset


= Configuration =

Go to Administer -> Content management -> Collections. Create a new collection. Required are name, the URL of the remote SRU webservice to search, and the XML standard to be used (currently Dublin Core or MARC 21). Also required are identifier elements for query and results.

Once saved it is possible to search the collection from the Collection overview page.

On the search results page assets may be checked and saved. Each asset will be stored as a node in Drupal, containing title, a reference (URL) to the SRU webservice, and - if available - a URL of a remote image.

Updating assets from the admin page will overwrite any locally made changes (e.g. title).

The included sru_client_termcopy.module will copy all terms related to a collection to its assets. This will assists in e.g. faceted search.

Remote objects may contain a link to an image. The locally stored asset will contain this link as well. The included sru_client_image.module will create a thumbnail copy of the image and store it in the Drupal files folder. This thumbnail may be used in views and search results. If imagecache is enabled thumbnail image presets will be available.

Thumbnails will be regenerated if an asset is updated from the admin pages, or if an asset is saved while the thumbnail field is empty on the asset node form.


= Search

Searching from the admin page will search the whole collection.

Searching from the general Drupal search page will constrain the search to the locally stored assets.


= Authors =

This module was commissioned by the International Institute of Social History (www.iisg.nl).
Originally developed by Madcap BV (projectbureau@madcap.nl).
Rewritten and extended by Guruburu (gaele@guruburu.com).




