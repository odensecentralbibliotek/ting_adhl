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
  'title' => t('Ting TOP ADHL recommendation'),
  'description' => t('Show a number of the most recent recommendationv from ADHL service'),
  'single' => TRUE,
  'content_types' => array('recommendation_list'),
  'render callback' => 'ting_adhl_top_recommendation_list_content_type_render',
  'category' => t('Ting'),
);

function ting_adhl_top_recommendation_list_ctools_content_types() {
  return array(
    'title' => t('Recommendation list'),
  );
}



/**
 * Return the pane contents.
 */
function ting_adhl_top_recommendation_list_content_type_render($subtype, $conf, $panel_args, $contexts) {
  // Get the objects to base the recommendation on based on the first supplied
  // context
    //drupal_add_js(drupal_get_path('module', 'ting_adhl') . '/js/ting_top_adhl.js');

  $output = '';
  $number_of_results = 14;
  $top_recommendations = variable_get('ting_adhl_top_recommendations');
  if ($top_recommendations) {
    $covers = ting_adhl_check_local_covers($top_recommendations);
    $covers = array_slice($covers, -$number_of_results);
    $output = ting_adhl_render_cover($covers );
  }

  // Build the block, if then context was present.
  $block = new stdClass();
  $block->content = $output;
  return $block;
}

///**
// * Callback function to supply a list of content types.
// */
//function ting_adhl_recommendation_list_content_type_content_types() {
//  $types = array(
//    'recommendation_list' => array(
//      'title' => t('Ting recommendation list'),
//      'description' => t('Displays a list of recommended ting entities.'),
//    ),
//  );
//
//  // Append our default settings to every type.
//  foreach ($types as $name => $type) {
//    $types[$name] += array(
//      'category' => t('Ting'),
//      'required context' => array(
//        new ctools_context_optional(t('Ting object'), 'ting_object'),
//        new ctools_context_optional(t('Ting collection'), 'ting_collection'),
//      ),
//    );
//  }
//  return $types;
//}
//
///**
// * Return the pane titles.
// */
//function ting_adhl_recommendation_list_content_type_admin_title($subtype, $conf, $contexts) {
//  $identifiers =  array();
//  foreach ($contexts as $context) {
//    if ($context->type != 'any') {
//      $identifiers[] = $context->identifier;
//    }
//  }
//  $identifiers = implode(', ', $identifiers);
//
//  switch ($subtype) {
//    case 'recommendation_list':
//      return t('“@s”: Ting recommendation list', array('@s' => $identifiers));
//  }
//}

/**
 * Returns an edit form for the content type.
 */
function ting_adhl_top_recommendation_list_content_type_edit_form($form, &$form_state) {
  return $form;
}
