package com.lockotron.mobi_o_tron.controller;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.JsonReader;
import android.util.Log;

import com.lockotron.mobi_o_tron.exception.ServerNotSetException;

import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class Usuario {
    private static final String TAG = "MOBI-O-TRON";
    private static final String KEY_SERVER_ADDRESS = "server_address";

    public static List<com.lockotron.mobi_o_tron.model.Usuario> getAll(Context context) throws IOException, ServerNotSetException {
        assert context != null;

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        if (prefs.contains(KEY_SERVER_ADDRESS) && !prefs.getString(KEY_SERVER_ADDRESS, "").equals("")) {
            String url = prefs.getString(KEY_SERVER_ADDRESS, "");
            List<com.lockotron.mobi_o_tron.model.Usuario> result = Usuario.getFromUrl(url);
            Log.d(TAG, "Got users: " + result.toString());

            return result;
        } else {
            throw new ServerNotSetException();
        }

    }

    private static List<com.lockotron.mobi_o_tron.model.Usuario> getFromUrl(String server_addr) throws IOException {

        URL url = new URL("http://" + server_addr + "/users.php");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setUseCaches(false);
        conn.setAllowUserInteraction(false);
        conn.setConnectTimeout(10000);
        conn.connect();
        int status = conn.getResponseCode();

        switch (status) {
            case 200:
            case 201:
                JsonReader reader = new JsonReader(new InputStreamReader(conn.getInputStream()));
                List<com.lockotron.mobi_o_tron.model.Usuario> usuarios = new ArrayList<>();

                reader.beginObject();
                parseArray:
                while (reader.hasNext()) {
                    String name = reader.nextName();
                    switch (name) {
                        case "success":
                            // Break if success == false
                            if (!reader.nextBoolean())
                                break parseArray;
                            break;
                        case "data":
                            reader.beginArray();
                            while (reader.hasNext()){
                                usuarios.add(readUser(reader));
                            }
                            reader.endArray();
                            break;
                        default:
                            reader.skipValue();
                            break;
                    }
                }
                reader.endObject();

                return usuarios;

            default:
                return new ArrayList<>();
        }
    }
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
