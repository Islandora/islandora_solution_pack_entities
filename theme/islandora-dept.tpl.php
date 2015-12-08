<?php
/**
 * @file
 * This is the template file for the object page for organization objects.
 */
?>

<div class="islandora-object-image islandora-department-thumbnail">
  <?php if (isset($variables['tn'])): ?>
    <img src="<?php print $variables['tn']; ?>"/>
  <?php endif; ?>
</div>

<?php if (isset($variables['metadata'])): ?>
  <div class="departmental_metadata">
    <?php print $variables['metadata']; ?>
  </div>
<?php endif; ?>

