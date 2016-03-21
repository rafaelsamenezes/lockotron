package com.lockotron.mobi_o_tron.exception;

public class GalileoNotFoundException extends Exception {
    @Override
    public String getMessage() {
        return "The server was not able to find Galileo.";
    }
}
