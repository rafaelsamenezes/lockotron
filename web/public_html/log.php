<?php
require_once("../controller/HistoricoController.class.php");
require_once("../controller/UsuarioController.class.php");
header("Content-Type:application/json");
$log = new HistoricoController();
if (isset($_GET['insert'])) {
	$error = false;
	if (isset($_POST['user_id']) && $_POST['user_id'] != '' &&
		isset($_POST['date']) && $_POST['date'] != '' &&
		isset($_POST['status']) && $_POST['status'] != '')
	{
		$userController = new UsuarioController();
		$user = $userController->get($_POST['user_id']);

		if (count($user) > 0)
			$user = $user[0];
		else
			$error = true;
	} else {
		$error = true;
	}

	if ($error) {
		http_response_code(400);
		echo json_encode(array(
			'success' => false,
		));
	} else {

		$new = $log->insert(new Historico(null, $user, $_POST['date'], $_POST['status']));
		echo json_encode(array(
			'success' => true,
			'data' => array($new->toArray()),
		));
	}
} else {
	$data = $log->getAll();
	foreach ($data as $i => $value) {
		$data[$i] = $value->toArray();
	}
	echo json_encode(array(
		'success' => true,
		'data' => $data,
	));
}
