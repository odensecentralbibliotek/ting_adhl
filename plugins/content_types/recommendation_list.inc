<?php

/**
 * @file
 * Provides lists of recommended ting objects/entities as panels content types
 * based on the object/entity being display.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing
 * multiple types here (since we have no single => TRUE in the array).
 */

$plugin = array(
  'title' => t('Ting ADHL recommendation'),
  'description' => t('Show a number of post from ADHL service'),
  'single' => TRUE,
  'content_types' => array('recommendation_list'),
  'render callback' => 'ting_adhl_recommendation_list_content_type_render',
  'category' => t('Ting'),
);

function ting_adhl_recommendation_list_ctools_content_types() {
  return array(
    'title' => t('Recommendation list'),
  );
}



/**
 * Return the pane contents.
 */
function ting_adhl_recommendation_list_content_type_render($subtype, $conf, $panel_args, $contexts) {
  $block = new stdClass();
  $block->content = '';

  $ting_object_id = ting_adhl_get_id($contexts);
  if ($ting_object_id) {
    $output = ting_adhl_check_cache($ting_object_id);
    if ($output) {
      $block->content = $output;
    } else {
      drupal_add_js(drupal_get_path('module', 'ting_adhl') . '/js/ting_adhl.js');
      drupal_add_js(array('ting_adhl_objectId' => $ting_object_id), 'setting');
      $block->content = '<div id="ting-adhl-recommendation"> </div>';
    }
  }
  return $block;
}

function ting_adhl_check_cache($ting_object_id) {
  $output = null;
  $cache = cache_get('ting-adhl-cache-' . $ting_object_id, 'cache');
  if ($cache) {
    $covers = $cache->data;
    $local_covers = ting_adhl_check_local_covers($covers);
    //If we lost more than 1 coverimage we reload from addi server with ajax call.
    if (count($covers) <= count($local_covers) + 1) {
      $output = ting_adhl_render_cover($covers);
    }
  }
  return $output;
}

function ting_adhl_get_id($contexts) {
// Get the objects to base the recommendation on based on the first supplied
// context
  $id = null;
  $ting_object_id = null;
  foreach ($contexts as $context) {
    $object = $context->get_original_argument();
    if ($object) {
      $id = $object->getId();
      break;
    }
  }
  if ($id) {
    $parts = explode(":", $id);
    if (isset($parts[1])) {
      $ting_object_id = $parts[1];
    }
  }
  return $ting_object_id;
}

/**
 * Callback function to supply a list of content types.
 */
function ting_adhl_recommendation_list_content_type_content_types() {
  $types = array(
    'recommendation_list' => array(
      'title' => t('Ting recommendation list'),
      'description' => t('Displays a list of recommended ting entities.'),
    ),
  );

  // Append our default settings to every type.
  foreach ($types as $name => $type) {
    $types[$name] += array(
      'category' => t('Ting'),
      'required context' => array(
        new ctools_context_optional(t('Ting object'), 'ting_object'),
        new ctools_context_optional(t('Ting collection'), 'ting_collection'),
      ),
    );
  }
  return $types;
}

/**
 * Return the pane titles.
 */
function ting_adhl_recommendation_list_content_type_admin_title($subtype, $conf, $contexts) {
  $identifiers =  array();
  foreach ($contexts as $context) {
    if ($context->type != 'any') {
      $identifiers[] = $context->identifier;
    }
  }
  $identifiers = implode(', ', $identifiers);

  switch ($subtype) {
    case 'recommendation_list':
      return t('“@s”: Ting recommendation list', array('@s' => $identifiers));
  }
}

/**
 * Returns an edit form for the content type.
 */
function ting_adhl_recommendation_list_content_type_edit_form($form, &$form_state) {
  return $form;
}
