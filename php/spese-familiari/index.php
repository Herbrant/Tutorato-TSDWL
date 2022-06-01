<html>
<?php
$f = fopen('entrate.json', 'r');
$entrate = fread($f, filesize('entrate.json'));
fclose($f);
$entrate = json_decode($entrate, true);

$f = fopen('uscite.json', 'r');
$uscite = fread($f, filesize('uscite.json'));
fclose($f);
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
