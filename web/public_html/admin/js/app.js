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
        $('#users-table-mask').show();
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

                    var row = $('\
                    <tr class="user-row" data-user-id="{id}">\
                        <td>{id}</td>\
                        <td class="mdl-data-table__cell--non-numeric">{name}</td>\
                        <td class="mdl-data-table__cell--non-numeric">{access}\
                        </td>\
                        <td class="mdl-data-table__cell--non-numeric">\
                            <button class="user-edit-button mdl-button mdl-js-button mdl-button--icon">\
                                <i class="material-icons">edit</i>\
                            </button>\
                            <button class="user-delete-button mdl-button mdl-js-button mdl-button--icon">\
                                <i class="material-icons">delete</i>\
                            </button>\
                        </td>\
                    </tr>'
                    .replace(/{id}/g, el.id)
                    .replace(/{name}/g, el.nome)
                    .replace(/{access}/g, access)
                    ).appendTo($('#users-table tbody'));
                    row.find('.user-edit-button').click(function() {
                        userDialog.edit(el);
                    });

                    row.find('.user-delete-button').click(function() {
                        userDialog.delete(el);
                    });
                });

                $('#users-table-mask').hide();
            });
    },


    loadLog: function() {
        $('#log-table-mask').show();
         $.ajax("/log.php")
            .done(function(data){
                $('#log-table tbody').empty();
                data.data.forEach(function(el){

                    $('#log-table tbody').append('\
                        <tr>\
                            <td class="mdl-data-table__cell--non-numeric">{date}</td>\
                            <td class="mdl-data-table__cell--non-numeric">{name}</td>\
                            <td class="mdl-data-table__cell--non-numeric"><div style="display:inline-flex;vertical-align:middle;">{action}</div></td>\
                        </tr>'
                    .replace(/{date}/g, el.data)
                    .replace(/{name}/g, el.usuario.nome)
                    .replace(/{action}/g, el.estado == 1 ? "<i class=\"material-icons icon-ok\">check_circle</i>&nbsp;Autorizado" : "<i class=\"material-icons icon-no\">remove_circle</i>&nbsp;Proibido")
                    );
                });
            });
        $('#log-table-mask').hide();
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

    delete: function(user) {
        console.log("delete", user);
        var dialog = $('#user-delete-dialog');
        if (! dialog[0].showModal) {
            dialogPolyfill.registerDialog(dialog[0]);
        }

        dialog.find('.mdl-dialog__content').text("Excluir " + user.nome + "?");
        dialog.find('#user-delete-cancel').unbind('click').click(function() {
            dialog[0].close();
        });
        dialog.find('#user-delete-confirm').unbind('click').click(function() {
            $.post("/users.php?delete", {id:user.id})
            .done(function(data) {
                var msg = "";
                if (data.success) {
                    msg = "Usuário(a) \"{0}\" excluído(a)."
                } else {
                    msg = "Erro ao excluir \"{0}\"."
                }
                $('#snackbar')[0].MaterialSnackbar.showSnackbar({message: msg.replace(/\{0\}/g, user.nome)});
                app.loadUsers();
                dialog[0].close();
            });
        });
        dialog[0].showModal();
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
            console.log(user);
            dialog.find('.mdl-dialog__title').text("Editar usuário");
            dialog.find('#user-name').val(user.nome);
            user.access.forEach(function(rule) {
                userDialog.newRule(rule);
            });

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
        $('\
        <div class="rule mdl-grid mdl-grid--no-spacing">\
            <div class="mdl-cell mdl-cell--12-col">\
                <input type="hidden" class="access-id" value="{id}">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <select class="mdl-textfield__input access-day" id="day-{n}">\
                        <option value="0">domingo</option>\
                        <option value="1">segunda</option>\
                        <option value="2">terça</option>\
                        <option value="3">quarta</option>\
                        <option value="4">quinta</option>\
                        <option value="5">sexta</option>\
                        <option value="6">sábado</option>\
                    </select>\
                    <label class="mdl-textfield__label" for="day-{n}">Dia</label>\
                </div>\
            </div>\
            <div class="mdl-cell mdl-cell--6-col">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <input class="mdl-textfield__input access-time-start" type="text" id="horario-inicio-{n}" pattern="(0?[0-9]|1[0-9]|2[0-3])\:[0-5][0-9](\:[0-5][0-9])?" value="{time-start}">\
                    <label class="mdl-textfield__label" for="horario-inicio-{n}">De</label>\
                    <span class="mdl-textfield__error">Insira um horário válido!</span>\
                </div>\
            </div>\
            <div class="mdl-cell mdl-cell--6-col">\
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">\
                    <input class="mdl-textfield__input access-time-end" type="text" id="horario-fim-{n}" pattern="(0?[0-9]|1[0-9]|2[0-3])\:[0-5][0-9](\:[0-5][0-9])?" value="{time-end}">\
                    <label class="mdl-textfield__label" for="horario-fim-{n}">Até</label>\
                </div>\
            </div>\
        </div>'
        .replace(/\{n\}/g, userDialog.rules)
        .replace(/\{id\}/g, access ? access.id : "")
        .replace(/\{time-start\}/g, access ? access.horario_inicio : "")
        .replace(/\{time-end\}/g, access ? access.horario_fim : "")
    ).appendTo($('#access-rules'))
    .find('select.access-day').val(access ? access.dia : "1");
        userDialog.rules = userDialog.rules + 1;
        componentHandler.upgradeDom();
    },

    save: function (user) {
        if (user.id != null) {
            // UPDATE
            $.post("/users.php?edit", {id:user.id, name: user.name, access: JSON.stringify(user.access)})
            .done(function(data) {
                console.log("edited", data);
                app.loadUsers();
            });
        } else {
            // CREATE
            $.post("/users.php?insert", {name: user.name, access: JSON.stringify(user.access)})
            .done(function(data) {
                console.log("inserted", data);
                app.loadUsers();
            });
        }
    },

};

$(document).ready(function(){
    app.init();
});
