<?php
require_once 'DbConnect.class.php';
require_once '../model/historico.php';
require_once 'UsuarioController.class.php';

/**
*
*/
class HistoricoController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM historico ORDER BY data_hora DESC');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    private function arrayToObject(array $array) {
        $usuario = (new UsuarioController())->get($array['usuario_id']);
        return new Historico(
                    $array['id'],
                    $usuario[0],
                    $array['data_hora'],
                    $array['status']
                );
    }
}
