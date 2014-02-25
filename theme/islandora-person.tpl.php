<?php
/**
 * @file
 * This is the template file for the object page for person objects.
 */
?>
<div class="islandora-object islandora"></div>
<div>
  <dl class="islandora-object-tn">

    <?php if (isset($variables['tn'])): ?>
      <dt>
      <img src="<?php print $variables['tn']; ?>"/>
      </dt>
    <?php endif; ?>

    <?php if (isset($variables['activities'])): ?>
      <?php print $variables['activities']; ?>
    <?php endif; ?>


  </dl>
  <h1><?php print $variables['title']; ?></h1>
  <p>Biography</p>
  <?php if (isset($variables['biography'])): ?>
    <p><?php print $variables['biography']; ?></p>
  <?php endif; ?>
  <?php if (isset($variables['metadata'])): ?>
    <?php print $variables['metadata']; ?>
  <?php endif; ?>
  <?php if (isset($variables['fellow_scholars'])): ?>
    <?php foreach ($variables['fellow_scholars'] as $dept): ?>
      <?php print $dept; ?>
    <?php endforeach; ?>
  <?php endif; ?>
  <?php if (isset($variables['recent_citations'])): ?>
    <?php print $variables['recent_citations']; ?>
  <?php endif; ?>

</div>
