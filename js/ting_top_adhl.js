/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

(function($) {
  

  Drupal.behaviors.tingAdhlGetTopRecommendation = {		
    attach: function(context, settings) {
      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + "ting/adhl/top",
        dataType: "json",
        data: { },
        success: function (data) {
          if (data != null) {
            
            $("#ting-adhl-top-recommendation").html(data);
          }
        }
      });				
      
    }
  }

})(jQuery);


