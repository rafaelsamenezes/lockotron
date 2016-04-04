package com.lockotron.mobi_o_tron.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.lockotron.mobi_o_tron.controller.Usuario;

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

    public static int mostFrequentUser(Context context, int[] userIds){
        //TODO: Pegar usuários e passar vetor de IDs

        if (isNative(context))
            return Native.mostFrequentUser(userIds);
        else
            return 0;
    }
    private static class Native {
        public native static int mostFrequentUser(int[] userIds);
    }
}