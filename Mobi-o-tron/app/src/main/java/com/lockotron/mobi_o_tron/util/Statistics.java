package com.lockotron.mobi_o_tron.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import java.util.List;

public class Statistics {

    private static boolean isNative(Context context) {
        final String PREF_NATIVE = "use_native";
        boolean result = false;
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        if (prefs.contains(PREF_NATIVE)) {
            result = prefs.getBoolean(PREF_NATIVE, false);
        }
        return result;
    }

    public static com.lockotron.mobi_o_tron.model.Usuario mostFrequentUser(Context context, List<com.lockotron.mobi_o_tron.model.Usuario> users){
        int userId;
        com.lockotron.mobi_o_tron.model.Usuario user = users.get(0);
        int[] idArray = new int[users.size()];

        for (int i = 0; i < users.size(); i++) {
            idArray[i] = users.get(i).getId();
        }

        if (isNative(context))
            userId = Native.mostFrequentUser(idArray);
        else
            userId = mostFrequentUser(idArray);

        for (int i = 0; i < users.size(); i++) {
            if (users.get(i).getId() == userId) {
                user = users.get(i);
                break;
            }
        }

        return user;
    }

    private static int mostFrequentUser(int[] userIds) {
        //TODO: Implementar moda em Java
        return 1;
    }

    private static class Native {
        public native static int mostFrequentUser(int[] userIds);
    }
}