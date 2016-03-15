package com.lockotron.mobi_o_tron.model;

public class Historico {
    public Historico(int id, Usuario usuario, String data, String estado) {
        this.id = id;
        this.usuario = usuario;
        this.data = data;
        this.estado = estado;
    }

    public int getId() {
        return id;
    }

    public Usuario getUsuario() {
        return usuario;
    }

    public String getData() {
        return data;
    }

    public String getEstado() {
        return estado;
    }

    private int id;
    private Usuario usuario;
    private String data;
    private String estado;
}
