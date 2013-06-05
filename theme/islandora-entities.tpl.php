<?php
/**
 * @file
 *   islandora-entities.tpl.php
 */

?>

<div class="islandora-entities-wrapper">
  <div class="islandora-object islandora">
    <h2>EAC-CPF</h2>
    <dl class="islandora-inline-metadata islandora-object-fields">
      <?php foreach($data_array as $key => $value): ?>
        <dt class="<?php print $value['values']['class']; ?>">
          <?php print $value['values']['text']; ?>
        </dt>
        <dd class="<?php print $value['values']['class']; ?>">
          <?php print $value['values']['text']; ?>
        </dd>
      <?php endforeach; ?>
    </dl>
  </div>
</div>