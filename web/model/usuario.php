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

    /**
     * Retrieves the currently set nome.
     *
     * @return mixed
     */
    public function getNome()
    {
        return $this->nome;
    }

    /**
     * Sets the nome to use.
     *
     * @param mixed $nome
     *
     * @return $this
     */
    public function setNome($nome)
    {
        $this->nome = $nome;
        return $this;
    }

    /**
     * Retrieves the currently set id.
     *
     * @return mixed
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * Sets the id to use.
     *
     * @param mixed $id
     *
     * @return $this
     */
    public function setId($id)
    {
        $this->id = $id;
        return $this;
    }

    function toArray()
    {
        return array(
            'id' => $this->id,
            'nome' => $this->nome,
        );
    }
}
