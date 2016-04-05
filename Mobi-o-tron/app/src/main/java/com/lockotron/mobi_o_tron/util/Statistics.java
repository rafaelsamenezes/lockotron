package com.lockotron.mobi_o_tron.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.lockotron.mobi_o_tron.R;
import com.lockotron.mobi_o_tron.model.Historico;
import com.lockotron.mobi_o_tron.model.Usuario;

import java.util.Arrays;
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

    public static com.lockotron.mobi_o_tron.model.Usuario mostFrequentUser(Context context, List<Historico> log){
        int userId;
        if (log.size() == 0)
            return new Usuario(0, context.getString(R.string.not_available));
        com.lockotron.mobi_o_tron.model.Usuario user = log.get(0).getUsuario();
        int[] idArray = new int[log.size()];

        for (int i = 0; i < log.size(); i++) {
            idArray[i] = log.get(i).getUsuario().getId();
        }

        if (isNative(context))
            userId = Native.mostFrequentUser(idArray);
        else
            userId = mostFrequentUser(idArray);

        for (int i = 0; i < log.size(); i++) {
            if (log.get(i).getId() == userId) {
                user = log.get(i).getUsuario();
                break;
            }
        }

        return user;
    }

    private static int mostFrequentUser(int[] userIds) {
        Arrays.sort(userIds);

        int maior = 0;
        int valorAtual = userIds[0];
        int quantidadeMax = 0;
        int quantidadeAtual = 0;

        for (int userId : userIds) {
            if (userId == valorAtual) {
                quantidadeAtual++;
            } else {
                valorAtual = userId;
                quantidadeAtual = 1;
            }

            if (quantidadeAtual > quantidadeMax) {
                quantidadeMax = quantidadeAtual;
                maior = userId;
            }
        }
        return maior;
    }

    private static class Native {
        public native static int mostFrequentUser(int[] userIds);
    }
}