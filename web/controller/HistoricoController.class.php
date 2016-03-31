<?php
require_once 'DbConnect.class.php';
require_once '../model/historico.php';
require_once 'UsuarioController.class.php';

/**
* Operações relacionadas à tabela de histórico
*/
class HistoricoController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    /**
     * Insere um registro no banco de dados
     * @param  Historico $log  O registro a ser inserido
     * @return Historico       O registro inserido, com o ID
     */
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

    /**
     * Obtém todos os valores da tabela, ordenados pelo mais recente.
     * @return array Array com os dados do histórico
     */
    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM historico ORDER BY data_hora DESC');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    /**
     * Converte um array para objeto
     * @param  array  $array Array associativo com os valores da tabela
     * @return Historico   Objeto convertido
     */
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
