/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

(function($) {
  

  Drupal.behaviors.tingAdhlGetRecommendation = {		
    attach: function(context, settings) {
      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + "ting/adhl/ajax",
        dataType: "json",
        data: {
          "objectId" : settings.ting_adhl_objectId
        },
        success: function (data) {
          if (data != null) {
            
            $("#ting-adhl-recommendation").html(data);
          }
        }
      });				
      
    }
  }

})(jQuery);


