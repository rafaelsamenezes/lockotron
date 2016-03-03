<?php
/**
* Modelo autorizacao
*/
class Autorizacao
{
    private $id, $usuario, $dia, $horario_inicio, $horario_fim;
    function __construct($id, $usuario, $dia, $horario_inicio, $horario_fim)
    {
        $this->id = $id;
        $this->usuario = $usuario;
        $this->dia = $dia;
        $this->horario_inicio = $horario_inicio;
        $this->horario_fim = $horario_fim;
    }

    function getHorarioInicio() {
        return $this->horario_inicio;
    }

    function getHorarioFim() {
        return $this->horario_fim;
    }

    function getDia() {
        return $this->dia;
    }

    function toArray()
    {
        return array(
            'id' => $this->id,
            'usuario' => $this->usuario,
            'dia' => $this->dia,
            'horario_inicio' => $this->horario_inicio,
            'horario_fim' => $this->horario_fim,
        );
    }
}
