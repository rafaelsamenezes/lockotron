<?php
require_once 'DbConnect.class.php';
require_once '../model/autorizacao.php';

/**
* Operações relacionadas à tabela de autorização
*/
class AutorizacaoController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    /**
     * Obtém todos os dados de autorização
     * @return array Array de objetos Autorizacao
     */
    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM autorizacao');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    /**
     * Insere um novo dado na tabela
     * @param  Autorizacao $access Objeto a ser inserido
     * @return Autorizacao         Objeto inserido com o valor do ID
     */
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

    /**
     * Retorna as autorizações de um usuário específico
     * @param  int $user_id    O ID do usuário
     * @return array           Array com as autorizações do usuário
     */
    function getForUser($user_id) {
        $stmt = $this->conn->prepare('SELECT * FROM autorizacao WHERE usuario_id = :user_id ORDER BY dia ASC, horario_inicio ASC');
        $stmt->execute(array(':user_id' => $user_id));
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    /**
     * Remove do banco de dados todas as autorizações de um usuário
     * @param  int $user_id    ID do usuário
     */
    function deleteAllOfUser($user_id)
    {
        $stmt = $this->conn->prepare('DELETE FROM autorizacao WHERE usuario_id = :user_id');
        return $stmt->execute(array(':user_id' => $user_id));
    }

    /**
     * Converte um array para objeto
     * @param  array  $array Array associativo com os valores da tabela
     * @return Autorizacao   Objeto convertido
     */
    private function arrayToObject(array $array) {
        return new Autorizacao($array['id'],
                    $array['usuario_id'],
                    $array['dia'],
                    $array['horario_inicio'],
                    $array['horario_fim']
                );
    }
}
