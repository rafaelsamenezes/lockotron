<?php
require_once 'DbConnect.class.php';
require_once("../controller/AutorizacaoController.class.php");
require_once '../model/usuario.php';

/**
* Operações relacionadas à tabela de usuários
*/
class UsuarioController
{
    private $conn;

    function __construct() {
        $this->conn = (new DbConnect())->getConnection();
    }

    /**
     * Insere um registro na tabela
     * @param  Usuario $user   Usuário a ser inserido
     * @return Usuario         Usuário inserido, mas com valor do ID
     */
    function insert(Usuario $user) {
        $stmt = $this->conn->prepare("INSERT INTO usuario (nome) VALUES (?)");
        $stmt->bindParam(1, $user->getNome());
        $stmt->execute();
        $user->setId($this->conn->lastInsertId());
        return $user;
    }

    /**
     * Edita um usuário.
     * Esta classe se baseia no ID do usuário fornecido para editar o nome do
     * usuário. O novo nome será o nome incluído no objeto que for passado como
     * argumento.
     * @param  Usuario $user  Usuário a ser editado
     * @return Usuario        Usuário editado
     */
    function edit(Usuario $user) {
        $stmt = $this->conn->prepare("UPDATE usuario SET nome = ? WHERE usuario.id = ?");
        $stmt->bindParam(1, $user->getNome());
        $stmt->bindParam(2, $user->getId());
        $stmt->execute();
        return $user;
    }

    /**
     * Remove um usuário do banco de dados
     * @param  Usuario $user   Usuário a ser removido
     */
    function delete(Usuario $user)
    {
        return $this->deleteId($user->getId());
    }

    /**
     * Remove um usuário do banco de dados
     * @param  int $user_id   ID do usuário a ser removido
     */
    function deleteId($user_id)
    {
        $acc = new AutorizacaoController();
        $acc->deleteAllOfUser($user_id);

        $stmt = $this->conn->prepare('DELETE FROM usuario WHERE id = :user_id');
        return $stmt->execute(array(':user_id' => $user_id));
    }

    /**
     * Obtém todos os usuários
     * @return array Array de objetos Usuario
     */
    function getAll() {
        $stmt = $this->conn->query('SELECT * FROM usuario ORDER BY usuario.nome ASC');
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    /**
     * Recebe os dados de um usuário dado seu ID.
     * @param  int $id  ID do usuário a ser procurado
     * @return Usuario  Usuário referente ao ID informado
     */
    function get($id) {
        $stmt = $this->conn->prepare('SELECT * FROM usuario WHERE id = :id');
        $stmt->execute(array(':id' => $id));
        $data = $stmt->fetchAll();
        foreach ($data as $i => $row) {
            $data[$i] = $this->arrayToObject($row);
        }
        return $data;
    }

    /**
     * Converte um array para objeto
     * @param  array  $array Array associativo com os valores da tabela
     * @return Usuario   Objeto convertido
     */
    private function arrayToObject(array $array) {
        return new Usuario($array['id'],
                    $array['nome']);
    }
}
