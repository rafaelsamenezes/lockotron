var app = {
    init: function() {
        app.loadUsers();
        app.loadLog();
        $('.new-user-button').click(function(){
            userDialog.insert();
        });
        $('.users-refresh').click(function() {
            app.loadUsers();
        });
    },

    weekDays: ["domingo", "segunda", "terça", "quarta", "quinta", "sexta", "sábado"],
    weekDaysShort: ["dom", "seg", "ter", "qua", "qui", "sex", "sáb"],

    loadUsers: function() {
         $.ajax("/users.php")
            .done(function(data){
                $('#users-table tbody').empty();
                data.data.forEach(function(el){

                    var access = "";
                    el.access.forEach(function (acc) {
                        access +=
                            app.weekDaysShort[acc.dia] + ", de "
                            + acc.horario_inicio + " a "
                            + acc.horario_fim + "<br/>";
                    });

                    $('#users-table tbody').append('\
                    <tr data-user-id="{id}">\
                        <td>{id}</td>\
                        <td class="mdl-data-table__cell--non-numeric">{name}</td>\
                        <td class="mdl-data-table__cell--non-numeric">{access}\
                        </td>\
                        <td class="mdl-data-table__cell--non-numeric">\
                            <span id="delete-{id}"><button class="mdl-button mdl-js-button mdl-button--icon">\
                                <i class="material-icons">delete</i>\
                            </button></span>\
                            <span class="mdl-tooltip" for="delete-{id}">Excluir</span>\
                        </td>\
                    </tr>'
                    .replace(/{id}/g, el.id)
                    .replace(/{name}/g, el.nome)
                    .replace(/{access}/g, access)
                    );
                });
            });
    },


    loadLog: function() {
         $.ajax("/log.php")
            .done(function(data){
                $('#log-table tbody').empty();
                data.data.forEach(function(el){

                    $('#log-table tbody').append('\
                        <tr>\
                            <td class="mdl-data-table__cell--non-numeric">{date}</td>\
                            <td class="mdl-data-table__cell--non-numeric">{name}</td>\
                            <td class="mdl-data-table__cell--non-numeric">{action}</td>\
                        </tr>'
                    .replace(/{date}/g, el.data)
                    .replace(/{name}/g, el.usuario.nome)
                    .replace(/{action}/g, el.estado ? "Autorizado" : "Proibido")
                    );
                });
            });
    }

};

var userDialog = {
    rules: 0,
    edit: function(user) {
        userDialog.show(user)
    },

    insert: function() {
        userDialog.show({id:null});
    },

    show: function(user) {
        var dialog = $('#user-dialog');
        if (! dialog[0].showModal) {
            dialogPolyfill.registerDialog(dialog[0]);
        }

        userDialog.emptyRules();

        if (user.id === null) {
            dialog.find('.mdl-dialog__title').text("Novo usuário");
            dialog.find('#user-name').val("");
            user.name = "";
            user.access = [];

        } else {
            dialog.find('.mdl-dialog__title').text("Editar usuário");
        }

        dialog[0].showModal();
        dialog.find('#access-add').unbind('click').click(function() {
            userDialog.newRule();
        });
        dialog.find('#user-close').unbind('click').click(function() {
            dialog[0].close();
        });
        dialog.find('#user-save').unbind('click').click(function() {
            user['name'] = dialog.find('#user-name').val();

            var rules = dialog.find('.rule');
            var access = [];
            rules.each(function(i, el) {
                access.push({
                    'id': $(el).find('.access-id').val(),
                    'day': $(el).find('.access-day').val(),
                    'time-start': $(el).find('.access-time-start').val(),
                    'time-end': $(el).find('.access-time-end').val(),
                });
            });

            user.access = access;

            userDialog.save(user);
            dialog[0].close();
        });
    },

    emptyRules: function() {
        $('#access-rules').empty();
        userDialog.rules = 0;
    },

    newRule: function(access) {
        $('#access-rules').append('\
        <div class="rule mdl-grid mdl-grid--no-spacing">\
            <div class="mdl-cell mdl-cell--12-col">\
                <input type="hidden" class="access-id">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <select class="mdl-textfield__input access-day" id="day-{n}">\
                        <option value="0">Todo domingo</option>\
                        <option value="1">Toda segunda</option>\
                        <option value="2">Toda terça</option>\
                        <option value="3">Toda quarta</option>\
                        <option value="4">Toda quinta</option>\
                        <option value="5">Toda sexta</option>\
                        <option value="6">Todo sábado</option>\
                    </select>\
                    <label class="mdl-textfield__label" for="day-{n}">Dia</label>\
                </div>\
            </div>\
            <div class="mdl-cell mdl-cell--6-col">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <input class="mdl-textfield__input access-time-start" type="text" id="horario-inicio-{n}" pattern="(0?[0-9]|1[0-9]|2[0-3])\:[0-5][0-9](\:[0-5][0-9])?">\
                    <label class="mdl-textfield__label" for="horario-inicio-{n}">De</label>\
                    <span class="mdl-textfield__error">Insira um horário válido!</span>\
                </div>\
            </div>\
            <div class="mdl-cell mdl-cell--6-col">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <input class="mdl-textfield__input access-time-end" type="text" id="horario-fim-{n}" pattern="(0?[0-9]|1[0-9]|2[0-3])\:[0-5][0-9](\:[0-5][0-9])?">\
                    <label class="mdl-textfield__label" for="horario-fim-{n}">Até</label>\
                </div>\
            </div>\
        </div>'
        .replace(/{n}/g, userDialog.rules)
        );
        userDialog.rules = userDialog.rules + 1;
        componentHandler.upgradeDom();
    },

    save: function (user) {
        console.log(user);
        $.post("/users.php?insert", {name: user.name, access: JSON.stringify(user.access)})
        .done(function(data) {
            console.log(data);
        });
        app.loadUsers();
    },

};

$(document).ready(function(){
    app.init();
});
