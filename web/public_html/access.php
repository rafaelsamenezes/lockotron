<?php
require_once("../controller/AutorizacaoController.class.php");
header("Content-Type:application/json");
$access = new AutorizacaoController();
if (isset($_REQUEST['user_id'])) {
	if (isset($_POST['user_id']) && $_POST['user_id'] != '') {
		$user_id = $_POST['user_id'];
	} else if (isset($_GET['user_id']) && $_GET['user_id'] != ''){
		$user_id = $_GET['user_id'];
	}

	$data = $access->getForUser($user_id);
	$now = time();
	$today = date('w');
	$access = false;
	foreach ($data as $value) {
		if ($value->getDia() == $today &&
			strtotime($value->getHorarioInicio()) <= $now &&
			strtotime($value->getHorarioFim()) >= $now) {
				$access = true;
				break;
		}
	}

	if (!isset($_GET['notlog'])) {
		require_once("../controller/HistoricoController.class.php");
		require_once("../controller/UsuarioController.class.php");
		$error = false;

		$userController = new UsuarioController();
		$user = $userController->get($user_id);

		if (count($user) > 0)
			$user = $user[0];
		else
			$error = true;

		if (!$error) {
			$log = new HistoricoController();
			$log->insert(new Historico(null, $user, date('Y-m-d H:i:s', $now), $access));
		}
	}
	echo json_encode(array(
		'success' => true,
		'logSuccess' => !$error,
		'data' => array(
			'access' => $access,
			'time' => date('H:i:s', $now),
			'day' => $today,
		),
	));

} else {
	$data = $access->getAll();
	foreach ($data as $i => $value) {
		$data[$i] = $value->toArray();
	}
	echo json_encode(array(
		'success' => true,
		'data' => $data,
	));
}
