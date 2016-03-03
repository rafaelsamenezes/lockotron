<?php
/**
* Modelo usuário
*/
class Usuario
{
    private $id, $nome;
    /**
     * @param int $id
     * @param string $nome
     */
    function __construct($id, $nome)
    {
        $this->id = $id;
        $this->nome = $nome;
    }

    function toArray()
    {
        return array(
            'id' => $this->id,
            'nome' => $this->nome,
        );
    }
}
