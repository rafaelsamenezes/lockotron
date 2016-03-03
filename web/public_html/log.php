<?php
require_once("../controller/HistoricoController.class.php");
header("Content-Type:application/json");
$log = new HistoricoController();
$data = $log->getAll();
foreach ($data as $i => $value) {
	$data[$i] = $value->toArray();
}
echo json_encode(array(
	'success' => true,
	'data' => $data,
));
