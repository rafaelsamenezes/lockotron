package model;

/**
 * Created by rafael on 06/03/16.
 */
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
