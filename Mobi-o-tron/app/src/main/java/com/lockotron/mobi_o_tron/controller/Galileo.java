package com.lockotron.mobi_o_tron.controller;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.lockotron.mobi_o_tron.Exception.ServerNotSetException;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

public class Galileo {
    private static final String TAG = "MOBI-O-TRON";
    private static final String KEY_SERVER_ADDRESS = "server_address";

    public static void openDoor(Context context) throws IOException, ServerNotSetException {
        request(context, "panic");
    }

    public static void update(Context context) throws IOException, ServerNotSetException {
        request(context, "update");
    }

    public static void kill(Context context) throws IOException, ServerNotSetException {
        request(context, "kill");
    }

    private static void request(Context context, String param) throws ServerNotSetException, IOException {

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        if (prefs.contains(KEY_SERVER_ADDRESS) && !prefs.getString(KEY_SERVER_ADDRESS, "").equals("")) {
            String url = prefs.getString(KEY_SERVER_ADDRESS, "");
            Galileo.request(url + "/galileo?" + param);
        } else {
            throw new ServerNotSetException();
        }
    }

    private static boolean request(String server_addr) throws IOException {

        URL url = new URL("http://" + server_addr);
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
                return true;

            default:
                return false;
        }
    }
}
