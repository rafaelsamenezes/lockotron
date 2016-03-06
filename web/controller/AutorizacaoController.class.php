<?php
require_once 'DbConnect.class.php';
require_once '../model/autorizacao.php';

/**
*
*/
class AutorizacaoController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM autorizacao');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    function getForUser($user_id) {
        $stmt = $this->conn->prepare('SELECT * FROM autorizacao WHERE usuario_id = :user_id ORDER BY dia ASC, horario_inicio ASC');
        $stmt->execute(array(':user_id' => $user_id));
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    private function arrayToObject(array $array) {
        return new Autorizacao($array['id'],
                    $array['usuario_id'],
                    $array['dia'],
                    $array['horario_inicio'],
                    $array['horario_fim']
                );
    }
}
