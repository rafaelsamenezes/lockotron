package model;

import java.util.List;

/**
 * Created by rafael on 06/03/16.
 */
public class Historico {
    public Historico(List<Log> logs, boolean success) {
        this.logs = logs;
        this.success = success;
    }

    public List<Log> getLogs() {
        return logs;
    }

    public boolean isSuccess() {
        return success;
    }

    private List<Log> logs;
    private boolean success;
}
