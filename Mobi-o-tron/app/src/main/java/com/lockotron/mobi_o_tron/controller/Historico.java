package com.lockotron.mobi_o_tron.controller;

import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.List;

public class Historico {
    public static List<com.lockotron.mobi_o_tron.model.Historico> getAll() {

        String result = Historico.getFromUrl("http://192.168.43.205:81");

        Log.d("CONEXAO", result);

        return null; // TODO: 14/03/16 Mudar aqui

    }

    private static String getFromUrl(String server_addr){
        try {
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
                    BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
                    StringBuilder sb = new StringBuilder();
                    String line;
                    while ((line = br.readLine()) != null) {
                        sb.append(line).append("\n");
                    }
                    br.close();
                    return sb.toString();

            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return "";
    }
}