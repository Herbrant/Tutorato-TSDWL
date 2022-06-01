<?php
if ($_SERVER['REQUEST_METHOD'] == 'GET'){
?>
<html>
<form action="add.php" method="post">
    <label for="type" >Tipo</label>
    <select name="type" id="type">
        <option value="entrata">Entrata</option>
        <option value="uscita">Uscita</option>
    </select>
    <label for="data">Data</label>
    <input type="date" name="data" id="data">
    <label for="nome">Nome</label>
    <input type="text" name="nome" id="nome">
    <label for="cognome">Cognome</label>
    <input type="text" name="cognome" id="cognome">
    <label for="importo">Importo</label>
    <input type="number" name="importo" id="importo">
    <input type="submit" value="Aggiungi">
</form>
</html>
<?php 
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $type = $_POST['type'];
    $name = $_POST['nome'];
    $lastname = $_POST['cognome'];
    $import = $_POST['importo'];
    $date = $_POST['data'];

    $entry = [
        'nome' => $name,
        'cognome' => $lastname,
        'data' => $date,
        'importo' => $import
    ];

    if ($type == 'entrata')
        $filename = './entrate.json';    
    else
        $filename = './uscite.json';
    
    if (file_exists($filename) && filesize($filename) > 0) {
        $jsonString = file_get_contents($filename);
        $entries = json_decode($jsonString, true);
        $entries[] = $entry;
        $jsonString = json_encode($entries);
        file_put_contents($filename, $jsonString);
    } else {
        $f = fopen($filename, 'w');
        $entries = [];
        $entries[] = $entry;
        $jsonString = json_encode($entries);
        file_put_contents($filename, $jsonString);
    }

    header('Location: index.php');
}

?>