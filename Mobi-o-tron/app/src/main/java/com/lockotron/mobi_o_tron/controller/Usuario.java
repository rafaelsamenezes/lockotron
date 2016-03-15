package com.lockotron.mobi_o_tron.controller;

import android.util.JsonReader;

import java.io.IOException;

public class Usuario {
    public static com.lockotron.mobi_o_tron.model.Usuario readUser(JsonReader reader) throws IOException {
        int id = -1;
        String nome = "";

        reader.beginObject();
        while (reader.hasNext()) {
            String obj = reader.nextName();
            switch (obj) {
                case "id":
                    id = reader.nextInt();
                    break;
                case "nome":
                    nome = reader.nextString();
                    break;
                default:
                    reader.skipValue();
                    break;
            }
        }
        reader.endObject();

        return new com.lockotron.mobi_o_tron.model.Usuario(id,nome);
    }
}
