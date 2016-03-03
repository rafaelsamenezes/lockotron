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

    function toArray() {
        return array(
            'id' => $this->id,
            'usuario' => $this->usuario->toArray(),
            'data' => $this->data,
            'estado' => $this->estado,
        );
    }
}
