<?php
/**
 * @file
 * This is the template file for the object page for organization objects.
 */
?>

<div class="islandora-object islandora">
<?php if (isset($variables['tn'])): ?>
  <dl class="islandora-object-tn islandora-department">
    <dt>
      <img alt="<?php print $variables['tn_alt'];?>" id="<?php print $variables['tn_id'];?>" src="<?php print $variables['tn']; ?>"/>
    </dt>
    <dd>
      <label class="element-invisible" for="<?php print $variables['tn_id'];?>"><?php print $tn_alt;?></label>
    </dd>
  </dl>
<?php endif; ?>

<?php if (isset($variables['metadata'])): ?>
  <div class="departmental_metadata">
    <?php print $variables['metadata']; ?>
  </div>
<?php endif; ?>
</div>
