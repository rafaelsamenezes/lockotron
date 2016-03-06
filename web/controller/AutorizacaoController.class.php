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

    function insert(Autorizacao $access) {
        $stmt = $this->conn->prepare("INSERT INTO autorizacao (usuario_id, dia, horario_inicio, horario_fim)"
                                                ."VALUES (?, ?, ?, ?)"
                                    );
        $stmt->bindParam(1, $access->getUsuario()->getId());
        $stmt->bindParam(2, $access->getDia());
        $stmt->bindParam(3, $access->getHorarioInicio());
        $stmt->bindParam(4, $access->getHorarioFim());
        $stmt->execute();
        $access->setId($this->conn->lastInsertId());
        return $access;
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
