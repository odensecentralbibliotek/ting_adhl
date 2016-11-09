
<?php
/**
 *
 */
?>
<?php if ($title) : ?>
  <div class="adhl-header">
    <div class="adhl-title">
      <h2><?php print $title; ?></h2>
    </div>
  </div>
<?php endif; ?>

<?php if ($results) : ?>
  <div class="search-results adhl-results">
    <ul class="list floated">
      <?php foreach ($results as $result) : ?>
        <li class="list-item" style="display:inline-block">
          <?php if ($result['snippet']): ?>
            <?php print $result['snippet']; ?>
          <?php endif; ?>
        </li>
      <?php endforeach; ?>
    </ul>
  </div>
<?php endif; ?>
