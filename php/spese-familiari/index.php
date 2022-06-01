<html>
<?php
$entrate = file_get_contents('entrate.json');
$entrate = json_decode($entrate, true);

$uscite = file_get_contents('uscite.json');
$uscite = json_decode($uscite, true);
?>

<h1>Registro Famiglia</h1>
<h2>Entrate</h2>
<?php
foreach($entrate as $entrata) {
    echo $entrata['data'] . ' ' . $entrata['nome'] . ' ' . $entrata['cognome'] . ':' . $entrata['importo'] . '$<br>';
}
?>
<h2>Uscite</h2>
<?php
foreach($uscite as $uscita) {
    echo $uscita['data'] . ' ' . $uscita['nome'] . ' ' . $uscita['cognome'] . ':' . $uscita['importo'] . '$<br>';
}
?>
<br>
<a href="add.php">Aggiungi entry</a>
</html>
