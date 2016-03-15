package com.lockotron.mobi_o_tron.model;

public class Usuario {


    public Usuario(int id, String nome) {
        this.id = id;
        this.nome = nome;
    }

    public int getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    private int id;
    private String nome;


}
