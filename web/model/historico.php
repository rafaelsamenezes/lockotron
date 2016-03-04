<?php
/**
* Modelo histórico
*/
class Historico
{
    private $id, $usuario, $data, $estado;
    function __construct($id, $usuario, $data, $estado)
    {
        $this->id = $id;
        $this->usuario = $usuario;
        $this->data = $data;
        $this->estado = $estado;
    }

    /**
     * Retrieves the currently set data.
     *
     * @return mixed
     */
    public function getData()
    {
        return $this->data;
    }

    /**
     * Sets the date to use.
     *
     * @param mixed $data
     *
     * @return $this
     */
    public function setData($data)
    {
        $this->data = $data;
        return $this;
    }

    /**
     * Retrieves the currently set estado.
     *
     * @return mixed
     */
    public function getEstado()
    {
        return $this->estado;
    }

    /**
     * Sets the estado to use.
     *
     * @param mixed $estado
     *
     * @return $this
     */
    public function setEstado($estado)
    {
        $this->estado = $estado;
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

    /**
     * Retrieves the currently set usuario.
     *
     * @return mixed
     */
    public function getUsuario()
    {
        return $this->usuario;
    }

    function toArray() {
        return array(
            'id' => $this->id,
            'usuario' => $this->usuario->toArray(),
            'data' => $this->data,
            'estado' => $this->estado,
        );
    }
}
