package com.lockotron.mobi_o_tron.controller;

import android.util.JsonReader;
import android.util.Log;

import com.lockotron.mobi_o_tron.model.Usuario;

import org.json.JSONArray;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class Historico {
    private static final String TAG = "MOBI-O-TRON";

    public static List<com.lockotron.mobi_o_tron.model.Historico> getAll() throws IOException {

        List<com.lockotron.mobi_o_tron.model.Historico> result = Historico.getFromUrl("http://192.168.1.3:82");

        Log.d(TAG, "Got log: " + result.toString());

        return result;

    }

    private static List<com.lockotron.mobi_o_tron.model.Historico> getFromUrl(String server_addr) throws IOException {

        URL url = new URL(server_addr + "/log.php");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setUseCaches(false);
        conn.setAllowUserInteraction(false);
        conn.connect();
        int status = conn.getResponseCode();

        switch (status) {
            case 200:
            case 201:
                JsonReader reader = new JsonReader(new InputStreamReader(conn.getInputStream()));
                List<com.lockotron.mobi_o_tron.model.Historico> historicos = new ArrayList<>();

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
                                historicos.add(readLog(reader));
                            }
                            reader.endArray();
                            break;
                        default:
                            reader.skipValue();
                            break;
                    }
                }
                reader.endObject();

                return historicos;

            default:
                return new ArrayList<>();
            }
    }

    public static com.lockotron.mobi_o_tron.model.Historico readLog(JsonReader reader) throws IOException {
        int id = -1;
        Usuario usuario = null;
        String data = "";
        boolean estado = Boolean.FALSE;

        reader.beginObject();
        while (reader.hasNext()) {
            String obj = reader.nextName();
            switch (obj) {
                case "id":
                    id = reader.nextInt();
                    break;
                case "usuario":
                    usuario = com.lockotron.mobi_o_tron.controller.Usuario.readUser(reader);
                    break;
                case "data":
                    data = reader.nextString();
                    break;
                case "estado":
                    estado = reader.nextInt() != 0;
                    break;
                default:
                    reader.skipValue();
                    break;
            }
        }
        reader.endObject();

        return new com.lockotron.mobi_o_tron.model.Historico(id,usuario,data,estado);
    }
}