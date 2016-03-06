<?php
require_once("../controller/HistoricoController.class.php");
require_once("../controller/AutorizacaoController.class.php");
header("Content-Type:application/json");
$user = new UsuarioController();
$access = new AutorizacaoController();
$data = $user->getAll();
foreach ($data as $i => $value) {
	$data[$i] = $value->toArray();
	$data[$i]['access'] = $access->getForUser($value->getId());
	foreach ($data[$i]['access'] as $j => $a) {
		$data[$i]['access'][$j] = $a->toArray();
	}
}
echo json_encode(array(
	'success' => true,
	'data' => $data,
));
