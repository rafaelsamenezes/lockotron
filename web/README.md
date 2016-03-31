# Interface web para administração
## Instruções iniciais
* Execute os SQLs na pasta `sql`.
* Copie o arquivo `db_connection.local.php.dist` para `db_connection.local.php`
  e personalize as variáveis de conexão.

## Estrutura dos arquivos
A estrutura de pastas e arquivos do projeto é a seguinte:

* `controller/`
  * `DbConnect.class.php` - Estabelece a conexão com o banco de dados
  * Demais arquivos - Classes necessárias para operações com cada uma das tabelas.

* `model/` - Contém as classes que representam os objetos do banco de dados.

* `public_html/`
  * `admin/` - **Página de administração. Esta é a interface gráfica interativa.**
  * `galileo.php` - Página que se comunica com o _Galileo_.
  * Demais arquivos - Web service: páginas que retornam JSON.

* `sql/` - _Dumps_ completos do banco de dados.
