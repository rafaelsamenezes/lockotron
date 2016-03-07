<?php
require_once 'DbConnect.class.php';
require_once '../model/usuario.php';

/**
*
*/
class UsuarioController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    function insert(Usuario $user) {
        $stmt = $this->conn->prepare("INSERT INTO usuario (nome) VALUES (?)");
        $stmt->bindParam(1, $user->getNome());
        $stmt->execute();
        $user->setId($this->conn->lastInsertId());
        return $user;
    }

    function edit(Usuario $user) {
        $stmt = $this->conn->prepare("UPDATE usuario SET nome = ? WHERE usuario.id = ?");
        $stmt->bindParam(1, $user->getNome());
        $stmt->bindParam(2, $user->getId());
        $stmt->execute();
        return $user;
    }

    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM usuario');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    function get($id) {
        $stmt = $this->conn->prepare('SELECT * FROM usuario WHERE id = :id');
        $stmt->execute(array(':id' => $id));
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }


    private function arrayToObject(array $array) {
        return new Usuario($array['id'],
                    $array['nome']);
    }
}
