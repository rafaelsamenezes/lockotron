package com.lockotron.mobi_o_tron.util;

public class Statistics {
    public static int mostFrequentUser(int[] userIds){
        return Native.mostFrequentUser(userIds);
    }
    private static class Native {
        public native static int mostFrequentUser(int[] userIds);
    }
}