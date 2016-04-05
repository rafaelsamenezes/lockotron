package com.lockotron.mobi_o_tron.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;

import com.lockotron.mobi_o_tron.model.Historico;
import com.lockotron.mobi_o_tron.model.Usuario;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

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
            return null;
        com.lockotron.mobi_o_tron.model.Usuario user = log.get(0).getUsuario();
        int[] idArray = new int[log.size()];

        for (int i = 0; i < log.size(); i++) {
            idArray[i] = log.get(i).getUsuario().getId();
        }

        if (isNative(context))
            userId = Native.mostFrequentUser(idArray);
        else
            userId = getMode(idArray);

        for (int i = 0; i < log.size(); i++) {
            if (log.get(i).getId() == userId) {
                user = log.get(i).getUsuario();
                break;
            }
        }

        return user;
    }

    @Nullable
    public static Usuario lessFrequentUser(Context context, List<Historico> log) {
        int userId;
        if (log.size() == 0)
            return null;
        com.lockotron.mobi_o_tron.model.Usuario user = log.get(0).getUsuario();
        int[] idArray = new int[log.size()];

        for (int i = 0; i < log.size(); i++) {
            idArray[i] = log.get(i).getUsuario().getId();
        }

        if (isNative(context))
            userId = Native.lessFrequentUser(idArray);
        else
            userId = lessRepeated(idArray);

        for (int i = 0; i < log.size(); i++) {
            if (log.get(i).getId() == userId) {
                user = log.get(i).getUsuario();
                break;
            }
        }

        return user;
    }

    @Nullable
    public static String mostFrequentTime(Context context, List<Historico> log, int userId){
        List<Historico> newList = new ArrayList<>(log);

        for (Historico l : newList) {
            if (l.getUsuario().getId() != userId) {
                newList.remove(l);
            }
        }

        return mostFrequentTime(context, newList);
    }

    @Nullable
    public static String mostFrequentTime(Context context, List<Historico> log) {
        if (log.size() == 0)
            return null;

        int[] hours = new int[log.size()];

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.US);

        for (int i = 0; i < log.size(); i++) {
            try {
                hours[i] = dateFormat.parse(log.get(i).getData()).getHours();
            } catch (ParseException e) {
                hours[i] = -1;
            }
        }

        int time;
        if (isNative(context))
            time = Native.mostFrequentUser(hours);
        else
            time = getMode(hours);

        return String.format(Locale.getDefault(), "%02d:00 - %02d:00", time, time+1);
    }

    private static int lessRepeated(int[] values) {
        //FIXME: Fazer funcionar isso aqui.
        Arrays.sort(values);

        int menor = 0;
        int valorAtual = values[0];
        int quantidadeMin = values.length;
        int quantidadeAtual = 0;

        for (int userId : values) {
            if (userId == valorAtual) {
                quantidadeAtual++;
            } else {
                valorAtual = userId;
                quantidadeAtual = 1;
            }

            if (quantidadeAtual < quantidadeMin) {
                quantidadeMin = quantidadeAtual;
                menor = userId;
            }
        }
        return menor;
    }

    private static int getMode(int[] values) {
        Arrays.sort(values);

        int maior = 0;
        int valorAtual = values[0];
        int quantidadeMax = 0;
        int quantidadeAtual = 0;

        for (int userId : values) {
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
        @SuppressWarnings("JniMissingFunction")
        public native static int mostFrequentUser(int[] userIds);
        @SuppressWarnings("JniMissingFunction")
        public native static int lessFrequentUser(int[] userIds);
    }
}