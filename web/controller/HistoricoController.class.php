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

    function insert(Historico $log) {
        $stmt = $this->conn->prepare("INSERT INTO historico (usuario_id, data_hora, status) "
                                        . "VALUES (?, ?, ?)");
        $stmt->bindParam(1, $log->getUsuario()->getId());
        $stmt->bindParam(2, $log->getData());
        $stmt->bindParam(3, $log->getEstado());
        $stmt->execute();
        $log->setId($this->conn->lastInsertId());
        return $log;
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
